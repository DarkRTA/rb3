#include "os/MapFile_Wii.h"
#include "os/Debug.h"
#include <string.h>
#include <stdlib.h>
#include "utl/Str.h"

bool HasMoreParams(String str){
    unsigned int len = strlen(str.c_str());
    if(len != 0){
        if((str[0] <= '`' || str[0] >= '{') && (str[0] != 'P') && (str[0] != 'R') && (str[0] != 'U') && (str[0] != 'Q') && (str[0] != 'C')){
            return IsAsciiNum(str[0]);
        }
        return true;
    }
    return false;
}

int GetVarLength(String& str){
    int len = 0;
    if(IsAsciiNum(str[1])){
        len = atoi(str.substr(0, 2).c_str());
        str = str.substr(2, strlen(str.c_str()));
    }
    else {
        len = atoi(str.substr(0, 1).c_str());
        str = str.substr(1, strlen(str.c_str()));
    }
    return len;
}

// tabling this for now, see: https://decomp.me/scratch/Ry4am
void AddParams(String& s1, String& s2, String s3){
    switch(s1[0]){
        case 'Q': // 0x51
            s1 = s1.substr(1, strlen(s1.c_str()));
            int len = atoi(s1.substr(0, 1).c_str());
            s1 = s1.substr(1, strlen(s1.c_str()));
            
            for(int i = 0; i < len; i++){
                int outerlen;
                if(IsAsciiNum(s1[1])){
                    if(IsAsciiNum(s1[2])){
                        outerlen = atoi(s1.substr(0, 3).c_str());
                        s1 = s1.substr(3, strlen(s1.c_str()));
                    }
                    else {
                        if(1 < strlen(s1.c_str())){
                            outerlen = atoi(s1.substr(0, 2).c_str());
                            s1 = s1.substr(2, strlen(s1.c_str()));
                        }
                    }
                }
                else {
                    outerlen = atoi(s1.substr(0, 1).c_str());
                    s1 = s1.substr(1, strlen(s1.c_str()));
                }

                unsigned int findlt = s1.substr(0, outerlen).find("<");

                if(findlt == String::npos){
                    unsigned int s1len = strlen(s1.c_str());
                    if(outerlen <= s1len){
                        s2 = s2 + "::" + s1.substr(0, s1len);
                        s1 = s1.substr(outerlen, s1len);
                    }
                }
                else {
                    String comma_substr = s1.substr(0, outerlen);
                    unsigned int findcomma = comma_substr.find(",");
                    s1 = s1.substr(strlen(comma_substr.c_str()), strlen(s1.c_str()));
                    while(findcomma != String::npos){
                        comma_substr.erase(findcomma, 1);
                        findcomma = comma_substr.find(",");
                    }
                    unsigned int comma_substr_find_lt = comma_substr.find("<");

//         iVar4 = String::find(aSStack_44,@stringBase0);
//         String::substr(&SStack_d4,aSStack_44,0,iVar4 + 1);
//         String::operator_+(&SStack_e0,param_2);
//         String::operator_=((String *)param_2,(String *)&SStack_e0);
//         String::~String(&SStack_e0);
//         String::~String(&SStack_d4);
//         sVar8 = strlen(aSStack_44[0].mStr);
//         iVar4 = String::find(aSStack_44,@stringBase0);
//         String::substr(&SStack_ec,aSStack_44,iVar4 + 1,sVar8);
//         String::operator_=(aSStack_44,(String *)&SStack_ec);
//         String::~String(&SStack_ec);
//         while( true ) {
//           String::String(&SStack_104,(String *)aSStack_44);
//           iVar4 = HasMoreParams((String)((char)SVar1 + -0x34));
//           String::~String(&SStack_104);
//           if (iVar4 == 0) break;
//           String::String(&SStack_f8,s__80bb4734);
//           AddParams((String *)aSStack_44,param_2,(String)((char)SVar1 + -0x28));
//           String::~String(&SStack_f8);
//         }

//         pcVar7 = *(char **)(param_2 + 8);
//         sVar8 = strlen(pcVar7);
//         sVar6 = strlen(pcVar7);
//         String::substr(&SStack_110,(String *)param_2,sVar6 - 2,sVar8);
//         iVar4 = String::operator_==(&SStack_110,s_,_80bb4735);
//         String::~String(&SStack_110);
//         if (iVar4 != 0) {
//           sVar8 = strlen(*(char **)(param_2 + 8));
//           String::substr(&SStack_11c,(String *)param_2,0,sVar8 - 2);
//           String::operator_=((String *)param_2,(String *)&SStack_11c);
//           String::~String(&SStack_11c);
//         }
//         String::operator_+(&SStack_128,param_2);
//         String::operator_+(&SStack_134,(String *)&SStack_128);
//         String::operator_=((String *)param_2,(String *)&SStack_134);
//         String::~String(&SStack_134);
//         String::~String(&SStack_128);
//         String::~String(aSStack_44);

                }

            }

            if(s2.substr(strlen(s2.c_str() - 2), strlen(s2.c_str())) == "::"){
                s2 = s2.substr(0, strlen(s2.c_str()) - 2);
            }
            s2 = s2 + s2;

            break;
        case 'P': // 0x50
            s3 = s3 + "*";
            s1 = s1.substr(1, strlen(s1.c_str()));
            AddParams(s1, s2, String(s3));
            break;
        case 'R': // 0x52
            s3 = s3 + "&";
            s1 = s1.substr(1, strlen(s1.c_str()));
            AddParams(s1, s2, String(s3));
            break;
        case 'C': // 0x43
            s2 = s2 + "const" + s3 + " ";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 'U': // 0x55
            s2 = s2 + "unsigned" + s3 + " ";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 'v': // 0x76
            if(s3.c_str() != 0){
                s2 = s2 + "void" + s3 + ",";
            }
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 'i': // 0x69
            s2 = s2 + "int" + s3 + ",";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 'c': // 0x63
            s2 = s2 + "char" + s3 + ",";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 'b': // 0x62
            s2 = s2 + "bool" + s3 + ",";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 'f': // 0x66
            s2 = s2 + "float" + s3 + ",";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        
        case 'l': // 0x6C
            s2 = s2 + "long" + s3 + ",";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        case 's': // 0x73
            s2 = s2 + "short" + s3 + ",";
            s1 = s1.substr(1, strlen(s1.c_str()));
            break;
        
        case 'D': // 0x44
            break;
        default:
            if(IsAsciiNum(s1[0])){
                s2 = s2 + "," + s2 + s1.substr(0, GetVarLength(s1));
            }
            else {
                TheDebug << MakeString(" PI NMB DEBUG: UNEXPECTED CHARACTER '%c'\n", s1[0]);
                s1 = s1.substr(1, strlen(s1.c_str()));
            }
            break;
    }
}
