#ifndef OBJ_MESSAGETIMER_H
#define OBJ_MESSAGETIMER_H
#include "os/Timer.h"
#include "utl/Symbol.h"

class ObjEntry {
public:
    Symbol name; // 0x0
    float maxMs; // 0x4
    float totalMs; // 0x8
    int num; // 0xc
};

class EventEntry {
public:
    Symbol msgs; // 0x0
    std::vector<ObjEntry*> objs; // 0x4
};

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
    static void AddTime(Hmx::Object* o, Symbol msg, float ms);
    static void Init();
    static void Start();
    static void Stop();
    static void Dump();
};

#endif
