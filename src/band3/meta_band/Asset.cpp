#include "Asset.h"

#include "system/os/Debug.h"

Asset::Asset(DataArray*, int) {

}

Asset::~Asset() {

}

Symbol Asset::GetDescription() const {
    return MakeString("%s_desc", mName);
}

void Asset::HasFinishes() {

}

void Asset::GetFinishes(std::vector<Symbol>&) const {

}

void Asset::GetFinish(int) const {

}

Symbol Asset::GetHint() const {
    return MakeString("%s_hint", mName);
}
