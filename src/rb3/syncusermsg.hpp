#ifndef RB3_SYNCUSERMSG_HPP
#define RB3_SYNCUSERMSG_HPP
#include "utl/BinStream.h"
#include "utl/Str.h"
#include "memstream.hpp"
#include "netmessage.hpp"

// this class is 0x14 big! according to NewNetMessage()
class SyncUserMsg : NetMessage {
public:
    SyncUserMsg(); // fn_800AAEDC
    // SyncUserMsg(some var); // fn_800BAA8C
    virtual ~SyncUserMsg(); // fn_800AD2DC
    virtual void Save(BinStream &) const; // fn_800BAAE8
    virtual void Load(BinStream &); // fn_800BAAF8
    virtual void Dispatch(); // fn_800BAB08

    virtual void ByteCode() const; // fn_800BABE8
    virtual void Name() const; // fn_800BAC44

    void NewNetMessage(); // fn_800AAEAC

    // unknown_class unk4;
};

#endif
