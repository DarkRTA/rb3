#include "std/string.h"
#include "unknown.hpp"
#include "string.hpp"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"

// fn_802FA190
void FileQualifiedFilename(String& s, const char* c){
    char lol[256];
    FileQualifiedFilename(lol, 0x100, c);
    s = lol;
}

extern "C" void FileNormalizePath(char*);
extern char fn_80018764(char);

// fn_802FA1D4
void FileNormalizePath(char* c){
    for(char* p = c; *p != 0; p++){
        if(*p == '\\') *p = '/';
        else *p = fn_80018764(*p);
    }
}

extern "C" char* fn_802FA848(char*, char*);
extern char lbl_809071C8[];

// fn_802FA848
char* fn_802FA848(char* arg1, char* arg2){
    char* p2;
    
    if(arg2 == 0) arg2 = lbl_809071C8;
    if(arg1 != 0){
        strcpy(arg2, arg1);
        p2 = arg2 + strlen(arg2);
        
        p2--;
        // while(*p2 != '\\'){
        //     p2--;
        //     if((p2 < arg2) || (*p2 == '/')) break;
        // }
        
        do {
            p2--;
            if((p2 < arg2) || (*p2 == '/')) break;
        } while(*p2 != '\\');
        
        if(arg2 >= p2){
            if((p2 != arg2) && (p2[-1] == ':')){
                p2[1] = '\0';
            }
            else {
                *p2 = '\0';
                return arg2;
            }
        }
    }
    *arg2 = '.';
    arg2[1] = '\0';
    return arg2;
}

extern "C" char* FileMakePath(char*, char*, char*);
extern char lbl_80852A60[]; // string table
extern char lbl_80906FC8[];

char* FileMakePath(char* c1, char* c2, char* c3){
    char* c3_ptr;
    char** c1_2;
    char sp88[256];
    char* sp8[32];
    bool is_slash;    
    char* var_r3;
    
    if(c3 == 0) c3 = lbl_80906FC8;
    
    if((c2 >= c3) && (c2 < (c3 + 4))){
        strcpy(sp88, c2);
        c2 = sp88;
    }
    else if((c1 >= c3) && (c1 < (c3 + 4))){
        strcpy(sp88, c1);
        c1 = sp88;
    }
    
    char c2_res_inner; 
    char* c2_res = FileGetDrive(c2);
    c2_res_inner = *c2_res;
    
    if(c2_res_inner != '\0'){
        c2 += strlen(c2_res) + 1;
    }
    if((*c2 == '/') || (*c2 == '\\') || (*c2 == '\0')){
        if(c2_res_inner != 0){
            sprintf(c3, lbl_80852A60 + 0x104, c2_res, c2);
            c3_ptr = c3 + strlen(c2_res) + 1;
        }
        else {
            char* c1_res = FileGetDrive(c1);
            if (*c1_res != 0) {
                sprintf(c3, lbl_80852A60 + 0x104, c1_res, c2);
                c3_ptr = c3 + strlen(c1_res) + 1;
            } 
            else {
                strcpy(c3, c2);
                c3_ptr = c3;
            }
        }
    }
    else {
        sprintf(c3, lbl_80852A60 + 0x10A, c1, c2);
        char* c1_res = FileGetDrive(c1);
        if (*c1_res != 0) {
            c3_ptr = c3 + strlen(c1_res) + 1;
        } else {
            c3_ptr = c3;
        }
    }
    
    FileNormalizePath(c3);
    c1_2 = sp8;
    is_slash = (*c3_ptr - '/') == 0;
    var_r3 = strtok(c3_ptr, lbl_80852A60 + 0x110);
    while(var_r3 != 0){
        if(*var_r3 != '.') *c1_2++ = var_r3;
        else if((var_r3[1] == '.') && (var_r3[2] == '\0')){
            if((c1_2 != sp8) && (*c1_2[-1] != '.')) c1_2--;
            else *c1_2++ = var_r3;
        }
        var_r3 = strtok((char*)0, lbl_80852A60 + 0x110);
    }
    if(c1_2 == sp8){
        if(is_slash) *c3_ptr++ = '/';
        else *c3_ptr++ = '.';
    }
    else {
        for(char** p = sp8; p != c1_2; p++){
            if ((p != sp8) || is_slash) {
                *c3_ptr++ = '/';
            }
            for(char* q = *p; *q != 0; q++, c3_ptr++){
                *c3_ptr = *q;
            }
        }
    }
    *c3_ptr = 0;
    return c3;
}