#include "Asset.h"

#include "system/os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols3.h"

Asset::Asset(DataArray* pConfig, int i) : mName(gNullStr), unk_0x8(0), unk_0xC(0), unk_0x10(0), unk_0x1C(0), 
    unk_0x1D(0), unk_0x20(i) {
    MILO_ASSERT(pConfig, 21);
    mName = pConfig->Sym(0);
    Symbol s(gNullStr);
    pConfig->FindData(gender, s, false);
    {
        MILO_WARN("(%s) should not have \"finishes\" in ui/customize/assets.dta");
    }
}

Asset::~Asset() {

}

Symbol Asset::GetDescription() const {
    return MakeString("%s_desc", mName);
}

bool Asset::HasFinishes() {
    return mFinishes.size() != 0;
}

void Asset::GetFinishes(std::vector<Symbol>& v) const {
    for (int i = 0; i < mFinishes.size(); i++) {
        Symbol s = mFinishes[i];
        v.push_back(s);
    }
}

Symbol Asset::GetFinish(int index) const {
    MILO_ASSERT(( 0) <= (index) && (index) < ( mFinishes.size()), 100);
    return mFinishes[index];
}

Symbol Asset::GetHint() const {
    return MakeString("%s_hint", mName);
}
