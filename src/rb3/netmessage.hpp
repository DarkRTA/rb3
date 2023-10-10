#ifndef RB3_NETMESSAGE_HPP
#define RB3_NETMESSAGE_HPP
#include "textstream.hpp"

class NetMessage {
public:
	virtual ~NetMessage(); // fn_8000DD10 - generic dtor
	virtual void V_Unk1() = 0; // Save
	virtual void V_Unk2() = 0; // Load
	virtual void V_Unk3() = 0; // Dispatch
	virtual int VoiceData(); // links to fn_8077BAA0, which returns 0
	virtual void Print(TextStream&) const; // links to fn_8076F540, which returns void
	virtual void V_Unk6() = 0; // ByteCode
	virtual void V_Unk7() = 0; // Name
};

#endif
