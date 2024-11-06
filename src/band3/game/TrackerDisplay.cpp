#include "game/TrackerDisplay.h"
#include "obj/Data.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

TrackerDisplay::TrackerDisplay(){

}

TrackerDisplay::~TrackerDisplay(){

}

void TrackerDisplay::MsToMinutesSeconds(float ms, int& min, int& sec){
    int totalsecs = ms / 1000.0f;
    min = totalsecs / 60;
    sec = totalsecs % 60;
}

DataArrayPtr TrackerDisplay::MakeIntegerTargetDescription(int i){
    return DataArrayPtr(tracker_integer_target, i);
}

DataArrayPtr TrackerDisplay::MakePercentTargetDescription(float perc){
    return DataArrayPtr(tracker_percentage_target, perc * 100.0f);
}

DataArrayPtr TrackerDisplay::MakeTimeTargetDescription(float ms){
    int min, sec;
    MsToMinutesSeconds(ms, min, sec);
    return DataArrayPtr(tracker_time_target, min, sec);
}

void TrackerDisplay::Initialize(Symbol s){
    static Message msg(show, 0);
    msg[0] = s;
    SendMsg(msg);
}

void TrackerDisplay::Show() const { SendMsg(show_msg); }
void TrackerDisplay::Hide() const { SendMsg(hide_msg); }

void TrackerDisplay::SetChallengeType(TrackerChallengeType ty) const {
    static Message msg(set_challenge_type, 0);
    msg[0] = ty;
    SendMsg(msg);
}

void TrackerDisplay::SetIntegerProgress(int i) const {
    static Message msg(set_int_progress, 0);
    msg[0] = i;
    SendMsg(msg);
}

#pragma push
#pragma pool_data off
void TrackerDisplay::SetPercentageProgress(float f) const {
    if(f < 0){
        DataArrayPtr ptr(tracker_percentage_missing);
        static Message msg(set_progress, 0);
        msg[0] = ptr;
        SendMsg(msg);
    }
    else {
        DataArrayPtr ptr(tracker_percentage, std::floor(f * 100.0f));
        static Message msg(set_progress, 0);
        msg[0] = ptr;
        SendMsg(msg);
    }
}
#pragma pop

void TrackerDisplay::SetTimeProgress(float ms) const {
    int totalsecs = ms / 1000.0f;
    DataArrayPtr ptr(tracker_time_remaining, totalsecs / 60, totalsecs % 60);
    static Message msg(set_progress, 0);
    msg[0] = ptr;
    SendMsg(msg);
}

void TrackerDisplay::HandleIncrement(){
    static Message msg(target_progress);
    SendMsg(msg);
}

void TrackerDisplay::ShowTarget(DataArrayPtr& ptr) const {
    static Message msg(set_target, 0);
    msg[0] = ptr;
    SendMsg(msg);
}

void TrackerDisplay::HandleTargetPass(int i, DataArrayPtr& ptr) const {
    static Message msg(advance_target, 0, 0);
    msg[0] = i;
    msg[1] = ptr;
    SendMsg(msg);
}

void TrackerDisplay::LastTargetPass() const {
    static Message msg(last_target_passed);
    SendMsg(msg);
}