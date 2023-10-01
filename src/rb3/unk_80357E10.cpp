#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

int fn_80362A50(char* arg0, char* arg1, char* arg2, char* arg3){
    int var_r31;
    int temp_r31;
    char* temp_r3;
    char* var_r27;
    
    *arg3 = 0;
    var_r31 = 0;

    while(true){
        temp_r3 = strstr(arg0, arg1);
        if(temp_r3 == 0) break;
        temp_r31 = temp_r3 - arg0;
        strncat(arg3, arg0, temp_r31);
        strcat(arg3, arg2);
        arg0 = strlen(arg1) + (arg0 + temp_r31);
        var_r31 = 1;
    }
    
    strcat(arg3, arg0); 
    return var_r31;
}

char fn_80362AF4(char* arg0, char* arg1, int arg2){
    int var_r5_2;
    char temp_r0;
    char var_r5;
    char* var_r3;
    char* var_r4;

    var_r3 = arg0;
    var_r4 = arg1;
    var_r5_2 = arg2 - 1;

    while(*var_r4 != 0 && (var_r5_2 != 0)){
        temp_r0 = *var_r4++;
        *var_r3++ = temp_r0;
        var_r5_2 -= 1;
    }
    
    var_r5 = 0;
    *var_r3 = 0;
    if((var_r5_2 != 0) || (*var_r4 == 0)){
        var_r5 = 1;
    }
    return var_r5;
}