#include "beatmatch/TrackType.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"

static inline const char* TrackSymStr() {
    return "TRACK_SYMBOLS";
}

#pragma push
#pragma force_active on
inline Symbol TrackTypeToSym(TrackType type){
    return DataGetMacro(TrackSymStr())->Sym(type);
}
#pragma pop

static Symbol lol(TrackType ty){
    return TrackTypeToSym(ty);
}

TrackType SymToTrackType(Symbol sym){
    for(int i = 0; i < 11; i++){
        if(sym == TrackTypeToSym((TrackType)i)){
            return (TrackType)i;
        }
    }
    MILO_ASSERT(false, 0x1B);
    return kTrackNone;
}
