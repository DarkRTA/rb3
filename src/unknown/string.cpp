#include <unknown/String.hpp>
#include <unknown/unknown_prototypes.hpp>
#include <MSL_C/string.h>

void String::fn_80361F88(String * src) // clone?
{
	char *pcSrc;
	pcSrc = fn_8000DB9C(src);
	fn_80361F04(this,pcSrc);
	return;
}

void String::operator= (char * str) {
	if (str == this->text) {
		return;
	}

	if ((str == (char *)0) || (*str == '\0')) {
		fn_80362260(this, 0);
	} else {
		fn_80361C90(this, strlen(str));
		strcpy(this->text, str);
	}

	return;
}
