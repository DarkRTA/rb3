#pragma once
#include "SongSortNode.h"
#include "bandobj/BandLabel.h"
#include "bandobj/BandTrack.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/PracticeSectionProvider.h"
#include "meta/StoreOffer.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/CharData.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/MainHubPanel.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/SongRecord.h"
#include "meta_band/StoreInfoPanel.h"
#include "meta_band/TokenRedemptionPanel.h"
#include "obj/Data.h"
#include "ui/UIPanel.h"

class Node;

class AppLabel : public BandLabel {
public:
    AppLabel() {}
    OBJ_CLASSNAME(AppLabel);
    OBJ_SET_TYPE(AppLabel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~AppLabel();
    virtual void SetCreditsText(DataArray *, UIListSlot *);

    DataNode OnSetUserName(const DataArray *);
    DataNode OnSetBandName(const DataArray *);

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
    void SetArtistName(const SortNode *);
    void SetAlbumName(const SongSortNode *);
    void SetMotd(MainHubPanel *);
    void SetDLCMotd(MainHubPanel *);
    void SetUnlinkedMotd(const MainHubMessageProvider *);
    void SetLeaderboardRankAndName(const LeaderboardRow &);
    void SetLeaderboardName(const LeaderboardRow &);
    void SetPitch(int, int);
    void SetSectionName(const PracticeSection &);
    void SetFromSongSelectNode(const Node *);
    void SetSongCount(int);
    void SetStarRating(int);
    void SetScoreOrStars(const MetaPerformer *, int);
    void SetSongAndArtistName(const SongSortNode *);
    void SetSongName(const SongSortNode *);
    void SetSetlistName(const SavedSetlist *);
    void SetSetlistDescription(const SavedSetlist *);
    void SetSetlistOwner(const SetlistRecord *);
    void SetEditSetlistName(const UIPanel *);
    void SetEditSetlistDesc(const UIPanel *);
    void SetOfferName(const StoreOffer *);
    void SetOfferCost(const StoreOffer *);
    void SetOfferArtist(const StoreOffer *);
    void SetOfferAlbum(const StoreOffer *);
    void SetOfferDescription(const StoreOffer *);
    void SetStoreCrumbText();
    void SetMusicLibraryStatus();
    void SetTokenRedemptionString(const TokenRedemptionPanel *, int);
    void SetBandName(const LocalBandUser *);
    void SetBandName(const BandProfile *);
    void SetLinkingCode(const char *);
    void SetRecommendation(const StoreInfoPanel *);
    void SetRatingIcon(int);
    void SetBattleTimeLeft(int);
    void SetBattleInstrument(ScoreType);
    void SetBattleInstrument(const SetlistRecord *);
    void SetPrimaryBandName();
};