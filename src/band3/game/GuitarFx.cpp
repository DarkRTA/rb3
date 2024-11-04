#include "game/GuitarFx.h"
#include "beatmatch/TrackType.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "rndobj/EventTrigger.h"
#include "synth/FxSend.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

GuitarFx::GuitarFx(TrackType ty) : unk1c(-1), unk20(0), unk21(0), mTrackType(ty), unk28(0x78), mFxCfg(0), unk3c(-1.0f), unk40(64.0f), unk44(0), unk4c(-1), unk50(-1), unk54(1), unk58(-1.0f) {

}

GuitarFx::~GuitarFx(){

}

void GuitarFx::Load(){
    const char* name = 0;
    switch(mTrackType){
        case 1:
            name = "sfx/guitar_fx.milo";
            mFxCfg = 0;
            break;
        case 2:
            mFxCfg = 0;
            name = "sfx/bass_fx.milo";
            break;
        default:
            MILO_FAIL("fx only for guitar and bass!");
            break;
    }
    mFxDir.LoadFile(FilePath(".", name), true, false, kLoadFront, false);
}

void GuitarFx::PostLoad(){
    mFxDir.PostLoad(0);
    mFxDir->Find<EventTrigger>("fx_reset.trig", true)->Trigger();
    mFxDir->Find<EventTrigger>("gains_off.trig", true)->Trigger();
    mFxDir->Find<EventTrigger>("reverb_off.trig", true)->Trigger();
    int nEffectsFound = 0;
    if(mFxCfg){
        for(ObjDirItr<FxSend> it(mFxDir, true); it != 0; ++it){
            DataArray* arr = mFxCfg->FindArray(it->Name(), false);
            if(arr && arr->Array(1)){
                nEffectsFound++;
                DataArray* nextarr = arr->Array(1);
                for(int i = 0; i < nextarr->Size(); i++){
                    DataArray* proparr = nextarr->Array(i);
                    it->SetProperty(proparr->Sym(0), proparr->Node(1));
                }
            }
        }
        MILO_ASSERT(nEffectsFound == mFxCfg->Size() - 1, 0x7E);
    }
}

void GuitarFx::Poll(int i1, bool b2, bool b3, float f4, float f5, float f6, bool b7, bool b8){
    int i8 = 3 - i1;
    if(i8 != unk1c){
        const char* trigname = "fx_reset.trig";
        if(i8 != -1){
            trigname = MakeString("fx_%i.trig", i8);
        }
        mFxDir->Find<EventTrigger>(trigname, true)->Trigger();
    }
    bool g7 = b2 || b3;
    if(unk20 != g7){
        const char* gainname = g7 ? "gains_on.trig" : "gains_off.trig";
        mFxDir->Find<EventTrigger>(gainname, true)->Trigger();
    }
    if(unk21 != b2){
        const char* reverbname = b2 ? "reverb_on.trig" : "reverb_off.trig";
        mFxDir->Find<EventTrigger>(reverbname, true)->Trigger();
    }
    unk1c = i8;
    unk20 = g7;
    unk21 = b2;
    if(f6 == 0) unk28++;
    else unk28 = 0;
    bool b54 = true;
    if(unk28 >= 0x78) b54 = false;
    ObjDirItr<FxSend> it(mFxDir, true);
    float negf6 = -f6;
    for( ; it != 0; ++it){
        it->EnableUpdates(false);
        DataNode* tempoprop = it->Property(tempo_sync, false);
        if(tempoprop && tempoprop->Int()){
            it->SetProperty(tempo, f4);
        }
        if(it->Property(beat_frac, false)){
            it->SetProperty(beat_frac, f5);
        }
        if(unk54 != b54){
            if(it->Property(auto_wah, false)){
                it->SetProperty(auto_wah, !b54);
            }
        }
        if(unk58 != f6){
            if(it->Property(frequency, false)){
                it->SetProperty(frequency, negf6);
            }
        }
        if(it->CanPushParameters()){
            it->EnableUpdates(true);
        }
    }
    unk54 = b54;
    unk58 = f6;
}

FxSend* GuitarFx::GetFxSend(){
    for(ObjDirItr<FxSend> it(mFxDir, true); it != 0; ++it){
        if(it->mStage == 0) return it;
    }
    MILO_WARN("couldn't find stage 0 guitar fx");
    return nullptr;
}

DataNode GuitarFx::OnMidiParser(DataArray* arr){
    unk40 = (float)arr->Int(2) + 24.0f;
    unk44 = arr->Float(3) + TheTaskMgr.Beat();
    return DataNode(kDataUnhandled, 0);
}

BEGIN_HANDLERS(GuitarFx)
    HANDLE(midi_parser, OnMidiParser)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x100)
END_HANDLERS