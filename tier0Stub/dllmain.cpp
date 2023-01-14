// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <cstddef>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

class IMemAlloc;










extern "C" void stub() {
#pragma comment(linker, "/EXPORT:" "Print_ClearClientTime"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Print_EnableTimePrefix"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "Print_SetClientTime"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JTGuts_AddDependentJobArray@@YA?AW4JobID_t@@W4JobTypeID_t@@W41@_K2IIPEBW41@2E@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "LoggingSystem_RegisterLoggingChannel"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "SendRemoteErrorReport" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "LoggingSystem_Log" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "StackToolsNotify_LoadedLibrary" "=" __FUNCTION__)

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

#pragma comment(linker, "/EXPORT:" "?JT_GrowJobArray_Lock@@YAIW4JobID_t@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_GrowJobArray_Unlock@@YAXW4JobID_t@@I@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_DoneGrowingJobArray@@YAXW4JobID_t@@@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_GrowJobArray_SingleGrower@@YAXW4JobID_t@@I@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_HelpWithJobTypes@@YA_NP6A_N_K@Z00@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JTGuts_AddJob_Try@@YA?AW4JobID_t@@W4JobTypeID_t@@W41@_K2@Z" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "?JT_SetThreadIdx@@YAXI@Z" "=" __FUNCTION__)
}

//#pragma comment(linker, "/EXPORT:" "" "=" __FUNCTION__)



extern "C" void error2(const char* format, ...) {
#pragma comment(linker, "/EXPORT:" "Error" "=" __FUNCTION__)
    //char message[9000];
    va_list args;
    va_start(args,format);
    vprintf(format,args);
    
    va_end(args);

}




struct CCommandLine {

    
    // based on the defs in the 2013 source sdk, but for some reason has an extra function (may be another CreateCmdLine overload?)
    // these seem to line up with what they should be though
    void (*CreateCmdLine)(void* thisPtr, const char* commandline) = 0;
    void (*CreateCmdLine1)(void* thisPtr, int argc, char** argv) = 0;
    void (*ClearCmdLine)(void* thisPtr) = 0;
    const char* (*GetCmdLine)(void* thisPtr) = 0;

    const char* (*CheckParm)(void* thisPtr, const char* psz, const char** ppszValue) = 0;
    void (*RemoveParm)(void* thisPtr, const char* parm) = 0;
    void (*AppendParm)(void* thisPtr, const char* pszParm, const char* pszValues) = 0;

    const char* (*ParmValue)(void* thisPtr, const char* psz, const char* pDefaultVal) = 0;
    int (*ParmValue1)(void* thisPtr, const char* psz, int nDefaultVal) = 0;
    float (*ParmValue2)(void* thisPtr, const char* psz, float flDefaultVal) = 0;

    int (*ParmCount)(void* thisPtr) = 0;
    int (*FindParm)(void* thisPtr,const char* psz) = 0;
    const char* (*GetParm)(void* thisPtr,int nIndex) = 0;
    void (*SetParm)(void* thisPtr, int nIndex, char const* pParm) = 0;

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

CCommandLine** commandLine = 0;
CCommandLine* commandLineObj;

int findParam(void* a1, const char* param) {
    return 0;
}

const char* checkParam(void* a1, const char* param,const char** ret) {
    return 0;
}

extern "C" __declspec(dllexport) CCommandLine * *CommandLine() {
    if (!commandLine) {
        commandLineObj = new CCommandLine;
        commandLineObj->FindParm = findParam;
        commandLineObj->CheckParm = checkParam;
        commandLine = &commandLineObj;
    }
    return commandLine;
}


BOOL APIENTRY DllMain(HMODULE hModule,
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
