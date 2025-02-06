#pragma once
#include "Gem.h"
#include "bandobj/ArpeggioShape.h"
#include "bandtrack/GemRepTemplate.h"
#include "bandtrack/NowBar.h"
#include "beatmatch/InternalSongParserSink.h"
#include "game/Player.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "track/TrackWidget.h"
#include "utl/Symbol.h"
#include "system/track/TrackDir.h"
#include "TrackConfig.h"

class GemTrack;

enum PhraseState {
    kPhraseNone,
    kPhraseMissed,
    kPhraseHitting,
    kPhraseComplete
};

class PlayerState {
public:
    PlayerState()
        : warning(0), overdriveReady(0), whammy(0), whammyActive(0),
          phraseState(kPhraseNone), fillState(0), streak(0) {}

    bool warning; // 0x0
    bool overdriveReady; // 0x1
    float whammy; // 0x4
    bool whammyActive; // 0x8
    PhraseState phraseState; // 0xc
    float fillState; // 0x10
    int streak; // 0x14
};

class GemManager {
public:
    class HitGem {
    public:
        HitGem(float f, int x, int y) : unk0(f), unk4(x), unk8(y) {}
        float unk0;
        int unk4;
        unsigned int unk8;
    };
    class ArpeggioPhrase {
    public:
        ArpeggioPhrase(int x, int y, int z)
            : unk0(x), unk4(y), unk8(z), mShape(0), unk10(0) {}
        int unk0;
        int unk4;
        int unk8;
        ArpeggioShape *mShape; // 0xc
        bool unk10;
    };
    GemManager(const TrackConfig &, TrackDir *);
    ~GemManager();

    bool GetChordWidgetName(class Symbol, class Symbol, class Symbol &);
    bool GetWidgetName(class Symbol &, int, class Symbol);
    TrackWidget *GetWidgetByName(Symbol);

    int GetMaxSlots() const;
    void ClearAllGems();
    void ClearMissedPhrases();
    void UpdateLeftyFlip(bool);
    void ClearGems(bool);
    void SetupGems(int);
    void UpdateEnabledSlots();
    int GetSlotsForGem(int);
    void Hit(float, int, int);
    void Miss(float, int, int);
    void Pass(int);
    void Ignore(int);
    void PartialHit(float, int, unsigned int, int);
    void FillHit(int, int);
    void SetSmasherGlowing(int, bool);
    void Released(float, int);
    void Jump(float);
    void SetGemsEnabled(float);
    bool OnMissPhrase(int);
    void SetBonusGems(bool, const PlayerState &);
    void SetInCoda(bool);
    void PopSmasher(int);
    void UpdateGemStates();
    void ResetSmashers(bool);
    void UpdateSlotPositions();
    Hmx::Object *GetSmasherObj(int);
    void HideGems();
    bool SlotEnabled(int) const;
    int GetSlotIntData(int, Symbol);
    void ClearArpeggios();
    void InitRGTuning(BandUser *);
    void DrawTrackMasks(int, int);
    void ResetArpeggios(float);
    void UpdateArpeggios(float, bool);
    void ClearTrackMasks();
    void SetupRealGuitarFretPos();
    void ProcessRealGuitarRun(std::vector<GameGem> &, int &);
    bool TrillStartsAt(int, const GameGem &, int &) const;
    void SetupRealGuitarImportantStrings();
    void EndRepeatedChordPhrase(int &, int &, int &);
    bool RollStartsAt(int, const GameGem &, int &, unsigned int &) const;
    int GetNumGems() const;
    const Gem &GetGem(int) const;
    void AdvanceBegin();
    void AdvanceEnd();
    Symbol GetTypeForGem(int);
    void AddChordBracket(Symbol, unsigned int, float);
    void PollVisibleGems(float, float);
    void RememberChordWidget(TrackWidget *);
    void AddWidgetInstanceImpl(TrackWidget *, int, float);
    void ReleaseSlot(int, int);
    void ReleaseHitGems();
    void CheckRemoveChordBracket(int);
    bool IsSpotlightGem(int, bool &);
    void PruneHitGems(float);
    void PollHelper(float, const PlayerState &);
    void EnableSlot(int);
    void DisableSlot(int);
    void ClearGem(int);
    bool GetFill(int, FillExtent &);
    bool IsInFill(int);
    bool IsEndOfFill(int);

    unsigned int EnabledSlots() const { return mEnabledSlots; }

    TrackDir *mTrackDir; // 0x0
    const TrackConfig &mTrackConfig; // 0x4
    std::vector<Gem> mGems; // 0x8
    DataArray *mGemData; // 0x10
    float unk14;
    std::vector<Extent> mMissedPhrases; // 0x18
    std::list<HitGem> mHitGems; // 0x20
    int mBegin; // 0x28
    int mEnd; // 0x2c
    GemRepTemplate mTemplate; // 0x30
    DataArray *mConfig; // 0xb4
    bool unkb8; // 0xb8
    NowBar *mNowBar; // 0xbc
    bool mBonusGems; // 0xc0
    bool mInCoda; // 0xc1
    float unkc4;
    float unkc8;
    float unkcc;
    std::list<int> mDisabledSlotsList; // 0xd0
    std::vector<TrackWidget *> unkd8;
    std::map<Symbol, TrackWidget *> mWidgets; // 0xe0
    RndGroup *mTailsGrp; // 0xf8
    int unkfc;
    int unk100;
    int unk104;
    unsigned int mEnabledSlots; // 0x108
    int unk10c;
    std::vector<ArpeggioPhrase> mArpeggioPhrases; // 0x110
    int unk118;
    std::vector<ArpeggioPhrase *> mActiveArpeggios; // 0x11c
    std::vector<ArpeggioPhrase *> mExpiredArpeggios; // 0x124
    float unk12c;
    int unk130;
    int unk134;
};

int GetBeardThreshold();