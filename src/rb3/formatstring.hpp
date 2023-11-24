#ifndef RB3_FORMATSTRING_HPP
#define RB3_FORMATSTRING_HPP

class FormatString {
public:
	char* unk0;
	int unk4;
	int unk8;
	char unk_arr[0x800];
	int unk80c;

	FormatString(const char*);
	void InitArray(const char*, bool);
	void UpdateType();
};

#endif
