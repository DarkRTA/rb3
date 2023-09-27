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

String::String(const String &str)
{
	len = 0;
	text = &lbl_808E4560;
	*this = str.GetText();
}

// extern "C" void fn_80361C90(String*, int);

extern "C" void fn_80354878(int, int, char *);

String::~String()
{
	if (len != 0) {
		fn_80354878(len + 1, 1, text);
	}
}

// void String::fn_80362260(int x){
//     fn_80361C90(this, 0);
//     *(text + x) = 0;
// }

// void String::operator=(const char* str){
//     if(str == text){
//         return;
//     }
//     if(str == 0 || (*str == '\0')){
//         fn_80362260(0);
//     }
//     else {
//         fn_80361C90(this, strlen(str));
//         strcpy(text, str);
//     }
// }

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