#ifndef OBJ_MESSAGETIMER_H
#define OBJ_MESSAGETIMER_H
#include "os/Timer.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Std.h"
#include <algorithm>

class ObjEntry {
public:
    ObjEntry(Symbol s, float ms, int inum) : name(s), maxMs(ms), totalMs(ms), num(inum) {}
    Symbol name; // 0x0
    float maxMs; // 0x4
    float totalMs; // 0x8
    int num; // 0xc

    void Dump() {
        MILO_LOG(
            "  %g %s num %d total %g av %g\n",
            maxMs,
            name.Str(),
            num,
            totalMs,
            totalMs / num
        );
    }
};

struct ObjSort {
    bool operator()(ObjEntry *e1, ObjEntry *e2) {
        return e1->maxMs > e2->maxMs ? true : false;
    }
};

class EventEntry {
public:
    EventEntry(Symbol s, Hmx::Object *o, float ms) {
        msgs = s;
        Add(o, ms);
    }

    Symbol msgs; // 0x0
    std::vector<ObjEntry *> objs; // 0x4

    ~EventEntry() {
        for (int i = 0; i < objs.size(); i++) {
            delete objs[i];
        }
    }

    float MaxMs() {
        float total = 0.0f;
        int i;
        for (i = 0; i < objs.size(); i++) {
            MaxEq(total, objs[i]->maxMs);
        }
        return total;
    }

    void Dump() {
        std::sort(objs.begin(), objs.end(), ObjSort());
        MILO_LOG("%g %s\n", MaxMs(), msgs.Str());
        for (int i = 0; i < objs.size(); i++) {
            objs[i]->Dump();
        }
    }

    void Add(Hmx::Object *o, float ms);
};

struct MaxSort {
    bool operator()(EventEntry *e1, EventEntry *e2) const {
        return e1->MaxMs() < e2->MaxMs() ? true : false;
    }
};

class MessageTimer {
public:
    Timer mTimer;
    class Hmx::Object *mObject;
    Symbol mMessage;

    static bool sActive;

    MessageTimer(class Hmx::Object *o, Symbol message) : mTimer() {
        mObject = o;
        mMessage = message;
        mTimer.Restart();
    }
    ~MessageTimer() { AddTime(mObject, mMessage, mTimer.SplitMs()); }
    static bool Active() { return sActive; }
    static void AddTime(Hmx::Object *o, Symbol msg, float ms);
    static void Init();
    static void Start();
    static void Stop();
    static void Dump();
};

#endif
