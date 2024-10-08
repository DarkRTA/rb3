#include "beatmatch/Playback.h"
#include "obj/Data.h"
#include "math/MathFuncs.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "obj/DataFile.h"
#include "beatmatch/BeatMatcher.h"

Playback TheBeatMatchPlayback;

#define kMaxNumberOfPlayers 8

Playback::Playback() : mPlayerIndex(0), mCommands(0), mCommandIndex(0), mTime(0.0f) {
    for(int i = 0; i < 8; i++) mPlayerSinks[i] = 0;
}

Playback::~Playback(){
    if(mCommands){
        mCommands->Release();
        mCommands = 0;
    }
}

// fn_80471F34
void Playback::Poll(float f){
    if(mCommands){
        int cmdSize = mCommands->Size();
        if(mCommandIndex < mCommands->Size()){
            DataArray* arr = mCommands->Array(mCommandIndex);
            float floc = 0.0f;
            if(1 < arr->Size()){
                DataNode& node = arr->Node(1);
                if(node.Type() == kDataFloat){
                    floc = node.Float(0);
                }
            }

            while(floc <= mTime || mTime < f && (std::fabs(floc - mTime) < std::fabs(floc - f))){
                DoCommand(arr);
                mCommandIndex++;
                if(mCommandIndex >= cmdSize) break;
                arr = mCommands->Array(mCommandIndex);
                if(1 < arr->Size()){
                    DataNode& node = arr->Node(1);
                    if(node.Type() == kDataFloat){
                        floc = node.Float(0);
                    }
                }
            }
            mTime = f;
        }
    }
}

void Playback::DoCommand(DataArray* arr){
    if(4 <= arr->Size()){
        int player = arr->Int(0);
        MILO_ASSERT(player < kMaxNumberOfPlayers, 0x5E);
        BeatMatcher* sink = mPlayerSinks[player];
        if(sink){
            Symbol sym = arr->Sym(2);
            if(sym == SWING){
                sink->Swing(arr->Int(3), arr->Int(4) != 0, true, false, arr->Int(4) != 0, kGemHitFlagNone);
            }
            else if(sym == UP){
                sink->FretButtonUp(arr->Int(3));
            }
            else if(sym == DOWN){
                sink->FretButtonDown(arr->Int(3), -1);
            }
            else if(sym == TRACK){
                sink->SetTrack(arr->Int(3));
            }
            else if(sym == HOPO){
                sink->NonStrumSwing(arr->Int(3), arr->Int(4) != 0, false);
            }
            else if(sym == FLIP){
                sink->MercurySwitch(arr->Float(3));
            }
            else if(sym == FFLIP){
                sink->ForceMercurySwitch(arr->Int(3) != 0);
            }
        }
    }
}

bool Playback::LoadFile(const class String& str){
    if(mCommands) mCommands->Release();
    mCommands = 0;
    mCommandIndex = 0;
    mCommands = DataReadFile(str.c_str(), true);
    return mCommands != 0;
}

void Playback::AddSink(BeatMatcher* bm){
    for(int i = 0; i < 8; i++){
        if(mPlayerSinks[i] == bm){
            mPlayerSinks[i] = 0;
            break;
        }
    }
    mPlayerSinks[mPlayerIndex++] = bm;
    if(mPlayerIndex < 8) return;
    mPlayerIndex = 0;
}

void Playback::Jump(float f){
    mCommandIndex = 0;
    mTime = f;
    if(mCommands){
        for(int i = 0; i < mCommands->Size(); i++){
            DataArray* arr = mCommands->Array(mCommandIndex);
            if(1 < arr->Size()){
                DataNode& node = arr->Node(1);
                if(node.Type() == kDataFloat){
                    if(node.Float(0) > f){
                        mCommandIndex = (mCommandIndex - 1) > 0 ? (mCommandIndex - 1) : 0;
                        return;
                    }
                }
            }
        }
    }
}

int Playback::GetPlaybackNum(BeatMatcher* bm){
    for(int i = 0; i < 8; i++){
        if(mPlayerSinks[i] == bm) return i;
    }
    MILO_FAIL("Couldn't find sink for playback.\n");
    return -1;
}
