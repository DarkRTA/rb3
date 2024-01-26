#include "system.hpp"

extern DataArray* gSystemConfig;

int gUsingCD;
Symbol gSystemLanguage;

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