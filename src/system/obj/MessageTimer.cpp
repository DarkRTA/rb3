#include "obj/MessageTimer.h"
#include "obj/DataFunc.h"
#include "utl/Std.h"
#include <algorithm>

std::vector<EventEntry *> gEntries;
bool MessageTimer::sActive;

static DataNode MessageTimerStart(DataArray *) {
    MessageTimer::Start();
    return DataNode(0);
}

static DataNode MessageTimerStop(DataArray *) {
    MessageTimer::Stop();
    return DataNode(0);
}

static DataNode MessageTimerDump(DataArray *) {
    MessageTimer::Dump();
    return DataNode(0);
}

static DataNode MessageTimerOn(DataArray *) { return DataNode(MessageTimer::sActive); }

void MessageTimer::Init() {
    DataRegisterFunc("message_timer_start", MessageTimerStart);
    DataRegisterFunc("message_timer_stop", MessageTimerStop);
    DataRegisterFunc("message_timer_dump", MessageTimerDump);
    DataRegisterFunc("message_timer_on", MessageTimerOn);
}

void MessageTimer::Start() {
    sActive = true;
    DeleteAll(gEntries);
}

void MessageTimer::Stop() { sActive = false; }

void MessageTimer::Dump() {
    MILO_LOG("Message Tracker Dump!\n");
    std::sort(gEntries.begin(), gEntries.end(), MaxSort());
    for (int i = 0; i < gEntries.size(); i++) {
        gEntries[i]->Dump();
    }
}

void MessageTimer::AddTime(Hmx::Object *o, Symbol msg, float ms) {
    if (sActive) {
        for (int i = 0; i < gEntries.size(); i++) {
            if (gEntries[i]->msgs == msg) {
                gEntries[i]->Add(o, ms);
                return;
            }
        }
        gEntries.push_back(new EventEntry(msg, o, ms));
    }
}

inline void EventEntry::Add(Hmx::Object *o, float ms) {
    Symbol sym =
        o ? MakeString("%s 0x%x", o->Name(), (int)o) : MakeString("0x%x", (int)o);
    for (int i = 0; i < objs.size(); i++) {
        if (objs[i]->name == sym) {
            ObjEntry *cur = objs[i];
            if (cur->maxMs < ms) {
                cur->maxMs = ms;
            }
            cur->num++;
            cur->totalMs += ms;
            return;
        }
    }
    objs.push_back(new ObjEntry(sym, ms, 1));
}