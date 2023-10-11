#include "std/string.h"
#include "unknown.hpp"

extern "C" char* FileGetDrive(char*);
extern char lbl_809072C8[];

// fn_802FA994
char* FileGetDrive(char* c){
    char* p1 = strchr(c, ':');
    if(p1 != 0){
        strncpy(lbl_809072C8, c, p1 - c);
        lbl_809072C8[p1 - c] = '\0';
    }
    else lbl_809072C8[0] = '\0';
    return lbl_809072C8;
}

extern "C" char* FileGetBase(char*, char*);
extern char lbl_809073C8[];

// fn_802FAA10
char* FileGetBase(char* fname, char* base){
    char* ext;
    char* dir;

    if(base == 0) base = lbl_809073C8;
    dir = strrchr(fname, '/');
    if ((dir != 0) || (dir = strrchr(fname, '\\'), (dir != 0))) {
        strcpy(base, dir + 1);
    } 
    else strcpy(base, fname);
    
    ext = strrchr(base, '.');
    if (ext != 0) {
        *ext = 0;
    }
    return base;
}

extern "C" char* FileGetName(char*);
extern char lbl_809074C8[];

// fn_802FAAC0
char* FileGetName(char* arg){
    char* dir = strrchr(arg, '/');
    if ((dir != 0) || (dir = strrchr(arg, '\\'), (dir != 0))) {
        strcpy(lbl_809074C8, dir + 1);
    } 
    else strcpy(lbl_809074C8, arg);
    return lbl_809074C8;
}

extern "C" bool FileMatch(const char*, const char*);

// fn_802FAE68
bool FileMatchInternal(const char* arg0, const char* arg1, bool arg2){
    for(; *arg0 != 0; arg0++){
        if(FileMatch(arg0, arg1)) return true;
        if(!arg2 && (*arg0 == '/' || *arg0 == '\\'))  return false;
    }
    return (*arg1 == *arg0);
}

// fn_802FAF0C
bool FileMatch(const char* param1, const char* param2){
    if(param2 == 0) return false;
    while(*param2 != '\0') {
        if(*param2 == '*') return FileMatchInternal(param1, param2 + 1, 0);
        if(*param2 == '&') return FileMatchInternal(param1, param2 + 1, 1);
        if(*param1 == '\0') break;
        if(*param2 == '?'){
            if((*param1 == '\\') || (*param1 == '/')) return 0;
        }
        else if((*param2 == '/') || (*param2 == '\\')){
            if((*param1 != '/') && (*param1 != '\\')) return 0;
        }
        else if(*param2 != *param1) return 0;
        param2++;
        param1++;
    }
    return (*param2 - *param1) == 0;
}