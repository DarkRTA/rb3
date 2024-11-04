#include "game/KeysFx.h"
#include "beatmatch/TrackType.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "synth/FxSend.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

KeysFx::KeysFx(TrackType ty) : mTrackType(ty), unk20(0x78), unk31(1), unk34(-1.0f) {

}

KeysFx::~KeysFx(){

}

void KeysFx::Load(){
    mFxDir.LoadFile(FilePath(".", "sfx/keys_fx.milo"), true, false, kLoadFront, false);
}

void KeysFx::PostLoad(){
    mFxDir.PostLoad(0);
}

void KeysFx::Poll(bool b1, bool b2, float f3, float f4, float f5){
    static DataNode& capstrip_motion = DataVariable("capstrip_motion");
    static DataNode& dump_wah = DataVariable("dump_wah");
    if(capstrip_motion.Int()){
        f5 = (float)capstrip_motion.Int() / 100.0f;
    }
    if(f5 == 0) unk20++;
    else unk20 = 0;
    bool b54 = true;
    if(unk20 >= 0x78) b54 = false;
    ObjDirItr<FxSend> it(mFxDir, true);
    float minprod = f5 * 4.0f;
    float freq = 1.0f - f5;
    for(; it != 0; ++it){
        it->EnableUpdates(false);
        DataNode* tempoprop = it->Property(tempo_sync, false);
        if(tempoprop && tempoprop->Int()){
            it->SetProperty(tempo, f3);
        }
        if(it->Property(beat_frac, false)){
            it->SetProperty(beat_frac, f4);
        }
        if(it->Property(dump, false)){
            if(dump_wah.Float() != 0){
                it->SetProperty(dump, dump_wah.Float());
            }
        }
        if(unk34 != f5){
            float min = Min(1.0f, minprod);
            float cos6 = std::cos(min * 1.5707964f);
            float log6 = std::log10(cos6 + 0.001f) * 20.0f;
            float cos7 = std::cos((1.0f - min) * 1.5707964f);
            float log7 = std::log10(cos7 + 0.001f) * 20.0f;
            if(it->Property(frequency, false)){
                it->SetProperty(frequency, freq);
            }
            if(it->Property(wet_gain, false)){
                it->SetProperty(wet_gain, log7);
            }
            if(it->Property(dry_gain, false)){
                it->SetProperty(dry_gain, log6);
            }
        }
        if(it->CanPushParameters()){
            it->EnableUpdates(true);
        }
    }
    unk31 = b54;
    unk34 = f5;
}

FxSend* KeysFx::GetFxSend(){
    for(ObjDirItr<FxSend> it(mFxDir, true); it != 0; ++it){
        if(it->mStage == 0) return it;
    }
    MILO_WARN("couldn't find stage 0 keys fx");
    return nullptr;
}

BEGIN_HANDLERS(KeysFx)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x9B)
END_HANDLERS