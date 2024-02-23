#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "os/Timer.h"

const char* gNullStr = "";

static Symbol gSystemLanguage;
static DataArray* gSystemConfig;
static DataArray* gSystemTitles;
static int gUsingCD;
static GfxMode gGfxMode;
static int gSystemMs;
static float gSystemFrac;
static Timer gSystemTimer;
bool gHostConfig;
bool gHostLogging;

GfxMode GetGfxMode(){ return gGfxMode; }

DataNode OnSystemLanguage(DataArray* da){
    return DataNode(gSystemLanguage);
}

DataNode OnUsingCD(DataArray* da){
    return DataNode(UsingCD());
}

DataNode OnSupportedLanguages(DataArray* da){
    return DataNode(SupportedLanguages(false), kDataArray);
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
