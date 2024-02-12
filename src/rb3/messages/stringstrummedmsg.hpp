#ifndef RB3_STRINGSTRUMMEDMSG_HPP
#define RB3_STRINGSTRUMMEDMSG_HPP
#include "utl/Message.h"
#include "utl/Symbol.h"

class StringStrummedMsg : public Message {
public:
    StringStrummedMsg(int, int, int, int); // fn_80313E98
    virtual ~StringStrummedMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("string_strummed");
        return t;
    }
};

#endif
