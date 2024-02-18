#ifndef RB3_SESSIONMSG_HPP
#define RB3_SESSIONMSG_HPP
#include "netmessage.hpp"
#include "utl/BinStream.h"
#include "utl/TextStream.h"

class SessionMsg : NetMessage {
public:
    SessionMsg(); // fn_800AD474
    virtual ~SessionMsg(); // fn_800AD2DC - same as ~SyncUserMsg()
    virtual void Save(BinStream &) const = 0;
    virtual void Load(BinStream &) = 0;
    virtual void Dispatch(); // fn_800B82EC

    virtual void ByteCode() const = 0;
    virtual void Name() const = 0;
};

#endif
