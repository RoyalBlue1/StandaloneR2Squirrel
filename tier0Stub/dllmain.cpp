// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <cstddef>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

class IMemAlloc;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}





extern "C" void stub() {
#pragma comment(linker, "/EXPORT:" "LoggingSystem_RegisterLoggingChannel"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "SendRemoteErrorReport" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "LoggingSystem_Log" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "StackToolsNotify_LoadedLibrary" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Error" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "GetCPUInformation" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MemFreeScratch" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MemAllocScratch" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Print_GetTimeStamp" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadSleep" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadInMainThread" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "g_ClockSpeedSecondsMultiplier" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Plat_MSTime" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "g_ClockSpeedMillisecondsMultiplier" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadInMainOrServerFrameThread" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "vtune" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "CoreMsgV" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Plat_ExitProcess" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "PlatFloatTime" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Print_ClearServerTime" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Print_SetServerTime" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadInServerFrameThread" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Plat_IsInDebugSession" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_HelpWithJobTypesOrSleep@@YAXP6A_N_K@Z00@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_ContinueJob@@YAXW4JobTypeID_t@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_EndJobGroup@@YAXW4JobID_t@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_BeginJobGroup@@YA?AW4JobID_t@@W41@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_RegisterCallJobType@@YA?AW4JobTypeID_t@@W4JobPriority_e@@PEBD@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??1CThreadMutex@@QEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??0CThreadMutex@@QEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?job_JT_ExecuteCall@@3PAW4JobTypeID_t@@A" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_AddCallArray@@YA?AW4JobID_t@@W4JobCallPriority_e@@W41@P6AX_K@Z222@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JTGuts_AddJobArray@@YA?AW4JobID_t@@W4JobTypeID_t@@W41@_K22E@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_WaitForJobAndOnlyHelpWithJobTypes@@YAXW4JobID_t@@_K1@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_IsJobDone@@YA_NW4JobID_t@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JTGuts_AddJob@@YA?AW4JobID_t@@W4JobTypeID_t@@W41@_K2@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_SetJobTypeAffinity@@YAXW4JobTypeID_t@@II@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_InitJobTypeForJobArrays@@YAXW4JobTypeID_t@@_KM@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JTGuts_RegisterJobType@@YA?AW4JobTypeID_t@@W4JobPriority_e@@P6AX_K11@ZP6AXXZ31PEBD@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_GetCurrentJob@@YA?AW4JobID_t@@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_ThreadIndexEnd@@YAIXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?g_nThreadID@@3V?$CThreadLocalInt@H@GenericThreadLocals@@A" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?SpinLockForRead@CThreadSpinRWLock@@QEAAXXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?SpinLockForWrite@CThreadSpinRWLock@@QEAAXXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Get@CThreadLocalBase@GenericThreadLocals@@QEBAPEAXXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?g_pakLoadApi@@3UPakLoadFuncs_s@@A" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_GetCurrentThread@@YAIXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?LockForRead@CThreadSpinRWLock@@QEBAXXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "DetectLanguage" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "CommandLine" "=" __FUNCTION__)//prob used
#pragma comment(linker, "/EXPORT:" "?Start@CThread@@UEAA_N_KW4ThreadPriorityEnum_t@1@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Run@CThread@@MEAAHXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "RunTSListTests" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "RunTSQueueTests" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Resume@CThread@@QEAAIXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Suspend@CThread@@QEAAIXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?SetPriority@CThread@@QEAA_NW4ThreadPriority_e@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?SetPriority@CThread@@QEAA_NW4ThreadPriority_e@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?GetPriority@CThread@@QEBA?AW4ThreadPriority_e@@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?GetThreadHandle@CThread@@QEAAPEAUV_ThreadHandle_t__@@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?IsAlive@CThread@@QEAA_NXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?SetName@CThread@@QEAAXPEBD@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??1CThread@@UEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??0CThread@@QEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?WaitForMultiple@CThreadEvent@@SAIHPEAPEAV1@_NI@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Wait@CThreadEvent@@QEAA_NI@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Check@CThreadEvent@@QEAA_NXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Reset@CThreadEvent@@QEAA_NXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Set@CThreadEvent@@QEAA_NXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??0CThreadEvent@@QEAA@_N@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??1CThreadSyncObject@@QEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadSetAffinity" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadSetDebugName" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadJoin" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadInMainThread" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadSetPriority" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadGetPriority" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "ThreadGetCurrentHandle" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "GetCPUInformation" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Set@CThreadLocalBase@GenericThreadLocals@@QEAAXPEAX@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?Get@CThreadLocalBase@GenericThreadLocals@@QEBAPEAXXZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??1CThreadLocalBase@GenericThreadLocals@@QEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "??0CThreadLocalBase@GenericThreadLocals@@QEAA@XZ" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JTGuts_AddDependentJob@@YA?AW4JobID_t@@W4JobTypeID_t@@W41@_K2IIPEBW41@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Plat_FloatTime" "=" __FUNCTION__)


}

//#pragma comment(linker, "/EXPORT:" "" "=" __FUNCTION__)



class CCommandLine
{
public:
	// based on the defs in the 2013 source sdk, but for some reason has an extra function (may be another CreateCmdLine overload?)
	// these seem to line up with what they should be though
	virtual void CreateCmdLine(const char* commandline) {}
	virtual void CreateCmdLine(int argc, char** argv) {}
	virtual void ClearCmdLine(void) {}
	virtual const char* GetCmdLine(void) const {}

	virtual const char* CheckParm(const char* psz, const char** ppszValue = 0) const {}
	virtual void RemoveParm(const char* parm) const {}
	virtual void AppendParm(const char* pszParm, const char* pszValues) {}

	virtual const char* ParmValue(const char* psz, const char* pDefaultVal = 0) const {}
	virtual int ParmValue(const char* psz, int nDefaultVal) const {}
	virtual float ParmValue(const char* psz, float flDefaultVal) const {}

	virtual int ParmCount() const {}
	virtual int FindParm(const char* psz) const {}
	virtual const char* GetParm(int nIndex) const {}
	virtual void SetParm(int nIndex, char const* pParm) {}

	// virtual const char** GetParms() const {}
};



void* _Alloc(IMemAlloc* memAlloc, size_t nSize) {
	void* mem = malloc(nSize);
    if (mem == 0)
        return 0;
    memset(mem,0,nSize);
    return mem;
}
void* _Realloc(IMemAlloc* memAlloc, void* pMem, size_t newSize) {

    if (pMem == 0) {
        return _Alloc(memAlloc, newSize);
    }
    else {
        size_t oldSize = _msize(pMem);
        char* mem = (char*)realloc(pMem, newSize);
        if (mem == 0)
            return 0;
        if (newSize > oldSize) {
            memset(mem + oldSize, 0, newSize - oldSize);
        }
        return mem;
    }
	
}
void _Free(IMemAlloc* memAlloc, void* pMem) {
	free(pMem);
}
size_t _GetSize(IMemAlloc* memAlloc, void* pMem) {
    return _msize(pMem);
}

class IMemAlloc
{
public:
	struct VTable
	{
		void* unknown[1]; // alloc debug
		void* (*Alloc)(IMemAlloc* memAlloc, size_t nSize);
		void* unknown2[1]; // realloc debug
		void* (*Realloc)(IMemAlloc* memAlloc, void* pMem, size_t nSize);
		void* unknown3[1]; // free #1
		void (*Free)(IMemAlloc* memAlloc, void* pMem);
		void* unknown4[2]; // nullsubs, maybe CrtSetDbgFlag
		size_t(*GetSize)(IMemAlloc* memAlloc, void* pMem);
		void* unknown5[9]; // they all do literally nothing
		void (*DumpStats)(IMemAlloc* memAlloc);
		void (*DumpStatsFileBase)(IMemAlloc* memAlloc, const char* pchFileBase);
		void* unknown6[4];
		int (*heapchk)(IMemAlloc* memAlloc);
	};

	VTable* m_vtable;
	IMemAlloc() {
		this->m_vtable = new VTable;
		this->m_vtable->Alloc = _Alloc;
		this->m_vtable->Free = _Free;
		this->m_vtable->Realloc = _Realloc;
        this->m_vtable->GetSize = _GetSize;

	}
};
static_assert(offsetof(IMemAlloc, m_vtable) == 0);



extern "C" __declspec(dllexport) IMemAlloc* CreateGlobalMemAlloc() {
	return new IMemAlloc();
}

extern "C" __declspec(dllexport) IMemAlloc* g_pMemAllocSingleton = 0;



enum lexSymbols
{
    TK_SPACE = 0x20,
    TK_EXCLAMATION_POINT = 0x21,
    TK_DOUBLE_QUOTES = 0x22,
    TK_HASHTAG = 0x23,
    TK_DOLLAR_SIGN = 0x24,
    TK_PERCENT_SIGN = 0x25,
    TK_OPEN_BRACKET = 0x28,
    TK_ClOSED_BRACKET = 0x29,
    TK_STAR = 0x2A,
    TK_FORWARD_SLASH = 0x2F,
    TK_SEMICOLON = 0x3B,
    TK_OPEN_CURLEY_BRACKET = 0x7B,
    TK_IDENTIFIER = 0x102,
    TK_STRING_LITERAL = 0x103,
    TK_INTEGER = 0x104,
    TK_FLOAT = 0x105,
    TK_DELEGATE = 0x106,
    TK_DELETE = 0x107,
    TK_EQ = 0x108,
    TK_NE = 0x109,
    TK_LE = 0x10A,
    TK_GE = 0x10B,
    TK_SWITCH = 0x10C,
    TK_ARROW = 0x10D,
    TK_AND = 0x10E,
    TK_OR = 0x10F,
    TK_IF = 0x110,
    TK_ELSE = 0x111,
    TK_WHILE = 0x112,
    TK_BREAK = 0x113,
    TK_FOR = 0x114,
    TK_DO = 0x115,
    TK_NULL = 0x116,
    TK_FOREACH = 0x117,
    TK_IN = 0x118,
    TK_NEWSLOT = 0x119,
    TK_MODULO = 0x11A,
    TK_LOCAL = 0x11B,
    TK_CLONE = 0x11C,
    TK_FUNCTION = 0x11D,
    TK_RETURN = 0x11E,
    TK_TYPEOF = 0x11F,
    TK_UMINUS = 0x120,
    TK_PLUSEQ = 0x121,
    TK_MINUSEQ = 0x122,
    TK_CONTINUE = 0x123,
    TK_YIELD = 0x124,
    TK_TRY = 0x125,
    TK_CATCH = 0x126,
    TK_THROW = 0x127,
    TK_SHIFTL = 0x128,
    TK_SHIFTR = 0x129,
    TK_RESUME = 0x12A,
    TK_DOUBLE_COLON = 0x12B,
    TK_CASE = 0x12C,
    TK_DEFAULT = 0x12D,
    TK_THIS = 0x12E,
    TK_PLUSPLUS = 0x12F,
    TK_MINUSMINUS = 0x130,
    TK_PARENT = 0x131,
    TK_USHIFTR = 0x132,
    TK_CLASS = 0x133,
    TK_EXTENDS = 0x134,
    TK_CONSTRUCTOR = 0x136,
    TK_INSTANCEOF = 0x137,
    TK_VARPARAMS = 0x138,
    TK_VARGC = 0x139,
    TK_VARGV = 0x13A,
    TK_TRUE = 0x13B,
    TK_FALSE = 0x13C,
    TK_MULEQ = 0x13D,
    TK_DIVEQ = 0x13E,
    TK_MODEQ = 0x13F,
    TK_ATTR_OPEN = 0x140,
    TK_ATTR_CLOSE = 0x141,
    TK_STATIC = 0x142,
    TK_ENUM = 0x143,
    TK_CONST = 0x144,
    TK_THREAD = 0x145,
    TK_WAIT_THREAD = 0x146,
    TK_WAIT_THREAD_SOLO = 0x147,
    TK_WAIT = 0x148,
    TK_DELAY_THREAD = 0x149,
    TK_ASSERT = 0x14A,
    TK_VECTOR = 0x14B,
    TK_NORMALIZE = 0x14C,
    TK_NORM = 0x14D,
    TK_DOT = 0x14E,
    TK_CROSS = 0x151,
    TK_LENGTH = 340,
    TK_LENGHT_SQR = 341,
    TK_LENGTH_2D = 0x156,
    TK_LENGTH_2D_SQR = 0x157,
    TK_DOTPRODUCT = 0x14F,
    TK_DOTPRODUCT_2D = 0x150,
    TK_DISTANCE = 344,
    TK_DISTANCE_SQR = 345,
    TK_DISTANCE_2D = 346,
    TK_DISTANCE_2D_SQR = 347,
    TK_KV = 348,
    TK_NV = 349,
    TK_UI = 350,
    TK_GLOBAL = 351,
    TK_GLOBALIZE_ALL_FUNCTIONS = 357,
    TK_STRUCT = 358,
    TK_INT = 359,
    TK_FLOAT2 = 360,
    TK_BOOL = 361,
    TK_STRING = 362,
    TK_VECTOR2 = 363,
    TK_VAR = 364,
    TK_TABLE = 365,
    TK_ARRAY = 366,
    TK_VOID = 367,
    TK_ENTITY = 368,
    TK_EXPECT = 369,
    TK_UNREACHABLE = 370,
    TK_FUNCTIONREF = 371,
    TK_TYPEDEF = 372,
    TK_ORNULL = 373,
    TK_ASSET = 374,
    TK_UNTYPED = 376,

    TK_PREPRO_IF = 0x160,
    TK_PREPRO_ELSEIF = 0x161,
    TK_PREPRO_ELSE = 0x162,
    TK_PREPRO_ENDIF = 0x163,
    TK_PREPRO_DOCUMENT = 0x164,

    
};
