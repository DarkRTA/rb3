#include "utl/Str.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include "system/milo_types.h"

#include <ctype.h>
#include <string.h>

#include "decomp.h"

const unsigned int String::npos = -1;

char gEmpty = 0;

DECOMP_FORCEACTIVE(Str,
    __FILE__,
    "i < mCap + 1"
)

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
        dest = (void *)_MemOrPoolAlloc(arg + 1, FastPool);
        memcpy(dest, mStr, mCap + 1);
        *((char *)dest + arg) = 0;

        if (mCap != 0) {
            _MemOrPoolFree(mCap + 1, FastPool, (void*)mStr);
        }

        mCap = arg;
        mStr = (char *)dest;
    }
}

String::String(unsigned int arg, char charg) : mCap(0), mStr(&gEmpty) {
    reserve(arg);
    for(unsigned int i = 0; i < arg; i++) mStr[i] = charg;
    mStr[arg] = '\0';
}

String::~String(){
    if(mCap != 0)
        _MemOrPoolFree(mCap + 1, FastPool, (void*)mStr);
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
    MILO_ASSERT(i < mCap, 0xB6);
    return mStr[i];
}

char String::rindex(int i) const {
    MILO_ASSERT(i < 0 && uint(-i) <= mCap, 0xBC);
    return mStr[mCap + i];
}

char& String::rindex(int i) {
    MILO_ASSERT(i < 0 && uint(-i) <= mCap, 0xC2);
    return mStr[mCap + i];
}

bool String::operator!=(const char *str) const {
    if (str == 0)
        return true;
    else
        return strcmp(str, mStr);
}

bool String::operator!=(const String &str) const {
    return strcmp(str.mStr, mStr);
}

bool String::operator==(const char *str) const {
    if (str == 0)
        return false;
    else
        return strcmp(str, mStr) == 0;
}

bool String::operator==(const String &str) const {
    return strcmp(str.mStr, mStr) == 0;
}

bool String::operator<(const String &str) const {
    return (strcmp(mStr, str.mStr) < 0);
}

void String::resize(unsigned int arg) {
    reserve(arg);
    mStr[arg] = 0;
}

unsigned int String::find(char c, unsigned int pos) const {
    MILO_ASSERT(pos <= mCap, 0xF3);
    char* p = &mStr[pos];
    while((*p != '\0') && (*p != c)) p++;
    if(*p != '\0') return p - mStr;
    else return -1;
}

unsigned int String::find(char c) const {
    return find(c, 0);
}

unsigned int String::find(const char* c) const {
    return find(c, 0);
}

unsigned int String::find(const char* str, unsigned int pos) const {
    MILO_ASSERT(pos <= mCap, 0x10A);
    char* found = strstr(&mStr[pos], str);
    if(found != 0) return found - mStr;
    else return -1;
}

unsigned int String::find_first_of(const char* str, unsigned int pos) const {
    char *p1;
    char *p2;
    if(str == 0) return -1;
    MILO_ASSERT(pos <= mCap, 0x115);
    for(p1 = &mStr[pos]; *p1 != '\0'; p1++){
        for(p2 = (char*)str; *p2 != '\0'; p2++){
            if(*p1 == *p2) return p1 - mStr;
        }
    }
    return -1;
}

unsigned int String::find_last_of(char c) const {
    char* found = strrchr(mStr, c);
    if(found != 0) return found - mStr;
    else return -1;
}

unsigned int String::find_last_of(const char* str) const {
    if(str == 0) return -1;
    int a = -1;
    for(char* tmp = (char*)str; *tmp != '\0'; tmp++){
        int lastIdx = find_last_of(*tmp);
        if((lastIdx != -1U) && (lastIdx > a)) a = lastIdx;
    }
    return (a != -1) ? a : -1;
}

unsigned int String::rfind(const char* str) const {
    int rv;
    if(str == 0) return -1;
    else {
        rv = -1;
        for(char *p4 = (char*)str; *p4 != '\0'; p4++){
            int x = find_last_of(*p4);
            if(x == -1U) return -1;
            if(rv == -1) rv = x;
            else if(x != p4 - str + rv) return -1;
        }
    }
    if(rv == -1) return -1;
    else return rv;
}

bool String::contains(const char *str) const {
    int index = find(str, 0);
    return (index != -1);
}

int String::split(const char *token, std::vector<String>& subStrings) const {
    MILO_ASSERT(subStrings.empty(), 345);

    int lastIndex = 0;
    int splitIndex = find_first_of(token, 0);

    while (splitIndex != -1U) {
        if (splitIndex > lastIndex) {
            String split = substr(lastIndex, splitIndex - lastIndex);
            subStrings.push_back(split);
        }
        lastIndex = splitIndex + 1;
        splitIndex = find_first_of(token, lastIndex);
    }

    if (lastIndex < length()) {
        String split = substr(lastIndex, length() - lastIndex);
        subStrings.push_back(split);
    }

    return subStrings.size();
}

String String::substr(unsigned int pos) const {
    MILO_ASSERT(pos <= mCap, 0x183);
    return String(&mStr[pos]);
}

String String::substr(unsigned int pos, unsigned int len) const {
    MILO_ASSERT(pos <= mCap, 0x189);
    char buf[512];
    if (pos + len >= mCap) {
        return String(&mStr[pos]);
    } else {
        MILO_ASSERT(len < 512, 0x192);
        strncpy(buf, &mStr[pos], len);
        buf[len] = '\0';
        return String(buf);
    }
}

void String::ToLower(){
    char *p;
    for (p = mStr; *p != '\0'; p++) {
        *p = tolower(*p);
    }
}

void String::ToUpper(){
    char *p;
    for (p = mStr; *p != '\0'; p++) {
        *p = toupper(*p);
    }
}

void String::ReplaceAll(char old_char, char new_char) {
    char *p;
    for (p = mStr; *p != '\0'; p++) {
        if (*p == old_char)
            *p = new_char;
    }
}

void String::swap(String &s) {
    char *temp_text;
    unsigned int temp_len;

    temp_text = mStr;
    mStr = s.mStr;
    temp_len = mCap;
    mCap = s.mCap;
    s.mStr = temp_text;
    s.mCap = temp_len;
}

// replaces this->text with the contents of buffer, at this->text index length
// pos: the starting index of the text you want to replace
// length: how many chars you want the replacement to be
// buffer: the replacement chars
String& String::replace(unsigned int pos, unsigned int n, const char *buffer) {
    char *text_offsetted;
    char *var_r4;
    char *var_r5;
    unsigned int bufferLength, end;
    char *tmp = 0;
    char c;

    MILO_ASSERT(pos <= mCap, 0x1C2);

    end = pos + n;
    if (end > mCap) {
        n = mCap - pos;
    }

    bufferLength = strlen(buffer);
    if (bufferLength > n) {
        String str_tmp;
        str_tmp.reserve(bufferLength + (length() - n));
        strncpy(str_tmp.mStr, mStr, pos);
        strncpy(str_tmp.mStr + pos, buffer, bufferLength);
        strcpy(str_tmp.mStr + (bufferLength + pos), mStr + (n + pos));
        swap(str_tmp);
    } else {
        strncpy(mStr + pos, buffer, bufferLength);
        text_offsetted = mStr + pos;
        var_r4 = text_offsetted + bufferLength;
        var_r5 = text_offsetted + n;
        while (*var_r5 != '\0') {
            c = *var_r5++;
            *var_r4++ = c;
        }
        *var_r4 = *var_r5;
    }

    return *this;
}

String& String::erase(){
    mStr[0] = '\0';
    return *this;
}

String& String::erase(unsigned int idx){
    if(idx >= mCap) return *this;
    mStr[idx] = '\0';
    return *this;
}

String& String::erase(unsigned int start, unsigned int len){
    return replace(start, len, "");
}

DECOMP_FORCEACTIVE(Str,
    "strlen( format ) < 30",
    "out",
    "in",
    "len > 0",
    "allowed"
)

// inserts the char c into this->text at index pos, cnt times
String& String::insert(unsigned int pos, unsigned int cnt, char c){
    MILO_ASSERT(pos <= mCap, 0x1FC);
    String sp8;
    char *temp_r0;
    char *var_r4;
    unsigned int var_ctr;

    sp8.reserve(cnt + length());
    strncpy(sp8.mStr, mStr, pos);
    for (int i = 0; i < cnt; i++) {
        sp8.mStr[pos + i] = c;
    }
    strcpy(&sp8.mStr[cnt + pos], &mStr[pos]);
    swap(sp8);
    return *this;
}

String& String::insert(unsigned int ui, const char* str){
    return replace(ui, 0, str);
}

String& String::insert(unsigned int ui, const String& str){
    return replace(ui, 0, str.c_str());
}

// searches for occurrences of substring substr_old within string src, and replaces each
// occurrence with substr_new. the result goes in dest. if a change was made, this fn
// returns true. if no changes to the original string were made, return false
bool SearchReplace(
    const char *src, const char *substr_old, const char *substr_new, char *dest
) {
    bool changed;
    int temp_r31;
    char *temp_r3;

    *dest = 0;
    changed = false;

    while (true) {
        temp_r3 = strstr(src, substr_old);
        if (temp_r3 == 0)
            break;
        temp_r31 = temp_r3 - src;
        strncat(dest, src, temp_r31);
        strcat(dest, substr_new);
        src = strlen(substr_old) + (src + temp_r31);
        changed = true;
    }

    strcat(dest, src);
    return changed;
}

// sorta like strncpy, except for the return value
// returns true if the copy operation was terminated because of reaching the maximum
// length or encountering the end of src, and 0 otherwise.
bool StrNCopy(char *dest, const char *src, int n) {
    MILO_ASSERT(n, 0x278);

    for(n = n - 1; *src != '\0' && n != 0; n--){
        *dest++ = *src++;
    }
    *dest = '\0';

    return (n != 0 || *src == '\0');
}
