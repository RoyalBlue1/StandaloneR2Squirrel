// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

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
#pragma comment(linker, "/EXPORT:" "MilesDriverGetSampleRate" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesDriverGetOutputChannelCount" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesDriverSetOptimizedMute" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesDriverSetMasterVolume" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesDriverDestroy" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesDriverCreate" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesAllocTrack" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSetAllocFns" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesAllocEx" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSetStartupParameters" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesShutdown" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesStartup" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBusAddFilter" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesDbToLinear" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesFileSetCallbacks" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesFilterRegister" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesFilterGetByName" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesFilterGetPropertyByName" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesFilterSetPropertyValue" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesOutputGetNull" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesEventSetStreamingCacheLimit" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesProjectLoad" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesProjectGetStatus" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesProjectGetBus" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankLoad" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankGetStatus" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankPatch" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankCommitPatches" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueCreate" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueDestroy" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueSubmit" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueGetIsRetired" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventRun" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventRunByTemplateId" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventInfoMask" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEvent3DOrientation" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEvent3DPosition" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventDelayVoicesByTime" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventStartTime" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventRateFactor" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventControllerValue" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueEventFilterId" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueControllerValue" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueListener3DPosition" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueListener3DOrientation" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueActiveEvent3DPosition" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueActiveEvent3DOrientation" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueActiveEventControllerValue" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesAsyncSetCallbacks" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSampleAddSource" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSamplePlay" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSampleSetEOBCallback" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSampleSetSourceRaw" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesQueueActiveEventRateFactor" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSampleSetSourceDiscards" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSampleDestroy" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesSampleCreate" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankGetSourceTemplateId" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankGetSourceCount" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesEventReferencesController" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesEventGetDetails" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesEventGetMetaContent" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankGetEventTemplateId" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesBankGetEventCount" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesOutputWASAPI" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesOutputDirectSound" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesOutputXAudio2" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesEventInfoQueueEnum" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesEventInfoQueueEnable" "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "MilesServiceDrivers" "=" __FUNCTION__)
}