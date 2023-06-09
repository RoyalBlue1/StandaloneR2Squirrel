
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

typedef SQInstruction* (*sq_instructionvectorreallocType)(SQInstruction** pVector, SQInteger iNewSize);


class SquirrelManager
{
private:
	std::vector<SQFuncRegistration*> m_funcRegistrations;

public:
	CSquirrelVM* m_pSQVM;
	std::map<std::string, SQFunction> m_funcOverrides = {};
	std::map<std::string, SQFunction> m_funcOriginals = {};

	bool m_bFatalCompilationErrors = false;

#pragma region SQVM funcs
	RegisterSquirrelFuncType RegisterSquirrelFunc = 0;
	sq_defconstType __sq_defconst = 0;

	sq_compilebufferType __sq_compilebuffer = 0;
	sq_callType __sq_call = 0;
	sq_raiseerrorType __sq_raiseerror = 0;

	sq_newarrayType __sq_newarray = 0;
	sq_arrayappendType __sq_arrayappend = 0;

	sq_newtableType __sq_newtable = 0;
	sq_newslotType __sq_newslot = 0;

	sq_pushroottableType __sq_pushroottable = 0;
	sq_pushstringType __sq_pushstring = 0;
	sq_pushintegerType __sq_pushinteger = 0;
	sq_pushfloatType __sq_pushfloat = 0;
	sq_pushboolType __sq_pushbool = 0;
	sq_pushassetType __sq_pushasset = 0;
	sq_pushvectorType __sq_pushvector = 0;

	sq_getstringType __sq_getstring = 0;
	sq_getintegerType __sq_getinteger = 0;
	sq_getfloatType __sq_getfloat = 0;
	sq_getboolType __sq_getbool = 0;
	sq_getType __sq_get = 0;
	sq_getassetType __sq_getasset = 0;
	sq_getuserdataType __sq_getuserdata = 0;
	sq_getvectorType __sq_getvector = 0;

	sq_createuserdataType __sq_createuserdata = 0;
	sq_setuserdatatypeidType __sq_setuserdatatypeid = 0;
    CSquirrelVM_InitType __CSquirrelVM_Init = 0;
    sq_getconstantstableType __sq_getconstantstable = 0;
    sq_removefromstackType __sq_removefromstack = 0;

    void** setjmpPtr  = 0;

    sq_instructionvectorreallocType __sq_instructionvectorrealloc  = 0;
    //Functions fror customExecute
    
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

	inline SQInteger raiseerror(HSquirrelVM* sqvm, const SQChar* sError)
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

    bool startVM() {
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


#pragma endregion
};

extern SquirrelManager* g_pSquirrel;

extern std::map<int,int> executedOPCodes;


