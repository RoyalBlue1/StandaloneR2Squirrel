
#include "modmanager.h"

#include "filesystem.h"
#include "squirrel.h"

#include <fstream>

std::string ModManager::BuildScriptsRson()
{
    //printf("Building custom scripts.rson\n");


    std::string scriptsRson = g_filesystem->ReadFileToString(fs::path("scripts\\vscripts\\scripts.rson"));
    scriptsRson += "\n\n// START MODDED SCRIPT CONTENT\n\n"; // newline before we start custom stuff

    for (Mod& mod : m_LoadedMods)
    {
        if (!mod.m_bEnabled)
            continue;

        // this isn't needed at all, just nice to have imo
        scriptsRson += "// MOD: ";
        scriptsRson += mod.Name;
        scriptsRson += ":\n\n";

        for (ModScript& script : mod.Scripts)
        {
            /* should create something with this format for each script
            When: "CONTEXT"
            Scripts:
            [
                _coolscript.gnut
            ]*/

            scriptsRson += "When: \"";
            scriptsRson += script.RunOn;
            scriptsRson += "\"\n";

            scriptsRson += "Scripts:\n[\n\t";
            scriptsRson += script.Path;
            scriptsRson += "\n]\n\n";
        }
    }

    

    return scriptsRson;

    
    

    

    // todo: for preventing dupe scripts in scripts.rson, we could actually parse when conditions with the squirrel vm, just need a way to
    // get a result out of squirrelmanager.ExecuteCode this would probably be the best way to do this, imo
}
