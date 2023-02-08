#pragma once
#include "squirrel.h"

struct CGlobals
{
    BYTE gap_0[16];
    float time;
    BYTE gap_14[36];
    int isMP;
    BYTE gap_3C[36];
    const char* mapName;
    BYTE gap_[16];
    __int32 unknown_78;
    BYTE gap7C[4];
    char* unknownPointer_80;
    BYTE gap_end[1000];
};

struct VEngineServerVtable {
    void* unknown_0[4];
    bool(*unknown_4)(__int64 a1);
    void* unknown_5[13];
    int16_t(*unknown_18)(void* a1, int16_t a2);
};

struct IVEngineServer022 {

    VEngineServerVtable* vtable;
};




extern CGlobals* globals;