#include "Award.h"

Award::Award(DataArray*, int) : mName(""), mIconArt("") {

}

Award::~Award() {

}

void Award::Configure(DataArray *) {

}

Symbol Award::GetName() const{
    return mName;
}

Symbol Award::GetDescription() const{
    bool hasAssets = HasAssets();
    if(!hasAssets){
        return Symbol("award_genericdesc");
    }
}

Symbol Award::GetDisplayName() const{
    bool hasAssets = HasAssets();
}

bool Award::HasIconArt() const {
    bool noIcon;

    if (gNullStr) {
        noIcon = !strcmp(mIconArt.Str(), gNullStr);
    } else {
        noIcon = (mIconArt.Str() == gNullStr);
    }

    return !noIcon;
}

Symbol Award::GetIconArt() const{
    return mIconArt;
}

bool Award::IsBonus() const{
    return mIsBonus;
}

void Award::InqAssets(std::vector<Symbol>&) {

}

bool Award::HasAssets() const{
    return false;
}