#include "game/GameConfig.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/SessionMgr.h"
#include "net/NetSession.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

GameConfig *TheGameConfig;

GameConfig::GameConfig()
    : mPracticeSectionProvider(new PracticeSectionProvider()),
      mSongLimitMs(3.4028235E+38f), mPracticeSpeed(0), mPracticeMode(0) {
    MILO_ASSERT(!TheGameConfig, 0x38);
    TheGameConfig = this;
    mPlayerTrackConfigList = new PlayerTrackConfigList(4);
    unk2c = -1;
    unk28 = -1;
}

GameConfig::~GameConfig() {
    delete mPracticeSectionProvider;
    TheGameConfig = 0;
    delete mPlayerTrackConfigList;
}

int GameConfig::GetTrackNum(const UserGuid &userGuid) const {
    MILO_ASSERT(!userGuid.IsNull(), 0x4D);
    return mPlayerTrackConfigList->GetConfigByUserGuid(userGuid).mTrackNum;
}

Difficulty GameConfig::GetAverageDifficulty() const {
    int count = 0;
    int sum = 0;
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    for (std::vector<BandUser *>::iterator it = users.begin(); it != users.end(); ++it) {
        BandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x5B);
        count++;
        sum += pUser->GetDifficulty();
    }
    int ret = 0;
    if (count > 0)
        ret = sum / count;
    return (Difficulty)ret;
}

Symbol GameConfig::GetController(BandUser *user) const {
    bool lefty = false;
    GameplayOptions *options = user->GetGameplayOptions();
    MILO_ASSERT(options, 0x7E);
    if (options)
        lefty = options->GetLefty();

    int padnum = user->IsLocal() ? user->GetLocalUser()->GetPadNum() : -1;
    Symbol cnttype = JoypadControllerTypePadNum(padnum);
    DataArray *cfg = SystemConfig(joypad, controller_mapping);
    DataArray *assoc = cfg->FindArray(cnttype, true);
    MILO_ASSERT(assoc, 0x85);
    if (assoc->Type(1) == kDataSymbol)
        return assoc->Sym(1);
    else {
        MILO_ASSERT(assoc->Type(1) == kDataArray && assoc->Array(1)->Size() == 2, 0x87);
        return assoc->Array(1)->Sym(lefty == 0);
    }
}

bool GameConfig::IsInstrumentUsed(Symbol s) const {
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    FOREACH (it, users) {
        BandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x92);
        if (pUser->GetTrackSym() == s)
            return true;
    }
    return false;
}

bool GameConfig::CanEndGame() const {
    if (!TheNetSession->IsInGame())
        return false;
    else {
        BandUser *user = TheSessionMgr->GetLeaderUser();
        if (!user)
            return true;
        else if (!TheNetSession->HasUser(user))
            return false;
        else
            return user->IsLocal();
    }
}

void GameConfig::AssignTrack(BandUser *u) {
    bool net = !u->IsLocal();
    TrackType ty = u->GetTrackType();
    MetaPerformer *pPerformer = MetaPerformer::Current();
    MILO_ASSERT(pPerformer, 0xC9);
    switch (ty) {
    case kTrackVocals:
        mPlayerTrackConfigList->SetUseVocalHarmony(pPerformer->IsNowUsingVocalHarmony());
        break;
    case kTrackRealGuitar:
    case kTrackRealBass:
        if (u->mHas22FretGuitar) {
            if (ty == kTrackRealGuitar)
                ty = kTrackRealGuitar22Fret;
            else
                ty = kTrackRealBass22Fret;
        }
        break;
    case kTrackDrum:
        bool cymsYes = TheGame->mProperties.mForceUseCymbals;
        bool cymsNo = TheGame->mProperties.mForceDontUseCymbals;
        bool pro = pPerformer->IsUsingRealDrums();
        if (cymsYes)
            pro = true;
        else if (cymsNo)
            pro = false;
        mPlayerTrackConfigList->SetUseRealDrums(pro);
        break;
    case kTrackKeys:
        mPlayerTrackConfigList->unk2c = u->GetControllerType() == kControllerKeys;
        break;
    case kTrackRealKeys:
        mPlayerTrackConfigList->unk2c = true;
        break;
    default:
        break;
    }
    if (pPerformer->PartPlaysInSong(u->GetTrackSym())) {
        int slot = TheBandUserMgr->GetSlot(u->GetUserGuid());
        MILO_ASSERT(slot != -1, 0x108);
        mPlayerTrackConfigList->UpdateConfig(
            u->GetUserGuid(), ty, u->GetDifficulty(), slot, net
        );
    }
}

void GameConfig::AssignTracks() {
    bool b11 = false;
    mPlayerTrackConfigList->Reset();
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsersInSession(users);
    for (int i = 0; i < users.size(); i++) {
        BandUser *u = users[i];
        mPlayerTrackConfigList->AddPlaceholderConfig(
            u->GetUserGuid(), u->GetSlot(), !u->IsLocal()
        );
    }
    for (int i = 0; i < users.size(); i++) {
        AssignTrack(users[i]);
        if (users[i]->GetTrackType() == kTrackVocals) {
            b11 = true;
        }
    }
    if (!b11) {
        bool autoVox = TheModifierMgr->IsModifierActive(mod_auto_vocals);
        bool b1 = TheGame->mProperties.mAllowAutoVocals;
        MetaPerformer *pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0x13A);
        bool bigbool = autoVox && b1 && pPerformer->PartPlaysInSong("vocals");
        mPlayerTrackConfigList->SetAutoVocals(bigbool);
        if (bigbool) {
            NullLocalBandUser *user = TheBandUserMgr->GetNullUser();
            MetaPerformer *pPerformer = MetaPerformer::Current();
            MILO_ASSERT(pPerformer, 0x145);
            mPlayerTrackConfigList->SetUseVocalHarmony(pPerformer->SongAllowsVocalHarmony(
            ));
            user->SetTrackType(kTrackVocals);
            user->SetDifficulty(kDifficultyMedium);
            mPlayerTrackConfigList->AddConfig(
                user->GetUserGuid(), user->GetTrackType(), user->GetDifficulty(), -1, false
            );
        }
    }
}

void GameConfig::ChangeDifficulty(BandUser *u, int i) {
    mPlayerTrackConfigList->ChangeDifficulty(u->GetUserGuid(), i);
}

void GameConfig::RemoveUser(BandUser *u) {
    mPlayerTrackConfigList->RemoveConfig(u->GetUserGuid());
}