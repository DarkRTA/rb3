#include "meta_band/SelectDifficultyPanel.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/BandUI.h"
#include "meta_band/Campaign.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/TrainingMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

SelectDifficultyPanel::SelectDifficultyPanel()
    : mMarqueeRotationMs(3000.0f), mCurrentSongIx(0) {}

bool SelectDifficultyPanel::IsLoaded() const {
    return UIPanel::IsLoaded() && TheContentMgr->RefreshDone()
        && MetaPerformer::Current()->NumSongs() > 0;
}

void SelectDifficultyPanel::PollForLoading() {
    UIPanel::PollForLoading();
    if (TheContentMgr->RefreshDone() && TheGameMode->InMode(party_shuffle)
        && MetaPerformer::Current()->NumSongs() == 0
        && (TheSessionMgr->IsLocal() || TheSessionMgr->IsLeaderLocal())) {
        TheMusicLibrary->BuildPartySetlist();
        TheMusicLibrary->SendSetlistToMetaPerformer();
    }
}

UNPOOL_DATA
void SelectDifficultyPanel::Enter() {
    UIPanel::Enter();
    mCurrentSongIx = 0;
    MetaPerformer *mp = MetaPerformer::Current();
    if (mp) {
        int numsongs = mp->NumSongs();
        PushSongDetailsToScreen(mp);
        DataArray *rotArr = TypeDef()->FindArray(marquee_rotation_ms, false);
        if (rotArr) {
            mMarqueeRotationMs = rotArr->Float(1);
        }
        if (numsongs > 1)
            mMarqueeTimer.Restart();
        if (TheGameMode->InMode("tour")) {
            static Message updateSetlistLabel("update_tour_setlist_label", 0, 0);
            updateSetlistLabel[0] = TheTour->GetCurrentFilterName();
            updateSetlistLabel[1] = numsongs;
            HandleType(updateSetlistLabel);
        } else if (TheGameMode->InMode("party_shuffle")
                   || TheGameMode->InMode("qp_party_shuffle")) {
            static Message updateSetlistLabel("update_partyshuffle_setlist_label", 0);
            updateSetlistLabel[0] = numsongs;
            HandleType(updateSetlistLabel);
        } else if (mp->HasSetlist()) {
            static Message updateSetlistLabel("update_named_setlist_label", 0, 0);
            updateSetlistLabel[0] = mp->GetSetlistName();
            updateSetlistLabel[1] = numsongs;
            HandleType(updateSetlistLabel);
        } else {
            static Message updateSetlistLabel("update_setlist_label", 0);
            updateSetlistLabel[0] = numsongs;
            HandleType(updateSetlistLabel);
        }
    }

    if (TheModifierMgr) {
        static Message updateAutoVocalsLabel("update_auto_vocals_label", 0, 0, 0);
        updateAutoVocalsLabel[0] = TheBandUserMgr->GetNumParticipants();
        updateAutoVocalsLabel[1] = TheModifierMgr->IsModifierActive(mod_auto_vocals);
        updateAutoVocalsLabel[2] = TheSessionMgr->IsLocal();
        HandleType(updateAutoVocalsLabel);
    }

    OvershellPanel *overshell = TheBandUI.GetOvershell();
    MILO_ASSERT(overshell != NULL, 0x79);
    overshell->ClearTrackTypesFromUsers();
    if (TheGameMode->InMode("campaign") == 1) {
        overshell->SetPartRestrictedUser(TheCampaign->GetLaunchUser());
        overshell->SetPartRestriction(
            TheCampaign->GetRequiredTrackTypeForCurrentAccomplishment()
        );
        overshell->SetMinimumDifficulty(
            TheCampaign->GetMinimumDifficultyForCurrentAccomplishment()
        );
    } else if (TheGameMode->InMode("trainer") == 1) {
        TrainingMgr *trainingMgr = TrainingMgr::GetTrainingMgr();
        MILO_ASSERT(trainingMgr, 0x86);
        overshell->SetPartRestrictedUser(trainingMgr->GetUser());
        overshell->SetPartRestriction(kNumTrackTypes);
        overshell->SetMinimumDifficulty(trainingMgr->GetMinimumDifficulty());
    } else {
        overshell->SetPartRestrictedUser(nullptr);
        overshell->SetPartRestriction(kNumTrackTypes);
        overshell->SetMinimumDifficulty(kDifficultyEasy);
    }
    TheContentMgr->RegisterCallback(this, false);
}
END_UNPOOL_DATA

void SelectDifficultyPanel::Poll() {
    UIPanel::Poll();
    if (mMarqueeTimer.Running() && mMarqueeTimer.SplitMs() > mMarqueeRotationMs) {
        mMarqueeTimer.Restart();
        MetaPerformer *mp = MetaPerformer::Current();
        if (mp) {
            mCurrentSongIx++;
            mCurrentSongIx %= mp->NumSongs();
            PushSongDetailsToScreen(mp);
        }
    }
}

void SelectDifficultyPanel::Exit() {
    mMarqueeTimer.Stop();
    TheContentMgr->UnregisterCallback(this, true);
    UIPanel::Exit();
}

void SelectDifficultyPanel::PushSongDetailsToScreen(const MetaPerformer *mp) {
    Symbol theSong = mp->GetSongSymbol(mCurrentSongIx);
    static Message update_preview_song("update_preview_song", 0, 0, 0);
    update_preview_song[0] = theSong;

    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(
        TheSongMgr.GetSongIDFromShortName(theSong, true)
    );
    if (data && data->HasAlbumArt()) {
        if (TheSongMgr.IsSongMounted(theSong)) {
            update_preview_song[1] = TheSongMgr.GetAlbumArtPath(theSong);
        } else
            update_preview_song[1] = gNullStr;
    } else
        update_preview_song[1] = gNullStr;

    if (GetNumSongs() > 1) {
        update_preview_song[2] = (int)(mCurrentSongIx + 1);
    } else
        update_preview_song[2] = 0;

    HandleType(update_preview_song);
}

int SelectDifficultyPanel::GetNumSongs() const {
    int songs = 0;
    MetaPerformer *mp = MetaPerformer::Current();
    if (mp)
        songs = mp->NumSongs();
    return songs;
}

bool SelectDifficultyPanel::IsBattle() const {
    MetaPerformer *mp = MetaPerformer::Current();
    if (mp)
        return mp->GetBattleID() > 0;
    else
        return false;
}

void SelectDifficultyPanel::ContentMounted(const char *, const char *) {
    if (!TheContentMgr->RefreshInProgress() && MetaPerformer::Current()) {
        PushSongDetailsToScreen(MetaPerformer::Current());
    }
}

BEGIN_HANDLERS(SelectDifficultyPanel)
    HANDLE_EXPR(is_battle, IsBattle())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xFC)
END_HANDLERS