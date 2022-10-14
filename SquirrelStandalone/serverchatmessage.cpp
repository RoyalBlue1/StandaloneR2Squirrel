
#include "limits.h"
#include "squirrel.h"
#include "hook.h"



AUTOHOOK_INIT()


// void function NSSendMessage( int playerIndex, string text, bool isTeam )
SQRESULT SQ_SendMessage(HSquirrelVM* sqvm)
{
    int playerIndex = g_pSquirrel<ScriptContext::SERVER>->getinteger(sqvm, 1);
    const char* text = g_pSquirrel<ScriptContext::SERVER>->getstring(sqvm, 2);
    bool isTeam = g_pSquirrel<ScriptContext::SERVER>->getbool(sqvm, 3);

    

    return SQRESULT_NULL;
}

// void function NSBroadcastMessage( int fromPlayerIndex, int toPlayerIndex, string text, bool isTeam, bool isDead, int messageType )
SQRESULT SQ_BroadcastMessage(HSquirrelVM* sqvm)
{
    int fromPlayerIndex = g_pSquirrel<ScriptContext::SERVER>->getinteger(sqvm, 1);
    int toPlayerIndex = g_pSquirrel<ScriptContext::SERVER>->getinteger(sqvm, 2);
    const char* text = g_pSquirrel<ScriptContext::SERVER>->getstring(sqvm, 3);
    bool isTeam = g_pSquirrel<ScriptContext::SERVER>->getbool(sqvm, 4);
    bool isDead = g_pSquirrel<ScriptContext::SERVER>->getbool(sqvm, 5);
    int messageType = g_pSquirrel<ScriptContext::SERVER>->getinteger(sqvm, 6);


    

    return SQRESULT_NULL;
}


ON_DLL_LOAD_RELIESON("server.dll", ServerChatHooks, ServerSquirrel, (CModule module))
{
    AUTOHOOK_DISPATCH_MODULE(server.dll)


    // Chat sending functions
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration(
        "void", "NSSendMessage", "int playerIndex, string text, bool isTeam", "", SQ_SendMessage);
    g_pSquirrel<ScriptContext::SERVER>->AddFuncRegistration(
        "void",
        "NSBroadcastMessage",
        "int fromPlayerIndex, int toPlayerIndex, string text, bool isTeam, bool isDead, int messageType",
        "",
        SQ_BroadcastMessage);
}
