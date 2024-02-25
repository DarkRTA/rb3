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

    static bool sActive;

    MessageTimer(Hmx::Object* o, Symbol message) : mTimer(), mObject(o), mMessage(message) { mTimer.Restart(); }
    ~MessageTimer(){
        AddTime(mObject, mMessage, mTimer.SplitMs());
    }
    static bool Active(){ return sActive; }
    static void AddTime(Hmx::Object* o, Symbol msg, float ms);
};

#endif
