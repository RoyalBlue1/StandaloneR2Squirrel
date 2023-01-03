#include "hook.h"
#include "squirrel.h"


SQRESULT SQ_FuncStub(HSquirrelVM* sqvm) {
    return SQRESULT_NULL;
}

ON_DLL_LOAD_RELIESON("client.dll", PluginCommands, ClientSquirrel, (CModule module))
{
    // i swear there's a way to make this not have be run in 2 contexts but i can't figure it out
    // some funcs i need are just not available in UI or CLIENT

    if (g_pSquirrel<ScriptContext::UI> && g_pSquirrel<ScriptContext::CLIENT>)
    {
        g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
            "void",
            "NSUpdateGameStateUI",
            "string gamemode, string gamemodeName, string map, string mapName, bool connected, bool loading",
            "",
            SQ_FuncStub);
        g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration(
            "void",
            "NSUpdateGameStateClient",
            "int playerCount, int maxPlayers, int outScore, int secondHighestScore, int highestScore, bool roundBased, int scoreLimit",
            "",
            SQ_FuncStub);
        g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
            "void",
            "NSUpdateServerInfo",
            "string id, string name, string password, int players, int maxPlayers, string map, string mapDisplayName, string playlist, "
            "string "
            "playlistDisplayName",
            "",
            SQ_FuncStub);
        g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration(
            "void", "NSUpdateServerInfoReload", "int maxPlayers", "", SQ_FuncStub);
        g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration("void", "NSUpdateTimeInfo", "float timeInFuture", "", SQ_FuncStub);
        g_pSquirrel<ScriptContext::UI>->AddFuncRegistration("void", "NSSetLoading", "bool loading", "",SQ_FuncStub);
        g_pSquirrel<ScriptContext::UI>->AddFuncRegistration("void", "NSUpdateListenServer", "", "", SQ_FuncStub);

        g_pSquirrel<ScriptContext::UI>->AddFuncRegistration("asset","StringToAsset","string val","",SQ_FuncStub);
        g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration("asset","StringToAsset","string val","",SQ_FuncStub);
    }
}