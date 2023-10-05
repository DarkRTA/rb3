#ifndef RB3_ASYNCFILECNT_HPP
#define RB3_ASYNCFILECNT_HPP
#include "asyncfile.hpp"
#include "file.hpp"
#include "string.hpp"

class AsyncFileCNT : AsyncFile {
public:
	AsyncFileCNT(const char*, int);
	virtual ~AsyncFileCNT();
	virtual int V_Unk16(int*); // fn_802E8774
	
	virtual void V_Unk18(char*, int); // fn_802E8784
	virtual int V_Unk19(); // fn_802E88C0
	virtual int V_Unk20(char*, int); // fn_802E88C8
	virtual int V_Unk21(); // fn_802E88CC
	virtual void V_Unk22(); // fn_802E88D4
	virtual void V_Unk23(); // fn_802E892C
	virtual int _ReadDone(); // fn_802E89FC
	virtual void V_Unk25(); // fn_802E8AA4

	unsigned int unk38;
	int unk3c;
	int unk40;
	int unk44; // probably a class
	char unk48; 
	char unk49;
	char unk4a;
	int unk4c, unk50, unk54, unk58, unk5c, unk60, unk64, unk68, unk6c, unk70, unk74;
	int unk78;
};

#endif
