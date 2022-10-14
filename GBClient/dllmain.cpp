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
#pragma comment(linker, "/EXPORT:" "__imp_??0GBPublicTargetId@GameBlocks@@QEAA@PEBD@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??0GBPublicTargetId@GameBlocks@@QEAA@H@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??0GBPublicTargetId@GameBlocks@@QEAA@_K@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??1GBPublicTargetId@GameBlocks@@QEAA@XZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??BGBPublicTargetId@GameBlocks@@QEBA_KXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??0GBSourceProperty@GameBlocks@@QEAA@PEBD@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??0GBSourceProperty@GameBlocks@@QEAA@H@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??1GBSourceProperty@GameBlocks@@QEAA@XZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??0GBPredefinedId@GameBlocks@@QEAA@H@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerList_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerList_Push@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@PEBD2@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerCount_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@H@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_MaxPlayerCount_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@H@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerJoin_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@1PEBD2@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_AimBotDetect_Send@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@11@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_WeaponCheatDetect_Send@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@1@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerLeave_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@1PEBD@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerLocationList_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerLocationList_Push@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@MMMMMMAEBVGBPredefinedId@1@H@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerScreenShotJpg_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@1PEBD_K@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_Chat_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@1PEBD_N@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_MatchEnd_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@HH@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Event_PlayerMatchEnd_Prepare@GameBlocks@@YA?AW4EGBClientError@1@PEAVGBClient@1@AEBVGBPublicTargetId@1@1HHHHHHHH@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??0GBClient@GameBlocks@@QEAA@XZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_??1GBClient@GameBlocks@@QEAA@XZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?InitSocketsSubsystem@GBClient@GameBlocks@@SAXXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?SetAuthenticationEnabled@GBClient@GameBlocks@@QEAAX_N@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?SetAuthenticationKey@GBClient@GameBlocks@@QEAAXPEBD@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?EnableSSL@GBClient@GameBlocks@@QEAAX_N@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?ConnectUsingUrl@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@PEBDGAEBVGBPublicTargetId@2@H_N0@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Close@GBClient@GameBlocks@@QEAAXXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?SetTitleInterface@GBClient@GameBlocks@@QEAAXPEAVGBTitleInterface@2@@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Tick@GBClient@GameBlocks@@QEAAXXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Connected@GBClient@GameBlocks@@QEAA_NXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?PrepareEventForSending@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@PEBDAEBVGBPublicTargetId@2@1@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AddKeyValueInt@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@PEBDH@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AddKeyValueString@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@PEBD0@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AddKeyValueFloat@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@PEBDM@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AddKeyValueVector3D@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@PEBDMMM@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?SendEvent@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@XZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Incoming_GetName@GBClient@GameBlocks@@QEBAPEBDXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Incoming_GetPlayerId@GBClient@GameBlocks@@QEBAAEBVGBPublicTargetId@2@XZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Incoming_GetPairValueInt@GBClient@GameBlocks@@QEBA?AW4EGBClientError@2@AEAHPEBD@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?EnableAimBotDetector@GBClient@GameBlocks@@QEAAX_KM@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AimBotDetector_BeginFrame@GBClient@GameBlocks@@QEAAXXZ:"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AimBotDetector_Add@GBClient@GameBlocks@@QEAAXAEBVGBPublicTargetId@2@AEBVGBPredefinedId@2@1MMMMMMMMM@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?AimBotDetector_EndFrame@GBClient@GameBlocks@@QEAAXXZ"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?EnableWeaponCheatDetector@GBClient@GameBlocks@@QEAAX_K@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?WeaponCheatDetector_AddProjImpact@GBClient@GameBlocks@@QEAAXAEBVGBPublicTargetId@2@0AEBVGBPredefinedId@2@_NMHHHMMMI@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?WeaponCheatDetector_AddProjectile@GBClient@GameBlocks@@QEAAXAEBVGBPublicTargetId@2@AEBVGBPredefinedId@2@1MMMMMM111@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?Source_SetProperty@GBClient@GameBlocks@@QEAA?AW4EGBClientError@2@AEBVGBPublicTargetId@2@PEBDAEBVGBSourceProperty@2@@Z"  "=" __FUNCTION__)
#pragma comment(linker, "/EXPORT:" "__imp_?RegisterThread@GBClient@GameBlocks@@QEAAXXZ"  "=" __FUNCTION__)


}