#ifndef RB3_STORAGECHANGEDMSG_HPP
#define RB3_STORAGECHANGEDMSG_HPP
#include "obj/Data.h"
#include "utl/Message.h"
#include "utl/Symbol.h"

class StorageChangedMsg : Message {
public:
    StorageChangedMsg(DataArray *); // fn_802F8244
    StorageChangedMsg(); // fn_8030B290
    virtual ~StorageChangedMsg(); // fn_800A7FF4

    Symbol Type();
};

#endif
