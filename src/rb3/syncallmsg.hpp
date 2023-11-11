#ifndef RB3_SYNCALLMSG_HPP
#define RB3_SYNCALLMSG_HPP
#include "netmessage.hpp"
#include "binstream.hpp"
#include "string.hpp"
#include "memstream.hpp"

class SyncAllMsg : NetMessage {
public:
	SyncAllMsg(); // fn_800AAF80
	virtual ~SyncAllMsg(); // fn_800AD2DC - same as ~SyncUserMsg
	virtual void Save(BinStream &) const; // fn_8076F540 - returns void
	virtual void Load(BinStream &); // fn_8076F540 - returns void
	virtual void Dispatch(); // fn_800BAB74

	virtual void ByteCode() const; // fn_800BAC50
	virtual void Name() const; // fn_800BACAC

	void NewNetMessage(); // fn_800AAF50
};

#endif
