#include "game/TrackerDisplay.h"
#include "bandobj/BandTrack.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/TrackType.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

float TrackerDisplay::kMissingPercentage = -1.0f;

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

TrackerBandDisplay::TrackerBandDisplay(){

}

TrackerBandDisplay::~TrackerBandDisplay(){

}

void TrackerBandDisplay::SetType(TrackerBandDisplayType ty) const {
    static Message msg(set_display_type, 0);
    msg[0] = ty;
    SendMsg(msg);
}

void TrackerBandDisplay::SetStyle(TrackerBandDisplayStyle sty) const {
    static Message msg(set_display_style, 0);
    msg[0] = sty;
    SendMsg(msg);
}

void TrackerBandDisplay::SetSuccessState(bool b) const {
    static Message msg(set_success_state, 0);
    msg[0] = b;
    SendMsg(msg);
}

void TrackerBandDisplay::SetProgressPercentage(float f) const {
    static Message msg(set_progress_percentage, 0.0f);
    msg[0] = f;
    SendMsg(msg);
}

void TrackerBandDisplay::SendMsg(const Message& msg) const {
    GetTrackPanel()->SendTrackerDisplayMessage(msg);
}

TrackerPlayerDisplay::TrackerPlayerDisplay() : mPlayer(0) {

}

TrackerPlayerDisplay::~TrackerPlayerDisplay(){

}

void TrackerPlayerDisplay::Hide() const { TrackerDisplay::Hide(); }

void TrackerPlayerDisplay::Enable() const {
    SendMsg(enable_msg);
    bool cansend = mPlayer && mPlayer->IsLocal();
    if(cansend){
        SendPlayerDisplayMsg((NetDisplayMsg)0, 0, 0);
    }
}

void TrackerPlayerDisplay::Disable() const { return SendMsg(disable_msg); }

void TrackerPlayerDisplay::GainFocus(bool gain) const {
    static Message msg(gain_focus, 0);
    msg[0] = gain;
    SendMsg(msg);
    bool cansend = mPlayer && mPlayer->IsLocal();
    if(cansend){
        SendPlayerDisplayMsg((NetDisplayMsg)1, gain, 0);
    }
}

void TrackerPlayerDisplay::LoseFocus(bool lose) const {
    static Message msg(lose_focus, 0);
    msg[0] = lose;
    SendMsg(msg);
    bool cansend = mPlayer && mPlayer->IsLocal();
    if(cansend){
        SendPlayerDisplayMsg((NetDisplayMsg)2, lose, 0);
    }
}

void TrackerPlayerDisplay::SetSuccessState(bool succ) const {
    static Message msg(set_success_state, 0);
    msg[0] = succ;
    SendMsg(msg);
}

void TrackerPlayerDisplay::Pulse(bool topulse) const {
    static Message msg(pulse, 0);
    msg[0] = topulse;
    SendMsg(msg);
    bool cansend = mPlayer && mPlayer->IsLocal();
    if(cansend){
        SendPlayerDisplayMsg((NetDisplayMsg)3, topulse, 0);
    }
}

void TrackerPlayerDisplay::SetProgressPercentage(float perc, bool b) const {
    static Message msg(set_progress_percentage, 0.0f, 0);
    msg[0] = perc;
    msg[1] = b;
    SendMsg(msg);
}

void TrackerPlayerDisplay::FillProgressAndReset(bool b) const {
    if(!b || (mPlayer && mPlayer->GetTrackType() == kTrackVocals)){
        SendMsg(fill_progress_and_reset_msg);
    }
    bool cansend = mPlayer && mPlayer->IsLocal();
    if(cansend){
        SendPlayerDisplayMsg((NetDisplayMsg)4, b, 0);
    }
}

void TrackerPlayerDisplay::SetSecondaryStateLevel(int i) const {
    static Message msg(set_secondary_state_level, 0.0f);
    msg[0] = i;
    SendMsg(msg);
    bool cansend = mPlayer && mPlayer->IsLocal();
    if(cansend){
        SendPlayerDisplayMsg((NetDisplayMsg)5, i, 0);
    }
}

void TrackerPlayerDisplay::RemotePlayerDisplayMsg(int i1, int i2, int i3) const {
    switch(i1){
        case 0:
            Enable();
            break;
        case 1:
            GainFocus(i2);
            break;
        case 2:
            LoseFocus(i2);
            break;
        case 3:
            Pulse(i2);
            break;
        case 4:
            FillProgressAndReset(i2);
            break;
        case 5:
            SetSecondaryStateLevel(i2);
            break;
        default:
            MILO_WARN("Unhandled tracker player display msg: %d %d %d.\n", i1, i2, i3);
            break;
    }
}

void TrackerPlayerDisplay::SendPlayerDisplayMsg(NetDisplayMsg msg, int i1, int i2) const {
    if(mPlayer){
        static Message displayMsg("send_tracker_player_display", 0, 0, 0);
        displayMsg[0] = msg;
        displayMsg[1] = i1;
        displayMsg[2] = i2;
        mPlayer->HandleType(displayMsg);
    }
}

void TrackerPlayerDisplay::SendMsg(const Message& msg) const {
    MILO_ASSERT(mPlayer, 0x233);
    BandTrack* track = mPlayer->GetBandTrack();
    if(track) track->SendTrackerDisplayMessage(msg);
}

TrackerBroadcastDisplay::TrackerBroadcastDisplay(){

}

TrackerBroadcastDisplay::~TrackerBroadcastDisplay(){

}

void TrackerBroadcastDisplay::Broadcast(const DataArrayPtr& ptr, Symbol s){
    SetType((BroadcastDisplayType)0);
    static Message msg(broadcast, 0, 0);
    msg[0] = ptr;
    msg[1] = s;
    SendMsg(msg);
}

void TrackerBroadcastDisplay::SetType(BroadcastDisplayType ty) const {
    static Message msg(set_display_type, 0);
    msg[0] = ty;
    SendMsg(msg);
}

void TrackerBroadcastDisplay::SetSecondaryStateLevel(int level) const {
    static Message msg(set_secondary_state_level, 0);
    msg[0] = level;
    SendMsg(msg);
}

void TrackerBroadcastDisplay::SetBandMessage(const DataArrayPtr& ptr) const {
    SetType((BroadcastDisplayType)1);
    static Message msg(set_band_message, 0);
    msg[0] = ptr;
    SendMsg(msg);
}

void TrackerBroadcastDisplay::ShowBriefBandMessage(const DataArrayPtr& ptr) const {
    SetType((BroadcastDisplayType)1);
    static Message msg(show_brief_band_message, 0);
    msg[0] = ptr;
    SendMsg(msg);
}

void TrackerBroadcastDisplay::SendMsg(const Message& msg) const {
    GetTrackPanel()->SendTrackerBroadcastDisplayMessage(msg);
}