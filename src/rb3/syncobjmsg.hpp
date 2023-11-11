#ifndef RB3_SYNCOBJMSG_HPP
#define RB3_SYNCOBJMSG_HPP
#include "netmessage.hpp"
#include "binstream.hpp"
#include "string.hpp"
#include "memstream.hpp"

// this class is 0x34 big! according to NewNetMessage()
class SyncObjMsg : NetMessage {
public:
	SyncObjMsg(); // fn_800AAE4C
	// SyncObjMsg(String&, unsigned int); // found in RB2
	virtual ~SyncObjMsg(); // fn_800BA1EC
	virtual void Save(BinStream &) const; // fn_800BA7E0
	virtual void Load(BinStream &); // fn_800BA84C
	virtual void Dispatch(); // fn_800BA8C8

	virtual void Print(TextStream &) const; // fn_800BA9BC
	virtual void ByteCode() const; // fn_800BAB80
	virtual void Name() const; // fn_800BABDC

	String tag;
	unsigned int dirty_mask;
	MemStream unk14;

	void NewNetMessage(); // fn_800AAE1C

	void fn_800BA788(BinStream &) const;
};

#endif
