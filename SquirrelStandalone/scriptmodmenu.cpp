#include "hook.h"
#include "squirrel.h"

// array<string> function NSGetModNames()
SQRESULT SQ_GetModNames(HSquirrelVM* sqvm)
{
    return SQRESULT_NOTNULL;
}

// bool function NSIsModEnabled(string modName)
SQRESULT SQ_IsModEnabled(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

// void function NSSetModEnabled(string modName, bool enabled)
SQRESULT SQ_SetModEnabled(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

// string function NSGetModDescriptionByModName(string modName)
SQRESULT SQ_GetModDescription(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

// string function NSGetModVersionByModName(string modName)
SQRESULT SQ_GetModVersion(HSquirrelVM* sqvm)
{
 
    return SQRESULT_NULL;
}

// string function NSGetModDownloadLinkByModName(string modName)
SQRESULT SQ_GetModDownloadLink(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

// int function NSGetModLoadPriority(string modName)
SQRESULT SQ_GetModLoadPriority(HSquirrelVM* sqvm)
{
    return SQRESULT_NULL;
}

// bool function NSIsModRequiredOnClient(string modName)
SQRESULT SQ_IsModRequiredOnClient(HSquirrelVM* sqvm)
{
    return SQRESULT_NULL;
}

// array<string> function NSGetModConvarsByModName(string modName)
SQRESULT SQ_GetModConvars(HSquirrelVM* sqvm)
{
    return SQRESULT_NOTNULL; // return empty array
}

// void function NSReloadMods()
SQRESULT SQ_ReloadMods(HSquirrelVM* sqvm)
{

    return SQRESULT_NULL;
}

ON_DLL_LOAD_RELIESON("client.dll", ScriptModMenu, ClientSquirrel, (CModule module))
{
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "array<string>", "NSGetModNames", "", "Returns the names of all loaded mods", SQ_GetModNames);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "bool", "NSIsModEnabled", "string modName", "Returns whether a given mod is enabled", SQ_IsModEnabled);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "void", "NSSetModEnabled", "string modName, bool enabled", "Sets whether a given mod is enabled", SQ_SetModEnabled);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "string", "NSGetModDescriptionByModName", "string modName", "Returns a given mod's description", SQ_GetModDescription);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "string", "NSGetModVersionByModName", "string modName", "Returns a given mod's version", SQ_GetModVersion);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "string", "NSGetModDownloadLinkByModName", "string modName", "Returns a given mod's download link", SQ_GetModDownloadLink);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "bool",
        "NSIsModRequiredOnClient",
        "string modName",
        "Returns whether a given mod is required on connecting clients",
        SQ_IsModRequiredOnClient);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "int", "NSGetModLoadPriority", "string modName", "Returns a given mod's load priority", SQ_GetModLoadPriority);
    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration(
        "array<string>", "NSGetModConvarsByModName", "string modName", "Returns the names of all a given mod's cvars", SQ_GetModConvars);

    g_pSquirrel<ScriptContext::UI>->AddFuncRegistration("void", "NSReloadMods", "", "Reloads mods", SQ_ReloadMods);
}
