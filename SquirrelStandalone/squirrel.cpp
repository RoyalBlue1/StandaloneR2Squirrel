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



SquirrelManager* g_pSquirrel;

AUTOHOOK_INIT()


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
class SquirrelManager;


void SquirrelManager::VMCreated(CSquirrelVM* newSqvm)
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

void SquirrelManager::VMDestroyed()
{
	m_pSQVM = nullptr;
}

void SquirrelManager::ExecuteCode(const char* pCode)
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

void SquirrelManager::AddFuncRegistration(
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

SQRESULT SquirrelManager::setupfunc(const SQChar* funcname)
{
	pushroottable(m_pSQVM->sqvm);
	pushstring(m_pSQVM->sqvm, funcname, -1);

	SQRESULT result = get(m_pSQVM->sqvm, -2);
	if (result != SQRESULT_ERROR)
		pushroottable(m_pSQVM->sqvm);

	return result;
}

void SquirrelManager::AddFuncOverride(std::string name, SQFunction func)
{
	m_funcOverrides[name] = func;
}


void* (*__fastcall sq_compiler_create)(HSquirrelVM* sqvm, void* a2, void* a3, SQBool bShouldThrowError);
void* __fastcall sq_compiler_createHook(HSquirrelVM* sqvm, void* a2, void* a3, SQBool bShouldThrowError)
{

	g_pSquirrel->m_bFatalCompilationErrors = bShouldThrowError;

	return sq_compiler_create(sqvm, a2, a3, bShouldThrowError);
}

SQInteger(*SQPrint)(HSquirrelVM* sqvm, const char* fmt);
SQInteger SQPrintHook(HSquirrelVM* sqvm, const char* fmt, ...)
{   
    char outstring[4000];
	va_list va;
	va_start(va, fmt);
	vsnprintf( outstring, 4000,fmt, va);
    spdlog::info("{}",std::string(outstring));
	va_end(va);
	return 0;
}

CSquirrelVM* (*__fastcall CreateNewVM)(void* a1, int realContext);
CSquirrelVM* __fastcall CreateNewVMHook(void* a1, int realContext)
{
	CSquirrelVM* sqvm = CreateNewVM(a1, realContext);

	g_pSquirrel->VMCreated(sqvm);

	return sqvm;
}

void (*__fastcall DestroyVM)(void* a1, HSquirrelVM* sqvm);
void __fastcall DestroyVMHook(void* a1, HSquirrelVM* sqvm)
{

	DestroyVM(a1, sqvm);

}


void (*__fastcall SQCompileError)(HSquirrelVM* sqvm, const char* error, const char* file, int line, int column);

void __fastcall ScriptCompileErrorHook(HSquirrelVM* sqvm, const char* error, const char* file, int line, int column)
{
	bool bIsFatalError = g_pSquirrel->m_bFatalCompilationErrors;
    spdlog::error("Compile Error \"{}\" in file {} on line {} in column {}\n", error, file, line, column);


}


int64_t(*__fastcall RegisterSquirrelFunction)(CSquirrelVM* sqvm, SQFuncRegistration* funcReg, char unknown);

int64_t __fastcall RegisterSquirrelFunctionHook(CSquirrelVM* sqvm, SQFuncRegistration* funcReg, char unknown)
{


	if (g_pSquirrel->m_funcOverrides.find(funcReg->squirrelFuncName) != g_pSquirrel->m_funcOverrides.end())
	{
		g_pSquirrel->m_funcOriginals[funcReg->squirrelFuncName] = funcReg->funcPtr;
		funcReg->funcPtr = g_pSquirrel->m_funcOverrides[funcReg->squirrelFuncName];
			}

	return g_pSquirrel->RegisterSquirrelFunc(sqvm, funcReg, unknown);
}




ON_DLL_LOAD("server.dll", ServerSquirrel, (CModule module))
{
    AUTOHOOK_DISPATCH_MODULE(server.dll)
    //printf("server.dll loaded and Squirrel initialized\n");


	g_pSquirrel = new SquirrelManager;

	g_pSquirrel->__sq_defconst = module.Offset(0x1F550).As<sq_defconstType>();

	g_pSquirrel->__sq_compilebuffer = module.Offset(0x3110).As<sq_compilebufferType>();
	g_pSquirrel->__sq_pushroottable = module.Offset(0x5840).As<sq_pushroottableType>();
	g_pSquirrel->__sq_call = module.Offset(0x8620).As<sq_callType>();

	g_pSquirrel->__sq_newarray = module.Offset(0x39F0).As<sq_newarrayType>();
	g_pSquirrel->__sq_arrayappend = module.Offset(0x3C70).As<sq_arrayappendType>();

	g_pSquirrel->__sq_newtable = module.Offset(0x3960).As<sq_newtableType>();
	g_pSquirrel->__sq_newslot = module.Offset(0x7080).As<sq_newslotType>();

	g_pSquirrel->__sq_pushstring = module.Offset(0x3440).As<sq_pushstringType>();
	g_pSquirrel->__sq_pushinteger = module.Offset(0x36A0).As<sq_pushintegerType>();
	g_pSquirrel->__sq_pushfloat = module.Offset(0x3800).As<sq_pushfloatType>();
	g_pSquirrel->__sq_pushbool = module.Offset(0x3710).As<sq_pushboolType>();
	g_pSquirrel->__sq_pushasset = module.Offset(0x3560).As<sq_pushassetType>();
	g_pSquirrel->__sq_pushvector = module.Offset(0x3780).As<sq_pushvectorType>();
	g_pSquirrel->__sq_raiseerror = module.Offset(0x8440).As<sq_raiseerrorType>();

	g_pSquirrel->__sq_getstring = module.Offset(0x60A0).As<sq_getstringType>();
	g_pSquirrel->__sq_getinteger = module.Offset(0x60C0).As<sq_getintegerType>();
	g_pSquirrel->__sq_getfloat = module.Offset(0x60E0).As<sq_getfloatType>();
	g_pSquirrel->__sq_getbool = module.Offset(0x6110).As<sq_getboolType>();
	g_pSquirrel->__sq_getasset = module.Offset(0x5FF0).As<sq_getassetType>();
	g_pSquirrel->__sq_getuserdata = module.Offset(0x63B0).As<sq_getuserdataType>();
	g_pSquirrel->__sq_getvector = module.Offset(0x6120).As<sq_getvectorType>();
	g_pSquirrel->__sq_get = module.Offset(0x7C00).As<sq_getType>();

	g_pSquirrel->__sq_createuserdata = module.Offset(0x38D0).As<sq_createuserdataType>();
	g_pSquirrel->__sq_setuserdatatypeid = module.Offset(0x6470).As<sq_setuserdatatypeidType>();
    g_pSquirrel->__CSquirrelVM_Init = module.Offset(0x289C50).As<CSquirrelVM_InitType>();
    g_pSquirrel->__sq_getconstantstable = module.Offset(0x5920).As<sq_getconstantstableType>();
    g_pSquirrel->__sq_removefromstack = module.Offset(0x7000).As<sq_removefromstackType>();
    g_pSquirrel->setjmpPtr = module.Offset(0x23AAF10).As<void**>();


    g_pSquirrel->__sq_instructionvectorrealloc = module.Offset(0x69A20).As<sq_instructionvectorreallocType>();


	MAKEHOOK(
		module.Offset(0x1DD10),
		&RegisterSquirrelFunctionHook,
		&g_pSquirrel->RegisterSquirrelFunc);

	MAKEHOOK(module.Offset(0x8AA0), &sq_compiler_createHook, &sq_compiler_create);

	MAKEHOOK(module.Offset(0x1FE90), &SQPrintHook, &SQPrint);
	MAKEHOOK(module.Offset(0x260E0), &CreateNewVMHook, &CreateNewVM);
	MAKEHOOK(module.Offset(0x26E20), &DestroyVMHook, &DestroyVM);
	MAKEHOOK(module.Offset(0x799E0), &ScriptCompileErrorHook, &SQCompileError);

}


/*
AUTOHOOK(sq_nativecall, server.dll + 0x33E00, char, __fastcall, (HSquirrelVM* sqvm, SQNativeClosure* closure, SQObject* obj, unsigned int a4, SQObject* a5, BYTE* a6, char a7)) {
    printf("Calling Native: %s with string %016llx\n", closure->_name->_val,*(long long*)closure->value_70);
    return sq_nativecall(sqvm, closure, obj, a4, a5, a6, a7);
}

*/

