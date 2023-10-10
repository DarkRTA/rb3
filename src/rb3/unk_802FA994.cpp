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

extern "C" char* fn_802FAA10(char*, char*);
extern char lbl_809073C8[];

// fn_802FAA10
char* fn_802FAA10(char* arg0, char* arg1){
    char* ext;
    char* dir;

    if(arg1 == 0) arg1 = lbl_809073C8;
    dir = strrchr(arg0, '/');
    if ((dir != 0) || (dir = strrchr(arg0, '\\'), (dir != 0))) {
        strcpy(arg1, dir + 1);
    } 
    else strcpy(arg1, arg0);
    
    ext = strrchr(arg1, '.');
    if (ext != 0) {
        *ext = 0;
    }
    return arg1;
}

extern "C" char* fn_802FAAC0(char*);
extern char lbl_809074C8[];

// fn_802FAAC0
char* fn_802FAAC0(char* arg){
    char* dir = strrchr(arg, '/');
    if ((dir != 0) || (dir = strrchr(arg, '\\'), (dir != 0))) {
        strcpy(lbl_809074C8, dir + 1);
    } 
    else strcpy(lbl_809074C8, arg);
    return lbl_809074C8;
}