#ifndef RB3_STORAGECHANGEDMSG_HPP
#define RB3_STORAGECHANGEDMSG_HPP
#include "message.hpp"
#include "data.hpp"
#include "symbol.hpp"

class StorageChangedMsg : Message {
public:
    StorageChangedMsg(DataArray *); // fn_802F8244
    StorageChangedMsg(); // fn_8030B290
    virtual ~StorageChangedMsg(); // fn_800A7FF4

    Symbol Type();
};

#endif
