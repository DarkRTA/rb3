#include "bandobj/BandScoreboard.h"
#include "utl/Symbols.h"

BandScoreboard::BandScoreboard() : mScore(-1), unk190(this, 0), unk19c(this, 0), unk1a8(this), unk1b4(this), mStarDisplay(this, 0) {

}

BandScoreboard::~BandScoreboard(){
    
}

BEGIN_PROPSYNCS(BandScoreboard)
    SYNC_PROP_SET(score, mScore, SetScore(_val.Int(0)))
    SYNC_PROP_SET(num_stars, GetNumStars(), SetNumStars(_val.Float(0), true))
    SYNC_PROP(star_display, mStarDisplay)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(BandScoreboard)
    HANDLE_ACTION(reset, Reset())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0xE0)
END_HANDLERS