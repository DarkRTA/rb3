#include "meta_band/AppLabel.h"
#include "decomp.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/Utl.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "ui/UIListSlot.h"
#include "utl/Locale.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

DECOMP_FORCEACTIVE(AppLabel, "%s) %s")

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

void AppLabel::SetArtistName(const SortNode *) {}

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

void AppLabel::SetLinkingCode(const char *cc) {
    String s(cc);
    if (s.length() != 10)
        MILO_WARN("linking code is not 10 characters!\n");
    if (s.find(' ') != String::npos)
        MILO_WARN("linking code has spaces!\n");
    SetDisplayText(cc, 1);
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
