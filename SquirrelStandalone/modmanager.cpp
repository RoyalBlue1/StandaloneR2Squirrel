#define RAPIDJSON_NOMEMBERITERATORCLASS // need this for rapidjson
#define NOMINMAX // this too
#define _WINSOCK_DEPRECATED_NO_WARNINGS // temp because i'm very lazy and want to use inet_addr, remove later
#define RAPIDJSON_HAS_STDSTRING 1

#include "modmanager.h"
#include "filesystem.h"
#include "hook.h"

#include "rapidjson/error/en.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "prefix.h"

ModManager* g_pModManager;

Mod::Mod(fs::path modDir, char* jsonBuf)
{
    m_bWasReadSuccessfully = false;

    m_ModDirectory = modDir;

    rapidjson::Document modJson;
    modJson.Parse<rapidjson::ParseFlag::kParseCommentsFlag | rapidjson::ParseFlag::kParseTrailingCommasFlag>(jsonBuf);

    // fail if parse error
    if (modJson.HasParseError())
    {
        spdlog::info("error reading mod {}", modDir.string());
        return;
    }

    // fail if it's not a json obj (could be an array, string, etc)
    if (!modJson.IsObject())
    {
        spdlog::info("Failed reading mod file {}: file is not a JSON object", (modDir / "mod.json").string());
        return;
    }

    // basic mod info
    // name is required
    if (!modJson.HasMember("Name"))
    {
        spdlog::info("Failed reading mod file {}: missing required member \"Name\"", (modDir / "mod.json").string());
        return;
    }

    Name = modJson["Name"].GetString();

    if (modJson.HasMember("Description"))
        Description = modJson["Description"].GetString();
    else
        Description = "";

    if (modJson.HasMember("Version"))
        Version = modJson["Version"].GetString();
    else
    {
        Version = "0.0.0";
        spdlog::info("Mod file {} is missing a version, consider adding a version", (modDir / "mod.json").string());
    }

    if (modJson.HasMember("DownloadLink"))
        DownloadLink = modJson["DownloadLink"].GetString();
    else
        DownloadLink = "";

    if (modJson.HasMember("RequiredOnClient"))
        RequiredOnClient = modJson["RequiredOnClient"].GetBool();
    else
        RequiredOnClient = false;

    if (modJson.HasMember("LoadPriority"))
        LoadPriority = modJson["LoadPriority"].GetInt();
    else
    {
        spdlog::info("Mod file {} is missing a LoadPriority, consider adding one", (modDir / "mod.json").string());
        LoadPriority = 0;
    }

    // mod scripts
    if (modJson.HasMember("Scripts") && modJson["Scripts"].IsArray())
    {
        for (auto& scriptObj : modJson["Scripts"].GetArray())
        {
            if (!scriptObj.IsObject() || !scriptObj.HasMember("Path") || !scriptObj.HasMember("RunOn"))
                continue;

            ModScript script;

            script.Path = scriptObj["Path"].GetString();
            script.RunOn = scriptObj["RunOn"].GetString();

            if (scriptObj.HasMember("ServerCallback") && scriptObj["ServerCallback"].IsObject())
            {
                ModScriptCallback callback;
                callback.Context = ScriptContext::SERVER;

                if (scriptObj["ServerCallback"].HasMember("Before") && scriptObj["ServerCallback"]["Before"].IsString())
                    callback.BeforeCallback = scriptObj["ServerCallback"]["Before"].GetString();

                if (scriptObj["ServerCallback"].HasMember("After") && scriptObj["ServerCallback"]["After"].IsString())
                    callback.AfterCallback = scriptObj["ServerCallback"]["After"].GetString();

                script.Callbacks.push_back(callback);
            }

            if (scriptObj.HasMember("ClientCallback") && scriptObj["ClientCallback"].IsObject())
            {
                ModScriptCallback callback;
                callback.Context = ScriptContext::CLIENT;

                if (scriptObj["ClientCallback"].HasMember("Before") && scriptObj["ClientCallback"]["Before"].IsString())
                    callback.BeforeCallback = scriptObj["ClientCallback"]["Before"].GetString();

                if (scriptObj["ClientCallback"].HasMember("After") && scriptObj["ClientCallback"]["After"].IsString())
                    callback.AfterCallback = scriptObj["ClientCallback"]["After"].GetString();

                script.Callbacks.push_back(callback);
            }

            if (scriptObj.HasMember("UICallback") && scriptObj["UICallback"].IsObject())
            {
                ModScriptCallback callback;
                callback.Context = ScriptContext::UI;

                if (scriptObj["UICallback"].HasMember("Before") && scriptObj["UICallback"]["Before"].IsString())
                    callback.BeforeCallback = scriptObj["UICallback"]["Before"].GetString();

                if (scriptObj["UICallback"].HasMember("After") && scriptObj["UICallback"]["After"].IsString())
                    callback.AfterCallback = scriptObj["UICallback"]["After"].GetString();

                script.Callbacks.push_back(callback);
            }

            Scripts.push_back(script);
        }
    }

    if (modJson.HasMember("Dependencies") && modJson["Dependencies"].IsObject())
    {
        for (auto v = modJson["Dependencies"].MemberBegin(); v != modJson["Dependencies"].MemberEnd(); v++)
        {
            if (!v->name.IsString() || !v->value.IsString())
                continue;

            //spdlog::info("Constant {} defined by {} for mod {}", v->name.GetString(), Name.c_str(), v->value.GetString());
            if (DependencyConstants.find(v->name.GetString()) != DependencyConstants.end() &&
                v->value.GetString() != DependencyConstants[v->name.GetString()])
            {
                spdlog::info("A dependency constant with the same name already exists for another mod. Change the constant name.");
                return;
            }

            if (DependencyConstants.find(v->name.GetString()) == DependencyConstants.end())
                DependencyConstants.emplace(v->name.GetString(), v->value.GetString());
        }
    }

    m_bWasReadSuccessfully = true;
}

ModManager::ModManager()
{
    // precaculated string hashes
    // note: use backslashes for these, since we use lexically_normal for file paths which uses them
    //m_hScriptsRsonHash = STR_HASH("scripts\\vscripts\\scripts.rson");
    //m_hPdefHash = STR_HASH(
        //  "cfg\\server\\persistent_player_data_version_231.pdef" // this can have multiple versions, but we use 231 so that's what we hash
        //);

    LoadMods();
}

void ModManager::LoadMods()
{
    if (m_bHasLoadedMods)
        UnloadMods();

    std::vector<fs::path> modDirs;

    // ensure dirs exist
    fs::remove_all(GetCompiledAssetsPath());
    fs::create_directories(GetModFolderPath());

    m_DependencyConstants.clear();

    // read enabled mods cfg
    std::ifstream enabledModsStream(GetFilePrefix() / fs::path("enabledmods.json"));
    std::stringstream enabledModsStringStream;

    if (!enabledModsStream.fail())
    {
        while (enabledModsStream.peek() != EOF)
            enabledModsStringStream << (char)enabledModsStream.get();

        enabledModsStream.close();
        m_EnabledModsCfg.Parse<rapidjson::ParseFlag::kParseCommentsFlag | rapidjson::ParseFlag::kParseTrailingCommasFlag>(
            enabledModsStringStream.str().c_str());

        m_bHasEnabledModsCfg = m_EnabledModsCfg.IsObject();
    }

    // get mod directories
    for (fs::directory_entry dir : fs::directory_iterator(GetModFolderPath()))
        if (fs::exists(dir.path() / "mod.json"))
            modDirs.push_back(dir.path());

    for (fs::path modDir : modDirs)
    {
        // read mod json file
        std::ifstream jsonStream(modDir / "mod.json");
        std::stringstream jsonStringStream;

        // fail if no mod json
        if (jsonStream.fail())
        {
            spdlog::info("Mod {} has a directory but no mod.json", modDir.string());
            continue;
        }

        while (jsonStream.peek() != EOF)
            jsonStringStream << (char)jsonStream.get();

        jsonStream.close();

        Mod mod(modDir, (char*)jsonStringStream.str().c_str());

        for (auto& pair : mod.DependencyConstants)
        {
            if (m_DependencyConstants.find(pair.first) != m_DependencyConstants.end() && m_DependencyConstants[pair.first] != pair.second)
            {
                spdlog::info("Constant {} in mod {} already exists in another mod.", pair.first, mod.Name);
                mod.m_bWasReadSuccessfully = false;
                break;
            }
            if (m_DependencyConstants.find(pair.first) == m_DependencyConstants.end())
                m_DependencyConstants.emplace(pair);
        }

        if (m_bHasEnabledModsCfg && m_EnabledModsCfg.HasMember(mod.Name.c_str()))
            mod.m_bEnabled = m_EnabledModsCfg[mod.Name.c_str()].IsTrue();
        else
            mod.m_bEnabled = true;

        if (mod.m_bWasReadSuccessfully)
        {
            /*printf("Loaded mod %s successfully\n", mod.Name.c_str());
            if (mod.m_bEnabled)
                printf("Mod %s is enabled\n", mod.Name.c_str());
            else
                printf("Mod %s is disabled\n", mod.Name.c_str());
            */
            m_LoadedMods.push_back(mod);
        }
        //else
        //    printf("Skipping loading mod file %s \n", (modDir / "mod.json").c_str());
    }

    // sort by load prio, lowest-highest
    std::sort(m_LoadedMods.begin(), m_LoadedMods.end(), [](Mod& a, Mod& b) { return a.LoadPriority < b.LoadPriority; });


    // in a seperate loop because we register mod files in reverse order, since mods loaded later should have their files prioritised
    for (int64_t i = m_LoadedMods.size() - 1; i > -1; i--)
    {
        if (!m_LoadedMods[i].m_bEnabled)
            continue;

        if (fs::exists(m_LoadedMods[i].m_ModDirectory / MOD_OVERRIDE_DIR))
        {
            for (fs::directory_entry file : fs::recursive_directory_iterator(m_LoadedMods[i].m_ModDirectory / MOD_OVERRIDE_DIR))
            {
                std::string path =
                    g_pModManager->NormaliseModFilePath(file.path().lexically_relative(m_LoadedMods[i].m_ModDirectory / MOD_OVERRIDE_DIR));
                if (file.is_regular_file() && m_ModFiles.find(path) == m_ModFiles.end())
                {
                    ModOverrideFile modFile;
                    modFile.m_pOwningMod = &m_LoadedMods[i];
                    modFile.m_Path = path;
                    m_ModFiles.insert(std::make_pair(path, modFile));
                    //printf("Mod Path %s\n", path.c_str());
                }
            }
        }
    }

    // build modinfo obj for masterserver
    rapidjson::Document modinfoDoc;
    modinfoDoc.SetObject();
    modinfoDoc.AddMember("Mods", rapidjson::Document::GenericValue(rapidjson::kArrayType), modinfoDoc.GetAllocator());

    int currentModIndex = 0;
    for (Mod& mod : m_LoadedMods)
    {
        if (!mod.m_bEnabled || (!mod.RequiredOnClient && !mod.Pdiff.size()))
            continue;

        modinfoDoc["Mods"].PushBack(rapidjson::Document::GenericValue(rapidjson::kObjectType), modinfoDoc.GetAllocator());
        modinfoDoc["Mods"][currentModIndex].AddMember("Name", rapidjson::StringRef(&mod.Name[0]), modinfoDoc.GetAllocator());
        modinfoDoc["Mods"][currentModIndex].AddMember("Version", rapidjson::StringRef(&mod.Version[0]), modinfoDoc.GetAllocator());
        modinfoDoc["Mods"][currentModIndex].AddMember("RequiredOnClient", mod.RequiredOnClient, modinfoDoc.GetAllocator());
        modinfoDoc["Mods"][currentModIndex].AddMember("Pdiff", rapidjson::StringRef(&mod.Pdiff[0]), modinfoDoc.GetAllocator());

        currentModIndex++;
    }

    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    modinfoDoc.Accept(writer);

    m_bHasLoadedMods = true;
}

void ModManager::UnloadMods()
{
    // clean up stuff from mods before we unload
    m_ModFiles.clear();
    fs::remove_all(GetCompiledAssetsPath());

 

    if (!m_bHasEnabledModsCfg)
        m_EnabledModsCfg.SetObject();

    for (Mod& mod : m_LoadedMods)
    {
        // remove all built kvs
        for (std::pair<size_t, std::string> kvPaths : mod.KeyValues)
            fs::remove(GetCompiledAssetsPath() / fs::path(kvPaths.second).lexically_relative(mod.m_ModDirectory));

        mod.KeyValues.clear();

        // write to m_enabledModsCfg
        // should we be doing this here or should scripts be doing this manually?
        // main issue with doing this here is when we reload mods for connecting to a server, we write enabled mods, which isn't necessarily
        // what we wanna do
        if (!m_EnabledModsCfg.HasMember(mod.Name.c_str()))
            m_EnabledModsCfg.AddMember(
                rapidjson::Document::StringRefType(mod.Name.c_str()),
                rapidjson::Document::GenericValue(false),
                m_EnabledModsCfg.GetAllocator());

        m_EnabledModsCfg[mod.Name.c_str()].SetBool(mod.m_bEnabled);
    }

    std::ofstream writeStream(GetFilePrefix() / "enabledmods.json");
    rapidjson::OStreamWrapper writeStreamWrapper(writeStream);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(writeStreamWrapper);
    m_EnabledModsCfg.Accept(writer);

    // do we need to dealloc individual entries in m_loadedMods? idk, rework
    m_LoadedMods.clear();
}

std::string ModManager::NormaliseModFilePath(const fs::path path)
{
    std::string str = path.lexically_normal().string();

    // force to lowercase
    for (char& c : str)
        if (c <= 'Z' && c >= 'A')
            c = c - ('Z' - 'z');

    return str;
}





fs::path GetModFolderPath()
{
    return fs::path(GetFilePrefix() / GetModFolder());
}
fs::path GetCompiledAssetsPath()
{
    return fs::path(GetFilePrefix() / COMPILED_ASSETS_SUFFIX);
}

ON_DLL_LOAD_RELIESON("engine.dll", ModManager, (ConCommand, MasterServer), (CModule module))
{
    g_pModManager = new ModManager;


}