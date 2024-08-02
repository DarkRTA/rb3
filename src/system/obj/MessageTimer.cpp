#include "obj/MessageTimer.h"
#include "obj/DataFunc.h"
#include "utl/STLHelpers.h"
#include <algorithm>

std::vector<EventEntry*> gEntries;
bool MessageTimer::sActive;

static DataNode MessageTimerStart(DataArray*){
    MessageTimer::Start();
    return DataNode(0);
}

static DataNode MessageTimerStop(DataArray*){
    MessageTimer::Stop();
    return DataNode(0);
}

static DataNode MessageTimerDump(DataArray*){
    MessageTimer::Dump();
    return DataNode(0);
}

static DataNode MessageTimerOn(DataArray*){
    return DataNode(MessageTimer::sActive);
}

void MessageTimer::Init(){
    DataRegisterFunc("message_timer_start", MessageTimerStart);
    DataRegisterFunc("message_timer_stop", MessageTimerStop);
    DataRegisterFunc("message_timer_dump", MessageTimerDump);
    DataRegisterFunc("message_timer_on", MessageTimerOn);
}

void MessageTimer::Start(){
    sActive = true;
    DeleteRange(gEntries.begin(), gEntries.end());
    // for(std::vector<EventEntry*>::iterator it = gEntries.begin(); it != gEntries.end(); ++it){
    //     EventEntry* ev = *it;
    //     if(ev){
    //         DeleteRange(ev->objs.begin(), ev->objs.end());
    //     }
    //     delete ev;
    // }
    gEntries.clear();
}

void MessageTimer::Stop(){ sActive = false; }

struct MaxSort {
    bool operator()(EventEntry* e1, EventEntry* e2){ return e1->msgs < e2->msgs; }
};

struct ObjSort {
    bool operator()(ObjEntry* e1, ObjEntry* e2){ return e1->maxMs < e2->maxMs; }
};

void MessageTimer::Dump(){
    MILO_LOG("Message Tracker Dump!\n");
    std::sort(gEntries.begin(), gEntries.end(), MaxSort());
    for(int i = 0; i < gEntries.size(); i++){
        EventEntry* e = gEntries[i];
        std::sort(e->objs.begin(), e->objs.end(), ObjSort());
        e->Dump();
        for(int j = 0; j < e->objs.size(); j++){
            e->objs[j]->Dump();
        }
    }
}