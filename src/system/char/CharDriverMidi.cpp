#include "char/CharDriverMidi.h"
#include "obj/MsgSource.h"

INIT_REVS(CharDriverMidi)

CharDriverMidi::CharDriverMidi() : mParser(), mFlagParser(), mClipFlags(0), mBlendOverridePct(1.0f) {
    
}

void CharDriverMidi::Enter(){
    unk89 = true;
    CharDriver::Enter();
    MsgSource* msgParser = dynamic_cast<MsgSource*>(Dir()->FindObject(mParser.Str(), true));
    if(msgParser) msgParser->AddSink(this, Symbol(), Symbol(), MsgSource::kHandle);
    MsgSource* msgFlagParser = dynamic_cast<MsgSource*>(Dir()->FindObject(mFlagParser.Str(), true));
    if(msgFlagParser) msgFlagParser->AddSink(this, Symbol(), Symbol(), MsgSource::kHandle);
}

void CharDriverMidi::Exit(){
    CharDriver::Exit();
    MsgSource* msgParser = dynamic_cast<MsgSource*>(ObjectDir::Main()->FindObject(mParser.Str(), false));
    if(msgParser) msgParser->RemoveSink(this, Symbol());
    MsgSource* msgFlagParser = dynamic_cast<MsgSource*>(ObjectDir::Main()->FindObject(mFlagParser.Str(), false));
    if(msgFlagParser) msgFlagParser->RemoveSink(this, Symbol());
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

