#ifndef RB3_CONTENTINSTALLEDMSG_HPP
#define RB3_CONTENTINSTALLEDMSG_HPP
#include "obj/Data.h"
#include "utl/Message.h"
#include "utl/Symbol.h"

class ContentInstalledMsg : Message {
public:
    ContentInstalledMsg(DataArray *);
    ContentInstalledMsg();
    virtual ~ContentInstalledMsg(); // fn_800A7FF4

    Symbol Type();
};

#endif
