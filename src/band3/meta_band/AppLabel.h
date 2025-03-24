#pragma once
#include "SongSortNode.h"
#include "bandobj/BandLabel.h"
#include "bandobj/BandTrack.h"
#include "game/BandUser.h"
#include "game/PracticeSectionProvider.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/CharData.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/MainHubPanel.h"
#include "meta_band/SongRecord.h"
#include "meta_band/TokenRedemptionPanel.h"

class Node;

class AppLabel : public BandLabel {
public:
    AppLabel() {}
    OBJ_CLASSNAME(AppLabel);
    OBJ_SET_TYPE(AppLabel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~AppLabel();
    virtual void SetCreditsText(DataArray *, UIListSlot *);

    void SetFromCharacter(const CharData *);
    void SetSongName(Symbol, bool);
    void SetSongNameWithNumber(int, int, const char *);
    void SetFromScoreDisplayData(short, int, int, bool);
    void SetUserName(const User *);
    void SetUserName(int);
    void SetUserName(BandTrack *);
    void SetIntroName(BandUser *);
    void SetProfileName(const LocalBandUser *);
    void SetIconAndProfileName(ScoreType, const BandProfile *);
    void SetFormattedProfileName(Symbol, BandUser *);
    void SetSongAndArtistNameFromSymbol(Symbol, int);
    void SetSongYear(int, int);
    void SetArtistName(Symbol);
    void SetArtistName(const BandSongMetadata *);
    void SetArtistName(const char *, bool);
    void SetMotd(MainHubPanel *);
    void SetDLCMotd(MainHubPanel *);
    void SetUnlinkedMotd(const MainHubMessageProvider *);
    void SetLeaderboardRankAndName(const LeaderboardRow &);
    void SetLeaderboardName(const LeaderboardRow &);
    void SetPitch(int, int);
    void SetSectionName(const PracticeSection &);
    void SetFromSongSelectNode(const Node *);
    void SetSongCount(int);
    void SetSongAndArtistName(const SongSortNode *);
    void SetSongName(const SongSortNode *);
    void SetSetlistName(const SavedSetlist *);
    void SetBattleInstrument(const SetlistRecord *);
    void SetTokenRedemptionString(const TokenRedemptionPanel *, int);
};