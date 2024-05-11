#include "Award.h"

Award::Award(DataArray*, int) {

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
}

Symbol Award::GetDisplayName() const{
    bool hasAssets = HasAssets();
}

bool Award::HasIconArt() const{

}
Symbol* Award::GetIconArt() const{
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