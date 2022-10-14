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

void fixStuffForStandalone(CModule module) {
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



ON_DLL_LOAD("server.dll", ServerSquirrelStubs, (CModule module)) {
    AUTOHOOK_DISPATCH_MODULE(server.dll)
        fixStuffForStandalone(module);
}