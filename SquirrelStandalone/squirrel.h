
#pragma once
#define NOMINMAX // this too
#include <windows.h>

#include "spdlog/spdlog.h"
#include "squirreldatatypes.h"
#include "vector.h"
#include <string>
#include <map>
#include <vector>

// stolen from ttf2sdk: sqvm types
typedef float SQFloat;
typedef long SQInteger;
typedef unsigned long SQUnsignedInteger;
typedef char SQChar;
typedef SQUnsignedInteger SQBool;

enum SQRESULT : SQInteger
{
	SQRESULT_ERROR = -1,
	SQRESULT_NULL = 0,
	SQRESULT_NOTNULL = 1,
};

typedef SQRESULT(*SQFunction)(HSquirrelVM* sqvm);

enum class eSQReturnType
{
	Float = 0x1,
	Vector = 0x3,
	Integer = 0x5,
	Boolean = 0x6,
	Entity = 0xD,
	String = 0x21,
	Default = 0x20,
	Arrays = 0x25,
	Asset = 0x28,
	Table = 0x26,
};

const std::map<SQRESULT, const char*> PrintSQRESULT = {
	{SQRESULT_ERROR, "SQRESULT_ERROR"}, {SQRESULT_NULL, "SQRESULT_NULL"}, {SQRESULT_NOTNULL, "SQRESULT_NOTNULL"} };

struct CompileBufferState
{
	const SQChar* buffer;
	const SQChar* bufferPlusLength;
	const SQChar* bufferAgain;

	CompileBufferState(const std::string& code)
	{
		buffer = code.c_str();
		bufferPlusLength = code.c_str() + code.size();
		bufferAgain = code.c_str();
	}
};

struct SQFuncRegistration
{
	const char* squirrelFuncName;
	const char* cppFuncName;
	const char* helpText;
	const char* returnTypeString;
	const char* argTypes;
	uint32_t unknown1;
	uint32_t devLevel;
	const char* shortNameMaybe;
	uint32_t unknown2;
	eSQReturnType returnType;
	uint32_t* externalBufferPointer;
	uint64_t externalBufferSize;
	uint64_t unknown3;
	uint64_t unknown4;
	SQFunction funcPtr;

	SQFuncRegistration()
	{
		memset(this, 0, sizeof(SQFuncRegistration));
		this->returnType = eSQReturnType::Default;
	}
};

enum class ScriptContext : int
{
	SERVER,
	CLIENT,
	UI,
};

const char* GetContextName(ScriptContext context);
eSQReturnType SQReturnTypeFromString(const char* pReturnType);
const char* SQTypeNameFromID(const int iTypeId);

// core sqvm funcs
typedef int64_t(*RegisterSquirrelFuncType)(CSquirrelVM* sqvm, SQFuncRegistration* funcReg, char unknown);
typedef void (*sq_defconstType)(CSquirrelVM* sqvm, const SQChar* name, int value);

typedef SQRESULT(*sq_compilebufferType)(
	HSquirrelVM* sqvm, CompileBufferState* compileBuffer, const char* file, int a1, SQBool bShouldThrowError);
typedef SQRESULT(*sq_callType)(HSquirrelVM* sqvm, SQInteger iArgs, SQBool bShouldReturn, SQBool bThrowError);
typedef SQInteger(*sq_raiseerrorType)(HSquirrelVM* sqvm, const SQChar* pError);

// sq stack array funcs
typedef void (*sq_newarrayType)(HSquirrelVM* sqvm, SQInteger iStackpos);
typedef SQRESULT(*sq_arrayappendType)(HSquirrelVM* sqvm, SQInteger iStackpos);

// sq table funcs
typedef SQRESULT(*sq_newtableType)(HSquirrelVM* sqvm);
typedef SQRESULT(*sq_newslotType)(HSquirrelVM* sqvm, SQInteger idx, SQBool bStatic);

// sq stack push funcs
typedef void (*sq_pushroottableType)(HSquirrelVM* sqvm);
typedef void (*sq_pushstringType)(HSquirrelVM* sqvm, const SQChar* pStr, SQInteger iLength);
typedef void (*sq_pushintegerType)(HSquirrelVM* sqvm, SQInteger i);
typedef void (*sq_pushfloatType)(HSquirrelVM* sqvm, SQFloat f);
typedef void (*sq_pushboolType)(HSquirrelVM* sqvm, SQBool b);
typedef void (*sq_pushassetType)(HSquirrelVM* sqvm, const SQChar* str, SQInteger iLength);
typedef void (*sq_pushvectorType)(HSquirrelVM* sqvm, const SQFloat* pVec);

// sq stack get funcs
typedef const SQChar* (*sq_getstringType)(HSquirrelVM* sqvm, SQInteger iStackpos);
typedef SQInteger(*sq_getintegerType)(HSquirrelVM* sqvm, SQInteger iStackpos);
typedef SQFloat(*sq_getfloatType)(HSquirrelVM*, SQInteger iStackpos);
typedef SQBool(*sq_getboolType)(HSquirrelVM*, SQInteger iStackpos);
typedef SQRESULT(*sq_getType)(HSquirrelVM* sqvm, SQInteger iStackpos);
typedef SQRESULT(*sq_getassetType)(HSquirrelVM* sqvm, SQInteger iStackpos, const char** pResult);
typedef SQRESULT(*sq_getuserdataType)(HSquirrelVM* sqvm, SQInteger iStackpos, void** pData, uint64_t* pTypeId);
typedef SQFloat* (*sq_getvectorType)(HSquirrelVM* sqvm, SQInteger iStackpos);
typedef bool (*CSquirrelVM_InitType)();
typedef SQTable* (*sq_getconstantstableType)(HSquirrelVM* sqvm);
// sq stack userpointer funcs
typedef void* (*sq_createuserdataType)(HSquirrelVM* sqvm, SQInteger iSize);
typedef SQRESULT(*sq_setuserdatatypeidType)(HSquirrelVM* sqvm, SQInteger iStackpos, uint64_t iTypeId);
typedef __int64 (*sq_removefromstackType)(HSquirrelVM* sqvm);



typedef char (*SQVMStartCallType)(HSquirrelVM* a1, SQClosure* a2, int a3, __int64 nInputParams, unsigned int a5, char a6);
typedef long long (*SQVMCallErrorHandlerType)(HSquirrelVM* sqvm, SQObject* a2);
typedef void (*sq_op_loadcopyType)(SQSharedState* a1, SQObject* a2, SQObject* a3);
typedef bool (*sq_op_callType)(HSquirrelVM* a1, SQInstruction* a2, SQObject* a3, int* a4, ...);
typedef long long (*sq_op_precallType)(HSquirrelVM* a1, SQInstruction* a2, SQObject* key);
typedef char (*SQVMGetType)(HSquirrelVM* self, SQObject* key, SQObject* dest, SQObject* temp_reg, char a5, char a6);
typedef int (*sub_35B80Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef char (*SQVMNewSlotType)(HSquirrelVM* sqvm, SQObject* self, SQObject* key, SQObject* val, char bstatic);
typedef char (*sub_34CF0Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_setType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, char a5);
typedef bool (*sq_op_eqType)(__int64 a1, SQObject* a2, SQObject* a3);
typedef char (*sub_2B590Type)(HSquirrelVM* a1, int a2, SQObject* a3, SQObject* a4, SQObject* a5);
typedef long long (*sq_sqvm_ReturnType)(HSquirrelVM* a1, int _arg0, int _arg1, SQObject* retval);
typedef SQObject* (*sq_copyObjectType)(SQObject* dest, SQObject* src);
typedef SQTable* (*sq_createTableType)(SQSharedState* sharedState, unsigned int length);;
typedef SQArray* (*sub_1800Type)(SQSharedState* a1, unsigned int a2);
typedef long long (*sub_1A20Type)(SQArray* a1, SQObject* a2);
typedef char (*sub_2F740Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef long long (*sub_2E670Type)(HSquirrelVM* a1, unsigned int a2, SQObject* a3, SQObject* a4, SQObject* a5);
typedef bool (*sub_2B6C0Type)(HSquirrelVM* a1, __int64 a2, SQObject* a3, SQObject* a4, SQObject* a5);
typedef char (*sub_2E960Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, int a5);
typedef char (*sq_op_increment_prefix_localType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4);
typedef char (*sp_op_increment_prefix_structfieldType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4, int a5);
typedef char (*sub_2EA30Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, int a5);
typedef char (*sub_2E860Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4);
typedef char (*sq_op_increment_postfix_structfieldType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4, int a5);
typedef char (*sub_2D1E0Type)(HSquirrelVM* a1, int a2, SQObject* a3, SQObject* a4, SQObject* dest);
typedef char (*sub_2CF10Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef char (*sub_2F0B0Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef char (*sub_2EE20Type)(
    HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, SQObject* a5, int a6, int a7, int a8, CallInfo* a9);
typedef char (*sub_2EF60Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sub_34A30Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef long long (*sub_2D950Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, __int64 a4);
typedef long long (*sub_35800Type)(__int64* a1, int a2);
typedef long long (*sub_2F2F0Type)(HSquirrelVM* a1, SQObject* a2, int a3, int a4);
typedef long long (*sub_3EA70Type)(void* a1, SQObject* a2, SQObject* a3);
typedef SQObject* (*SQVMToStringType)(HSquirrelVM* a1, SQObject* object, SQObject* res);
typedef char (*sq_op_addType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef long long (*sq_dropStackType)(HSquirrelVM* a1, int a2);
typedef long long (*sub_C6F0Type)(SQObject** a1, int a2);
typedef long long (*sub_27390Type)(SQObject* a1, int a2);
typedef SQStructInstance* (*sub_35B20Type)(HSquirrelVM* a1, SQObject* a2);
typedef char (*sq_op_subType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_multiplicationType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_divType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_moduloType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_compareType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, unsigned int* a4);
typedef SQObject* (*sq_setObjectToFloatType)(SQObject* a1, float a2);
typedef char (*sub_2E100Type)(HSquirrelVM* sqvm, __int64 a2, int a3, int a4, unsigned int a5);
typedef char (*sq_nativecallType)(HSquirrelVM* sqvm, SQNativeClosure* closure, __int64 a3, unsigned int a4, SQObject* a5, bool* shouldSuspend, bool argCheck);
typedef char (*sq_op_typecastType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4);
typedef char (*sq_op_check_entity_classType)(HSquirrelVM* a1, SQObject* a2, __int64 a3);
typedef long long (*sub_29A40Type)(SQSharedState* sharedState, SQObject* a2, int* a3);
typedef long long (*sub_63E00Type)(SQSharedState* a1, unsigned int a2, unsigned int* a3);
typedef void (*sub_2EDB0Type)(HSquirrelVM* a1, __int16* a2);
typedef SQString* (*sqStringTableAddType)(StringTable* a1, char* newString, int length);
typedef long long (*sub_BEF0Type)(SQObject** a1, unsigned int a2, SQObject* a3);
typedef long long (*SQVMRaise_ErrorType)(HSquirrelVM* a1, const char* a2, ...);
typedef void (*sq_rdbg_hookType)(
    SQDbgServer* dbgServer,
    HSquirrelVM* sqvm,
    int event_type,
    unsigned int line,
    const char* srcFileName,
    int unknown,
    const char* funcName,
    int unknown1);
typedef long long (*sq_rdbg_updateType)(SQDbgServer* dbgServer);

typedef SQInstruction* (*sq_instructionvectorreallocType)(SQInstruction** pVector, SQInteger iNewSize);


template <ScriptContext context> class SquirrelManager
{
private:
	std::vector<SQFuncRegistration*> m_funcRegistrations;

public:
	CSquirrelVM* m_pSQVM;
	std::map<std::string, SQFunction> m_funcOverrides = {};
	std::map<std::string, SQFunction> m_funcOriginals = {};

	bool m_bFatalCompilationErrors = false;

#pragma region SQVM funcs
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

    void** setjmpPtr;

    sq_instructionvectorreallocType __sq_instructionvectorrealloc;
    //Functions fror customExecute
    SQVMStartCallType __SQVMStartCall;
    SQVMCallErrorHandlerType __SQVMCallErrorHandler;
    sq_op_loadcopyType __sq_op_loadcopy;
    sq_op_callType __sq_op_call;
    sq_op_precallType __sq_op_precall;
    SQVMGetType __SQVMGet;
    sub_35B80Type __sub_35B80;
    SQVMNewSlotType __SQVMNewSlot;
    sub_34CF0Type __sub_34CF0;
    sq_op_setType __sq_op_set;
    sq_op_eqType __sq_op_eq;
    sub_2B590Type __sub_2B590;
    sq_sqvm_ReturnType __sq_sqvm_Return;
    sq_copyObjectType __sq_copyObject;
    sq_createTableType __sq_createTable;
    sub_1800Type __sub_1800;
    sub_1A20Type __sub_1A20;
    sub_2F740Type __sub_2F740;
    sub_2E670Type __sub_2E670;
    sub_2B6C0Type __sub_2B6C0;
    sub_2E960Type __sub_2E960;
    sq_op_increment_prefix_localType __sq_op_increment_prefix_local;
    sp_op_increment_prefix_structfieldType __sp_op_increment_prefix_structfield;
    sub_2EA30Type __sq_op_increment_postfix;
    sub_2E860Type __sq_op_increment_postfix_local;
    sq_op_increment_postfix_structfieldType __sq_op_increment_postfix_structfield;
    sub_2D1E0Type __sq_op_cmp;
    sub_2CF10Type __sub_2CF10;
    sub_2F0B0Type __sub_2F0B0;
    sub_2EE20Type __sub_2EE20;
    sub_2EF60Type __sub_2EF60;
    sub_34A30Type __sub_34A30;
    sub_2D950Type __sub_2D950;
    sub_35800Type __sub_35800;
    sub_2F2F0Type __sub_2F2F0;
    sub_3EA70Type __sub_3EA70;
    SQVMToStringType __SQVMToString;
    sq_op_addType __sq_op_add;
    sq_dropStackType __sq_dropStack;
    sub_C6F0Type __sub_C6F0;
    sub_27390Type __sub_27390;
    sub_35B20Type __sub_35B20;
    sq_op_subType __sq_op_sub;
    sq_op_multiplicationType __sq_op_multiplication;
    sq_op_divType __sq_op_div;
    sq_op_moduloType __sq_op_modulo;
    sq_compareType __sq_compare;
    sq_setObjectToFloatType __sq_setObjectToFloat;
    sub_2E100Type __sub_2E100;
    sq_nativecallType __sq_nativecall;
    sq_op_typecastType __sq_op_typecast;
    sq_op_check_entity_classType __sq_op_check_entity_class;
    sub_29A40Type __sub_29A40;
    sub_63E00Type __sub_63E00;
    sub_2EDB0Type __sub_2EDB0;
    sqStringTableAddType __sqStringTableAdd;
    sub_BEF0Type __sub_BEF0;
    SQVMRaise_ErrorType __SQVMRaise_Error;
    sq_rdbg_hookType __sq_rdbg_hook;
    sq_rdbg_updateType __sq_rdbg_update;

    SQObject* __globalClosure;
#pragma endregion

public:
	SquirrelManager() : m_pSQVM(nullptr) {}

	void VMCreated(CSquirrelVM* newSqvm);
	void VMDestroyed();
	void ExecuteCode(const char* code);
	void AddFuncRegistration(std::string returnType, std::string name, std::string argTypes, std::string helpText, SQFunction func);
	SQRESULT setupfunc(const SQChar* funcname);
	void AddFuncOverride(std::string name, SQFunction func);

#pragma region SQVM func wrappers
	inline void defconst(CSquirrelVM* sqvm, const SQChar* pName, int nValue)
	{
		__sq_defconst(sqvm, pName, nValue);
	}

	inline SQRESULT
		compilebuffer(CompileBufferState* bufferState, const SQChar* bufferName = "unnamedbuffer", const SQBool bShouldThrowError = false)
	{
		return __sq_compilebuffer(m_pSQVM->sqvm, bufferState, bufferName, -1, bShouldThrowError);
	}

	inline SQRESULT call(HSquirrelVM* sqvm, const SQInteger args)
	{
		return __sq_call(sqvm, args + 1, false, false);
	}

	inline SQInteger raiseerror(HSquirrelVM* sqvm, const const SQChar* sError)
	{
		return __sq_raiseerror(sqvm, sError);
	}

	inline void newarray(HSquirrelVM* sqvm, const SQInteger stackpos = 0)
	{
		__sq_newarray(sqvm, stackpos);
	}

	inline SQRESULT arrayappend(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		return __sq_arrayappend(sqvm, stackpos);
	}

	inline SQRESULT newtable(HSquirrelVM* sqvm)
	{
		return __sq_newtable(sqvm);
	}

	inline SQRESULT newslot(HSquirrelVM* sqvm, SQInteger idx, SQBool bStatic)
	{
		return __sq_newslot(sqvm, idx, bStatic);
	}

	inline void pushroottable(HSquirrelVM* sqvm)
	{
		__sq_pushroottable(sqvm);
	}

	inline void pushstring(HSquirrelVM* sqvm, const SQChar* sVal, int length = -1)
	{
		__sq_pushstring(sqvm, sVal, length);
	}

	inline void pushinteger(HSquirrelVM* sqvm, const SQInteger iVal)
	{
		__sq_pushinteger(sqvm, iVal);
	}

	inline void pushfloat(HSquirrelVM* sqvm, const SQFloat flVal)
	{
		__sq_pushfloat(sqvm, flVal);
	}

	inline void pushbool(HSquirrelVM* sqvm, const SQBool bVal)
	{
		__sq_pushbool(sqvm, bVal);
	}

	inline void pushasset(HSquirrelVM* sqvm, const SQChar* sVal, int length = -1)
	{
		__sq_pushasset(sqvm, sVal, length);
	}

	inline void pushvector(HSquirrelVM* sqvm, const Vector3 pVal)
	{
		__sq_pushvector(sqvm, *(float**)&pVal);
	}

	inline const SQChar* getstring(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		return __sq_getstring(sqvm, stackpos);
	}

	inline SQInteger getinteger(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		return __sq_getinteger(sqvm, stackpos);
	}

	inline SQFloat getfloat(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		return __sq_getfloat(sqvm, stackpos);
	}

	inline SQBool getbool(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		return __sq_getbool(sqvm, stackpos);
	}

	inline SQRESULT get(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		return __sq_get(sqvm, stackpos);
	}

	inline Vector3 getvector(HSquirrelVM* sqvm, const SQInteger stackpos)
	{
		float* pRet = __sq_getvector(sqvm, stackpos);
		return *(Vector3*)&pRet;
	}

	inline SQRESULT getasset(HSquirrelVM* sqvm, const SQInteger stackpos, const char** result)
	{
		return __sq_getasset(sqvm, stackpos, result);
	}

	template <typename T> inline SQRESULT getuserdata(HSquirrelVM* sqvm, const SQInteger stackpos, T* data, uint64_t* typeId)
	{
		return __sq_getuserdata(sqvm, stackpos, (void**)data, typeId); // this sometimes crashes idk
	}

	template <typename T> inline T* createuserdata(HSquirrelVM* sqvm, SQInteger size)
	{
		void* ret = __sq_createuserdata(sqvm, size);
		memset(ret, 0, size);
		return (T*)ret;
	}

	inline SQRESULT setuserdatatypeid(HSquirrelVM* sqvm, const SQInteger stackpos, uint64_t typeId)
	{
		return __sq_setuserdatatypeid(sqvm, stackpos, typeId);
	}

    inline bool startVM() {
        return __CSquirrelVM_Init();
    }

    inline SQTable* getConstants(HSquirrelVM* sqvm) {
        return __sq_getconstantstable(sqvm);
    }
    inline __int64 removeFromStack(HSquirrelVM* sqvm) {
        return __sq_removefromstack(sqvm);
    }

    inline SQInstruction* reallocinstructionvector(SQInstruction** vector, const SQInteger size)
    {
        return __sq_instructionvectorrealloc(vector, size);
    }

    inline void callLineDebugger(SQDbgServer* dbgServer, HSquirrelVM* sqvm, int line, const char* srcFileName) {
        __sq_rdbg_hook(dbgServer, sqvm, 'l', line, srcFileName, 0, 0, 0);
        if (dbgServer->_autoupdate && __sq_rdbg_update(dbgServer))
            __sq_raiseerror(sqvm, "invalid socket");
    }
#pragma endregion
};

template <ScriptContext context> SquirrelManager<context>* g_pSquirrel;

