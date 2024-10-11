#include "meta_band/StandInProvider.h"
#include "ui/UIListLabel.h"
#include "meta_band/CharData.h"
#include "meta_band/AppLabel.h"
#include "utl/Symbols.h"

StandInProvider::StandInProvider(BandProfile* pf){
    Reload(pf);
}

void StandInProvider::Reload(BandProfile* pProfile){
    MILO_ASSERT(pProfile, 0x1B);
    mProfile = pProfile;
}

void StandInProvider::Text(int, int idx, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x21);
    MILO_ASSERT(label, 0x22);
    if(slot->Matches("name")){
        StandIn* standin = mProfile->GetStandIn(idx);
        if(standin->IsNone()){
            label->SetTextToken(none);
        }
        else if(standin->IsPrefabCharacter()){
            label->SetTextToken(standin->mName);
        }
        else if(standin->IsCustomCharacter()){
            CharData* pCharacter = mProfile->GetCharFromGuid(standin->mGuid);
            MILO_ASSERT(pCharacter, 0x36);
            AppLabel* pAppLabel = dynamic_cast<AppLabel*>(label);
            MILO_ASSERT(pAppLabel, 0x39);
            pAppLabel->SetFromCharacter(pCharacter);
        }
    }
    else label->SetTextToken(gNullStr);
}