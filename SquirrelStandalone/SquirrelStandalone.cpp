// SquirrelStandalone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define NOMINMAX // this too


#include <Windows.h>
#include <iostream>

#include <filesystem>

#include "hook.h"
#include "squirrel.h"
#include "filesystem.h"
#include "modmanager.h"
#include "crashhandler.h"
#include "squirrelfunctionstubs.h"
#include <chrono>
#include <thread>

namespace fs = std::filesystem;



void compile_error_handler(HSquirrelVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column)
{
	std::cerr << "Error in " << source << " on line " << line << " column " << column << ": " << desc << std::endl;
}

void print_handler(HSquirrelVM v, const SQChar* s, ...)
{
	va_list vl;
	va_start(vl, s);
	vprintf(s, vl);
	std::cout << std::endl;
	va_end(vl);
}

bool LibraryLoadError(DWORD dwMessageId, const wchar_t* libName, const wchar_t* location)
{
    char text[2048];
    std::string message = std::system_category().message(dwMessageId);
    sprintf_s(text, "Failed to load the %ls at \"%ls\" (%lu):\n\n%hs", libName, location, dwMessageId, message.c_str());
    MessageBoxA(GetForegroundWindow(), text, "Launcher Error", MB_ICONERROR);
    return false;
}

const std::wstring GetExePathWide()
{
    WCHAR result[MAX_PATH];
    const DWORD length = GetModuleFileNameW(NULL, result, MAX_PATH);
    if (!length)
    {
        MessageBoxA(GetForegroundWindow(), "Failed calling GetModuleFileNameW.\nThis Program will now close.", "Launcher Error", MB_ICONERROR);
        std::exit(1);
    }
    fs::path path{ result };
    path._Remove_filename_and_separator();
    return path.wstring();
}


bool LoadLibraries()
{
    auto exePath = GetExePathWide();
    if (!exePath.length())
    {
        //MessageBoxA(GetForegroundWindow(), "Failed getting Squirrel directory.\nThis Program will now close.", "Error", MB_ICONERROR);
        return false;
    }

#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"%s\\" libname, exePath.c_str()); if (!LoadLibraryW(LibFullPath)) return LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
    wchar_t LibFullPath[1024];
    LOAD_LIBRARY("GBClient.dll");
    LOAD_LIBRARY("tier0.dll");
    LOAD_LIBRARY("vstdlib.dll");
    LOAD_LIBRARY("server.dll");
    LOAD_LIBRARY("client.dll");
    return true;

}


int main(int argc,char**argv)
{
    InitialiseCrashHandler();
    InstallInitialHooks();
    g_fileInterface = new IFileSystem;
	if (!LoadLibraries())
		return 1;
    
    CallAllPendingDLLLoadCallbacks();
    SetFilePrefixToCurrentDirectory(fs::path(argv[1]));
    g_pModManager = new ModManager();
    g_filesystem = new SquirrelFilesystem();
    





    g_pSquirrel<ScriptContext::SERVER>->compileTest();
    g_pSquirrel<ScriptContext::UI>->compileTest();
    g_pSquirrel<ScriptContext::CLIENT>->compileTest();
    spdlog::info("Compiled Successfully");






    return 0;
}

