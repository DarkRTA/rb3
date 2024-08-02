#include "obj/MessageTimer.h"
#include "obj/DataFunc.h"

std::vector<EventEntry*> gEntries;

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