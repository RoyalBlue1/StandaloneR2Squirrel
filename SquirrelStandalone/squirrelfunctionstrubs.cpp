#include "hook.h"
#include "squirrel.h"
#include "filesystem.h"
#include "squirrelfunctionstubs.h"

AUTOHOOK_INIT()


struct alignas(8) struct_memoryIDK
{
    int64_t qword_0;
    int64_t qword_8;
    int64_t *unknown_10;
    int64_t gap_18[8000];
    int32_t dword_FA18;
    int8_t gap_FA1C[4];
    int64_t qword_FA20;
    int32_t dword_FA28;
    int8_t gap_FA2C[4];
    int64_t qword_FA30;
    int64_t qword_FA38;
    int64_t qword_FA40;
    int32_t dword_FA48;
    int8_t gap_FA4C[4];
};

struct struct_unknown
{
    void (__fastcall **ppfunc0)(struct_unknown*, int64_t);
    int8_t gap_8[24];
    int int20;
    int8_t gap_24[12];
    SQObject *pint64_30;
    int8_t gap_38[8];
    int64_t qword_40;
    int64_t qword_48;
    int64_t qword_50;
    int64_t qword_58;
};
typedef __int64 (*sub_11110Type)(__int64 a1, SQObject *a2);
sub_11110Type sub_11110;

typedef __int64(*sub_52DF30Type)(__int64 a1, __int64 a2);
sub_52DF30Type sub_52DF30;

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
    sub_11110 = module.Offset(0x11110).As<sub_11110Type>();
    sub_52DF30 = module.Offset(0x52DF30).As<sub_52DF30Type>();
    *module.Offset(0x23E8248+92).As<int*>()= 0;

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

AUTOHOOK(isMp, client.dll + 0x26D9A0, bool, __fastcall, (void)) 
{
    return true;
}


//THIS SHOULD NOT BE FIXED LIKE THIS
/*
AUTOHOOK(sub_52DE40, client.dll +0x52DE40,void, __fastcall, (struct_memoryIDK *a1)) 
{
    struct_unknown *i; // rbx
    __int64 v3; // rcx
    __int64 v4; // rcx
    __int64 v5; // rcx
    SQObject *v6; // rdx
    __int64 v7; // rsi
    __int64 v8; // rax
    __int64 v9; // rcx
    while ( a1->dword_FA18 )
    {
        for ( i = (struct_unknown *)*((int64_t *)&a1->unknown_10 + (int)a1->dword_FA18);
            i->qword_48;
            sub_52DF30((__int64)a1, i->qword_48) )
        {
            ;
        }
        v3 = i->qword_50;
        if ( v3 )
            *(int64_t *)(v3 + 88) = i->qword_58;
        v4 = i->qword_58;
        if ( v4 )
            *(int64_t *)(v4 + 80) = i->qword_50;
        v5 = i->qword_40;
        if ( v5 && *(struct_unknown **)(v5 + 72) == i )
            *(int64_t *)(v5 + 72) = i->qword_58;
        v6 = i->pint64_30;
        v7 = i->int20;
        i->int20 = -1;
        if ( v6 != (SQObject *)-1i64 )
            sub_11110(a1->qword_FA20, v6);
        i->pint64_30 = (SQObject *)-1i64;
        (*i->ppfunc0)(i, 1i64);
        v8 = (int)--a1->dword_FA18;
        if ( (int)v7 < (int)v8 )
        {
            v9 = a1->gap_18[v8];
            a1->gap_18[v7] = v9;
            *(int *)(v9 + 32) = v7;
        }
    }
}


AUTOHOOK(sub_3C80E0, client.dll + 0x3C80E0, char, __fastcall, (void)) {

    spdlog::info("IT FUCKING RAN");
    return sub_3C80E0();
}
*/

