#include "synth/MoggClip.h"

MoggClip::PanInfo::PanInfo(int i, float f) : unk0(i), unk4(f) {}

MoggClip::MoggClip() : mFilePath(), mVolume(0.0f), mLoop(0), unk3c(0.0f), unk40(0), unk44(0.0f), unk48(0), unk4c(0), unk50(0), vec54(), unk5c() {
    Fader* f = Hmx::Object::New<Fader>();
    unk69 = 0;
    unk6a = 0;
    mLoopStart = 0;
    mLoopEnd = -1;
    unk64 = f;
    vec54.push_back(unk64);
    StartPolling();
}

MoggClip::~MoggClip(){

}

const char* MoggClip::GetSoundDisplayName(){
    if(unk6a){
        return MakeString("MoggClip: %s", FileGetName(mFilePath.c_str()));
    }
    return gNullStr;
}

SAVE_OBJ(MoggClip, 0x82)

BEGIN_COPYS(MoggClip)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(MoggClip)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mFilePath)
        COPY_MEMBER(mVolume)
        COPY_MEMBER(mLoop)
        COPY_MEMBER(mLoopStart)
        COPY_MEMBER(mLoopEnd)
    END_COPY_CHECKED
END_COPYS

void MoggClip::Load(BinStream& bs){
    PreLoad(bs);
    PostLoad(bs);
    MILO_WARN("%s:  Ogg files are not supported in RB3_Wii.", GetSoundDisplayName());
}