#include "bandobj/BandStarDisplay.h"
#include "utl/Symbols.h"

BandStarDisplay::BandStarDisplay() : mNumStars(0), unk190(this), unk19c(this), unk1a8(this), unk1b4(this), unk1c0(this, 0), unk1cc(this, 0), unk1d8(this, 0), mStarType("normal") {

}

BandStarDisplay::~BandStarDisplay(){
    
}

BEGIN_PROPSYNCS(BandStarDisplay)
    SYNC_PROP_SET(num_stars, mNumStars, SetNumStars(_val.Float(0), true))
    SYNC_PROP_SET(star_type, mStarType, SetStarType(_val.Sym(0), false))
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(BandStarDisplay)
    HANDLE_ACTION(reset, Reset())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x121)
END_HANDLERS