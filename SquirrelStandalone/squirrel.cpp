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

SQRESULT SQStub(HSquirrelVM* sqvm) {
    return SQRESULT_NULL;
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

RegisterSquirrelFuncType RegisterSquirrelFunc;
sq_defconstType __sq_defconst;

sq_compilebufferType __sq_compilebuffer;
sq_callType __sq_call;
sq_raiseerrorType __sq_raiseerror;

sq_newarrayType __sq_newarray;
sq_arrayappendType __sq_arrayappend;

sq_newtableType __sq_newtable;
sq_newslotType __sq_newslot;

sq_pushroottableType __sq_pushroottable;
sq_pushstringType __sq_pushstring;
sq_pushintegerType __sq_pushinteger;
sq_pushfloatType __sq_pushfloat;
sq_pushboolType __sq_pushbool;
sq_pushassetType __sq_pushasset;
sq_pushvectorType __sq_pushvector;

sq_getstringType __sq_getstring;
sq_getintegerType __sq_getinteger;
sq_getfloatType __sq_getfloat;
sq_getboolType __sq_getbool;
sq_getType __sq_get;
sq_getassetType __sq_getasset;
sq_getuserdataType __sq_getuserdata;
sq_getvectorType __sq_getvector;

sq_createuserdataType __sq_createuserdata;
sq_setuserdatatypeidType __sq_setuserdatatypeid;
CSquirrelVM_InitType __CSquirrelVM_Init;
sq_getconstantstableType __sq_getconstantstable;

sq_removefromstackType __sq_removefromstack;

CSquirrelVM_destroyType __CSquirrelVM_Destory;
CSquirrelVM_createType __CSquirrelVM_Create;

void ExecuteCode(CSquirrelVM* pSQVM,const char* pCode)
{
	if (!pSQVM || !pSQVM->sqvm)
	{
				return;
	}

	std::string strCode(pCode);
	CompileBufferState bufferState = CompileBufferState(strCode);

	SQRESULT compileResult = compilebuffer(pSQVM->sqvm,&bufferState, "console");
	
	if (compileResult != SQRESULT_ERROR)
	{
		pushroottable(pSQVM->sqvm);
		SQRESULT callResult = call(pSQVM->sqvm, 0);
	}
}


AUTOHOOK(SQPrintFunc_Server,server.dll + 0x1FE90,SQInteger,__fastcall,(HSquirrelVM* sqvm, const char* fmt, ...))
{
	va_list va;
	va_start(va, fmt);
    char buffer[4096];
	vsprintf_s(buffer, 4096, fmt, va);
    spdlog::info("[Server] {}", std::string(buffer));
	va_end(va);
	return 0;
}

AUTOHOOK(SQPrintFunc_Client,server.dll + 0x1FF30,SQInteger,__fastcall,(HSquirrelVM* sqvm, const char* fmt, ...))
{
    va_list va;
    va_start(va, fmt);
    char buffer[4096];
    vsprintf_s(buffer, 4096, fmt, va);
    spdlog::info("[Client] {}", std::string(buffer));
    va_end(va);
    return 0;
}

AUTOHOOK(SQPrintFunc_UI,server.dll + 0x1FFD0,SQInteger,__fastcall,(HSquirrelVM* sqvm, const char* fmt, ...))
{
    va_list va;
    va_start(va, fmt);
    char buffer[4096];
    vsprintf_s(buffer, 4096, fmt, va);
    spdlog::info("[UI] {}", std::string(buffer));
    va_end(va);
    return 0;
}



AUTOHOOK(ScriptCompileError,server.dll+0x799E0,void,__fastcall,(HSquirrelVM* sqvm, const char* error, const char* file, int line, int column))
{
    spdlog::error("Compile Error \"{}\" in {} VM in file {} on line {} in column {}\n", error,GetContextName((ScriptContext)sqvm->sharedState->cSquirrelVM->vmContext), file, line, column);
    exit(-1);
}


ON_DLL_LOAD("server.dll", ServerSquirrel, (CModule module))
{
    AUTOHOOK_DISPATCH_MODULE(server.dll)
    //printf("server.dll loaded and Squirrel initialized\n");



	__sq_defconst = module.Offset(0x1F550).As<sq_defconstType>();

	__sq_compilebuffer = module.Offset(0x3110).As<sq_compilebufferType>();
	__sq_pushroottable = module.Offset(0x5840).As<sq_pushroottableType>();
	__sq_call = module.Offset(0x8620).As<sq_callType>();

	__sq_newarray = module.Offset(0x39F0).As<sq_newarrayType>();
	__sq_arrayappend = module.Offset(0x3C70).As<sq_arrayappendType>();

	__sq_newtable = module.Offset(0x3960).As<sq_newtableType>();
	__sq_newslot = module.Offset(0x7080).As<sq_newslotType>();

	__sq_pushstring = module.Offset(0x3440).As<sq_pushstringType>();
	__sq_pushinteger = module.Offset(0x36A0).As<sq_pushintegerType>();
	__sq_pushfloat = module.Offset(0x3800).As<sq_pushfloatType>();
	__sq_pushbool = module.Offset(0x3710).As<sq_pushboolType>();
	__sq_pushasset = module.Offset(0x3560).As<sq_pushassetType>();
	__sq_pushvector = module.Offset(0x3780).As<sq_pushvectorType>();
	__sq_raiseerror = module.Offset(0x8440).As<sq_raiseerrorType>();

	__sq_getstring = module.Offset(0x60A0).As<sq_getstringType>();
	__sq_getinteger = module.Offset(0x60C0).As<sq_getintegerType>();
	__sq_getfloat = module.Offset(0x60E0).As<sq_getfloatType>();
	__sq_getbool = module.Offset(0x6110).As<sq_getboolType>();
	__sq_getasset = module.Offset(0x5FF0).As<sq_getassetType>();
	__sq_getuserdata = module.Offset(0x63B0).As<sq_getuserdataType>();
	__sq_getvector = module.Offset(0x6120).As<sq_getvectorType>();
	__sq_get = module.Offset(0x7C00).As<sq_getType>();

	__sq_createuserdata = module.Offset(0x38D0).As<sq_createuserdataType>();
	__sq_setuserdatatypeid = module.Offset(0x6470).As<sq_setuserdatatypeidType>();
    __CSquirrelVM_Init = module.Offset(0x289C50).As<CSquirrelVM_InitType>();
    __sq_getconstantstable = module.Offset(0x5920).As<sq_getconstantstableType>();
    __sq_removefromstack = module.Offset(0x7000).As<sq_removefromstackType>();



    __CSquirrelVM_Destory = module.Offset(0x280DB0).As<CSquirrelVM_destroyType>();

    __CSquirrelVM_Create = module.Offset(0x260E0).As<CSquirrelVM_createType>();

    RegisterSquirrelFunc = module.Offset(0x1DD10).As<RegisterSquirrelFuncType>();
 
}

CSquirrelVM* createVM(int context) {
    CSquirrelVM* vm = __CSquirrelVM_Create(0,context,1.0);
    std::ifstream jsonStream(GetFilePrefix() / "natives.json");
    std::stringstream jsonStringStream;

    if (jsonStream.fail())
    {
        spdlog::error("natives.json not found");
        return vm;
    }

    while (jsonStream.peek() != EOF)
        jsonStringStream << (char)jsonStream.get();

    rapidjson::Document nativeJson;
    nativeJson.Parse<rapidjson::ParseFlag::kParseCommentsFlag | rapidjson::ParseFlag::kParseTrailingCommasFlag>(jsonStringStream.str());

    // fail if parse error
    if (nativeJson.HasParseError())
    {
        spdlog::error("natives.json could not be read");
        return vm;
    }

    const char* contextName = GetContextName((ScriptContext)context);

    if (!(nativeJson.HasMember(contextName)&&nativeJson[contextName].IsObject())) 
    {
        spdlog::error("natives.json does not have a member for {} context or member is not an object",contextName);
        return vm;
    }
    if (nativeJson[contextName].HasMember("nativeFunctions") && nativeJson[contextName]["nativeFunctions"].IsArray()) 
    {
        for (auto& func : nativeJson[contextName]["nativeFunctions"].GetArray()) 
        {
            /*
            std::string name;
            std::string helpText;
            std::string returnType;
            std::string argTypes;
            if(func.HasMember("name")&&func["name"].IsString())
            {
                name =  func["name"].GetString();
            }
            else 
            {
                spdlog::warn("Function does not have a name");
                continue;
            }
                
            if(func.HasMember("helpText")&&func["helpText"].IsString())      
                helpText = func["helpText"].GetString();
            else
                helpText = "";

            if(func.HasMember("returnType")&&func["returnType"].IsString())
                returnType = func["returnType"].GetString();
            else
                returnType = "void";


            if(func.HasMember("argTypes")&&func["argTypes"].IsString())
                argTypes = func["argTypes"].GetString();
            else
                argTypes = "";


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

            reg->funcPtr = SQStub;
            
            //TODO du not just leak the memory
            */
            SQFuncRegistration reg;

            if(func.HasMember("name")&&func["name"].IsString())
            {
                reg.cppFuncName =  func["name"].GetString();
                reg.squirrelFuncName = reg.cppFuncName;
            }
            else 
            {
                spdlog::warn("Function does not have a name");
                continue;
            }

            if(func.HasMember("helpText")&&func["helpText"].IsString())      
                reg.helpText = func["helpText"].GetString();
            
            
            if(func.HasMember("returnTypeString")&&func["returnTypeString"].IsString())
                reg.returnTypeString = func["returnTypeString"].GetString();
            
            
            if(func.HasMember("returnType")&&func["returnType"].IsInt())
                reg.returnType =(eSQReturnType) func["returnType"].GetInt();
            

            if(func.HasMember("argTypes")&&func["argTypes"].IsString())
                reg.argTypes = func["argTypes"].GetString();
            

            reg.funcPtr = SQStub;
            if (!strcmp("DispatchSpawn", reg.cppFuncName)) {
                spdlog::info("foundFunc");
            }
            spdlog::info("func {}",reg.cppFuncName);
            RegisterSquirrelFunc(vm,&reg,0);
        }

    }
    if (nativeJson[contextName].HasMember("intConstants") && nativeJson[contextName]["intConstants"].IsArray()) 
    {
        for (auto& constant : nativeJson[contextName]["intConstants"].GetArray()) 
        {


            int val = 0;
            const char* name;
            if(constant.HasMember("name")&&constant["name"].IsString())
                name = constant["name"].GetString();
            else
                continue;
            if(constant.HasMember("val")&&constant["val"].IsInt())
                val = constant["val"].GetInt();


            defIntConst(vm,name,val);
        }
    }
    if (nativeJson[contextName].HasMember("nativeClassFunctions") && nativeJson[contextName]["nativeClassFunctions"].IsArray())
    {
        for (auto& func : nativeJson[contextName]["nativeClassFunctions"].GetArray())
        {
            
        }
    }

    return vm;
}