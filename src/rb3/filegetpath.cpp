#include "file_ops.hpp"
#include "std/string.h"

extern char lbl_809071C8[];

// fn_802FA848
char* FileGetPath(char* arg1, char* arg2){
    char* p2;
    if(arg2 == 0) arg2 = lbl_809071C8;
    if(arg1 != 0){
        strcpy(arg2, arg1);
        p2 = arg2 + strlen(arg2);
        p2--;        
        while(p2 >= arg2 && *p2 != '/' && *p2 != '\\') {
            p2--;
        }
        if(p2 >= arg2){
            if((p2 == arg2) || (p2[-1] == ':')) p2[1] = '\0';
            else *p2 = '\0';
            return arg2;
        }
    }
    *arg2 = '.';
    arg2[1] = '\0';
    return arg2;
}