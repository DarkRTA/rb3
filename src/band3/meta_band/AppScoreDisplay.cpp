#include "meta_band/AppScoreDisplay.h"
#include "meta_band/AppLabel.h"
#include "os/Debug.h"

void AppScoreDisplay::UpdateDisplay(){
    AppLabel* label = dynamic_cast<AppLabel*>(mCombinedLabel);
    MILO_ASSERT(label, 0x10);
    label->SetFromScoreDisplayData(unk114, mScore, mRank, mGlobally);
}