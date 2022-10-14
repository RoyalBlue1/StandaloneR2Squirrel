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
    printf("Compile Error \"%s\" in file %s on line %d in column %d\n", error, file, line, column);
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

AUTOHOOK(loaddDamageFlags, server.dll + 0x6CC9F0, void*, __fastcall, (void)) {
    return 0;
}


template <ScriptContext context> bool (*__fastcall CallScriptInitCallback)(void* sqvm, const char* callback);
template <ScriptContext context> bool __fastcall CallScriptInitCallbackHook(void* sqvm, const char* callback)
{
	ScriptContext realContext = context;
	bool bShouldCallCustomCallbacks = true;

	if (context == ScriptContext::CLIENT)
	{
		if (!strcmp(callback, "UICodeCallback_UIInit"))
			realContext = ScriptContext::UI;
		else if (strcmp(callback, "ClientCodeCallback_MapSpawn"))
			bShouldCallCustomCallbacks = false;
	}
	else if (context == ScriptContext::SERVER)
		bShouldCallCustomCallbacks = !strcmp(callback, "CodeCallback_MapSpawn");

	if (bShouldCallCustomCallbacks)
	{
		for (Mod mod : g_pModManager->m_LoadedMods)
		{
			if (!mod.m_bEnabled)
				continue;

			for (ModScript script : mod.Scripts)
			{
				for (ModScriptCallback modCallback : script.Callbacks)
				{
					if (modCallback.Context == realContext && modCallback.BeforeCallback.length())
					{
						CallScriptInitCallback<context>(sqvm, modCallback.BeforeCallback.c_str());
					}
				}
			}
		}
	}


	bool ret = CallScriptInitCallback<context>(sqvm, callback);

	// run after callbacks
	if (bShouldCallCustomCallbacks)
	{
		for (Mod mod : g_pModManager->m_LoadedMods)
		{
			if (!mod.m_bEnabled)
				continue;

			for (ModScript script : mod.Scripts)
			{
				for (ModScriptCallback modCallback : script.Callbacks)
				{
					if (modCallback.Context == realContext && modCallback.AfterCallback.length())
					{
						CallScriptInitCallback<context>(sqvm, modCallback.AfterCallback.c_str());
					}
				}
			}
		}
	}

	return ret;
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


    g_pSquirrel<ScriptContext::SERVER>->__sq_instructionvectorrealloc = module.Offset(0x69A20).As<sq_instructionvectorreallocType>();

    g_pSquirrel<ScriptContext::SERVER>->__SQVMStartCall = module.Offset(0x2DD20).As<SQVMStartCallType>();
    g_pSquirrel<ScriptContext::SERVER>->__SQVMCallErrorHandler = module.Offset(0x33A70).As<SQVMCallErrorHandlerType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_loadcopy = module.Offset(0x3d390).As<sq_op_loadcopyType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_call = module.Offset(0x2C440).As<sq_op_callType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_precall = module.Offset(0x2C2B0).As<sq_op_precallType>();
    g_pSquirrel<ScriptContext::SERVER>->__SQVMGet = module.Offset(0x343A0).As<SQVMGetType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_35B80 = module.Offset(0x35B80).As<sub_35B80Type>();
    g_pSquirrel<ScriptContext::SERVER>->__SQVMNewSlot = module.Offset(0x34B30).As<SQVMNewSlotType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_34CF0 = module.Offset(0x34CF0).As<sub_34CF0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_set = module.Offset(0x34810).As<sq_op_setType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_eq = module.Offset(0x2F460).As<sq_op_eqType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2B590 = module.Offset(0x2B590).As<sub_2B590Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_sqvm_Return = module.Offset(0x2E490).As<sq_sqvm_ReturnType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_copyObject = module.Offset(0x1370).As<sq_copyObjectType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_createTable = module.Offset(0x1580).As<sq_createTableType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_1800 = module.Offset(0x1800).As<sub_1800Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_1A20 = module.Offset(0x1A20).As<sub_1A20Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2F740 = module.Offset(0x2F740).As<sub_2F740Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2E670 = module.Offset(0x2E670).As<sub_2E670Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2B6C0 = module.Offset(0x2B6C0).As<sub_2B6C0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2E960 = module.Offset(0x2E960).As<sub_2E960Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_increment_prefix_local = module.Offset(0x2E780).As<sq_op_increment_prefix_localType>();
    g_pSquirrel<ScriptContext::SERVER>->__sp_op_increment_prefix_structfield =
        module.Offset(0x2EB70).As<sp_op_increment_prefix_structfieldType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_increment_postfix = module.Offset(0x2EA30).As<sub_2EA30Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_increment_postfix_local = module.Offset(0x2E860).As<sub_2E860Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_increment_postfix_structfield =
        module.Offset(0x2EC60).As<sq_op_increment_postfix_structfieldType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_cmp = module.Offset(0x2D1E0).As<sub_2D1E0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2CF10 = module.Offset(0x2CF10).As<sub_2CF10Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2F0B0 = module.Offset(0x2F0B0).As<sub_2F0B0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2EE20 = module.Offset(0x2EE20).As<sub_2EE20Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2EF60 = module.Offset(0x2EF60).As<sub_2EF60Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_34A30 = module.Offset(0x34A30).As<sub_34A30Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2D950 = module.Offset(0x2D950).As<sub_2D950Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_35800 = module.Offset(0x35800).As<sub_35800Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2F2F0 = module.Offset(0x2F2F0).As<sub_2F2F0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_3EA70 = module.Offset(0x3EA70).As<sub_3EA70Type>();
    g_pSquirrel<ScriptContext::SERVER>->__SQVMToString = module.Offset(0x2D2D0).As<SQVMToStringType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_add = module.Offset(0x2BAF0).As<sq_op_addType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_dropStack = module.Offset(0x2B500).As<sq_dropStackType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_C6F0 = module.Offset(0xC6F0).As<sub_C6F0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_27390 = module.Offset(0x27390).As<sub_27390Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_35B20 = module.Offset(0x35B20).As<sub_35B20Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_sub = module.Offset(0x2BC80).As<sq_op_subType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_multiplication = module.Offset(0x2BE10).As<sq_op_multiplicationType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_div = module.Offset(0x2C020).As<sq_op_divType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_modulo = module.Offset(0x2C1C0).As<sq_op_moduloType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_compare = module.Offset(0x2D080).As<sq_compareType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_setObjectToFloat = module.Offset(0x27430).As<sq_setObjectToFloatType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2E100 = module.Offset(0x2E100).As<sub_2E100Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_nativecall = module.Offset(0x33E00).As<sq_nativecallType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_typecast = module.Offset(0x2F500).As<sq_op_typecastType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_op_check_entity_class = module.Offset(0x2F6B0).As<sq_op_check_entity_classType>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_29A40 = module.Offset(0x29A40).As<sub_29A40Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_63E00 = module.Offset(0x63E00).As<sub_63E00Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_2EDB0 = module.Offset(0x2EDB0).As<sub_2EDB0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__sub_BEF0 = module.Offset(0xBEF0).As<sub_BEF0Type>();
    g_pSquirrel<ScriptContext::SERVER>->__SQVMRaise_Error = module.Offset(0x35A10).As<SQVMRaise_ErrorType>();
    g_pSquirrel<ScriptContext::SERVER>->__globalClosure = module.Offset(0xBCCE30).As<SQObject*>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_rdbg_hook = module.Offset(0x6F680).As<sq_rdbg_hookType>();
    g_pSquirrel<ScriptContext::SERVER>->__sq_rdbg_update = module.Offset(0x6C670).As<sq_rdbg_updateType>();


	MAKEHOOK(
		module.Offset(0x1DD10),
		&RegisterSquirrelFunctionHook<ScriptContext::SERVER>,
		&g_pSquirrel<ScriptContext::SERVER>->RegisterSquirrelFunc);

	MAKEHOOK(module.Offset(0x8AA0), &sq_compiler_createHook<ScriptContext::SERVER>, &sq_compiler_create<ScriptContext::SERVER>);

	MAKEHOOK(module.Offset(0x1FE90), &SQPrintHook<ScriptContext::SERVER>, &SQPrint<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x260E0), &CreateNewVMHook<ScriptContext::SERVER>, &CreateNewVM<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x26E20), &DestroyVMHook<ScriptContext::SERVER>, &DestroyVM<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x799E0), &ScriptCompileErrorHook<ScriptContext::SERVER>, &SQCompileError<ScriptContext::SERVER>);
	MAKEHOOK(module.Offset(0x1D5C0), &CallScriptInitCallbackHook<ScriptContext::SERVER>, &CallScriptInitCallback<ScriptContext::SERVER>);

    


}



AUTOHOOK(sq_nativecall, server.dll + 0x33E00, char, __fastcall, (HSquirrelVM* sqvm, SQNativeClosure* closure, SQObject* obj, unsigned int a4, SQObject* a5, BYTE* a6, char a7)) {
    printf("Calling Native: %s with string %016llx\n", closure->_name->_val,*(long long*)closure->value_70);
    return sq_nativecall(sqvm, closure, obj, a4, a5, a6, a7);
}