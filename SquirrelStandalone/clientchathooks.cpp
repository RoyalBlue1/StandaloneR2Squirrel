
#include "squirrel.h"
#include "hook.h"


AUTOHOOK_INIT()

// clang-format off


// void NSChatWrite( int context, string str )
SQRESULT SQ_ChatWrite(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

// void NSChatWriteRaw( int context, string str )
SQRESULT SQ_ChatWriteRaw(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

// void NSChatWriteLine( int context, string str )
SQRESULT SQ_ChatWriteLine(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

ON_DLL_LOAD_CLIENT_RELIESON("client.dll", ClientChatHooks, ClientSquirrel, (CModule module))
{
    AUTOHOOK_DISPATCH()

        g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration("void", "NSChatWrite", "int context, string text", "", SQ_ChatWrite);
    g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration("void", "NSChatWriteRaw", "int context, string text", "", SQ_ChatWriteRaw);
    g_pSquirrel<ScriptContext::CLIENT>->AddFuncRegistration("void", "NSChatWriteLine", "int context, string text", "", SQ_ChatWriteLine);
}
