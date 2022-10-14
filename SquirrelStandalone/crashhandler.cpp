
#include "crashhandler.h"
#include <windows.h>
#include <psapi.h>
#include <set>
#include <map>
#include <filesystem>
#include <sstream>

#include <minidumpapiset.h>

HANDLE hExceptionFilter;

long __stdcall ExceptionFilter(EXCEPTION_POINTERS* exceptionInfo)
{
    static bool logged = false;
    if (logged)
        return EXCEPTION_CONTINUE_SEARCH;

    if (!IsDebuggerPresent())
    {
        const DWORD exceptionCode = exceptionInfo->ExceptionRecord->ExceptionCode;
        if (exceptionCode != EXCEPTION_ACCESS_VIOLATION && exceptionCode != EXCEPTION_ARRAY_BOUNDS_EXCEEDED &&
            exceptionCode != EXCEPTION_DATATYPE_MISALIGNMENT && exceptionCode != EXCEPTION_FLT_DENORMAL_OPERAND &&
            exceptionCode != EXCEPTION_FLT_DIVIDE_BY_ZERO && exceptionCode != EXCEPTION_FLT_INEXACT_RESULT &&
            exceptionCode != EXCEPTION_FLT_INVALID_OPERATION && exceptionCode != EXCEPTION_FLT_OVERFLOW &&
            exceptionCode != EXCEPTION_FLT_STACK_CHECK && exceptionCode != EXCEPTION_FLT_UNDERFLOW &&
            exceptionCode != EXCEPTION_ILLEGAL_INSTRUCTION && exceptionCode != EXCEPTION_IN_PAGE_ERROR &&
            exceptionCode != EXCEPTION_INT_DIVIDE_BY_ZERO && exceptionCode != EXCEPTION_INT_OVERFLOW &&
            exceptionCode != EXCEPTION_INVALID_DISPOSITION && exceptionCode != EXCEPTION_NONCONTINUABLE_EXCEPTION &&
            exceptionCode != EXCEPTION_PRIV_INSTRUCTION && exceptionCode != EXCEPTION_STACK_OVERFLOW)
            return EXCEPTION_CONTINUE_SEARCH;

        std::stringstream exceptionCause;
        exceptionCause << "Cause: ";
        switch (exceptionCode)
        {
        case EXCEPTION_ACCESS_VIOLATION:
        case EXCEPTION_IN_PAGE_ERROR:
        {
            exceptionCause << "Access Violation" << std::endl;

            auto exceptionInfo0 = exceptionInfo->ExceptionRecord->ExceptionInformation[0];
            auto exceptionInfo1 = exceptionInfo->ExceptionRecord->ExceptionInformation[1];

            if (!exceptionInfo0)
                exceptionCause << "Attempted to read from: 0x" << (void*)exceptionInfo1;
            else if (exceptionInfo0 == 1)
                exceptionCause << "Attempted to write to: 0x" << (void*)exceptionInfo1;
            else if (exceptionInfo0 == 8)
                exceptionCause << "Data Execution Prevention (DEP) at: 0x" << (void*)std::hex << exceptionInfo1;
            else
                exceptionCause << "Unknown access violation at: 0x" << (void*)exceptionInfo1;

            break;
        }
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            exceptionCause << "Array bounds exceeded";
            break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            exceptionCause << "Datatype misalignment";
            break;
        case EXCEPTION_FLT_DENORMAL_OPERAND:
            exceptionCause << "Denormal operand";
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            exceptionCause << "Divide by zero (float)";
            break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            exceptionCause << "Divide by zero (int)";
            break;
        case EXCEPTION_FLT_INEXACT_RESULT:
            exceptionCause << "Inexact result";
            break;
        case EXCEPTION_FLT_INVALID_OPERATION:
            exceptionCause << "Invalid operation";
            break;
        case EXCEPTION_FLT_OVERFLOW:
        case EXCEPTION_INT_OVERFLOW:
            exceptionCause << "Numeric overflow";
            break;
        case EXCEPTION_FLT_UNDERFLOW:
            exceptionCause << "Numeric underflow";
            break;
        case EXCEPTION_FLT_STACK_CHECK:
            exceptionCause << "Stack check";
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            exceptionCause << "Illegal instruction";
            break;
        case EXCEPTION_INVALID_DISPOSITION:
            exceptionCause << "Invalid disposition";
            break;
        case EXCEPTION_NONCONTINUABLE_EXCEPTION:
            exceptionCause << "Noncontinuable exception";
            break;
        case EXCEPTION_PRIV_INSTRUCTION:
            exceptionCause << "Priviledged instruction";
            break;
        case EXCEPTION_STACK_OVERFLOW:
            exceptionCause << "Stack overflow";
            break;
        default:
            exceptionCause << "Unknown";
            break;
        }

        void* exceptionAddress = exceptionInfo->ExceptionRecord->ExceptionAddress;

        HMODULE crashedModuleHandle;
        GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCSTR>(exceptionAddress), &crashedModuleHandle);

        MODULEINFO crashedModuleInfo;
        GetModuleInformation(GetCurrentProcess(), crashedModuleHandle, &crashedModuleInfo, sizeof(crashedModuleInfo));

        char crashedModuleFullName[MAX_PATH];
        GetModuleFileNameExA(GetCurrentProcess(), crashedModuleHandle, crashedModuleFullName, MAX_PATH);
        char* crashedModuleName = strrchr(crashedModuleFullName, '\\') + 1;

        DWORD64 crashedModuleOffset = ((DWORD64)exceptionAddress) - ((DWORD64)crashedModuleInfo.lpBaseOfDll);
        CONTEXT* exceptionContext = exceptionInfo->ContextRecord;

        printf("Northstar has crashed! a minidump has been written and exception info is available below:\n");
        printf("%s\n", exceptionCause.str().c_str());
        printf("At: %s + %lx\n", crashedModuleName, (void*)crashedModuleOffset);

        PVOID framesToCapture[62];
        int frames = RtlCaptureStackBackTrace(0, 62, framesToCapture, NULL);
        bool haveSkippedErrorHandlingFrames = false;
        if (frames > 0)
        {
            for (int i = 0; i < frames; i++)
            {
                HMODULE backtraceModuleHandle;
                GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCSTR>(framesToCapture[i]), &backtraceModuleHandle);

                char backtraceModuleFullName[MAX_PATH];
                GetModuleFileNameExA(GetCurrentProcess(), backtraceModuleHandle, backtraceModuleFullName, MAX_PATH);
                char* backtraceModuleName = strrchr(backtraceModuleFullName, '\\') + 1;
                if (!haveSkippedErrorHandlingFrames)
                {
                    if (!strncmp(backtraceModuleFullName, crashedModuleFullName, MAX_PATH) &&
                        !strncmp(backtraceModuleName, crashedModuleName, MAX_PATH))
                    {
                        haveSkippedErrorHandlingFrames = true;
                    }
                    else
                    {
                        continue;
                    }
                }
                void* actualAddress = (void*)framesToCapture[i];
                void* relativeAddress = (void*)(uintptr_t(actualAddress) - uintptr_t(backtraceModuleHandle));

                printf("    %25s + 0x%08llx (0x%016llx)\n", backtraceModuleName, (__int64)relativeAddress, (__int64)actualAddress);
            }
        }
        printf("RAX: 0x%016llx\n", exceptionContext->Rax);
        printf("RBX: 0x%016llx\n", exceptionContext->Rbx);
        printf("RCX: 0x%016llx\n", exceptionContext->Rcx);
        printf("RDX: 0x%016llx\n", exceptionContext->Rdx);
        printf("RSI: 0x%016llx\n", exceptionContext->Rsi);
        printf("RDI: 0x%016llx\n", exceptionContext->Rdi);
        printf("RBP: 0x%016llx\n", exceptionContext->Rbp);
        printf("RSP: 0x%016llx\n", exceptionContext->Rsp);
        printf(" R8: 0x%016llx\n", exceptionContext->R8);
        printf(" R9: 0x%016llx\n", exceptionContext->R9);
        printf("R10: 0x%016llx\n", exceptionContext->R10);
        printf("R11: 0x%016llx\n", exceptionContext->R11);
        printf("R12: 0x%016llx\n", exceptionContext->R12);
        printf("R13: 0x%016llx\n", exceptionContext->R13);
        printf("R14: 0x%016llx\n", exceptionContext->R14);
        printf("R15: 0x%016llx\n", exceptionContext->R15);

    }

       

    logged = true;
    return EXCEPTION_EXECUTE_HANDLER;
}

BOOL WINAPI ConsoleHandlerRoutine(DWORD eventCode)
{
    switch (eventCode)
    {
    case CTRL_CLOSE_EVENT:
        // User closed console, shut everything down
        printf("Exiting due to console close...\n");
        RemoveCrashHandler();
        exit(EXIT_SUCCESS);
        return FALSE;
    }

    return TRUE;
}

void InitialiseCrashHandler()
{
    hExceptionFilter = AddVectoredExceptionHandler(TRUE, ExceptionFilter);
    SetConsoleCtrlHandler(ConsoleHandlerRoutine, true);
}

void RemoveCrashHandler()
{
    RemoveVectoredExceptionHandler(hExceptionFilter);
}
