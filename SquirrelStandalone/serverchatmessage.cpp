
#include "limits.h"
#include "squirrel.h"
#include "hook.h"



AUTOHOOK_INIT()


// void function NSSendMessage( int playerIndex, string text, bool isTeam )
SQRESULT SQ_SendMessage(HSquirrelVM* sqvm)
{
    return SQRESULT_NULL;
}

// void function NSBroadcastMessage( int fromPlayerIndex, int toPlayerIndex, string text, bool isTeam, bool isDead, int messageType )
SQRESULT SQ_BroadcastMessage(HSquirrelVM* sqvm)
{
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
