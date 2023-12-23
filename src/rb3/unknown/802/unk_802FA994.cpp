#include "std/string.h"
#include "unknown.hpp"

extern "C" bool FileMatch(const char *, const char *);

// fn_802FAE68
bool FileMatchInternal(const char *arg0, const char *arg1, bool arg2)
{
	for (; *arg0 != 0; arg0++) {
		if (FileMatch(arg0, arg1))
			return true;
		if (!arg2 && (*arg0 == '/' || *arg0 == '\\'))
			return false;
	}
	return (*arg1 == *arg0);
}

// fn_802FAF0C
bool FileMatch(const char *param1, const char *param2)
{
	if (param2 == 0)
		return false;
	while (*param2 != '\0') {
		if (*param2 == '*')
			return FileMatchInternal(param1, param2 + 1, 0);
		if (*param2 == '&')
			return FileMatchInternal(param1, param2 + 1, 1);
		if (*param1 == '\0')
			break;
		if (*param2 == '?') {
			if ((*param1 == '\\') || (*param1 == '/'))
				return 0;
		} else if ((*param2 == '/') || (*param2 == '\\')) {
			if ((*param1 != '/') && (*param1 != '\\'))
				return 0;
		} else if (*param2 != *param1)
			return 0;
		param2++;
		param1++;
	}
	return (*param2 - *param1) == 0;
}