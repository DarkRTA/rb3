#include "utl/SongInfoAudioType.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

SongInfoAudioType SymbolToAudioType(Symbol sym){
    if(sym == drum) return kAudioTypeDrum;
    else if(sym == guitar) return kAudioTypeGuitar;
    else if(sym == bass) return kAudioTypeBass;
    else if(sym == keys) return kAudioTypeKeys;
    else if(sym == vocals) return kAudioTypeVocals;
    else if(sym == multi) return kAudioTypeMulti;
    else {
        MILO_FAIL("No instrument for %s\n", sym);
        return kAudioTypeDrum;
    }
}

static const char* const unusedInstrumentAudioTypeStrings[] = {
    "drum", "guitar", "bass", "vocals", "keys", "multi", "fake"
};
