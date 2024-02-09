#include "Str.h"
#include "unknown.hpp"
#include "string.h"
#include "Symbol.h"

extern char gEmpty;

String::String() {
    len = 0;
    text = &gEmpty;
}

String::String(const char *str) {
    len = 0;
    text = &gEmpty;
    *this = str;
}

String::String(Symbol s) {
    len = 0;
    text = &gEmpty;
    *this = s.m_string;
}

String::String(const String &str) {
    len = 0;
    text = &gEmpty;
    *this = str.c_str();
}

String::String(unsigned int arg, char charg) {
    len = 0;
    text = &gEmpty;
    reserve(arg);

    for (int i = 0; i < arg; i++)
        text[i] = charg;

    text[arg] = '\0';
}

extern void MemOrPoolFree(int, int, void *);

String::~String() {
    if (len != 0) {
        MemOrPoolFree(len + 1, 1, text); // MemOrPoolFree
    }
}

String *String::operator=(const char *str) {
    if (str == text) {
        return this;
    }
    if (str == 0 || (*str == '\0')) {
        resize(0);
    } else {
        reserve(strlen(str));
        strcpy(text, str);
    }
    return this;
}

bool String::operator!=(const char *str) const {
    if (str == nullptr)
        return true;
    else
        return strcmp(str, text);
}

bool String::operator!=(const String &str) const {
    return strcmp(str.text, text);
}

bool String::operator==(const char *str) const {
    if (str == nullptr)
        return false;
    else
        return strcmp(str, text) == 0;
}

bool String::operator==(const String &str) const {
    return strcmp(str.text, text) == 0;
}

extern int MemOrPoolAlloc(int, int);

// Redo this once you have MemOrPoolAlloc and MemOrPoolFree defined
// rk wanted to call this MemmyUppies but i had to put a stop to it
// -- dark
void String::reserve(unsigned int arg) {
    void *dest;
    if (arg > len) {
        dest = (void *)MemOrPoolAlloc(arg + 1, 1); // this fn: MemOrPoolAlloc
        memcpy(dest, text, len + 1);
        *((char *)dest + arg) = 0;

        if (len != 0) {
            MemOrPoolFree(len + 1, 1, text); // this fn: MemOrPoolFree
        }

        len = arg;
        text = (char *)dest;
    }
}

String *String::operator+=(const String &str) {
    const char *t = str.c_str();
    return *this += t;
}

String *String::operator+=(char c) {
    int iVar2 = length();
    reserve(iVar2 + 1);
    text[iVar2] = c;
    text[iVar2 + 1] = '\0';
    return this;
}

String *String::operator=(Symbol s) {
    return this->operator=(s.m_string);
}

int String::find(const char *str, unsigned int idx) const {
    char *found = strstr(text + idx, str);
    if (found != nullptr) {
        return found - text;
    }
    return -1;
}

int String::find(const char *c) const {
    return find(c, 0);
}

int String::find_last_of(char charg) const {
    char *found = strrchr(text, charg);
    if (found != nullptr) {
        return found - text;
    }
    return -1;
}

// similar to std::string::find_last_of
int String::find_last_of(const char *str) const {
    if (str == nullptr)
        return -1;

    int a = -1;
    for (char *tmp = (char *)str; *tmp != '\0'; tmp++) {
        int lastIndex = find_last_of(*tmp);
        if ((lastIndex != (size_t)-1) && (lastIndex > a)) {
            a = lastIndex;
        }
    }

    return (a != -1) ? a : -1;
}

bool String::contains(const char *str) const {
    int index = find(str, 0) + 1;
    return (index != 0);
}

void String::ReplaceAll(char old_char, char new_char) {
    char *p;
    for (p = text; *p != '\0'; p++) {
        if (*p == old_char)
            *p = new_char;
    }
}

void String::swap(String &s) {
    char *temp_text;
    unsigned int temp_len;

    temp_text = text;
    text = s.text;
    temp_len = len;
    len = s.len;
    s.text = temp_text;
    s.len = temp_len;
}

// finds index of the first instance of char argument in string at an offset
int String::find(char charg, int idx) {
    char *p = &text[idx];

    while ((*p != '\0') && (*p != charg))
        p++;

    if (*p != '\0') {
        return p - text;
    }
    return -1;
}

int String::find(char c) {
    return find(c, 0);
}

extern char fn_80018764(char);

void String::ToLower() {
    char *p;
    for (p = text; *p != '\0'; p++) {
        *p = fn_80018764(*p);
    }
}

extern char fn_80018734(char);

void String::ToUpper() {
    char *p;
    for (p = text; *p != '\0'; p++) {
        *p = fn_80018734(*p);
    }
}

String *String::operator=(const String &str) {
    const char *s;
    reserve(str.len);
    s = str.c_str();
    strcpy(text, s);
    return this;
}

void String::resize(unsigned int arg) {
    reserve(arg);
    text[arg] = 0;
}

// similar to std::string::find_first_of
int String::find_first_of(const char *str, unsigned int arg) const {
    char *p1;
    char *p2;
    if (str == nullptr)
        return -1;
    for (p1 = &text[arg]; *p1 != '\0'; p1++) {
        for (p2 = (char *)str; *p2 != '\0'; p2++) {
            if (*p1 == *p2) {
                return p1 - text;
            }
        }
    }
    return -1;
}

char *String::operator[](unsigned int arg) {
    return &text[arg];
}

String *String::operator+=(const char *str) {
    int iVar2;
    if (str == nullptr || *str == '\0')
        return this;
    iVar2 = length();
    reserve(iVar2 + strlen(str));
    strcpy(&text[iVar2], str);
    return this;
}

String String::operator+(const char *chrstr) const {
    String ret(*this);
    ret += chrstr;
    return ret;
}

String String::operator+(char c) {
    String ret(*this);
    ret += c;
    return ret;
}

String String::operator+(String *str) {
    String ret(*this);
    ret += *str;
    return ret;
}

// what even is the point of this fxn? it's in String's vtable,
// but all it does is just call +=
void String::Print(const char *asdf) {
    this->operator+=(asdf);
}

// get char #arg from the back
char String::rcharAt(int arg) {
    return text[len + arg];
}

char *String::rindex(int arg) {
    return &text[len + arg];
}

bool String::operator<(const String &str) const {
    return (strcmp(text, str.text) < 0);
}

int String::rfind(const char *str) const {
    int rv;
    if (str == nullptr)
        return -1;
    else {
        rv = -1;
        for (char *p4 = (char *)str; *p4 != '\0'; p4++) {
            int x = find_last_of(*p4);
            if (x == (size_t)-1)
                return -1;
            if (rv == -1) {
                rv = x;
            } else if (x != p4 - str + rv) {
                return -1;
            }
        }
    }
    if (rv == -1)
        return -1;
    return rv;
}

String String::substr(unsigned int index, unsigned int substr_len) const {
    char buf[512];
    if (index + substr_len >= len) {
        return String(&text[index]);
    } else {
        strncpy(buf, &text[index], substr_len);
        buf[substr_len] = '\0';
        return String(buf);
    }
}

String String::substr(unsigned int index) {
    return String(&text[index]);
}

String *String::erase() {
    text[0] = '\0';
    return this;
}

String *String::erase(unsigned int index) {
    if (index >= len)
        return this;
    text[index] = '\0';
    return this;
}

// replaces this->text with the contents of buffer, at this->text index length
// start: the starting index of the text you want to replace
// length: how many chars you want the replacement to be
// buffer: the replacement chars
String *String::replace(unsigned int start, unsigned int n, const char *buffer) {
    char *text_offsetted;
    char *var_r4;
    char *var_r5;
    unsigned int bufferLength, end;
    char *tmp = 0;
    char c;

    end = start + n;
    if (end > len) {
        n = len - start;
    }

    bufferLength = strlen(buffer);
    if (bufferLength > n) {
        String str_tmp;
        str_tmp.reserve(bufferLength + (length() - n));
        strncpy(str_tmp.text, text, start);
        strncpy(str_tmp.text + start, buffer, bufferLength);
        strcpy(str_tmp.text + (bufferLength + start), text + (n + start));
        swap(str_tmp);
    } else {
        strncpy(text + start, buffer, bufferLength);
        text_offsetted = text + start;
        var_r4 = text_offsetted + bufferLength;
        var_r5 = text_offsetted + n;
        while (*var_r5 != '\0') {
            c = *var_r5++;
            *var_r4++ = c;
        }
        *var_r4 = *var_r5;
    }

    return this;
}

extern char lbl_80858CA0[]; // appears to be empty (all 0's)

void String::erase(unsigned int start, unsigned int length) {
    replace(start, length, &lbl_80858CA0[0]);
}

String *String::replace(unsigned int start, const char *buf) {
    return replace(start, 0, buf);
}

String *String::replace(unsigned int start, String *str) {
    return replace(start, 0, str->c_str());
}

// extern void fn_801CEDFC(UnknownJsonConverterMember *, String *);

// void String::fn_80362560(char *buf, UnknownJsonConverterMember *mem) {
//     mem->fn_800AFE60();
//     int var_r31, var_r30;

//     var_r31 = 0;
//     var_r30 = find_first_of(buf, 0);

//     while (var_r30 != (size_t)-1) {
//         if (var_r30 > var_r31) {
//             String sp14 = substr(var_r31, var_r30 - var_r31);
//             fn_801CEDFC(mem, &sp14);
//         }
//         var_r31 = var_r30 + 1;
//         var_r30 = find_first_of(buf, var_r31);
//     }
//     if (var_r31 < length()) {
//         String sp14 = substr(var_r31, length() - var_r31);
//         fn_801CEDFC(mem, &sp14);
//     }
//     mem->GetUnk4();
// }

// inserts the char c into this->text at index idx, cnt times
String *String::insert(int idx, unsigned int cnt, char c) {
    String sp8;
    char *temp_r0;
    char *var_r4;
    unsigned int var_ctr;

    sp8.reserve(cnt + length());
    strncpy(sp8.text, text, idx);
    for (int i = 0; i < cnt; i++) {
        sp8.text[idx + i] = c;
    }
    strcpy(&sp8.text[cnt + idx], &text[idx]);
    swap(sp8);
    return this;
}

// fn_80362A50
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

// fn_80362AF4
// sorta like strncpy, except for the return value
// returns true if the copy operation was terminated because of reaching the maximum
// length or encountering the end of src, and 0 otherwise.
bool StrNCopy(char *dest, const char *src, int cnt) {
    int var_r5_2;
    char temp_r0;
    bool max_len_reached;
    char *var_r3;
    char *var_r4;

    var_r3 = dest;
    var_r4 = (char *)src;
    var_r5_2 = cnt - 1;

    while (*var_r4 != 0 && (var_r5_2 != 0)) {
        temp_r0 = *var_r4++;
        *var_r3++ = temp_r0;
        var_r5_2--;
    }

    max_len_reached = false;
    *var_r3 = 0;
    if ((var_r5_2 != 0) || (*var_r4 == 0)) {
        max_len_reached = true;
    }
    return max_len_reached;
}
