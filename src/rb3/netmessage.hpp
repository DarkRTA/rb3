#ifndef RB3_NETMESSAGE_HPP
#define RB3_NETMESSAGE_HPP
#include "textstream.hpp"
#include "binstream.hpp"

class NetMessage {
public:
	NetMessage(); // fn_800AAE9C
	virtual ~NetMessage(); // fn_8000DD10 - generic dtor
	virtual void Save(BinStream &) const = 0;
	virtual void Load(BinStream &) = 0;
	virtual void Dispatch() = 0;
	virtual int VoiceData(); // links to fn_8077BAA0, which returns 0
	virtual void
	Print(TextStream &) const; // links to fn_8076F540, which returns void
	virtual void ByteCode() const = 0;
	virtual void Name() const = 0;
};

#endif
