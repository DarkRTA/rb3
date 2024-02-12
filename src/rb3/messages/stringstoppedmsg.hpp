#ifndef RB3_STRINGSTOPPEDMSG_HPP
#define RB3_STRINGSTOPPEDMSG_HPP
#include "utl/Message.h"
#include "utl/Symbol.h"

class StringStoppedMsg : public Message {
public:
    StringStoppedMsg(int, int, int, int); // ???
    virtual ~StringStoppedMsg(){} // fn_800A7FF4
    static Symbol Type();
};

#endif
