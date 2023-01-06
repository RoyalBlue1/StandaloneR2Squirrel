#include "hook.h"
#include "squirrel.h"


SQRESULT SQ_IsDedicated(HSquirrelVM* sqvm) {
    pushbool(sqvm, true);
    return SQRESULT_NOTNULL;
}
SQRESULT SQ_IsWritingPlayerPersistence(HSquirrelVM* sqvm) {
    pushbool(sqvm, false);
    return SQRESULT_NOTNULL;
}
SQRESULT SQ_IsPlayerIndexLocalPlayer(HSquirrelVM* sqvm) {
    pushbool(sqvm, true);
    return SQRESULT_NOTNULL;
}
SQRESULT SQ_EarlyWritePlayerIndexPersistenceForLeave(HSquirrelVM* sqvm) {
    return SQRESULT_NULL;
}
SQRESULT NSDisconnectPlayer(HSquirrelVM* sqvm) {
    pushbool(sqvm, true);
    return SQRESULT_NOTNULL;
}
/*
ON_DLL_LOAD_RELIESON("server.dll", MiscServerScriptCommands, ServerSquirrel, (CModule module))
{
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration(
        "void", "NSEarlyWritePlayerPersistenceForLeave", "entity player", "", SQ_EarlyWritePlayerIndexPersistenceForLeave);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration("bool", "NSIsWritingPlayerPersistence", "", "", SQ_IsWritingPlayerPersistence);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration(
        "bool", "NSIsPlayerLocalPlayer", "entity player", "", SQ_IsPlayerIndexLocalPlayer);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration("bool", "NSIsDedicated", "", "", SQ_IsDedicated);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration("bool",
        "NSDisconnectPlayer",
        "entity player, string reason",
        "Disconnects the player from the server with the given reason",NSDisconnectPlayer);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration("asset","StringToAsset","string val","",SQ_IsDedicated);
}
*/