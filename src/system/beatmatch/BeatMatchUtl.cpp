#include "beatmatch/BeatMatchUtl.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "obj/Data.h"
#include "os/System.h"

namespace {
    static int gSlotsToNumSlots[32] = {
        0, 1, 1, 2, 1, 2, 2, 3,
        1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4,
        2, 3, 3, 4, 3, 4, 4, 5
    };
}

bool GemPlayableBy(int i, int j){
    bool ret = false;
    if(i == 0 || i & 1 << j) ret = true;
    return ret;
}

// fn_804595B4
int GemNumSlots(int slot_bitfield){
    MILO_ASSERT(0 <= slot_bitfield, 0x25);
    if((unsigned int)slot_bitfield < 0x20)
        return gSlotsToNumSlots[slot_bitfield];
    else {
        int ret = 0;
        int exp = 0;
        while(slot_bitfield){
            if(slot_bitfield & 1 << exp){
                slot_bitfield -= 1 << exp;
                ret++;
            }
            exp++;
        }
        return ret;
    }
}

// int fn_804595B4(uint param_1)

// {
//   int iVar1;
//   int iVar2;
  
//   if (param_1 < 0x20) {
//     return *(int *)(lbl_808835B8 + param_1 * 4);
//   }
//   iVar1 = 0;
//   iVar2 = 0;
//   while( true ) {
//     if (param_1 == 0) break;
//     if ((param_1 & 1 << iVar2) != 0) {
//       param_1 = param_1 - (1 << iVar2);
//       iVar1 = iVar1 + 1;
//     }
//     iVar2 = iVar2 + 1;
//   }
//   return iVar1;
// }

// fn_80459608
int ConsumeNumber(const char*& cc){
    int ret = 0;
    while(true){
        int num = *cc - 0x30;
        if(num < 0 || num > 9) break;
        cc++;
        ret = num + ret * 10;
    }
    return ret;
}

// int fn_80459608(char **param_1)

// {
//   int iVar1;
//   int iVar2;
  
//   iVar1 = 0;
//   while( true ) {
//     iVar2 = **param_1 + -0x30;
//     if ((iVar2 < 0) || (9 < iVar2)) break;
//     *param_1 = *param_1 + 1;
//     iVar1 = iVar2 + iVar1 * 10;
//   }
//   return iVar1;
// }

float VelocityBucketToDb(int bucket){
    DataArray* cfg = SystemConfig("beatmatcher", "audio");
    DataArray* found = cfg->FindArray("drum_velocity_to_db", false);
    if(found){
        DataArray* map = found->Array(1);
        MILO_ASSERT(0 <= bucket && bucket < map->Size(), 0x67);
        return map->Float(bucket);
    }
    else return 0.0f;
}

AudioType TrackTypeToAudioType(TrackType ty){
    switch(ty){
        case kTrackDrum:
            return (AudioType)0;
        case kTrackGuitar:
        case kTrackRealGuitar:
        case kTrackRealGuitar22Fret:
            return (AudioType)1;
        case kTrackBass:
        case kTrackRealBass:
        case kTrackRealBass22Fret:
            return (AudioType)2;
        case kTrackKeys:
        case kTrackRealKeys:
            return (AudioType)4;
        case kTrackVocals:
            return (AudioType)3;
        default:
            MILO_FAIL("No instrument for %d\n", ty);
            return (AudioType)0;
    }
}

float GetRollIntervalMs(const DataArray* cfg, TrackType ty, int idx, bool twoLanes){
    if(!cfg) return 0.0f;
    for(int x = 1; x < cfg->Size(); x++){
        DataArray* foundArr = cfg->Array(x);
        Symbol sym = foundArr->Sym(0);
        TrackType symType = SymToTrackType(sym);
        if(symType == ty){
            if(ty == kTrackDrum){
                if(twoLanes) foundArr = foundArr->FindArray("double_lane", true)->Array(1);
                else foundArr = foundArr->FindArray("single_lane", true)->Array(1);
            }
            else foundArr = foundArr->Array(1);

            if(!foundArr){
                MILO_WARN("Couldn't find roll interval data for %s.", sym);
                return 0.0f;
            }
            else return foundArr->Float(idx);
        }
    }
    return 0.0f;
}