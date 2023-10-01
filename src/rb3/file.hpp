#ifndef RB3_FILE_HPP
#define RB3_FILE_HPP

class File {
public:
	File();
	virtual ~File();
	virtual void fn_802E780C();
	virtual void unk1() = 0;
	virtual void unk2() = 0;
	virtual void unk3() = 0;
	virtual void fn_8077BAA0();
	virtual void unk4() = 0;
	virtual void unk5() = 0;
	virtual void unk6() = 0;
	virtual void unk7() = 0;
	virtual void unk8() = 0;
	virtual void unk9() = 0;
	virtual void unk10() = 0;
	virtual void unk11() = 0;
	virtual void fn_802E7818();
	virtual void unk12() = 0;
	// virtual void fn_8077BAA0();

	static int sOpenCount[4];
};

#endif
