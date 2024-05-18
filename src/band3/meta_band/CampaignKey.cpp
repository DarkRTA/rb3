#include "CampaignKey.h"
#include "os/Debug.h"

CampaignKey::CampaignKey(DataArray* da) : mName("") { Configure(da); }
CampaignKey::~CampaignKey() { }

void CampaignKey::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 25);
    mName = i_pConfig->Sym(0);
}

Symbol CampaignKey::GetName() const { return mName; }

const char* strip = "%s_desc";