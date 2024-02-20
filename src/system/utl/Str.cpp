#include "utl/Str.h"
#include "os/Debug.h"
#include "system/milo_types.h"

extern void* _MemOrPoolAlloc(int, int);
extern void _MemOrPoolFree(int, int, void*);

char gEmpty = 0;
const char* fname = "Str.cpp";
const char* unusedAssert = "i < mCap + 1";

String::String() : mCap(0), mStr(&gEmpty) {}

String::String(const char* str) : mCap(0), mStr(&gEmpty) {
    *this = str;
}

String::String(Symbol s) : mCap(0), mStr(&gEmpty) {
    *this = s.mStr;
}

String::String(const String& str) : mCap(0), mStr(&gEmpty) {
    *this = str.c_str();
}

// rk wanted to call this MemmyUppies but i had to put a stop to it
// -- dark
void String::reserve(unsigned int arg) {
    void *dest;
    if (arg > mCap) {
        dest = (void *)_MemOrPoolAlloc(arg + 1, 1);
        memcpy(dest, mStr, mCap + 1);
        *((char *)dest + arg) = 0;

        if (mCap != 0) {
            _MemOrPoolFree(mCap + 1, 1, (void*)mStr);
        }

        mCap = arg;
        mStr = (char *)dest;
    }
}

String::String(unsigned int arg, char charg) : mCap(0), mStr(&gEmpty) {
    reserve(arg);
    for(int i = 0; i < arg; i++) mStr[i] = charg;
    mStr[arg] = '\0';
}

String::~String(){
    if(mCap != 0)
        _MemOrPoolFree(mCap + 1, 1, (void*)mStr);
}

void String::Print(const char* c){
    *this += c;
}

String String::operator+(const char *chrstr) const {
    String ret(*this);
    ret += chrstr;
    return ret;
}

String String::operator+(char c) const {
    String ret(*this);
    ret += c;
    return ret;
}

String String::operator+(const String& str) const {
    String ret(*this);
    ret += str.c_str();
    return ret;
}

String& String::operator+=(const char* str){
    if(str == 0 || *str == '\0') return *this;
    int len = length();
    reserve(len + strlen(str));
    strcpy(&mStr[len], str);
    return *this;
}

String& String::operator+=(Symbol s){
    return *this += s.mStr;
}

String& String::operator+=(const String& str){
    return *this += str.c_str();
}

String& String::operator+=(char c){
    int len = length();
    reserve(len + 1);
    mStr[len] = c;
    mStr[len + 1] = '\0';
    return *this;
}

String& String::operator=(const char* str){
    if(str == mStr) return *this;
    if(str == 0 || *str == '\0'){
        resize(0);
    }
    else {
        reserve(strlen(str));
        strcpy(mStr, str);
    }
    return *this;
}

String& String::operator=(Symbol s){
    return *this = s.mStr;
}

String& String::operator=(const String& str){
    reserve(str.mCap);
    strcpy(mStr, str.c_str());
    return *this;
}

char& String::operator[](unsigned int i){
    ASSERT(i < mCap, 0xB6);
    return mStr[i];
}

char String::rindex(int i) const {
    ASSERT(i < 0 && uint(-i) <= mCap, 0xBC);
    return mStr[mCap + i];
}

char& String::rindex(int i) {
    ASSERT(i < 0 && uint(-i) <= mCap, 0xC2);
    return mStr[mCap + i];
}
