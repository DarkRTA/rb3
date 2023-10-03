#ifndef RB3_ASYNCFILE_HPP
#define RB3_ASYNCFILE_HPP
#include "file.hpp"
#include "string.hpp"

class AsyncFile : File {
public:
	AsyncFile(const char*, int);
	virtual ~AsyncFile();
	virtual String GetStringMember();
	virtual int V_Unk3(char*, int); // fn_802E7E8C
	virtual bool V_Unk4(char*, int); // fn_802E7F7C
	virtual int V_Unk5(char*, int); // fn_802E7F00
	virtual bool V_Unk6(char*, int); // fn_802E81D4
	virtual unsigned int V_Unk7(int, int); // fn_802E8300
	virtual unsigned int V_Unk8(); // fn_802E84AC
	virtual void V_Unk9(); // fn_802E84B4
	virtual bool V_Unk10(); // fn_802E85E0
	virtual bool V_Unk11(); // fn_802E85F8
	virtual unsigned int GetFileSize(); // fn_802E8600
	virtual int V_Unk13(); // fn_802E8608
	virtual int V_Unk14(int*); // fn_802E8030
	virtual int V_Unk15(int*); // fn_802E81AC
	virtual int V_Unk16() = 0;
	
	virtual void V_Unk18(char*, int) = 0;
	virtual int V_Unk19() = 0;
	virtual int V_Unk20(char*, int) = 0;
	virtual int V_Unk21() = 0;
	virtual void V_Unk22() = 0;
	virtual void V_Unk23() = 0;
	virtual int V_Unk24() = 0;
	virtual void V_Unk25() = 0;

	void fn_802E8530();
	void fn_802E7E2C();

	int unk4;
	bool unk8;
	char unk9;
	String unkc;
	unsigned int unk18;
	int unk1c;
	unsigned int filesize;
	int unk24;
	char* unk28;
	char* unk2c;
	int unk30;
	int unk34;
};

#endif
