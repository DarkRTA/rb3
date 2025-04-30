#include "meta_band/AppLabel.h"
#include "bandobj/BandTrack.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Scoring.h"
#include "macros.h"
#include "meta_band/BandMachineMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MainHubMessageProvider.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SongRecord.h"
#include "meta_band/SongSortNode.h"
#include "meta_band/Utl.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "ui/UIListSlot.h"
#include "utl/Locale.h"
#include "utl/MakeString.h"
#include "utl/Messages2.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

DECOMP_FORCEACTIVE(AppLabel, "%s) %s")

void AppLabel::SetLeaderboardName(const LeaderboardRow &lb) {
    if (lb.mUnnamedBand) {
        DataNode word = band_default_name;
        DataNode count = lb.mName.c_str();
        DataArray *da = new DataArray(2);
        da->Node(0) = count;
        da->Node(1) = word;
        SetTokenFmt(da);
        da->Release();
    } else {
        SetDisplayText(lb.mName.c_str(), true);
    }
}

void AppLabel::SetLeaderboardRankAndName(const LeaderboardRow &lb) {
    if (lb.mUnnamedBand) {
        SetDisplayText(
            MakeString(
                "%s) %s",
                LocalizeSeparatedInt(lb.mRank),
                MakeString(Localize(band_default_name, nullptr), lb.mName.c_str())
            ),
            true
        );
    } else {
        SetDisplayText(
            MakeString("%s) %s", LocalizeSeparatedInt(lb.mRank), lb.mName.c_str()), true
        );
    }
}

void AppLabel::SetCreditsText(DataArray *arr, UIListSlot *slot) {
    Symbol sym = blank;
    if (arr->Size() != 0) {
        sym = arr->Sym(0);
    }
    if (sym == blank) {
        SetTextToken(gNullStr);
    } else if (heading == sym) {
        if (slot->Matches("heading")) {
            SetDisplayText(arr->Str(1), true);
        } else
            SetTextToken(gNullStr);
    } else if (heading2 == sym) {
        if (slot->Matches("slot_heading")) {
            SetDisplayText(arr->Str(1), true);
        } else
            SetTextToken(gNullStr);
    } else if (title_name == sym) {
        if (slot->Matches("slot_left")) {
            SetDisplayText(arr->Str(1), true);
        } else if (slot->Matches("slot_right")) {
            SetDisplayText(arr->Str(2), true);
        } else
            SetTextToken(gNullStr);
    } else if (centered == sym) {
        if (slot->Matches("slot_centered")) {
            SetDisplayText(arr->Str(1), true);
        } else
            SetTextToken(gNullStr);
    } else if (image == sym) {
        SetTextToken(gNullStr);
    } else
        SetTextToken(gNullStr);
}

void AppLabel::SetUserName(const User *user) { SetDisplayText(user->UserName(), true); }

void AppLabel::SetUserName(int i) { SetDisplayText(ThePlatformMgr.GetName(i), true); }

void AppLabel::SetUserName(BandTrack *track) { SetDisplayText(track->UserName(), true); }

void AppLabel::SetIntroName(BandUser *user) { SetDisplayText(user->IntroName(), true); }

void AppLabel::SetProfileName(const LocalBandUser *user) {
    if (user) {
        SetDisplayText(user->ProfileName(), true);
    }
}

void AppLabel::SetIconAndProfileName(ScoreType ty, const BandProfile *profile) {
    MILO_ASSERT(profile, 0xAD);
    SetDisplayText(
        MakeString(
            "<alt>%s</alt> %s", GetFontCharFromScoreType(ty, 0), profile->GetName()
        ),
        true
    );
}

void AppLabel::SetFormattedProfileName(Symbol s, BandUser *user) {
    SetTokenFmt(s, user->ProfileName());
}

void AppLabel::SetSongName(Symbol shortname, bool fail) {
    if (!shortname.Null()) {
        SetSongNameWithNumber(TheSongMgr.GetSongIDFromShortName(shortname, fail), 0, 0);
    }
}

void AppLabel::SetSongNameWithNumber(int songID, int i2, const char *cc) {
    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(songID);
    if (data)
        cc = data->Title();
    else if (!cc) {
        cc = Localize(unknown_song, 0);
    }
    if (i2 > 0) {
        SetTokenFmt(setlist_song_fmt, i2, cc);
    } else
        SetDisplayText(cc, true);
}

void AppLabel::SetSongAndArtistNameFromSymbol(Symbol shortname, int i) {
    int songID = TheSongMgr.GetSongIDFromShortName(shortname, true);
    String artistStr;
    String titleStr;
    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(songID);
    if (!data) {
        titleStr = Localize(unknown_song, 0);
    } else {
        titleStr = data->Title();
        if (!data->IsMasterRecording()) {
            artistStr = MakeString("%s %s", Localize(store_famous_by, 0), data->Artist());
        } else {
            artistStr = data->Artist();
        }
    }
    if (i <= 0) {
        SetDisplayText(
            MakeString(Localize(song_artist_fmt, 0), titleStr.c_str(), artistStr.c_str()),
            true
        );
    } else {
        SetDisplayText(
            MakeString(
                Localize(song_artist_fmt_number, 0), i, titleStr.c_str(), artistStr.c_str()
            ),
            true
        );
    }
}

void AppLabel::SetSongName(const SongSortNode *ssn) {
    MILO_ASSERT(ssn, 265);
    SetDisplayText(ssn->GetTitle(), 1);
}

void AppLabel::SetSongYear(int i1, int i2) {
    if (i1 == i2) {
        SetInt(i1, false);
    } else
        SetDisplayText(MakeString("%i (%i)", i1, i2), true);
}

void AppLabel::SetAlbumName(const SongSortNode *ssn) {
    MILO_ASSERT(ssn, 279);
    SetDisplayText(ssn->GetAlbum(), 1);
}

void AppLabel::SetArtistName(const SortNode *sn) {
    if (sn->GetType() == kNodeSubheader) {
        const SubheaderSortNode *shsn = dynamic_cast<const SubheaderSortNode *>(sn);
        SetDisplayText(shsn->GetArtist(), true);
    } else if (sn->GetType() == kNodeSong) {
        const SongSortNode *ssn = dynamic_cast<const SongSortNode *>(sn);
        MILO_ASSERT(ssn, 293);
        SetArtistName(ssn->GetArtist(), ssn->GetIsCover());
    } else {
        const SetlistSortNode *ssn = dynamic_cast<const SetlistSortNode *>(sn);
        MILO_ASSERT(ssn, 299);
        SavedSetlist *setlist = ssn->GetSetlistRecord()->GetSetlist();
        if (setlist->GetOwner() != nullptr) {
            SetDisplayText(setlist->GetOwner(), true);
        } else {
            SetDisplayText(gNullStr, true);
        }
    }
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEBLOCK(AppLabel, (), {SetlistRecord* slr; slr->GetSetlist()->SavedSetlist::GetOwner();})
#pragma pop

void AppLabel::SetArtistName(Symbol shortname) {
    if (!shortname.Null()) {
        int songID = TheSongMgr.GetSongIDFromShortName(shortname, true);
        SetArtistName((BandSongMetadata *)TheSongMgr.Data(songID));
    }
}

void AppLabel::SetArtistName(const BandSongMetadata *data) {
    SetArtistName(data->Artist(), !data->IsMasterRecording());
}

void AppLabel::SetArtistName(const char *name, bool cover) {
    if (!cover)
        SetDisplayText(name, true);
    else {
        DataArrayPtr ptr;
        SetTokenFmt(cover_artist_fmt, ptr, name);
    }
}

void AppLabel::SetSongAndArtistName(const SongSortNode *ssn) {
    MILO_ASSERT(ssn, 342);
    String str;
    if (ssn->GetIsCover()) {
        str = MakeString("%s %s", Localize(store_famous_by, nullptr), ssn->GetArtist());
    } else {
        str = ssn->GetArtist();
    }

    SetDisplayText(
        MakeString(Localize(song_artist_fmt, nullptr), ssn->GetTitle(), str.c_str()), true
    );
}

void AppLabel::SetSongCount(int ct) {
    Symbol s = song_select_songs;
    if (ct == 1)
        s = song_select_song;
    DataNode word(s);
    DataNode count(LocalizeSeparatedInt(ct));
    DataArray *da = new DataArray(2);
    da->Node(0) = count;
    da->Node(1) = word;
    SetTokenFmt(da);
    da->Release();
}

void AppLabel::SetStarRating(int i) {
    SetDisplayText(TheScoring->GetStarRating(i).Str(), true);
}

void AppLabel::SetMotd(MainHubPanel *hub) {
    DataNode n = hub->Handle(motd_msg, true);
    if (n.NotNull())
        SetDisplayText(n.Str(), true);
    return;
}

void AppLabel::SetDLCMotd(MainHubPanel *hub) {
    DataNode n = hub->Handle(dlc_motd_msg, true);
    if (n.NotNull())
        SetDisplayText(n.Str(), true);
    return;
}

void AppLabel::SetUnlinkedMotd(const MainHubMessageProvider *mhmp) {
    SetDisplayText(mhmp->mUnlinkedMotd.c_str(), true);
}

void AppLabel::SetScoreOrStars(const MetaPerformer *p, int i) {
    MILO_ASSERT(p, 395);
    SetInt(i, true);
}

DataNode AppLabel::OnSetUserName(const DataArray *_msg) {
    const DataNode &node = _msg->Node(2).Evaluate();
    if (node.Type() == kDataInt) {
        SetUserName(node.Int());
    } else {
        Hmx::Object *obj = node.GetObj();
        User *user = dynamic_cast<User *>(obj);
        if (user != nullptr) {
            SetUserName(user);

        } else {
            BandTrack *bt = dynamic_cast<BandTrack *>(obj);
            if (bt != nullptr) {
                SetUserName(bt);
            } else
                MILO_WARN("Could not set user name, unknown class");
        }
    }
    return 1;
}

void AppLabel::SetFromSongSelectNode(const Node *n) {
    DateTime *dt = n->GetDateTime();
    if (dt) {
        SetDateTime(*dt, year_format);
    } else {
        if (n->LocalizeToken()) {
            SetTextToken(n->GetToken());
        } else {
            SetDisplayText(n->GetToken().Str(), true);
        }
    }
}

void AppLabel::SetFromCharacter(const CharData *cd) {
    const char *s = cd->GetCharacterName();
    if (strcmp(s, "") == 0) {
        SetTextToken(character_emptyname);
    } else
        SetDisplayText(s, 1);
}

void AppLabel::SetBandName(const LocalBandUser *lbu) {
    BandProfile *prof = TheProfileMgr.GetProfileForUser(lbu);
    if (prof)
        SetBandName(prof);
}

void AppLabel::SetBandName(const BandProfile *pProfile) {
    MILO_ASSERT(pProfile, 463);
    String name = pProfile->GetBandName();
    const char *s = name.c_str();
    if (strcmp(s, "") == 0) {
        SetTextToken(band_emptyname);
    } else
        SetDisplayText(s, 1);
}

void AppLabel::SetPrimaryBandName() {
    BandMachineMgr *pMachineMgr = TheSessionMgr->GetMachineMgr();
    MILO_ASSERT(pMachineMgr, 481);
    String pbn = pMachineMgr->GetLeaderPrimaryBandName();
    const char *s = pbn.c_str();
    if (pbn.length() != 0) {
        SetDisplayText(s, true);
    } else {
        String ppn = pMachineMgr->GetLeaderPrimaryProfileName();
        String defaultname =
            MakeString(Localize(band_default_name, nullptr), ppn.c_str());
        SetDisplayText(defaultname.c_str(), true);
    }
}

DataNode AppLabel::OnSetBandName(const DataArray *_msg) {
    Hmx::Object *obj = _msg->GetObj(2);
    LocalBandUser *lbu = dynamic_cast<LocalBandUser *>(obj);
    if (lbu) {
        SetBandName(lbu);
    } else {
        SetBandName(dynamic_cast<BandProfile *>(obj));
    }
    return 0;
}

void AppLabel::SetSetlistName(const SavedSetlist *setlist) {
    SetDisplayText(setlist->GetTitle(), true);
}

void AppLabel::SetSetlistDescription(const SavedSetlist *setlist) {
    SetDisplayText(setlist->GetDescription(), true);
}

void AppLabel::SetSetlistOwner(const SetlistRecord *setlist) {
    SetDisplayText(setlist->GetOwner(), true);
}

void AppLabel::SetLinkingCode(const char *cc) {
    String s(cc);
    if (s.length() != 10)
        MILO_WARN("linking code is not 10 characters!\n");
    if (s.find(' ') != String::npos)
        MILO_WARN("linking code has spaces!\n");
    SetDisplayText(cc, 1);
}

void AppLabel::SetBattleTimeLeft(int) {}

void AppLabel::SetBattleInstrument(ScoreType) {}

void AppLabel::SetBattleInstrument(const SetlistRecord *slr) {
    SavedSetlist *setlist = slr->GetSetlist();
    MILO_ASSERT(setlist, 930);
    if (setlist->IsBattle()) {
        SetBattleInstrument((ScoreType)slr->unk30);
    } else {
        SetTextToken(gNullStr);
    }
}

void AppLabel::SetRatingIcon(int i) {
    AUTO(ratingIcons, SystemConfig(song_select, rating_icons, SystemLanguage()));
    MILO_ASSERT(ratingIcons, 943);
    SetIcon(ratingIcons->Str(i)[0]);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(AppLabel)
    HANDLE(set_user_name, OnSetUserName)
    HANDLE_ACTION(set_intro_name, SetIntroName(_msg->Obj<BandUser>(2)))

    HANDLE_ACTION(set_linking_code, SetLinkingCode(_msg->Str(2)))
    HANDLE_ACTION(set_recommendation, SetRecommendation(_msg->Obj<StoreInfoPanel>(2)))
    HANDLE_SUPERCLASS(BandLabel)
    HANDLE_CHECK(1040)
END_HANDLERS
#pragma pop
