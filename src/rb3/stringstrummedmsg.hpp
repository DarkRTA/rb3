#ifndef RB3_STRINGSTRUMMEDMSG_HPP
#define RB3_STRINGSTRUMMEDMSG_HPP
#include "symbol.hpp"
#include "message.hpp"

class StringStrummedMsg : Message {
public:
    StringStrummedMsg(int, int, int, int); // fn_80313E98
    virtual ~StringStrummedMsg(); // fn_800A7FF4
    static Symbol Type();
};

#endif
