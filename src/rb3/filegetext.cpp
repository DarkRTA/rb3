#include <types.h>
#include <std/string.h>
extern "C" char* FileGetExt(char*);

// fn_802FA918
char* FileGetExt(char* filename){
	char* end = filename + strlen(filename);
	for(char* search = end - 1; search >= filename; search--){
		if(*search == '.'){
			return search + 1;
		}
		else if(*search == '/' || *search == '\\'){
			return end;
		}
	}
	return end;
}
