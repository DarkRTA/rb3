#include "char/CharDriverMidi.h"
#include "obj/MsgSource.h"
#include "char/CharClip.h"
#include "char/CharClipGroup.h"
#include "utl/TimeConversion.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

INIT_REVS(CharDriverMidi)

CharDriverMidi::CharDriverMidi() : mParser(), mFlagParser(), mClipFlags(0), mBlendOverridePct(1.0f) {
    
}

void CharDriverMidi::Enter(){
    unk89 = true;
    CharDriver::Enter();
    MsgSource* msgParser = dynamic_cast<MsgSource*>(Dir()->FindObject(mParser.Str(), true));
    if(msgParser) msgParser->AddSink(this);
    MsgSource* msgFlagParser = dynamic_cast<MsgSource*>(Dir()->FindObject(mFlagParser.Str(), true));
    if(msgFlagParser) msgFlagParser->AddSink(this);
}

void CharDriverMidi::Exit(){
    CharDriver::Exit();
    MsgSource* msgParser = dynamic_cast<MsgSource*>(ObjectDir::Main()->FindObject(mParser.Str(), false));
    if(msgParser) msgParser->RemoveSink(this);
    MsgSource* msgFlagParser = dynamic_cast<MsgSource*>(ObjectDir::Main()->FindObject(mFlagParser.Str(), false));
    if(msgFlagParser) msgFlagParser->RemoveSink(this);
}

void CharDriverMidi::Poll(){ CharDriver::Poll(); }

void CharDriverMidi::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    CharDriver::PollDeps(changedBy, change);
}

SAVE_OBJ(CharDriverMidi, 0x58)

BEGIN_LOADS(CharDriverMidi)
    LOAD_REVS(bs)
    ASSERT_REVS(7, 0)
    LOAD_SUPERCLASS(CharDriver)
    if(gRev < 7){
        ObjectDir* dir = mClips;
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if(!dir && mDefaultClip){
            dir = mDefaultClip->Dir();
        }
        if(mDefaultClip && dir){
            mDefaultClip = dir->FindObject(buf, false);
        }
        else {
            mDefaultClip = 0;
        }
    }
    if(gRev == 2){
        String str; bs >> str;
    }
    else if(gRev > 3) bs >> mParser;
    if(gRev > 4) bs >> mFlagParser;
    if(gRev > 5) bs >> mBlendOverridePct;
END_LOADS

BEGIN_COPYS(CharDriverMidi)
    COPY_SUPERCLASS(CharDriver)
    CREATE_COPY(CharDriverMidi)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(unk89)
        COPY_MEMBER(mParser)
        COPY_MEMBER(mFlagParser)
        COPY_MEMBER(mBlendOverridePct)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharDriverMidi)
    HANDLE(midi_parser, OnMidiParser)
    HANDLE(midi_parser_group, OnMidiParserGroup)
    HANDLE(midi_parser_flags, OnMidiParserFlags)
    HANDLE_SUPERCLASS(CharDriver)
    HANDLE_CHECK(0x99)
END_HANDLERS

float minblendWidth = 0.0f;

// fn_804C945C
DataNode CharDriverMidi::OnMidiParser(DataArray* da){
    CharClip* clip;
    bool b = false;
    if(!unk89 && mDefaultClip) b = true;
    if(b){
        clip = dynamic_cast<CharClip*>(mDefaultClip.Ptr());
    }
    else clip = FindClip(da->Node(2), false);
    if(!clip) return DataNode(0);
    if(clip || clip != FirstClip()){
        float somefloat = da->Float(3);
        if(clip->mPlayFlags & 0x200){
            float secs = TheTaskMgr.Seconds(TaskMgr::b);
            float bts = BeatToSeconds(somefloat + TheTaskMgr.Beat());
            float sub = (clip->AverageBeatsPerSecond() - secs);
            somefloat = sub * bts;
        }
        MaxEq(somefloat, minblendWidth);
        Play(clip, 0, somefloat * mBlendOverridePct, -somefloat, 0.0f);
    }
    return DataNode(0);
}

DataNode CharDriverMidi::OnMidiParserFlags(DataArray* da){
    mClipFlags = da->Int(2);
    return DataNode(0);
}

DataNode CharDriverMidi::OnMidiParserGroup(DataArray* da){
    const char* name = da->Str(2);
    CharClipGroup* grp = dynamic_cast<CharClipGroup*>(mClips->FindObject(name, false));
    if(!grp){
        MILO_WARN("%s could not find group %s in %s", PathName(this), name, mClips->Name());
        return DataNode(0);
    }
    else {
        CharClip* clip;
        bool b = false;
        if(!unk89 && mDefaultClip) b = true;
        if(b) clip = dynamic_cast<CharClip*>(mDefaultClip.Ptr());
        else clip = grp->GetClip(mClipFlags);
        if(!clip){
            MILO_WARN("%s could not find clip with flags %d in %s", PathName(this), mClipFlags, PathName(grp));
            return DataNode(0);
        }
        else {
            if(clip || clip != FirstClip()){
                float somefloat = da->Float(3);
                if(clip->mPlayFlags & 0x200){
                    somefloat *= clip->AverageBeatsPerSecond();
                }
                MaxEq(somefloat, minblendWidth);
                Play(clip, 0, -somefloat, 1e+30f, 0.0f); // returns something, which you then modify
            }
            return DataNode(0);
        }
    }
}

BEGIN_PROPSYNCS(CharDriverMidi)
    SYNC_PROP(parser, mParser)
    SYNC_PROP(flag_parser, mFlagParser)
    SYNC_PROP(blend_override_pct, mBlendOverridePct)
    SYNC_SUPERCLASS(CharDriver)
END_PROPSYNCS