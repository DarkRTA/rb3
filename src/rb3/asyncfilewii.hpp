#ifndef RB3_ASYNCFILEWII_HPP
#define RB3_ASYNCFILEWII_HPP
#include "asyncfile.hpp"
#include "file.hpp"
#include "string.hpp"

class AsyncFileWii : AsyncFile {
public:
	AsyncFileWii(const char*, int);
	virtual ~AsyncFileWii();	
	virtual int V_Unk16(); // links to fn_8077BAA0, which returns 0
	
	virtual void V_Unk18(char*, int); // fn_802E8BCC
	virtual int V_Unk19(); // fn_802E8C48
	virtual int V_Unk20(char*, int); // fn_802E8C50
	virtual int V_Unk21(); // fn_802E8C54
	virtual void V_Unk22(); // fn_802E8C5C
	virtual void V_Unk23(); // fn_802E8CB8
	virtual int V_Unk24(); // fn_802E8D28
	virtual void V_Unk25(); // fn_802E8F1C

	
	void fn_800E1114();

	unsigned int unk38;
	char unk3c;
	int unk40;
	int unk44;
	int unk48, unk4c, unk50, unk54, unk58, unk5c, unk60, unk64, unk68, unk6c, unk70, unk74;
	int unk78;
};

#endif
