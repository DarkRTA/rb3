#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

extern char lbl_808E4560;

String::String()
{
	len = 0;
	text = &lbl_808E4560;
}

String::String(const char *str)
{
	len = 0;
	text = &lbl_808E4560;
	*this = str;
}

String::String(const char** str){
    len = 0;
	text = &lbl_808E4560;
    *this = *str;
}

String::String(const String &str)
{
	len = 0;
	text = &lbl_808E4560;
	*this = str.GetText();
}

String::String(unsigned int arg, char charg){
    len = 0;
    text = &lbl_808E4560;
    Reserve(arg);

    for(int i = 0; i < arg; i++)
        text[i] = charg;

    text[arg] = '\0';
}

extern "C" void fn_80354878(int, int, char *);

String::~String()
{
	if (len != 0) {
		fn_80354878(len + 1, 1, text);
	}
}


String* String::operator=(const char* str){
    if(str == text){
        return this;
    }
    if(str == 0 || (*str == '\0')){
        fn_80362260(0);
    }
    else {
        Reserve(strlen(str));
        strcpy(text, str);
    }
    return this;
}

// returns false if strings are NOT different (matching)
// returns true if strings ARE different (non matching)
bool String::AreStringsDifferent(const char* str){
    if(str == nullptr) return true;
    else return strcmp(str, text);
}

bool String::AreStringsDifferent(const String* str){
    return strcmp(str->text, text);
}

// returns true if strings are NOT different (matching)
// returns false if strings ARE different (non matching)
bool String::AreStringsIdentical(const char* str){
    if(str == nullptr) return false;
    else return strcmp(str, text) == 0;
}

bool String::AreStringsIdentical(const String* str){
    return strcmp(str->text, text) == 0;
}

extern int fn_80354848(int, int);
extern void fn_80354878(int, int, char*);

// Redo this once you have fn_80354848 and fn_08354878 defined
// rk wanted to call this MemmyUppies but i had to put a stop to it
// -- dark
void String::Reserve(unsigned int arg){
    void* dest;
    if(arg > len){
        dest = (void*)fn_80354848(arg + 1, 1);
        memcpy(dest, text, len + 1);
        *((char*)dest + arg) = 0;

        if(len != 0){
            fn_80354878(len + 1, 1, text);
        }

        len = arg;
        text = (char*)dest;
    }
}

void String::fn_80361F88(String* str){
    const char* t = str->GetText();
    fn_80361F04(t);
}

void String::fn_80361FC4(char c){
    int iVar2 = GetTextLength();
    Reserve(iVar2 + 1);
    *(text + iVar2) = c;
    *(text + iVar2 + 1) = '\0';
}

// assigns char** to this String's text field
void String::fn_803620B4(char** str){
    this->operator=(*str);
}

// does strstr, and returns the index of where it begins
int String::FindIndexOfSubstring(const char* str, int idx){
    char* found = strstr(text + idx, str);
    if(found != nullptr){
        return found - text;
    }
    return -1;
}

int String::FindLastIndexOfChar(char charg){
    char* found = strrchr(text, charg);
    if(found != (char*)0){
        return found - text;
    }
    return -1;
}

static const size_t npos = -1;

// not fully matched! fix this
// also figure out exactly what this is supposed to do
int String::fn_803623E8(char* str){
    int a;
    int lastIndex;
    if(str == nullptr) return -1;
    else {
        a = -1;
        while(*str != '\0'){
            lastIndex = FindLastIndexOfChar(*str);
            if((lastIndex != npos) && (lastIndex > a)){
                a = lastIndex;
            }
            str++;
        }
        lastIndex = -1;
        if(a != -1){
            lastIndex = a;
        }
        return lastIndex;
    }
}

bool String::SubstrExistsInString(char* str){
    int index = FindIndexOfSubstring(str, 0) + 1;
    return (index != 0);
}

void String::ReplaceCharsInString(char old_char, char new_char){
    char* p;
    for(p = text; *p != '\0'; p++){
        if(*p == old_char)
            *p = new_char;
    }
}

void String::SwapStrings(String* s){
    char* temp_text;
    unsigned int temp_len;

    temp_text = text;
    text = s->text;
    temp_len = len;
    len = s->len;
    s->text = temp_text;
    s->len = temp_len;
}

// finds index of the first instance of char argument in string at an offset
int String::FindFirstIndexOfCharAtOffset(char charg, int idx){
    char* p = text + idx;

    while((*p != '\0') && (*p != charg)) p++;
    
    if(*p != '\0'){
        return p - text;
    }
    return -1;
}

extern char fn_80018764(char);

void String::ToLower()
{
	char c;
	char *p = text;

	while (*p != '\0') {
		c = fn_80018764(*p);
		*p = c;
		p++;
	}
}

extern char fn_80018734(char);

// rename this method once you figure out what fn_80018734 does
void String::fn_80362730(){
    char* p;
    for(p = text; *p != '\0'; p++){
        *p = fn_80018734(*p);
    }
}