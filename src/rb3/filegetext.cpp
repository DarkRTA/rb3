#include <types.h>
#include <std/string.h>
// nonmatching, i give up for now
extern "C" char * FileGetExt(char*);

char * FileGetExt(char* filename) { // 802fa918
/*
	char cVar1;
	int iVar2;
	char *endfile;
	char *needle;

	size_t len = strlen(filename);
	endfile = filename + len;
	needle = endfile - 1;
	iVar2 = endfile - filename;

	if (filename <= needle) {
		while (cVar1 = *needle, cVar1 != '.') {
			if (cVar1 == '/' || cVar1 == '\\') {
				return endfile;
			} else {
				needle++;
				if (--iVar2 == 0) {
					return endfile;
				}
			}
		}
		endfile = needle + 1;
	}
	return endfile;*/

	size_t len = strlen(filename);
	char* ext = filename + len;
	char* search = ext - 1;
	size_t extensionless_len = ext - filename;
	if (search >= filename) {
		char needle;
		while (needle = *search, needle != '.') {
			switch(needle) {
				case '/':
				case '\\':
					return ext;
				default:
					;
			}
			if (needle != '/') {
				continue;
			} else if (needle != '\\') {
				continue;
			}
			extensionless_len--;
			search--;
			return ext;
		}
		ext = (char *)((int)needle - 1);
	}
	return ext;
}
