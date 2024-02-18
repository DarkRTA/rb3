#include "os/System.h"

#include "symbols.hpp"

extern int StubOne();

extern DataArray* gSystemConfig;
extern char* gNullStr;

int gUsingCD;
Symbol gSystemLanguage;

DataNode OnSystemLanguage(DataArray* da){
    return DataNode(gSystemLanguage);
}

DataNode OnSystemExec(DataArray* da){
    da->GetStrAtIndex(1);
    return DataNode(SystemExec());
}

DataNode OnUsingCD(DataArray* da){
    return DataNode(StubOne());
}

DataNode OnSupportedLanguages(DataArray* da){
    return DataNode(SupportedLanguages(false), kDataArray);
}

Symbol PlatformSymbol(Platform pform){
    static Symbol platforms[6] = {
        gNullStr, gNullStr, "xbox", "pc", "ps3", "wii"
    };
    return platforms[pform];
}

extern "C" void fn_8030E5BC();

// TODO: figure out what this fn actually does and then rename it accordingly
void fn_8030E5BC(){
    Symbol editor("editor");
    Symbol types("types");
    DataArray* objectsCfg = SystemConfig("objects");
    for(int i = 1; i < objectsCfg->GetNodeCount(); i++){
        DataArray* objectsArr = objectsCfg->GetArrayAtIndex(i);
        DataArray* objEditorArr = objectsArr->FindArray(editor, false);
        if(objEditorArr != 0) objEditorArr->Resize(1);
        DataArray* typesArr = objectsArr->FindArray(types, false);
        if(typesArr != 0){
            for(int j = 1; j < typesArr->GetNodeCount(); j++){
                DataArray* typesEditorArr = typesArr->GetArrayAtIndex(j)->FindArray(editor, false);
                if(typesEditorArr != 0) typesEditorArr->Resize(1);
            }
        }
    }
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
    static Symbol sys("system");
    return SystemConfig(sys, SymLanguage, b ? SymCheatSupported : SymSupported)->GetArrayAtIndex(1);
}

bool IsSupportedLanguage(Symbol s, bool b){
    DataArray* languages = SupportedLanguages(b);
    for(int i = 0; i < languages->GetNodeCount(); i++){
        if(languages->GetSymAtIndex(i) == s) return true;
    }
    return false;
}

int SystemExec(){
    return -1;
}
