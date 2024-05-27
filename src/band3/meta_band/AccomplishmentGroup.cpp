#include "AccomplishmentGroup.h"

#include "system/os/Debug.h"
#include "system/utl/Symbols2.h"
#include "system/utl/Symbols3.h"
#include "system/utl/Symbols4.h"

AccomplishmentGroup::AccomplishmentGroup(DataArray* i_pConfig, int index) : mName(""), mIndex(index), mInstrumentIcon(0x47), mScoreType((ScoreType)10), mAward("") {
    Configure(i_pConfig);
}

AccomplishmentGroup::~AccomplishmentGroup() {

}

void AccomplishmentGroup::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1d);

    mName = i_pConfig->Sym(0);
    
    i_pConfig->FindData(award, mAward, false);
    String instrumentIcon;
    i_pConfig->FindData(instrument_icon, instrumentIcon, true);
    int scoreType;
    i_pConfig->FindData(preferred_scoretype, scoreType, true);
    mScoreType = (ScoreType)scoreType;
    if (1 < instrumentIcon.length()) {
        TheDebug.Notify(MakeString("Accomplishment Group has an instrument icon that is more than 1 character long! GROUP: %s\n", mName.Str()));
        instrumentIcon = instrumentIcon.substr(0, 1);
    }
    if (instrumentIcon.length() == 0) {
        TheDebug.Notify(MakeString("Accomplishment Group has an instrument icon that is 0 characters long! GROUP: %s\n", mName.Str()));
    } else {
        mInstrumentIcon = instrumentIcon[0];
    }
}

int AccomplishmentGroup::GetIndex() const {
    return mIndex;
}

Symbol AccomplishmentGroup::GetName() const {
    return mName;
}

char AccomplishmentGroup::GetInstrumentIcon() {
    return mInstrumentIcon;
}

Symbol AccomplishmentGroup::GetAward() const {
    return mAward;
}

bool AccomplishmentGroup::HasAward() const {
    return !(mAward == "");
}

const char* unusedStrings[] = {
    "%s_desc", 
    "ui/accomplishments/group_art/%s_keep.png", 
    "%s_gray"
};
