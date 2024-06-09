#ifndef OBJ_MESSAGETIMER_H
#define OBJ_MESSAGETIMER_H
#include "os/Timer.h"
#include "utl/Symbol.h"

class MessageTimer {
public:
    Timer mTimer;
    class Hmx::Object* mObject;
    Symbol mMessage;

    static bool sActive;

    MessageTimer(class Hmx::Object* o, Symbol message) : mTimer(), mObject(o), mMessage(message) { mTimer.Restart(); }
    ~MessageTimer(){
        AddTime(mObject, mMessage, mTimer.SplitMs());
    }
    static bool Active(){ return sActive; }
    static void AddTime(class Hmx::Object* o, Symbol msg, float ms);
};

#endif
