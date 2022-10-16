#include "hook.h"
#include "squirrel.h"
#include "filesystem.h"
#include "squirrelfunctionstubs.h"

AUTOHOOK_INIT()

AUTOHOOK(PrecacheModel, server.dll + 0x429550, __int64, _fastcall, (char* modelName)) {
    printf("Tried to load %s\n", modelName);
    return 1;
}

AUTOHOOK(sub_26BCB0, server.dll + 0x26BCB0, char, _fastcall, (void* a1, char* a2)) {
    return 0;
}




bool engineServer_unknown_4_stub(__int64 a1) {
    return true;
}

int16_t engineServer_unknown_18_stub(void* a1, int16_t a2) {
    return 1;
}

CGlobals* globals;

void fixStuffForStandaloneServer(CModule module) {
    globals = new CGlobals;
    globals->time = 0;
    globals->mapName = "mp_rise";
    globals->isMP = 1;
    globals->unknownPointer_80 = (char*)malloc(0x4000);
    IVEngineServer022* engineServer = new IVEngineServer022;
    engineServer->vtable = new VEngineServerVtable;
    engineServer->vtable->unknown_4 = engineServer_unknown_4_stub;
    engineServer->vtable->unknown_18 = engineServer_unknown_18_stub;

    module.Offset(0x1616730).Patch((uint8_t*)&g_fileInterface, 8);
    module.Offset(0xBFBE08).Patch((uint8_t*)&globals, 8);
    module.Offset(0xBFBD98).Patch((uint8_t*)&engineServer, 8);

}


struct VEngineGui {
    void* unknown[10];
    void (*unknown_10)(__int64, __int64, __int64);
};

void vEngineGui_10(__int64, __int64, __int64) {
    
}

void fixStuffForStandaloneClient(CModule module) {

    module.Offset(0x2E43FB0).Patch((uint8_t*)&g_fileInterface, 8);
    void* buf = malloc(792);
    static VEngineGui* vEngineGui = new VEngineGui;
    vEngineGui->unknown_10 = vEngineGui_10;
    VEngineGui** vEngineGuiPtr = &vEngineGui;
    module.Offset(0x2A87120).Patch((uint8_t*)&buf, 8);
    module.Offset(0xC3D9A8).Patch((uint8_t*)&vEngineGuiPtr, 8);
    
}

ON_DLL_LOAD("server.dll", ServerSquirrelStubs, (CModule module)) {
    AUTOHOOK_DISPATCH_MODULE(server.dll)
        fixStuffForStandaloneServer(module);
}

ON_DLL_LOAD("client.dll", ClientSquirrelStubs, (CModule module)) {
    AUTOHOOK_DISPATCH_MODULE(client.dll)
        fixStuffForStandaloneClient(module);
}

AUTOHOOK(loadDamageFlagsServer, server.dll + 0x6CC9F0, void*, __fastcall, (void)) {
    return 0;
}

AUTOHOOK(loadDamageFlagsClient, client.dll + 0x3CDDF0, void*, __fastcall, (void)) {
    return 0;
}

struct retStruct {
    void* unknown[32];
    void(*ret)(void*, __int64);
};
void sub_1ADD50_function(void*, __int64) {

}

AUTOHOOK(sub_1ADD50, client.dll + 0x1ADD50, retStruct**, __fastcall, (void)) {
    
    static retStruct* ret = new retStruct;
    ret->ret = sub_1ADD50_function;
    return &ret;
}


AUTOHOOK(sub_3A0EB0, client.dll + 0x3A0EB0, const char*, __fastcall, (void)) {
    return "mp_rise";
}
/*
AUTOHOOK(rson_evalWhenString, client.dll + 0x5C6900, __int64, __fastcall, (__int64 a1, char* a2, char** a3, __int64 a4)) {

    

    __int64 ret = rson_evalWhenString(a1, a2, a3, a4);
    spdlog::info("rson: WhenString: {} evaluated to {:X}", a2, **a3);
    return ret;
}
*/

AUTOHOOK(isMp, client.dll + 0x26D9A0, bool, __fastcall, (void)) {
    return true;
}

