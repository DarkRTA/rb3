#include "beatmatch/DrumPlayer.h"
#include "obj/Data.h"
#include "os/System.h"
#include "synth/Sequence.h"

DrumPlayer::DrumPlayer(SongInfo& info){
    v1 = info.GetDrumSoloSamples();
    mAttenuation = SystemConfig("beatmatcher", "audio")->FindFloat("drum_sample_attenuation");
}

DrumPlayer::~DrumPlayer(){
    mDrumKitBank = 0;
}

void DrumPlayer::Play(int i, float f){
    static const char* seq_names[9] = {
        "kick.cue", "snare.cue", "tom1.cue", "tom2.cue", "crash.cue", "hat.cue", "hatopen.cue", "ride.cue", "tom3.cue"
    };

    std::vector<Symbol>& v = v1;
    
    if(!v2.empty()) v = v2;
    
    if(!v.empty()){
        const char* name = (i < v.size()) ? v[i].Str() : seq_names[i];
        MILO_ASSERT(mDrumKitBank, 0x43);
        if(i == 5){
            Sequence* old_seq = mDrumKitBank->Find<Sequence>(seq_names[6], true);
            MILO_ASSERT(old_seq, 0x49);
            old_seq->Stop(false);
        }
        Sequence* seq = mDrumKitBank->Find<Sequence>(name, true);
        MILO_ASSERT(seq, 0x4E);
        seq->Play(f - mAttenuation, 0, 0);
    }
}

DECOMP_FORCEACTIVE(DrumPlayer, "seq_list")