#include "hook.h"
#include "squirrel.h"


SQRESULT SQ_IsDedicated(HSquirrelVM* sqvm) {
    g_pSquirrel<ScriptContext::SERVER>->pushbool(sqvm, true);
    return SQRESULT_NOTNULL;
}
SQRESULT SQ_IsWritingPlayerPersistence(HSquirrelVM* sqvm) {
    g_pSquirrel<ScriptContext::SERVER>->pushbool(sqvm, false);
    return SQRESULT_NOTNULL;
}
SQRESULT SQ_IsPlayerIndexLocalPlayer(HSquirrelVM* sqvm) {
    g_pSquirrel<ScriptContext::SERVER>->pushbool(sqvm, true);
    return SQRESULT_NOTNULL;
}
SQRESULT SQ_EarlyWritePlayerIndexPersistenceForLeave(HSquirrelVM* sqvm) {
    ;
    return SQRESULT_NULL;
}


ON_DLL_LOAD_RELIESON("server.dll", MiscServerScriptCommands, ServerSquirrel, (CModule module))
{
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration(
        "void", "NSEarlyWritePlayerIndexPersistenceForLeave", "int playerIndex", "", SQ_EarlyWritePlayerIndexPersistenceForLeave);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration("bool", "NSIsWritingPlayerPersistence", "", "", SQ_IsWritingPlayerPersistence);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration(
        "bool", "NSIsPlayerLocalPlayer", "entity player", "", SQ_IsPlayerIndexLocalPlayer);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration("bool", "NSIsDedicated", "", "", SQ_IsDedicated);
}