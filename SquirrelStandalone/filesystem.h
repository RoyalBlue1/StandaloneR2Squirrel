#pragma once
#define NOMINMAX // this too
#include <map>
#include <string>
#include <fstream>
#include <filesystem>
#include "prefix.h"
#include "modmanager.h"
namespace fs = std::filesystem;

class SquirrelFilesystem
{
    std::map<fs::path, fs::path> modOverrides;


public:
    std::string ReadFileToString(fs::path path)
    {
        fs::path normalizedPath = path.make_preferred();
        if (g_pModManager->m_ModFiles.count(normalizedPath.string())) {
            path = GetFilePrefix()/GetModFolder()/g_pModManager->m_ModFiles[normalizedPath.string()].m_pOwningMod->m_ModDirectory/fs::path("mod")/ normalizedPath;
        }
        else {
            path = GetFilePrefix()/ fs::path("base") / normalizedPath;
        }
        //printf("serarching for file: %s \n", path.string().c_str());
        if (!fs::exists(path)) {
            
            spdlog::info("FILE \"{}\"NOT FOUND",path.string());
            return std::string("");
        }
            
        std::ifstream f{ path };
        std::string fileData;
        f.seekg(0, std::ios::end);
        fileData.reserve(f.tellg());
        f.seekg(0, std::ios::beg);

        fileData.assign((std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());
        return fileData;
    }

    bool exists(fs::path path) {
        fs::path normalizedPath = path.make_preferred();
        if (g_pModManager->m_ModFiles.count(normalizedPath.string())){
            return true;
        }
        else {
            return fs::exists(GetFilePrefix() / fs::path("base") / normalizedPath);
        }
        

    }


    SquirrelFilesystem() {
    }
    
};



extern SquirrelFilesystem* g_filesystem;


enum SearchPathAdd_t
{
    PATH_ADD_TO_HEAD,		// First path searched
    PATH_ADD_TO_TAIL,		// Last path searched
};

enum FileSystemSeek_t
{
    FILESYSTEM_SEEK_HEAD = SEEK_SET,
    FILESYSTEM_SEEK_CURRENT = SEEK_CUR,
    FILESYSTEM_SEEK_TAIL = SEEK_END,
};

typedef void* FileHandle_t;

struct CUtlBuffer {
    void* data;
    long long size;//contains more but in dll only these are used
};
class IFileSystem;



class IFileSystem
{
public:
    struct VTable
    {
        //void* unknown[10];
        //void* unknown[11];
        void* unknown[12];
        void(__fastcall* AddSearchPath) (IFileSystem* fileSystem, const char* pPath, const char* pathID, SearchPathAdd_t addType); // +80 => +96
        /*void(*RemoveSearchPath) (IFileSystem* fileSystem, const char* pPath, const char* pathID, SearchPathAdd_t addType); // was +88 (11)
        void* unknown2[4];
        void(*GetSearchPath) (IFileSystem* fileSystem, const char* pathID, bool bGetPackFiles, char* pPath, int nMaxLen); // was +128 (16)
        void* unknown3[78];*/
        //void* unknown2[83];


        void* unknown2[82];
        bool(*ReadFromCache) (IFileSystem* fileSystem, const char* path, void* result); // was +760
        void* unknown4[15];
        void* (*MountVPK) (IFileSystem* fileSystem, const char* vpkPath); // was +888
        void* unknown5[22];
        //void* unknown6[1];
        void (*AddVPKFile) (IFileSystem* fileSystem, char const* pBasename, SearchPathAdd_t addType, __int64 a1, __int64 a2, __int64 a3); // was +1072
    };

    struct VTable2
    {
        int(*Read) (IFileSystem::VTable2** fileSystem, void* pOutput, int size, FileHandle_t file);
        int(*Write) (IFileSystem::VTable2** fileSystem, void const* pInput, int size, FileHandle_t file); // untested
        FileHandle_t(*Open) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pOptions, const char* pathID, int64_t unknown);
        void(*Close) (IFileSystem* fileSystem, FileHandle_t file);
        void(*Seek) (IFileSystem::VTable2** fileSystem, FileHandle_t file, int pos, FileSystemSeek_t seekType);
        unsigned int(*Tell) (IFileSystem::VTable2** fileSystem, FileHandle_t file);
        unsigned int(*Size_FromFilename) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPathID); // untested
        unsigned int(*Size_FromHandle) (IFileSystem::VTable2** fileSystem, FileHandle_t file); // untested (didn't work on its own? at least with Open and without any seeking)
        void(*Flush) (IFileSystem::VTable2** fileSystem, FileHandle_t file); // untested
        bool(*Precache) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPathID); // untested
        bool(*FileExists) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPathID);
        bool(*IsFileWritable) (IFileSystem::VTable2** fileSystem, char const* pFileName, const char* pPathID); // untested
        bool(*SetFileWritable) (IFileSystem::VTable2** fileSystem, char const* pFileName, bool writable, const char* pPathID); // untested
        long(*GetFileTime) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPathID); // untested
        bool(*ReadFile) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPath, CUtlBuffer* buf, int nMaxBytes, int nStartingByte, void* pfnAlloc); // untested, but appears to be right
        bool(*WriteFile) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPath, CUtlBuffer& buf); // untested
        bool(*UnzipFile) (IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPath, const char* pDestination); // untested

    };

    VTable* m_vtable;
    VTable2* m_vtable2;
    IFileSystem();
};
static_assert(offsetof(IFileSystem, m_vtable) == 0);
static_assert(offsetof(IFileSystem, m_vtable2) == 8);


extern IFileSystem* g_fileInterface;
