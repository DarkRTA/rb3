#include "AccomplishmentCategory.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h"

#include "decomp.h"

AccomplishmentCategory::AccomplishmentCategory(const DataArray* config, int index): mIndex(index), mName(""), mGroup(""), mAward("") {
    Configure(config);
}

AccomplishmentCategory::~AccomplishmentCategory(){
}
void AccomplishmentCategory::Configure(const DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1e);

    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(group, mGroup, true);
    i_pConfig->FindData(award, mAward, false);
}

Symbol AccomplishmentCategory::GetName() const {
    return mName;
}

int AccomplishmentCategory::GetIndex() const {
    return mIndex;
}

Symbol AccomplishmentCategory::GetGroup() const {
    return mGroup;
}

Symbol AccomplishmentCategory::GetAward() const {
    return mAward;
}

bool AccomplishmentCategory::HasAward() const {
    return !(mAward == "");
}

DECOMP_FORCEACTIVE(AccomplishmentCategory,
    "%s_desc",
    "ui/accomplishments/category_art/%s_keep.png",
    "%s_gray"
)
