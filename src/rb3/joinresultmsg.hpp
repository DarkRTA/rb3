#ifndef RB3_JOINRESULTMSG_HPP
#define RB3_JOINRESULTMSG_HPP
#include "obj/Data.h"
#include "utl/Message.h"

class JoinResultMsg : Message {
public:
    JoinResultMsg(DataArray *); // fn_800AE6D8
    virtual ~JoinResultMsg(); // fn_800A7FF4
};

#endif
