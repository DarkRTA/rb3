#include "System.h"

#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/DataFunc.h"
#include "obj/DataUtl.h"
#include "os/Archive.h"
#include "os/Debug.h"
#include "os/File_Wii.h"
#include "os/HolmesClient.h"
#include "os/PlatformMgr.h"
#include "os/Timer.h"
#include "utl/Loader.h"
#include "utl/Option.h"
#include "utl/Symbols.h"

#include <vector>

// includes for SystemTerminate
#include "math/Trig.h"
#include "os/AppChild.h"
#include "os/Keyboard.h"
#include "os/VirtualKeyboard.h"
#include "utl/Locale.h"
#include "utl/Spew.h"

const char* gNullStr = "";

Symbol gSystemLanguage;
DataArray* gSystemConfig;
DataArray* gSystemTitles;

int gUsingCD;
GfxMode gGfxMode;

int gSystemMs;
float gSystemFrac;
Timer gSystemTimer;
bool gNetUseTimedSleep;

std::vector<char*> TheSystemArgs;
const char* gHostFile;

unsigned char* g_pRSOReserveBuf;
unsigned char* g_pDefaultRSOBuf;

namespace {
    bool gHasPreconfig = true;
    bool gPreconfigOverride;

    bool CheckForArchive() {
        SetUsingCD(true);

        FileStat stat;
        if (FileGetStat(MakeString("gen/main_%s.hdr", PlatformSymbol(TheLoadMgr.GetPlatform())), &stat) < 0) {
            SetUsingCD(false);
        }
    }
}

bool gHostConfig;
bool gHostLogging;
bool gHostCached;

void SetGfxMode(GfxMode mode) {
    gGfxMode = mode;
    HolmesClientReInit();
    DataVariable("gfx_mode") = DataNode((int)mode);
}

GfxMode GetGfxMode(){ return gGfxMode; }

DataNode OnSystemLanguage(DataArray* da){
    return DataNode(gSystemLanguage);
}

DataNode OnSystemExec(DataArray* da){
    return DataNode(SystemExec(da->Str(1)));
}

DataNode OnUsingCD(DataArray* da){
    return DataNode(gUsingCD != 0);
}

DataNode OnSupportedLanguages(DataArray* da){
    return DataNode(SupportedLanguages(false), kDataArray);
}

DataNode OnSystemMs(DataArray* da){
    return DataNode(SystemMs());
}

DataNode OnSwitchSystemLanguage(DataArray* da){
    DataArray* languages = SupportedLanguages(true);

    int i;
    for (i = 0; i < languages->Size(); i++) {
        if (gSystemLanguage == languages->Sym(i)) {
            break;
        }
    }

    i = (i + 1) % languages->Size();
    SetSystemLanguage(languages->Sym(i), true);
    return DataNode(1);
}

void LanguageInit() {
    if (ThePlatformMgr.GetRegion() == kRegionNone) {
        MILO_WARN("LanguageInit called, but region has not been initialized");
    }

    // TODO: SystemConfig inlines here; retail confirms its usage
    DataArray* languageConfig = SystemConfig("system", "language");
    Symbol language = GetSystemLanguage("eng");

    DataArray* remap = languageConfig->FindArray("remap", false);
    if (remap != NULL) {
        remap->FindData(language, language, false);
    }

    Symbol force;
    if (languageConfig->FindData("force", force, false) && force != "") {
        language = force;
    }

    const char* languageOption = OptionStr("lang", NULL);
    if (languageOption != NULL) {
        language = languageOption;
    }

    languageOption = OptionStr("language", NULL);
    if (languageOption != NULL) {
        language = languageOption;
    }

    SetSystemLanguage(language, false);
}

Symbol PlatformSymbol(Platform pform){
    static Symbol sym[6] = {
        gNullStr, gNullStr, "xbox", "pc", "ps3", "wii"
    };
    return sym[pform];
}

bool PlatformLittleEndian(Platform p){
    MILO_ASSERT(p != kPlatformNone, 0x135);
    bool ret = false;
    if(p == kPlatformPC || p == kPlatformNone) ret = true;
    return ret;
}

Platform ConsolePlatform(){ return kPlatformWii; }

bool gReadingSystemConfig;

DataArray* ReadSystemConfig(const char* path) {
    gReadingSystemConfig = true;
    DataArray* config = DataReadFile(path, true);
    gReadingSystemConfig = false;
    return config;
}

void InitSystem(const char*);

void PreInitSystem(const char* path) {
    Archive* archive = TheArchive;
    bool usingCD = gUsingCD != 0;

    if (gHostConfig) {
        SetUsingCD(false);
        TheArchive = NULL;
    }

    DataArrayPtr root(1);

    DataSetMacro("HX_WII", root.mData);
    const char* macro;
    while ((macro = OptionStr("define", NULL)) != NULL) {
        DataSetMacro(macro, root.mData);
    }

    const char* config = OptionStr("config", NULL);
    if (config != NULL && !gHasPreconfig) {
        path = config;
    }

    BeginDataRead();
    gSystemConfig = ReadSystemConfig(path);
    MILO_ASSERT(gSystemConfig, 0x1AC);
    DataVariable("syscfg") = DataNode(gSystemConfig, kDataArray);

    DataArray* mem = gSystemConfig->FindArray("mem", true);

    SetUsingCD(usingCD);
    TheArchive = archive;

    DataRegisterFunc("system_language", OnSystemLanguage);
    DataRegisterFunc("system_exec", OnSystemExec);
    DataRegisterFunc("using_cd", OnUsingCD);
    DataRegisterFunc("supported_languages", OnSupportedLanguages);
    DataRegisterFunc("switch_system_language", OnSwitchSystemLanguage);
    DataRegisterFunc("system_ms", OnSystemMs);

    ThePlatformMgr.mEnableSFX = OptionBool("disable_sfx", false) == 0;
    SetGfxMode(kOldGfx);

    if (config != NULL && gHasPreconfig) {
        InitSystem(config);
        gPreconfigOverride = true;
    }
}

void StripEditorData(){
    Symbol editor("editor");
    Symbol types("types");
    DataArray* objectsCfg = SystemConfig("objects");
    for(int i = 1; i < objectsCfg->Size(); i++){
        DataArray* objectsArr = objectsCfg->Array(i);
        DataArray* objEditorArr = objectsArr->FindArray(editor, false);
        if(objEditorArr != 0) objEditorArr->Resize(1);
        DataArray* typesArr = objectsArr->FindArray(types, false);
        if(typesArr != 0){
            for(int j = 1; j < typesArr->Size(); j++){
                DataArray* typesEditorArr = typesArr->Array(j)->FindArray(editor, false);
                if(typesEditorArr != 0) typesEditorArr->Resize(1);
            }
        }
    }
}

void InitSystem(const char* path) {
    if (!gPreconfigOverride && path != NULL) {
        Archive* archive = TheArchive;
        bool usingCD = gUsingCD != 0;

        if (gHostConfig) {
            SetUsingCD(false);
            TheArchive = NULL;
        }

        DataArray* systemConfig = ReadSystemConfig(path);
        MILO_ASSERT(systemConfig, 0x22C);
        DataMergeTags(systemConfig, gSystemConfig);
        DataReplaceTags(systemConfig, gSystemConfig);
        gSystemConfig->Release();
        gSystemConfig = systemConfig;
        DataVariable("syscfg") = DataNode(gSystemConfig, kDataArray);

        SetUsingCD(usingCD);
        TheArchive = archive;
        StripEditorData();
    }

    // why is this split between here and PreInitSystem lol
    FinishDataRead();
}

void SystemTerminate() {
    TheDebug.RemoveExitCallback(SystemTerminate);
    TheVirtualKeyboard.Terminate();
    // CacheMgrTerminate();
    // NetCacheMgrTerminate();
    // FileCache::Terminate();
    TheLocale.Terminate();
    // TheMC.Terminate();
    // CheatsTerminate();
    KeyboardTerminate();
    // JoypadTerminate();
    SpewTerminate();
    // ThreadCallTerminate();
    // TheTaskMgr.Terminate();
    // ObjectDir::Terminate();
    // TheContentMgr.Terminate();
    TrigTableTerminate();
    // FileTerminate();
    gSystemConfig->Release();
    DataTerminate();
    Symbol::Terminate();
    // MemTerminate();
    AppChild::Terminate();
    TheSystemArgs.clear();
    TerminateMakeString();
}

int SystemMs() {
    gSystemTimer.Restart();
    float lastMs = gSystemTimer.GetLastMs();
    int ms = gSystemFrac + lastMs;
    gSystemFrac = (gSystemFrac + lastMs) - ms;
    gSystemMs += ms;
    return gSystemMs;
}

bool UsingCD(){
    return gUsingCD != 0;
}

void SetUsingCD(bool b){
    gUsingCD = b;
}

DataArray* SystemConfig(){
    return gSystemConfig;
}

DataArray* SystemConfig(Symbol s){
    return gSystemConfig->FindArray(s, true);
}

DataArray* SystemConfig(Symbol s1, Symbol s2){
    return gSystemConfig->FindArray(s1, true)->FindArray(s2, true);
}

DataArray* SystemConfig(Symbol s1, Symbol s2, Symbol s3){
    return gSystemConfig->FindArray(s1, true)->FindArray(s2, true)->FindArray(s3, true);
}

DataArray* SystemConfig(Symbol s1, Symbol s2, Symbol s3, Symbol s4){
    return gSystemConfig->FindArray(s1, true)->FindArray(s2, true)->FindArray(s3, true)->FindArray(s4, true);
}

DataArray* SystemConfig(Symbol s1, Symbol s2, Symbol s3, Symbol s4, Symbol s5){
    return gSystemConfig->FindArray(s1, true)->FindArray(s2, true)->FindArray(s3, true)->FindArray(s4, true)->FindArray(s5, true);
}

Symbol SystemLanguage(){
    return gSystemLanguage;
}

DataArray* SupportedLanguages(bool b){
    static Symbol system("system");
    return SystemConfig(system, language, b ? cheat_supported : supported)->Array(1);
}

bool IsSupportedLanguage(Symbol s, bool b){
    DataArray* languages = SupportedLanguages(b);
    for(int i = 0; i < languages->Size(); i++){
        if(languages->Sym(i) == s) return true;
    }
    return false;
}
