#define _CRT_SECURE_NO_WARNINGS 1
#include "filesystem.h"

SquirrelFilesystem* g_filesystem;
IFileSystem* g_fileInterface;
std::map<std::string,std::string> fileCache;

bool _ReadFromCache(IFileSystem* fileSystem, const char* path, void* result) {
    return false;
}

bool _ReadFile(IFileSystem::VTable2** fileSystem, const char* pFileName, const char* pPath, CUtlBuffer* buf, int nMaxBytes, int nStartingByte, void* pfnAlloc) {
    //printf("Load Path: %s \n", pFileName);
    std::string data = "";
    if (!strcmp(pFileName, "scripts/vscripts/scripts.rson")) {
        data = g_pModManager->BuildScriptsRson();
    }
    else {
        if (fileCache.count(std::string(pFileName))) {
            data = fileCache[std::string(pFileName)];
        }
        else {
            data = g_filesystem->ReadFileToString(fs::path(pFileName));
            fileCache[std::string(pFileName)] = data;
        }
        
    }
    if (data.size() <= 1)
        return false;
    buf->data = malloc(data.size() + 1);
    if (buf->data == 0)
        return false;
    memcpy(buf->data, data.c_str(), data.size());
    ((char*)buf->data)[data.size()] = '\0';
    buf->size = data.size();
    return true;

}

IFileSystem::IFileSystem() {
    this->m_vtable = new VTable;
    this->m_vtable2 = new VTable2;
    this->m_vtable->ReadFromCache = _ReadFromCache;
    this->m_vtable2->ReadFile = _ReadFile;
}

