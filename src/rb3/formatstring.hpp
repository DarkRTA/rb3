#ifndef RB3_FORMATSTRING_HPP
#define RB3_FORMATSTRING_HPP
#include "string.hpp"
#include "data.hpp"

class FormatString {
public:
	char* format;
	char* unk4;
	int unk8;
	char unk_arr[0x800];
	char* unk80c;
    int formatType; // 0 = integer, 1 = string, 2 = float, 3 = unknown

	FormatString();
	FormatString(const char*);
	void InitArray(const char*, bool);
	void UpdateType();
	char* Str();
	FormatString& operator<<(unsigned int);
	FormatString& operator<<(int);
	FormatString& operator<<(const String&);
	FormatString& operator<<(const DataNode&);
	FormatString& operator<<(float);
	FormatString& operator<<(const char*);
	FormatString& operator<<(Symbol);
};

#endif
