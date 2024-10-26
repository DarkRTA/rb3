#ifndef GAME_NETGAMEMSGS_H
#define GAME_NETGAMEMSGS_H
#include "utl/TextStream.h"
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

class NetMessage {
public:
    NetMessage(){}
    virtual ~NetMessage(){}
    virtual void Save(BinStream &) const = 0;
    virtual void Load(BinStream &) = 0;
    virtual void Dispatch() = 0;
    virtual int VoiceData() const { return 0; }
    virtual void Print(TextStream&) const {}
    virtual int ByteCode() const = 0;
    virtual const char* Name() const = 0;
};

class PlayerGameplayMsg : public NetMessage {
public:
    PlayerGameplayMsg(User *, int, int, int, int);
    ~PlayerGameplayMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString string("PlayerGameplayMsg");
        return string.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("PlayerGameplayMsg");
    }

    UserGuid mUserGuid;

    int mOpcode;
    int mArg1;
    int mArg2;
    int mArg3;
};

class RestartGameMsg : public NetMessage {
public:
    ~RestartGameMsg();
    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("RestartGameMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("RestartGameMsg");
    }

    int unk_0x4;
};

class ResumeNoScoreGameMsg : public NetMessage {
public:
    ResumeNoScoreGameMsg();
    ResumeNoScoreGameMsg(float);
    ~ResumeNoScoreGameMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("ResumeNoScoreGameMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("ResumeNoScoreGameMsg");
    }

    float unk_0x4;
};

class PlayerStatsMsg : public NetMessage {
public:
    PlayerStatsMsg(User *, int, const Stats &);
    ~PlayerStatsMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("PlayerStatsMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("PlayerStatsMsg");
    }

    HxGuid mGuid;
    Stats mStats;
};

class SetUserTrackTypeMsg : public NetMessage {
public:
    SetUserTrackTypeMsg(User *, String);

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("SetUserTrackTypeMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("SetUserTrackTypeMsg");
    }

    HxGuid mGuid;
    String mString;
};

class SetUserDifficultyMsg : public NetMessage {
public:
    SetUserDifficultyMsg(User *, String);

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("SetUserDifficultyMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("SetUserDifficultyMsg");
    }

    HxGuid mGuid;
    String mString;
};

class SetlistSubmissionMsg : public NetMessage {
public:
    SetlistSubmissionMsg(const std::vector<void *> &, int);
    ~SetlistSubmissionMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("SetlistSubmissionMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("SetlistSubmissionMsg");
    }

    std::vector<void *> unk_0x4;
    int unk_0xc;
};

class TourMostStarsMsg : public NetMessage {
public:
    TourMostStarsMsg(Symbol, int);
    ~TourMostStarsMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("TourMostStarsMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("TourMostStarsMsg");
    }

    Symbol mSymbol;
    int unk_0x8;
};

class TourPlayedMsg : public NetMessage {
public:
    TourPlayedMsg(Symbol);
    ~TourPlayedMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("TourPlayedMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("TourPlayedMsg");
    }

    Symbol mSymbol;
};

class AccomplishmentMsg : public NetMessage {
public:
    AccomplishmentMsg(Symbol);
    ~AccomplishmentMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("AccomplishmentMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("AccomplishmentMsg");
    }

    Symbol mSymbol;
};

class AccomplishmentEarnedMsg : public NetMessage {
public:
    AccomplishmentEarnedMsg(Symbol, const char *, Symbol);
    ~AccomplishmentEarnedMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("AccomplishmentEarnedMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("AccomplishmentEarnedMsg");
    }

    Symbol mSymbol1;
    String mStr;
    Symbol mSymbol2;
};

class SetPartyShuffleModeMsg : public NetMessage {
public:
    SetPartyShuffleModeMsg();
    ~SetPartyShuffleModeMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("SetPartyShuffleModeMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("SetPartyShuffleModeMsg");
    }
};

class TourHideShowFiltersMsg : public NetMessage {
public:
    TourHideShowFiltersMsg(bool);
    ~TourHideShowFiltersMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("TourHideShowFiltersMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("TourHideShowFiltersMsg");
    }

    bool mShowMode;
};

class SongResultsScrollMsg : public NetMessage {
public:
    SongResultsScrollMsg(int, int);
    ~SongResultsScrollMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("SongResultsScrollMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("SongResultsScrollMsg");
    }

    int unk_0x4;
    int unk_0x8;
};

class SetUpMicsMsg : public NetMessage {
public:
    ~SetUpMicsMsg();

    void Save(BinStream &) const;
    void Load(BinStream &);
    void Dispatch();

    const char *Name() const {
        FormatString format("SetUpMicsMsg");
        return format.Str();
    };

    int ByteCode() const {
        return TheNetMessageFactory.GetNetMessageByteCode("SetUpMicsMsg");
    }

    bool mHasMic1;
    bool mHasMic2;
    bool mHasMic3;
};

#endif // GAME_NETGAMEMSGS_H