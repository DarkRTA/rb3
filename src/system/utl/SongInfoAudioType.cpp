#include "utl/SongInfoAudioType.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

int SymbolToAudioType(Symbol sym){
    if(sym == drum) return 0;
    else if(sym == guitar) return 1;
    else if(sym == bass) return 2;
    else if(sym == keys) return 4;
    else if(sym == vocals) return 3;
    else if(sym == multi) return 6;
    else {
        MILO_FAIL("No instrument for %s\n", sym);
        return 0;
    }
}

static const char* const unusedInstrumentAudioTypeStrings[] = {
    "drum", "guitar", "bass", "vocals", "keys", "multi", "fake"
};
