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

String* String::AppendString(String *str)
{
	const char *t = str->GetText();
	return AppendString(t);
}

String* String::AppendChar(char c)
{
	int iVar2 = GetTextLength();
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

// not fully matched! fix this
// similar to std::string::find_last_of
int String::FindLastOf(char *str) const {
	int a;
	int lastIndex;
	if (str == nullptr)
		return -1;
	else {
		a = -1;
		while (*str != '\0') {
			lastIndex = FindLastIndexOfChar(*str);
			if ((lastIndex != npos) && (lastIndex > a)) {
				a = lastIndex;
			}
			str++;
		}
		lastIndex = -1;
		if (a != -1) {
			lastIndex = a;
		}
		return lastIndex;
	}
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

// appending str to String->text
String* String::AppendString(const char* str){
	int iVar2;
	if(str == nullptr || *str == '\0') return this;
	iVar2 = GetTextLength();
	Reserve(iVar2 + strlen(str));
	strcpy(&text[iVar2], str);
	return this;
}

// not matching - need to call the copy constructor instead of the assignment operator
String* String::fn_80361E38(String str, const char* chrstr){
	*this = str;
	return this->AppendString(chrstr);
}

// not matching - need to call the copy constructor instead of the assignment operator
String* String::fn_80361E7C(String str, char c){
	*this = str;
	return this->AppendChar(c);
}

// not matching - need to call the copy constructor instead of the assignment operator
String* String::fn_80361EC0(String str, String* str2){
	*this = str;
	return this->AppendString(str2);
}

// what even is the point of this fxn? it's in String's vtable,
// but all it does is just call AppendString
String* String::VirtuallyAppendString(const char* asdf){
	return AppendString(asdf);
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
String* String::ReplaceTextAtIndex(unsigned int start, unsigned int length, char* buffer){
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
        str_tmp.Reserve(bufferLength + (GetTextLength() - length));
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