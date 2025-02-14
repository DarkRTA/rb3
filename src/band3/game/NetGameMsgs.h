#pragma once
#include "utl/HxGuid.h"
#include <os/User.h>
#include "Stats.h"
#include "network/net/NetMessage.h"

enum NetUIState {
    kNetUI_None = 0,
    kNetUI_Synchronized = 1,
    kNetUI_MainMenu = 2,
    kNetUI_WaitingPartyShuffle = 3,
    kNetUI_WaitingChooseSong = 4,
    kNetUI_WaitingChooseSetlist = 5,
    kNetUI_WaitingQpFindPlayers = 6,
    kNetUI_WaitingTour = 7,
    kNetUI_WaitingTourFindPlayers = 8,
    kNetUI_FindPlayers = 9,
    kNetUI_MusicStore = 10,
    kNetUI_Campaign = 11,
    kNetUI_Customize = 12,
    kNetUI_MusicLibrary = 13,
    kNetUI_InGame = 14,
    kNetUI_MetaLoadingPreSave = 15,
    kNetUI_MetaLoadingPostSave = 16
};

class PlayerGameplayMsg : public NetMessage {
public:
    PlayerGameplayMsg() {}
    PlayerGameplayMsg(User *, int, int, int, int);
    virtual ~PlayerGameplayMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(PlayerGameplayMsg);
    NETMSG_NAME(PlayerGameplayMsg);

    NETMSG_NEWNETMSG(PlayerGameplayMsg);

    UserGuid mUserGuid; // 0x4
    int mOpcode; // 0x14
    int mArg1; // 0x18
    int mArg2; // 0x1c
    int mArg3; // 0x20
};

class RestartGameMsg : public NetMessage {
public:
    RestartGameMsg() : mFromWin(0) {}
    RestartGameMsg(bool w) : mFromWin(w) {}
    virtual ~RestartGameMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(RestartGameMsg);
    NETMSG_NAME(RestartGameMsg);

    NETMSG_NEWNETMSG(RestartGameMsg);

    int mFromWin; // 0x4
};

class ResumeNoScoreGameMsg : public NetMessage {
public:
    ResumeNoScoreGameMsg();
    ResumeNoScoreGameMsg(float);
    virtual ~ResumeNoScoreGameMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(ResumeNoScoreGameMsg);
    NETMSG_NAME(ResumeNoScoreGameMsg);

    NETMSG_NEWNETMSG(ResumeNoScoreGameMsg);

    float mFraction; // 0x4
};

class PlayerStatsMsg : public NetMessage {
public:
    PlayerStatsMsg() {}
    PlayerStatsMsg(User *, int, const Stats &);
    virtual ~PlayerStatsMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(PlayerStatsMsg);
    NETMSG_NAME(PlayerStatsMsg);

    NETMSG_NEWNETMSG(PlayerStatsMsg);

    UserGuid mUserGuid; // 0x4
    int mScore; // 0x14
    Stats mStats; // 0x18
};

class SetUserTrackTypeMsg : public NetMessage {
public:
    SetUserTrackTypeMsg() {}
    SetUserTrackTypeMsg(User *, String);
    virtual ~SetUserTrackTypeMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SetUserTrackTypeMsg);
    NETMSG_NAME(SetUserTrackTypeMsg);

    NETMSG_NEWNETMSG(SetUserTrackTypeMsg);

    UserGuid mUserGuid; // 0x4
    String mTrackType; // 0x14
};

class SetUserDifficultyMsg : public NetMessage {
public:
    SetUserDifficultyMsg() {}
    SetUserDifficultyMsg(User *, String);
    virtual ~SetUserDifficultyMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SetUserDifficultyMsg);
    NETMSG_NAME(SetUserDifficultyMsg);

    NETMSG_NEWNETMSG(SetUserDifficultyMsg);

    UserGuid mUserGuid; // 0x4
    String mDifficulty; // 0x14
};

class SetlistSubmissionMsg : public NetMessage {
public:
    SetlistSubmissionMsg() {}
    SetlistSubmissionMsg(const std::vector<int> &, int);
    virtual ~SetlistSubmissionMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SetlistSubmissionMsg);
    NETMSG_NAME(SetlistSubmissionMsg);

    NETMSG_NEWNETMSG(SetlistSubmissionMsg);

    std::vector<int> mSongIDs; // 0x4
    int mNumUsers; // 0xc
};

class TourMostStarsMsg : public NetMessage {
public:
    TourMostStarsMsg() {}
    TourMostStarsMsg(Symbol, int);
    virtual ~TourMostStarsMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(TourMostStarsMsg);
    NETMSG_NAME(TourMostStarsMsg);

    NETMSG_NEWNETMSG(TourMostStarsMsg);

    Symbol unk4; // 0x4
    int unk8; // 0x8
};

class TourPlayedMsg : public NetMessage {
public:
    TourPlayedMsg() {}
    TourPlayedMsg(Symbol);
    virtual ~TourPlayedMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(TourPlayedMsg);
    NETMSG_NAME(TourPlayedMsg);

    NETMSG_NEWNETMSG(TourPlayedMsg);

    Symbol mTourPlayed; // 0x4
};

class AccomplishmentMsg : public NetMessage {
public:
    AccomplishmentMsg() {}
    AccomplishmentMsg(Symbol);
    virtual ~AccomplishmentMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(AccomplishmentMsg);
    NETMSG_NAME(AccomplishmentMsg);

    NETMSG_NEWNETMSG(AccomplishmentMsg);

    Symbol mAccomplishment; // 0x4
};

class AccomplishmentEarnedMsg : public NetMessage {
public:
    AccomplishmentEarnedMsg() {}
    AccomplishmentEarnedMsg(Symbol, const char *, Symbol);
    virtual ~AccomplishmentEarnedMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(AccomplishmentEarnedMsg);
    NETMSG_NAME(AccomplishmentEarnedMsg);

    NETMSG_NEWNETMSG(AccomplishmentEarnedMsg);

    Symbol mSymbol1; // 0x4
    String mStr; // 0x8
    Symbol mSymbol2; // 0x14
};

class SetPartyShuffleModeMsg : public NetMessage {
public:
    SetPartyShuffleModeMsg();
    virtual ~SetPartyShuffleModeMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SetPartyShuffleModeMsg);
    NETMSG_NAME(SetPartyShuffleModeMsg);

    NETMSG_NEWNETMSG(SetPartyShuffleModeMsg);
};

class TourHideShowFiltersMsg : public NetMessage {
public:
    TourHideShowFiltersMsg() {}
    TourHideShowFiltersMsg(bool);
    virtual ~TourHideShowFiltersMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(TourHideShowFiltersMsg);
    NETMSG_NAME(TourHideShowFiltersMsg);

    NETMSG_NEWNETMSG(TourHideShowFiltersMsg);

    bool mShowMode; // 0x4
};

class SongResultsScrollMsg : public NetMessage {
public:
    SongResultsScrollMsg() {}
    SongResultsScrollMsg(int, int);
    virtual ~SongResultsScrollMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SongResultsScrollMsg);
    NETMSG_NAME(SongResultsScrollMsg);

    NETMSG_NEWNETMSG(SongResultsScrollMsg);

    int unk_0x4;
    int unk_0x8;
};

class SetUpMicsMsg : public NetMessage {
public:
    SetUpMicsMsg() {}
    virtual ~SetUpMicsMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(SetUpMicsMsg);
    NETMSG_NAME(SetUpMicsMsg);

    NETMSG_NEWNETMSG(SetUpMicsMsg);

    bool mHasMic1;
    bool mHasMic2;
    bool mHasMic3;
};
