#ifndef OS_PROFILESWAPPEDMSG_H
#define OS_PROFILESWAPPEDMSG_H
#include "obj/Msg.h"
#include "os/User.h"

BEGIN_MESSAGE(ProfileSwappedMsg, profile_swapped, LocalUser*, LocalUser*);
    LocalUser* GetUser1() const;
    LocalUser* GetUser2() const;
END_MESSAGE;

#endif
