#ifndef RB3_MODECHANGEDMSG_HPP
#define RB3_MODECHANGEDMSG_HPP
#include "symbol.hpp"
#include "message.hpp"

class ModeChangedMsg : public Message {
public:
    ModeChangedMsg();
    virtual ~ModeChangedMsg(){} // fn_800A7FF4
    static Symbol Type();
};

#endif
