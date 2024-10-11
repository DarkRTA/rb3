#include "game/GameConfig.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "utl/Symbols.h"

GameConfig* TheGameConfig;

GameConfig::GameConfig() : mPracticeSectionProvider(new PracticeSectionProvider()), mSongLimitMs(3.4028235E+38f), mPracticeSpeed(0), mPracticeMode(0) {
    MILO_ASSERT(!TheGameConfig, 0x38);
    TheGameConfig = this;
    mPlayerTrackConfigList = new PlayerTrackConfigList(4);
    unk2c = -1;
    unk28 = -1;
}

GameConfig::~GameConfig(){
    delete mPracticeSectionProvider;
    TheGameConfig = 0;
    delete mPlayerTrackConfigList;
}

int GameConfig::GetTrackNum(const UserGuid& userGuid) const {
    MILO_ASSERT(!userGuid.IsNull(), 0x4D);
    return mPlayerTrackConfigList->GetConfigByUserGuid(userGuid).mTrackNum;
}

Difficulty GameConfig::GetAverageDifficulty() const {
    int count = 0;
    int sum = 0;
    std::vector<BandUser*> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    for(std::vector<BandUser*>::iterator it = users.begin(); it != users.end(); ++it){
        BandUser* pUser = *it;
        MILO_ASSERT(pUser, 0x5B);
        count++;
        sum += pUser->GetDifficulty();
    }
    int ret = 0;
    if(count > 0) ret = sum / count;
    return (Difficulty)ret;
}

Symbol GameConfig::GetController(BandUser* user) const {
    bool lefty = false;
    GameplayOptions* options = user->GetGameplayOptions();
    MILO_ASSERT(options, 0x7E);
    if(options) lefty = options->GetLefty();

    int padnum = user->IsLocal() ? user->GetLocalUser()->GetPadNum() : -1;
    Symbol cnttype = JoypadControllerTypePadNum(padnum);
    DataArray* cfg = SystemConfig(joypad, controller_mapping);
    DataArray* assoc = cfg->FindArray(cnttype, true);
    MILO_ASSERT(assoc, 0x85);
    if(assoc->Type(1) == kDataSymbol) return assoc->Sym(1);
    else {
        MILO_ASSERT(assoc->Type(1) == kDataArray && assoc->Array(1)->Size() == 2, 0x87);
        return assoc->Array(1)->Sym(lefty == 0);
    }
}