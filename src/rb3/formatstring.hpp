#ifndef RB3_FORMATSTRING_HPP
#define RB3_FORMATSTRING_HPP

class FormatString {
public:
	char* format;
	int unk4;
	int unk8;
	char unk_arr[0x800];
	char* unk80c;
    int formatType; // 0 = integer, 1 = string, 2 = float, 3 = unknown

	FormatString(const char*);
	void InitArray(const char*, bool);
	void UpdateType();
	FormatString& operator<<(unsigned int);
};

#endif
