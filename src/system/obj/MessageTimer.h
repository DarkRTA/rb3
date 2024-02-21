#ifndef OBJ_MESSAGETIMER_H
#define OBJ_MESSAGETIMER_H
#include "os/Timer.h"
#include "obj/Object.h"
#include "utl/Symbol.h"

class MessageTimer {
public:
    Timer mTimer;
    Hmx::Object* mObject;
    Symbol mMessage;

    MessageTimer(Hmx::Object*, Symbol);
    ~MessageTimer();
    bool Active();
};

#endif
