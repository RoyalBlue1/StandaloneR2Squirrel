#include "squirrel.h"

#include "hook.h"








/*

template <ScriptContext context> void RegisterSQFuncs()
{
    g_pSquirrel<context>->AddFuncRegistration(
        "int",
        "NS_InternalMakeHttpRequest",
        "int method, string baseUrl, table<string, array<string> > headers, table<string, array<string> > queryParams, string contentType, "
        "string body, "
        "int timeout, string userAgent",
        "[Internal use only] Passes the HttpRequest struct fields to be reconstructed in native and used for an http request",
        SQ_InternalMakeHttpRequest<context>);

    g_pSquirrel<context>->AddFuncRegistration(
        "bool",
        "NSIsHttpEnabled",
        "",
        "Whether or not HTTP requests are enabled. You can opt-out by starting the game with -disablehttprequests.",
        SQ_IsHttpEnabled<context>);

    g_pSquirrel<context>->AddFuncRegistration(
        "bool",
        "NSIsLocalHttpAllowed",
        "",
        "Whether or not HTTP requests can be made to a private network address. You can enable this by starting the game with "
        "-allowlocalhttp.",
        SQ_IsLocalHttpAllowed<context>);
}
*/
// int NS_InternalMakeHttpRequest(int method, string baseUrl, table<string, string> headers, table<string, string> queryParams,
//	string contentType, string body, int timeout, string userAgent)
template <ScriptContext context> SQRESULT SQ_InternalMakeHttpRequest(HSquirrelVM* sqvm)
{

    return SQRESULT_NOTNULL;
}

// bool NSIsHttpEnabled()
template <ScriptContext context> SQRESULT SQ_IsHttpEnabled(HSquirrelVM* sqvm)
{
    g_pSquirrel<context>->pushbool(sqvm, true);
    return SQRESULT_NOTNULL;
}

// bool NSIsLocalHttpAllowed()
template <ScriptContext context> SQRESULT SQ_IsLocalHttpAllowed(HSquirrelVM* sqvm)
{
    g_pSquirrel<context>->pushbool(sqvm, false);
    return SQRESULT_NOTNULL;
}
/*
ON_DLL_LOAD_RELIESON("client.dll", HttpRequestHandler_ClientInit, ClientSquirrel, (CModule module))
{
    RegisterSQFuncs<ScriptContext::CLIENT>();
    RegisterSQFuncs<ScriptContext::UI>();
}

ON_DLL_LOAD_RELIESON("server.dll", HttpRequestHandler_ServerInit, ServerSquirrel, (CModule module))
{
    RegisterSQFuncs<ScriptContext::SERVER>();
}

*/