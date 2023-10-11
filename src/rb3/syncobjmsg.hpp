#ifndef RB3_SYNCOBJMSG_HPP
#define RB3_SYNCOBJMSG_HPP
#include "netmessage.hpp"
#include "binstream.hpp"
#include "string.hpp"
#include "memstream.hpp"

class SyncObjMsg : NetMessage {
public:
	SyncObjMsg(String&, unsigned int); // fn_800AAE4C
	virtual ~SyncObjMsg(); // fn_800BA1EC
	virtual void Save(BinStream&) const; // fn_800BA7E0
	virtual void Load(BinStream&); // fn_800BA84C
	virtual void Dispatch(); // fn_800BA8C8
	
	virtual void Print(TextStream&) const; // fn_800BA9BC
	virtual void ByteCode() const; // fn_800BAB80
	virtual void Name() const; // fn_800BABDC

	String tag;
	unsigned int dirty_mask;

	// int unk14;
	MemStream* unk14;

	void fn_800BA788(BinStream&) const;
};

#endif
