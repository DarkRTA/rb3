#include "bandobj/ScoreDisplay.h"
#include "utl/Symbols.h"

ScoreDisplay::ScoreDisplay() : unk114(0), mScore(1000000), mRank(0), mGlobally(0), mTextColor(this, 0) {
    unk110 = Hmx::Object::New<BandLabel>();
}

ScoreDisplay::~ScoreDisplay(){
    
}

BEGIN_HANDLERS(ScoreDisplay)
    HANDLE(set_values, OnSetValues)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xDA)
END_HANDLERS

BEGIN_PROPSYNCS(ScoreDisplay)
    SYNC_PROP_MODIFY(score, mScore, UpdateDisplay())
    SYNC_PROP_MODIFY(rank, mRank, UpdateDisplay())
    SYNC_PROP_MODIFY(globally, mGlobally, UpdateDisplay())
    SYNC_PROP_MODIFY_ALT(text_color, mTextColor, unk110->SetColorOverride(mTextColor))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS