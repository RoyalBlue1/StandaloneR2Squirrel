#define _CRT_SECURE_NO_WARNINGS 1
#include "squirrel.h"
#include <string>
#include <map>
#include "hookutils.h"
#include "hook.h"
#include "modmanager.h"
#include "filesystem.h"
#include <minidumpapiset.h>
#include <Psapi.h>




AUTOHOOK_INIT()

const char* GetContextName(ScriptContext context)
{
	switch (context)
	{
	case ScriptContext::CLIENT:
		return "CLIENT";
	case ScriptContext::SERVER:
		return "SERVER";
	case ScriptContext::UI:
		return "UI";
	default:
		return "UNKNOWN";
	}
}

eSQReturnType SQReturnTypeFromString(const char* pReturnType)
{
	static const std::map<std::string, eSQReturnType> sqReturnTypeNameToString = {
		{"bool", eSQReturnType::Boolean},
		{"float", eSQReturnType::Float},
		{"vector", eSQReturnType::Vector},
		{"int", eSQReturnType::Integer},
		{"entity", eSQReturnType::Entity},
		{"string", eSQReturnType::String},
		{"array", eSQReturnType::Arrays},
		{"asset", eSQReturnType::Asset},
		{"table", eSQReturnType::Table} };

	if (sqReturnTypeNameToString.find(pReturnType) != sqReturnTypeNameToString.end())
		return sqReturnTypeNameToString.at(pReturnType);
	else
		return eSQReturnType::Default; // previous default value
}

const char* SQTypeNameFromID(int type)
{
	switch (type)
	{
	case OT_ASSET:
		return "asset";
	case OT_INTEGER:
		return "int";
	case OT_BOOL:
		return "bool";
	case SQOBJECT_NUMERIC:
		return "float or int";
	case OT_NULL:
		return "null";
	case OT_VECTOR:
		return "vector";
	case 0:
		return "var";
	case OT_USERDATA:
		return "userdata";
	case OT_FLOAT:
		return "float";
	case OT_STRING:
		return "string";
	case OT_ARRAY:
		return "array";
	case 0x8000200:
		return "function";
	case 0x8100000:
		return "structdef";
	case OT_THREAD:
		return "thread";
	case OT_FUNCPROTO:
		return "function";
	case OT_CLAAS:
		return "class";
	case OT_WEAKREF:
		return "weakref";
	case 0x8080000:
		return "unimplemented function";
	case 0x8200000:
		return "struct instance";
	case OT_TABLE:
		return "table";
	case 0xA008000:
		return "instance";
	case OT_ENTITY:
		return "entity";
	}
	return "";
}

// needed to define implementations for squirrelmanager outside of squirrel.h without compiler errors
template class SquirrelManager<ScriptContext::SERVER>;
template class SquirrelManager<ScriptContext::CLIENT>;
template class SquirrelManager<ScriptContext::UI>;

template <ScriptContext context> void SquirrelManager<context>::VMCreated(CSquirrelVM* newSqvm)
{
	m_pSQVM = newSqvm;

	for (SQFuncRegistration* funcReg : m_funcRegistrations)
	{
		RegisterSquirrelFunc(m_pSQVM, funcReg, 1);
	}

	for (auto& pair : g_pModManager->m_DependencyConstants)
	{
		bool bWasFound = false;
		for (Mod& dependency : g_pModManager->m_LoadedMods)
		{
			if (!dependency.m_bEnabled)
				continue;

			if (dependency.Name == pair.second)
			{
				bWasFound = true;
				break;
			}
		}

		defconst(m_pSQVM, pair.first.c_str(), bWasFound);
	}
}

template <ScriptContext context> void SquirrelManager<context>::VMDestroyed()
{
	m_pSQVM = nullptr;
}

template <ScriptContext context> void SquirrelManager<context>::ExecuteCode(const char* pCode)
{
	if (!m_pSQVM || !m_pSQVM->sqvm)
	{
				return;
	}

	
	std::string strCode(pCode);
	CompileBufferState bufferState = CompileBufferState(strCode);

	SQRESULT compileResult = compilebuffer(&bufferState, "console");
	
	if (compileResult != SQRESULT_ERROR)
	{
		pushroottable(m_pSQVM->sqvm);
		SQRESULT callResult = call(m_pSQVM->sqvm, 0);
			}
}

template <ScriptContext context> void SquirrelManager<context>::AddFuncRegistration(
    std::string returnType, std::string name, std::string argTypes, std::string helpText, SQFunction func)
{

    SQFuncRegistration* reg = new SQFuncRegistration;

    reg->squirrelFuncName = new char[name.size() + 1];
    strcpy((char*)reg->squirrelFuncName, name.c_str());
    reg->cppFuncName = reg->squirrelFuncName;

    reg->helpText = new char[helpText.size() + 1];
    strcpy((char*)reg->helpText, helpText.c_str());

    reg->returnTypeString = new char[returnType.size() + 1];
    strcpy((char*)reg->returnTypeString, returnType.c_str());
    reg->returnType = SQReturnTypeFromString(returnType.c_str());

    reg->argTypes = new char[argTypes.size() + 1];
    strcpy((char*)reg->argTypes, argTypes.c_str());

    reg->funcPtr = func;

    m_funcRegistrations.push_back(reg);
}

template <ScriptContext context> SQRESULT SquirrelManager<context>::setupfunc(const SQChar* funcname)
{
	pushroottable(m_pSQVM->sqvm);
	pushstring(m_pSQVM->sqvm, funcname, -1);

	SQRESULT result = get(m_pSQVM->sqvm, -2);
	if (result != SQRESULT_ERROR)
		pushroottable(m_pSQVM->sqvm);

	return result;
}

template <ScriptContext context> void SquirrelManager<context>::AddFuncOverride(std::string name, SQFunction func)
{
	m_funcOverrides[name] = func;
}

// hooks
bool IsUIVM(ScriptContext context, HSquirrelVM* pSqvm)
{
	return context != ScriptContext::SERVER && g_pSquirrel<ScriptContext::UI>->m_pSQVM &&
		g_pSquirrel<ScriptContext::UI>->m_pSQVM->sqvm == pSqvm;
}

template <ScriptContext context> void* (*__fastcall sq_compiler_create)(HSquirrelVM* sqvm, void* a2, void* a3, SQBool bShouldThrowError);
template <ScriptContext context> void* __fastcall sq_compiler_createHook(HSquirrelVM* sqvm, void* a2, void* a3, SQBool bShouldThrowError)
{
	// store whether errors generated from this compile should be fatal
	if (IsUIVM(context, sqvm))
		g_pSquirrel<ScriptContext::UI>->m_bFatalCompilationErrors = bShouldThrowError;
	else
		g_pSquirrel<context>->m_bFatalCompilationErrors = bShouldThrowError;

	return sq_compiler_create<context>(sqvm, a2, a3, bShouldThrowError);
}

template <ScriptContext context> SQInteger(*SQPrint)(HSquirrelVM* sqvm, const char* fmt);
template <ScriptContext context> SQInteger SQPrintHook(HSquirrelVM* sqvm, const char* fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vprintf( fmt, va);
    //printf("\n");
	va_end(va);
	return 0;
}

template <ScriptContext context> CSquirrelVM* (*__fastcall CreateNewVM)(void* a1, ScriptContext realContext);
template <ScriptContext context> CSquirrelVM* __fastcall CreateNewVMHook(void* a1, ScriptContext realContext)
{
	CSquirrelVM* sqvm = CreateNewVM<context>(a1, realContext);
	if (realContext == ScriptContext::UI)
		g_pSquirrel<ScriptContext::UI>->VMCreated(sqvm);
	else
		g_pSquirrel<context>->VMCreated(sqvm);

		return sqvm;
}

template <ScriptContext context> bool (*__fastcall CSquirrelVM_init)(CSquirrelVM* vm, ScriptContext realContext, float time);
template <ScriptContext context> bool __fastcall CSquirrelVM_initHook(CSquirrelVM* vm, ScriptContext realContext, float time)
{
    bool ret = CSquirrelVM_init<context>(vm, realContext, time);
    for (Mod mod : g_pModManager->m_LoadedMods)
    {
        if (mod.initScript.size() != 0)
        {
            std::string name = mod.initScript.substr(mod.initScript.find_last_of('/') + 1);
            std::string path = std::string("scripts/vscripts/") + mod.initScript;
            if (g_pSquirrel<context>->compilefile(vm, path.c_str(), name.c_str(), 0))
                g_pSquirrel<context>->compilefile(vm, path.c_str(), name.c_str(), 1);
        }
    }
    return ret;
}

template <ScriptContext context> void (*__fastcall DestroyVM)(void* a1, HSquirrelVM* sqvm);
template <ScriptContext context> void __fastcall DestroyVMHook(void* a1, HSquirrelVM* sqvm)
{
	ScriptContext realContext = context; // ui and client use the same function so we use this for prints
	if (IsUIVM(context, sqvm))
	{
		realContext = ScriptContext::UI;
		g_pSquirrel<ScriptContext::UI>->VMDestroyed();
	}
	else
		DestroyVM<context>(a1, sqvm);

	}

template <ScriptContext context>
void (*__fastcall SQCompileError)(HSquirrelVM* sqvm, const char* error, const char* file, int line, int column);
template <ScriptContext context>
void __fastcall ScriptCompileErrorHook(HSquirrelVM* sqvm, const char* error, const char* file, int line, int column)
{
	bool bIsFatalError = g_pSquirrel<context>->m_bFatalCompilationErrors;
    ScriptContext realContext = context;
    if(realContext == ScriptContext::CLIENT && sqvm == g_pSquirrel<ScriptContext::UI>->m_pSQVM->sqvm)
        realContext = ScriptContext::UI;
    spdlog::error("Compile Error \"{}\" in {} VM in file {} on line {} in column {}\n", error,GetContextName(realContext), file, line, column);
    exit(-1);
    /*
    

    g_pSquirrel<realContext>.lastCompileError.errorDuringCompile = true;
    g_pSquirrel<realContext>.lastCompileError.errorName = std::string(error);
    g_pSquirrel<realContext>.lastCompileError.fileName = std::string(file);
    g_pSquirrel<realContext>.lastCompileError.line = line;
    g_pSquirrel<realContext>.lastCompileError.column = column;*/
}

template <ScriptContext context>
int64_t(*__fastcall RegisterSquirrelFunction)(CSquirrelVM* sqvm, SQFuncRegistration* funcReg, char unknown);
template <ScriptContext context>
int64_t __fastcall RegisterSquirrelFunctionHook(CSquirrelVM* sqvm, SQFuncRegistration* funcReg, char unknown)
{
	if (IsUIVM(context, sqvm->sqvm))
	{
		if (g_pSquirrel<ScriptContext::UI>->m_funcOverrides.count(funcReg->squirrelFuncName))
		{
			g_pSquirrel<ScriptContext::UI>->m_funcOriginals[funcReg->squirrelFuncName] = funcReg->funcPtr;
			funcReg->funcPtr = g_pSquirrel<ScriptContext::UI>->m_funcOverrides[funcReg->squirrelFuncName];
					}

		return g_pSquirrel<ScriptContext::UI>->RegisterSquirrelFunc(sqvm, funcReg, unknown);
	}

	if (g_pSquirrel<context>->m_funcOverrides.find(funcReg->squirrelFuncName) != g_pSquirrel<context>->m_funcOverrides.end())
	{
		g_pSquirrel<context>->m_funcOriginals[funcReg->squirrelFuncName] = funcReg->funcPtr;
		funcReg->funcPtr = g_pSquirrel<context>->m_funcOverrides[funcReg->squirrelFuncName];
			}

	return g_pSquirrel<context>->RegisterSquirrelFunc(sqvm, funcReg, unknown);
}


template <ScriptContext context>CompileError* SquirrelManager<context>::compileTest() {
    lastCompileError.errorDuringCompile = false;
    startVM();
    //__CSquirrelVM_Destory();
    return &lastCompileError;
}


ON_DLL_LOAD("client.dll", ClientSquirrel, (CModule module))
{
    AUTOHOOK_DISPATCH_MODULE(client.dll)

        g_pSquirrel<ScriptContext::CLIENT> = new SquirrelManager<ScriptContext::CLIENT>;
    g_pSquirrel<ScriptContext::UI> = new SquirrelManager<ScriptContext::UI>;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_defconst = module.Offset(0x12120).As<sq_defconstType>();
    g_pSquirrel<ScriptContext::UI>->__sq_defconst = g_pSquirrel<ScriptContext::CLIENT>->__sq_defconst;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_compilebuffer = module.Offset(0x3110).As<sq_compilebufferType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushroottable = module.Offset(0x5860).As<sq_pushroottableType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_compilefile = module.Offset(0xF950).As<sq_compilefileType>();
    g_pSquirrel<ScriptContext::UI>->__sq_compilebuffer = g_pSquirrel<ScriptContext::CLIENT>->__sq_compilebuffer;
    g_pSquirrel<ScriptContext::UI>->__sq_pushroottable = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushroottable;
    g_pSquirrel<ScriptContext::UI>->__sq_compilefile = g_pSquirrel<ScriptContext::CLIENT>->__sq_compilefile;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_call = module.Offset(0x8650).As<sq_callType>();
    g_pSquirrel<ScriptContext::UI>->__sq_call = g_pSquirrel<ScriptContext::CLIENT>->__sq_call;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_newarray = module.Offset(0x39F0).As<sq_newarrayType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_arrayappend = module.Offset(0x3C70).As<sq_arrayappendType>();
    g_pSquirrel<ScriptContext::UI>->__sq_newarray = g_pSquirrel<ScriptContext::CLIENT>->__sq_newarray;
    g_pSquirrel<ScriptContext::UI>->__sq_arrayappend = g_pSquirrel<ScriptContext::CLIENT>->__sq_arrayappend;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_newtable = module.Offset(0x3960).As<sq_newtableType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_newslot = module.Offset(0x70B0).As<sq_newslotType>();
    g_pSquirrel<ScriptContext::UI>->__sq_newtable = g_pSquirrel<ScriptContext::CLIENT>->__sq_newtable;
    g_pSquirrel<ScriptContext::UI>->__sq_newslot = g_pSquirrel<ScriptContext::CLIENT>->__sq_newslot;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushstring = module.Offset(0x3440).As<sq_pushstringType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushinteger = module.Offset(0x36A0).As<sq_pushintegerType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushfloat = module.Offset(0x3800).As<sq_pushfloatType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushbool = module.Offset(0x3710).As<sq_pushboolType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushasset = module.Offset(0x3560).As<sq_pushassetType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_pushvector = module.Offset(0x3780).As<sq_pushvectorType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_raiseerror = module.Offset(0x8470).As<sq_raiseerrorType>();
    g_pSquirrel<ScriptContext::UI>->__sq_pushstring = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushstring;
    g_pSquirrel<ScriptContext::UI>->__sq_pushinteger = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushinteger;
    g_pSquirrel<ScriptContext::UI>->__sq_pushfloat = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushfloat;
    g_pSquirrel<ScriptContext::UI>->__sq_pushbool = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushbool;
    g_pSquirrel<ScriptContext::UI>->__sq_pushvector = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushvector;
    g_pSquirrel<ScriptContext::UI>->__sq_pushasset = g_pSquirrel<ScriptContext::CLIENT>->__sq_pushasset;
    g_pSquirrel<ScriptContext::UI>->__sq_raiseerror = g_pSquirrel<ScriptContext::CLIENT>->__sq_raiseerror;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_getstring = module.Offset(0x60C0).As<sq_getstringType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_getinteger = module.Offset(0x60E0).As<sq_getintegerType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_getfloat = module.Offset(0x6100).As<sq_getfloatType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_getbool = module.Offset(0x6130).As<sq_getboolType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_get = module.Offset(0x7C30).As<sq_getType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_getasset = module.Offset(0x6010).As<sq_getassetType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_getuserdata = module.Offset(0x63D0).As<sq_getuserdataType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_getvector = module.Offset(0x6140).As<sq_getvectorType>();
    g_pSquirrel<ScriptContext::UI>->__sq_getstring = g_pSquirrel<ScriptContext::CLIENT>->__sq_getstring;
    g_pSquirrel<ScriptContext::UI>->__sq_getinteger = g_pSquirrel<ScriptContext::CLIENT>->__sq_getinteger;
    g_pSquirrel<ScriptContext::UI>->__sq_getfloat = g_pSquirrel<ScriptContext::CLIENT>->__sq_getfloat;
    g_pSquirrel<ScriptContext::UI>->__sq_getbool = g_pSquirrel<ScriptContext::CLIENT>->__sq_getbool;
    g_pSquirrel<ScriptContext::UI>->__sq_get = g_pSquirrel<ScriptContext::CLIENT>->__sq_get;
    g_pSquirrel<ScriptContext::UI>->__sq_getasset = g_pSquirrel<ScriptContext::CLIENT>->__sq_getasset;
    g_pSquirrel<ScriptContext::UI>->__sq_getuserdata = g_pSquirrel<ScriptContext::CLIENT>->__sq_getuserdata;
    g_pSquirrel<ScriptContext::UI>->__sq_getvector = g_pSquirrel<ScriptContext::CLIENT>->__sq_getvector;

    g_pSquirrel<ScriptContext::CLIENT>->__sq_createuserdata = module.Offset(0x38D0).As<sq_createuserdataType>();
    g_pSquirrel<ScriptContext::CLIENT>->__sq_setuserdatatypeid = module.Offset(0x6490).As<sq_setuserdatatypeidType>();
    g_pSquirrel<ScriptContext::UI>->__sq_createuserdata = g_pSquirrel<ScriptContext::CLIENT>->__sq_createuserdata;
    g_pSquirrel<ScriptContext::UI>->__sq_setuserdatatypeid = g_pSquirrel<ScriptContext::CLIENT>->__sq_setuserdatatypeid;
    g_pSquirrel<ScriptContext::CLIENT>->__CSquirrelVM_Init = module.Offset(0x384F90).As<CSquirrelVM_InitType>();
    g_pSquirrel<ScriptContext::UI>->__CSquirrelVM_Init = module.Offset(0x3C8390).As<CSquirrelVM_InitType>();

    g_pSquirrel<ScriptContext::CLIENT>->__sq_getconstantstable = module.Offset(0x5940).As<sq_getconstantstableType>();
    g_pSquirrel<ScriptContext::UI>->__sq_getconstantstable = g_pSquirrel<ScriptContext::CLIENT>->__sq_getconstantstable;
    g_pSquirrel<ScriptContext::CLIENT>->__sq_removefromstack = module.Offset(0x7030).As<sq_removefromstackType>();
    g_pSquirrel<ScriptContext::UI>->__sq_removefromstack = g_pSquirrel<ScriptContext::CLIENT>->__sq_removefromstack;

    g_pSquirrel<ScriptContext::CLIENT>->__CSquirrelVM_Destory = module.Offset(0x385400).As<CSquirrelVM_destroyType>();
    g_pSquirrel<ScriptContext::UI>->__CSquirrelVM_Destory = module.Offset(0x3C84F0).As<CSquirrelVM_destroyType>();

    MAKEHOOK(
        module.Offset(0x108E0),
        &RegisterSquirrelFunctionHook<ScriptContext::CLIENT>,
        &g_pSquirrel<ScriptContext::CLIENT>->RegisterSquirrelFunc);
    g_pSquirrel<ScriptContext::UI>->RegisterSquirrelFunc = g_pSquirrel<ScriptContext::CLIENT>->RegisterSquirrelFunc;

    // uiscript_reset concommand: don't loop forever if compilation fails
    module.Offset(0x3C6E4C).NOP(6);

    MAKEHOOK(module.Offset(0x8AD0), &sq_compiler_createHook<ScriptContext::CLIENT>, &sq_compiler_create<ScriptContext::CLIENT>);

    MAKEHOOK(module.Offset(0x12B00), &SQPrintHook<ScriptContext::CLIENT>, &SQPrint<ScriptContext::CLIENT>);
    MAKEHOOK(module.Offset(0x12BA0), &SQPrintHook<ScriptContext::UI>, &SQPrint<ScriptContext::UI>);

    MAKEHOOK(module.Offset(0x26130), &CreateNewVMHook<ScriptContext::CLIENT>, &CreateNewVM<ScriptContext::CLIENT>);
    MAKEHOOK(module.Offset(0x26E70), &DestroyVMHook<ScriptContext::CLIENT>, &DestroyVM<ScriptContext::CLIENT>);
    MAKEHOOK(module.Offset(0x79A50), &ScriptCompileErrorHook<ScriptContext::CLIENT>, &SQCompileError<ScriptContext::CLIENT>);

    MAKEHOOK(module.Offset(0xE3B0), &CSquirrelVM_initHook<ScriptContext::CLIENT>, &CSquirrelVM_init<ScriptContext::CLIENT>);
}

ON_DLL_LOAD("server.dll", ServerSquirrel, (CModule module))
{
    AUTOHOOK_DISPATCH_MODULE(server.dll)
    //printf("server.dll loaded and Squirrel initialized\n");


	g_pSquirrel<ScriptContext::SERVER> = new SquirrelManager<ScriptContext::SERVER>;

	g_pSquirrel<ScriptContext::SERVER>->__sq_defconst = module.Offset(0x1F550).As<sq_defconstType>();

	g_pSquirrel<ScriptContext::SERVER>->__sq_compilebuffer = module.Offset(0x3110).As<sq_compilebufferType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_pushroottable = module.Offset(0x5840).As<sq_pushroottableType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_call = module.Offset(0x8620).As<sq_callType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_compilefile = module.Offset(0x1CD80).As<sq_compilefileType>();

	g_pSquirrel<ScriptContext::SERVER>->__sq_newarray = module.Offset(0x39F0).As<sq_newarrayType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_arrayappend = module.Offset(0x3C70).As<sq_arrayappendType>();

	g_pSquirrel<ScriptContext::SERVER>->__sq_newtable = module.Offset(0x3960).As<sq_newtableType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_newslot = module.Offset(0x7080).As<sq_newslotType>();

	g_pSquirrel<ScriptContext::SERVER>->__sq_pushstring = module.Offset(0x3440).As<sq_pushstringType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_pushinteger = module.Offset(0x36A0).As<sq_pushintegerType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_pushfloat = module.Offset(0x3800).As<sq_pushfloatType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_pushbool = module.Offset(0x3710).As<sq_pushboolType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_pushasset = module.Offset(0x3560).As<sq_pushassetType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_pushvector = module.Offset(0x3780).As<sq_pushvectorType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_raiseerror = module.Offset(0x8440).As<sq_raiseerrorType>();

	g_pSquirrel<ScriptContext::SERVER>->__sq_getstring = module.Offset(0x60A0).As<sq_getstringType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_getinteger = module.Offset(0x60C0).As<sq_getintegerType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_getfloat = module.Offset(0x60E0).As<sq_getfloatType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_getbool = module.Offset(0x6110).As<sq_getboolType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_getasset = module.Offset(0x5FF0).As<sq_getassetType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_getuserdata = module.Offset(0x63B0).As<sq_getuserdataType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_getvector = module.Offset(0x6120).As<sq_getvectorType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_get = module.Offset(0x7C00).As<sq_getType>();

	g_pSquirrel<ScriptContext::SERVER>->__sq_createuserdata = module.Offset(0x38D0).As<sq_createuserdataType>();
	g_pSquirrel<ScriptContext::SERVER>->__sq_setuserdatatypeid = module.Offset(0x6470).As<sq_setuserdatatypeidType>();
    g_pSquirrel<ScriptContext::SERVER>->__CSquirrelVM_Init = module.Offset(0x289C50).As<CSquirrelVM_InitType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_getconstantstable = module.Offset(0x5920).As<sq_getconstantstableType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_removefromstack = module.Offset(0x7000).As<sq_removefromstackType>();
    g_pSquirrel<ScriptContext::SERVER>->setjmpPtr = module.Offset(0x23AAF10).As<void**>();



    g_pSquirrel<ScriptContext::SERVER>->__CSquirrelVM_Destory = module.Offset(0x280DB0).As<CSquirrelVM_destroyType>();
 
	MAKEHOOK(
		module.Offset(0x1DD10),
		&RegisterSquirrelFunctionHook<ScriptContext::SERVER>,
		&g_pSquirrel<ScriptContext::SERVER>->RegisterSquirrelFunc);

	MAKEHOOK(module.Offset(0x8AA0), &sq_compiler_createHook<ScriptContext::SERVER>, &sq_compiler_create<ScriptContext::SERVER>);

	MAKEHOOK(module.Offset(0x1FE90), &SQPrintHook<ScriptContext::SERVER>, &SQPrint<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x260E0), &CreateNewVMHook<ScriptContext::SERVER>, &CreateNewVM<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x26E20), &DestroyVMHook<ScriptContext::SERVER>, &DestroyVM<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x799E0), &ScriptCompileErrorHook<ScriptContext::SERVER>, &SQCompileError<ScriptContext::SERVER>);
    MAKEHOOK(module.Offset(0x17BE0), &CSquirrelVM_initHook<ScriptContext::SERVER>, &CSquirrelVM_init<ScriptContext::SERVER>);

}



