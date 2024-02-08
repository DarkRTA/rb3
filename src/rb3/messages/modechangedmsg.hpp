#ifndef RB3_MODECHANGEDMSG_HPP
#define RB3_MODECHANGEDMSG_HPP
#include "Symbol.h"
#include "message.hpp"

class ModeChangedMsg : public Message {
public:
    ModeChangedMsg() : Message(Type()) {}
    virtual ~ModeChangedMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("mode_changed");
        return t;
    }
};

#endif
