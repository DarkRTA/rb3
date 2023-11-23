#ifndef RB3_ARCHIVE_HPP
#define RB3_ARCHIVE_HPP

class Archive {
public:
	int unk0, unk4, unk8, unkc, unk10, unk14, unk18, unk1c, unk20, unk24;
	// ArkHash at 0x28
	// String at 0x3C
	// 0x48 is some word
	bool GetFileInfo(const char*, int&, unsigned long long&, int&, int&);
};

#endif