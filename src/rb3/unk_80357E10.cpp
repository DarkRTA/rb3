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

String::String(const char **str)
{
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

String::String(unsigned int arg, char charg)
{
	len = 0;
	text = &lbl_808E4560;
	Reserve(arg);

	for (int i = 0; i < arg; i++)
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

String *String::operator=(const char *str)
{
	if (str == text) {
		return this;
	}
	if (str == 0 || (*str == '\0')) {
		CreateEmptyString(0);
	} else {
		Reserve(strlen(str));
		strcpy(text, str);
	}
	return this;
}

// returns false if strings are NOT different (matching)
// returns true if strings ARE different (non matching)
bool String::AreStringsDifferent(const char *str)
{
	if (str == nullptr)
		return true;
	else
		return strcmp(str, text);
}

bool String::AreStringsDifferent(const String *str)
{
	return strcmp(str->text, text);
}

// returns true if strings are NOT different (matching)
// returns false if strings ARE different (non matching)
bool String::AreStringsIdentical(const char *str)
{
	if (str == nullptr)
		return false;
	else
		return strcmp(str, text) == 0;
}

bool String::AreStringsIdentical(const String *str)
{
	return strcmp(str->text, text) == 0;
}

extern int fn_80354848(int, int);
extern void fn_80354878(int, int, char *);

// Redo this once you have fn_80354848 and fn_08354878 defined
// rk wanted to call this MemmyUppies but i had to put a stop to it
// -- dark
void String::Reserve(unsigned int arg)
{
	void *dest;
	if (arg > len) {
		dest = (void *)fn_80354848(arg + 1, 1);
		memcpy(dest, text, len + 1);
		*((char *)dest + arg) = 0;

		if (len != 0) {
			fn_80354878(len + 1, 1, text);
		}

		len = arg;
		text = (char *)dest;
	}
}

// MAKE THIS OPERATOR += OVERLOAD
String* String::operator+=(String *str)
{
	const char *t = str->GetText();
	return *this += t;
}


String* String::operator+=(char c)
{
	int iVar2 = GetStrLen();
	Reserve(iVar2 + 1);
	text[iVar2] = c;
	text[iVar2 + 1] = '\0';
	return this;
}

// assigns char** to this String's text field
String* String::operator=(const char** str){
	return this->operator=(*str);
}

// does strstr, and returns the index of where it begins
int String::FindIndexOfSubstringAtOffset(const char *str, int idx)
{
	char *found = strstr(text + idx, str);
	if (found != nullptr) {
		return found - text;
	}
	return -1;
}

int String::FindIndexOfSubstringStrStr(char* c){
	return FindIndexOfSubstringAtOffset(c, 0);
}

int String::FindLastIndexOfChar(char charg) const
{
	char *found = strrchr(text, charg);
	if (found != (char *)0) {
		return found - text;
	}
	return -1;
}

static const size_t npos = -1;

// similar to std::string::find_last_of
int String::FindLastOf(char *str) const {
	if (str == nullptr) return -1;

	int a = -1;
	for(char* tmp = str; *tmp != '\0'; tmp++){
		int lastIndex = FindLastIndexOfChar(*tmp);
		if((lastIndex != npos) && (lastIndex > a)){
			a = lastIndex;
		}
	}
	
	return (a != -1) ? a : -1;
}

bool String::SubstrExistsInString(char *str)
{
	int index = FindIndexOfSubstringAtOffset(str, 0) + 1;
	return (index != 0);
}

void String::ReplaceCharsInString(char old_char, char new_char)
{
	char *p;
	for (p = text; *p != '\0'; p++) {
		if (*p == old_char)
			*p = new_char;
	}
}

void String::SwapStrings(String *s)
{
	char *temp_text;
	unsigned int temp_len;

	temp_text = text;
	text = s->text;
	temp_len = len;
	len = s->len;
	s->text = temp_text;
	s->len = temp_len;
}

// finds index of the first instance of char argument in string at an offset
int String::FindFirstIndexOfCharAtOffset(char charg, int idx)
{
	char *p = &text[idx];

	while ((*p != '\0') && (*p != charg))
		p++;

	if (*p != '\0') {
		return p - text;
	}
	return -1;
}

int String::FindFirstIndexOfChar(char c){
	return FindFirstIndexOfCharAtOffset(c, 0);
}

extern char fn_80018764(char);

void String::ToLower()
{
	char* p;
	for(p = text; *p != '\0'; p++){
		*p = fn_80018764(*p);
	}
}

extern char fn_80018734(char);

// rename this method once you figure out what fn_80018734 does
// my guess? it's ToUpper
void String::fn_80362730()
{
	char *p;
	for (p = text; *p != '\0'; p++) {
		*p = fn_80018734(*p);
	}
}

// copies the text inside str->text, and puts it into this String's text
String* String::CopyString(String* str){
	const char* s;
	Reserve(str->len);
	s = str->GetText();
	strcpy(text, s);
	return this;
}

// creates an empty char* for this->text, of length arg
void String::CreateEmptyString(unsigned int arg){
	Reserve(arg);
	text[arg] = 0;
}

// similar to std::string::find_first_of
int String::FindFirstOf(char* str, int arg){
	char* p1;
	char* p2;
	if(str == nullptr) return -1;
	for(p1 = &text[arg]; *p1 != '\0'; p1++){
		for(p2 = str; *p2 != '\0'; p2++){
			if(*p1 == *p2){
				return p1 - text;
			}
		}
	}
	return -1;
}

char* String::GetTextAtOffset(int arg){
	return &text[arg];
}

// MAKE THIS OPERATOR += OVERLOAD
// appending str to String->text
String* String::operator+=(const char* str){
	int iVar2;
	if(str == nullptr || *str == '\0') return this;
	iVar2 = GetStrLen();
	Reserve(iVar2 + strlen(str));
	strcpy(&text[iVar2], str);
	return this;
}

// MAKE THIS OPERATOR+ OVERLOAD
// not matching - need to call the copy constructor instead of the assignment operator
String String::operator+(const char* chrstr){
	String ret(*this);
	ret += chrstr;
	return ret;
}

// not matching - need to call the copy constructor instead of the assignment operator
String String::operator+(char c){
	String ret(*this);
	ret += c;
	return ret;
}

// not matching - need to call the copy constructor instead of the assignment operator
String String::operator+(String* str){
	String ret(*this);
	ret += str;
	return ret;
}

// what even is the point of this fxn? it's in String's vtable,
// but all it does is just call +=
String* String::VirtualAppend(const char* asdf){
	return this->operator+=(asdf);
}

// get char #arg from the back
char String::GetCharFromBackIndex(int arg){
	return text[len + arg];
}

// get char* #arg from the back
char* String::GetSubstrFromBackIndex(int arg){
	return &text[len + arg];
}

// is text < str->text? if so, return true 
bool String::IsThisStrLessThan(String* str) const {
	return (strcmp(text, str->text) < 0);
}

// like the other method above but it doesn't use strstr
int String::FindIndexOfSubstring(char* str){
	int rv;
	if(str == nullptr) return -1;
	else {
		rv = -1;
		for(char* p4 = str; *p4 != '\0'; p4++){
			int x = FindLastIndexOfChar(*p4);
			if(x == npos) return -1;
			if(rv == -1){
				rv = x;
			}
			else if(x != p4 - str + rv){
				return -1;
			}
		}
	}
	if(rv == -1) return -1;
	return rv;
}

String String::CreateSubstringFromString(unsigned int index, unsigned int substr_len) const {
	char buf[512];
	if(index + substr_len >= len){
		return String(&text[index]);
	}
	else {
		strncpy(buf, &text[index], substr_len);
		buf[substr_len] = '\0';
		return String(buf);
	}
}

String String::CreateSubstringFromString(unsigned int index){
	return String(&text[index]);
}

String* String::ClearString(){
	text[0] = '\0';
	return this;
}

String* String::TruncateString(unsigned int index){
	if(index >= len) return this;
	text[index] = '\0';
	return this;
}

// replaces this->text with the contents of buffer, at this->text index length
// start: the starting index of the text you want to replace
// length: how many chars you want the replacement to be
// buffer: the replacement chars
String* String::ReplaceTextAtIndex(unsigned int start, unsigned int length, const char* buffer){
    char* text_offsetted;
    char* var_r4;
    char* var_r5;
    unsigned int bufferLength, end;
    char* tmp = 0;
    char c;

    end = start + length;
    if (end > len){
        length = len - start;
    }

    bufferLength = strlen(buffer);
    if (bufferLength > length){
        String str_tmp;
        str_tmp.Reserve(bufferLength + (GetStrLen() - length));
        strncpy(str_tmp.text, text, start);
        strncpy(str_tmp.text + start, buffer, bufferLength);
        strcpy(str_tmp.text + (bufferLength + start), text + (length + start));
        SwapStrings(&str_tmp);
    }
    else {
        strncpy(text + start, buffer, bufferLength);
        text_offsetted = text + start;
        var_r4 = text_offsetted + bufferLength;
        var_r5 = text_offsetted + length;
        while(*var_r5 != '\0'){
            c = *var_r5++;
            *var_r4++ = c;
        }
        *var_r4 = *var_r5;
    }

    return this;
}

extern char lbl_80858CA0[];

String* String::ReplaceTextAtIndexWithLabel(unsigned int start, unsigned int length){
	return ReplaceTextAtIndex(start, length, &lbl_80858CA0[0]);
}

String* String::ReplaceTextAtIndex(unsigned int start, const char* buf){
	return ReplaceTextAtIndex(start, 0, buf);
}

String* String::ReplaceTextAtIndex(unsigned int start, String* str){
	return ReplaceTextAtIndex(start, 0, str->GetText());
}

extern void fn_800A6BD0(String*);

void String::fn_80362560(char* buf, String* str){
	str->IsTextLengthZero();
	int var_r31, var_r30;

	var_r31 = 0;
	var_r30 = FindFirstOf(buf, 0);

	while(var_r30 != npos){
		if(var_r30 > var_r31){
			String sp14 = CreateSubstringFromString(var_r31, var_r30 - var_r31);
			str->fn_801CEDFC(&sp14);
		}
		var_r31 = var_r30 + 1;
		var_r30 = FindFirstOf(buf, var_r31);
	}
	if(var_r31 < GetStrLen()){
		String sp14 = CreateSubstringFromString(var_r31, GetStrLen() - var_r31);
		str->fn_801CEDFC(&sp14);
	}
	fn_800A6BD0(str);
}

// inserts the char c into this->text at index idx, cnt times
String* String::InsertCharAtIndex(int idx, unsigned int cnt, char c){
	String sp8;
	char* temp_r0;
	char* var_r4;
	unsigned int var_ctr;

	sp8.Reserve(cnt + GetStrLen());
	strncpy(sp8.text, text, idx);
	for(int i = 0; i < cnt; i++){
		sp8.text[idx + i] = c;
	}
	strcpy(&sp8.text[cnt + idx], &text[idx]);
	SwapStrings(&sp8);
	return this;
}

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