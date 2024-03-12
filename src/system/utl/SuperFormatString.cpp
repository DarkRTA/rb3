#include "utl/SuperFormatString.h"
#include "os/Debug.h"
#include <string.h>
#include "obj/Data.h"
#include "utl/Locale.h"
#include "utl/LocaleOrdinal.h"

#define BUF_SIZE 0x800

// https://decomp.me/scratch/yZLdj
SuperFormatString::SuperFormatString(const char* cc, const DataArray* da, bool b){
    char param[8];
    char tempFmt[2048];
    char phInfo[64];
    if(!da && !b) InitializeWithFmt(cc, true);
    else {
        int phType = 0;
        int i13 = 0;
        char* paramPos = param;
        char* phInfoPos = phInfo;
        char* baseTempFmt = tempFmt;
        char* tempFmtPos = tempFmt;
        for(const char* p = cc; *p != 0; p++){
            switch(i13){
                case 0:
                    if(*p == '{'){
                        if(cc[1] == '{'){
                            *tempFmtPos++ = '{';
                            cc++;
                        }
                        else i13 = 1;
                    }
                    else *tempFmtPos++ = *p;
                    break;
                case 1:
                    if(*p == ':'){
                        MILO_ASSERT(phInfoPos - phInfo < 64, 0x43);
                        *phInfoPos = '\0';
                        phInfoPos = phInfo;
                        i13 = 3;
                        bool phInfoCmp = strcmp(phInfoPos, "string") == 0;
                        if(phInfoCmp){
                            phType = 0;
                            continue;
                        }
                        phInfoCmp = strcmp(phInfoPos, "int") == 0;
                        if(phInfoCmp){
                            *paramPos++ = '%';
                            i13 = 2;
                            phType = 1;
                            continue;
                        }
                        phInfoCmp = strcmp(phInfoPos, "sep_int") == 0;
                        if(phInfoCmp){
                            phType = 2;
                            continue;
                        }
                        phInfoCmp = strcmp(phInfoPos, "float") == 0;
                        if(phInfoCmp){
                            *paramPos++ = '%';
                            phType = 3;
                            i13 = 2;
                            continue;
                        }
                        phInfoCmp = strcmp(phInfoPos, "token") == 0;
                        if(phInfoCmp){
                            phType = 4;
                            continue;
                        }
                        phInfoCmp = strcmp(phInfoPos, "ordinal") == 0;
                        if(phInfoCmp){
                            phType = 5;
                            i13 = 2;
                            continue;
                        }
                        MILO_FAIL("bad SuperFormatString placeholder type '%s'", phInfoPos);
                    }
                    else *phInfoPos++ = *p;
                    break;
                case 2:
                    if(*p == ':'){
                        if(phType == 3){
                            *paramPos++ = 'f';
                            *paramPos = '\0';
                        }
                        else if(phType == 1){
                            *paramPos++ = 'i';
                            *paramPos = '\0';
                        }
                        MILO_ASSERT(paramPos - param < 8, 0x78);
                        if (phType == 5) {
                            MILO_ASSERT(param + 2 == paramPos, 0x7E);
                        }
                        paramPos = param;
                        i13 = 3;
                    }
                    else *paramPos++ = *p;
                    break;
                case 3:
                    if(*p == '}'){
                        MILO_ASSERT(phInfoPos - phInfo < 64, 0x8C);
                        *phInfoPos = '\0';
                        phInfoPos = phInfo;
                        i13 = 0;
                        DataArray* theArr = 0;
                        bool isToken = phType == 4;
                        if(!b && !isToken){
                            theArr = da->FindArray(phInfoPos, false);
                        }
                        if(theArr || isToken) {
                            DataNode node((isToken) ? DataNode(0) : theArr->Evaluate(1));
                            bool node_bool = false;
                            switch(phType){
                                case 0:
                                    node_bool = (node.Type() != kDataString) && (node.Type() != kDataSymbol);
                                    break;
                                case 1: 
                                    node_bool = node.Type() != kDataInt;
                                    break;
                                case 2:
                                    node_bool = node.Type() != kDataInt;
                                    break;
                                case 3:
                                    node_bool = (node.Type() != kDataFloat) && (node.Type() != kDataInt);
                                    break;
                                case 4:
                                    node_bool = false;
                                    break;
                                case 5:
                                    node_bool = node.Type() != kDataInt;
                                    break;
                                default: break;
                            }

                            if(!node_bool){
                                int sn_res = 0; 
                                LocaleGender gender;
                                LocaleNumber  num;
                                int x;
                                switch(phType){
                                    case 0:
                                        if(node.Type() == kDataString){
                                            sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, "%s", node.Str(0));
                                        }
                                        else {
                                            sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, "%s", Localize(node.Sym(0), false));
                                        }
                                        break;
                                    case 1:
                                        sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, param, node.Int(0));
                                        break;
                                    case 2:
                                        sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, "%s", LocalizeSeparatedInt(node.Int(0)));
                                        break;
                                    case 3:
                                        sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, param, node.Float(0));
                                        break;
                                    case 4:
                                        sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, "%s", Localize(phInfo, false));
                                        break;
                                    case 5:
                                        gender = (LocaleGender)(param[0] != 'm');
                                        num = (LocaleNumber)(param[1] != 's'); 
                                        x = node.Int(0);
                                        sn_res = snprintf(tempFmtPos, baseTempFmt - tempFmtPos, "%s", 
                                            LocalizeOrdinal(x, 
                                                gender, 
                                                num, 
                                                false));
                                        break;
                                }

                                tempFmtPos += sn_res;
                                continue;
                            }
                            MILO_WARN("parameter for placeholder '%s' was the wrong type\n", phInfo);
                        }
                        else MILO_WARN("couldn't find parameter for placeholder '%s'\n", phInfo);
                        tempFmtPos += snprintf(tempFmtPos, baseTempFmt - tempFmtPos, "{missing:%s}", phInfo);
                    }
                    else *tempFmtPos++ = *p;
                    break;
                default:
                    break;
            }
        }

        if(i13 != 0){
            *phInfoPos = '\0';
            MILO_WARN("bad formatting for placeholder '%s'\n", phInfo);
            // I think this is wrong
            tempFmtPos += snprintf(tempFmtPos, tempFmt - tempFmtPos, "{badfmt:%s", phInfo);
        }
        *tempFmtPos = 0;
        MILO_ASSERT(tempFmtPos - tempFmt < BUF_SIZE, 0xF0);
        InitializeWithFmt(tempFmt, b == 0);
    }
}

const char* SuperFormatString::RawFmt() const {
    return mFmt;
}
