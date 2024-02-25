#include "utl/LocaleOrdinal.h"
#include "utl/Str.h"
#include "utl/UTF8.h"
#include <string.h>
#include "os/System.h"
#include "utl/Locale.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "os/Debug.h"

const char* LocalizeOrdinal(int i, LocaleGender gender, LocaleNumber number, bool super){
    char buf[254];
    char code1, code2;
    
    strcpy(buf, LocalizeSeparatedInt(i));
    int len = strlen(buf);
    if(len != 0) code1 = buf[len - 1];
    else code1 = '0';
    if(len > 1) code2 = buf[len - 2];
    else code2 = '0';
    Symbol lang = SystemLanguage();
    if(!(lang == jpn)){
        if(lang == eng){
            if(super) strcat(buf, "<sup>");
            if(code1 == '1' && code2 != '1') strcat(buf, "st");
            else if(code1 == '2' && code2 != '1') strcat(buf, "nd");
            else if(code1 == '3' && code2 != '1') strcat(buf, "rd");
            else strcat(buf, "th");
            if(super) strcat(buf, "</sup>");
        }
        else if(lang == fre){
            if(super) strcat(buf, "<sup>");
            if(!strcmp(buf, "1")){
                if(gender == LocaleGenderMasculine) strcat(buf, "er");
                else strcat(buf, "re");
            }
            else strcat(buf, "e");
            if(super) strcat(buf, "</sup>");
        }
        else if(lang == deu) strcat(buf, ".");
        else if(lang == esl || lang == ita){
            String str;
            EncodeUTF8(str, 0xB0);
            if(gender == 0){
                if(number == 0) strcat(buf, str.c_str());
                else {
                    strcat(buf, str.c_str());
                    strcat(buf, "s");
                }
            }
            else if(number == 0) strcat(buf, str.c_str());
            else {
                strcat(buf, str.c_str());
                strcat(buf, "s");
            }
        }
        else {
            MILO_WARN("Localizing Ordinal for unsupported language %s", lang);
        }
    }
    return MakeString(buf);
}
