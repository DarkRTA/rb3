#ifndef BANDTRACK_GEMMANAGER_H
#define BANDTRACK_GEMMANAGER_H
#include "obj/Object.h"
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
    PlayerState() : warning(0), overdriveReady(0), whammy(0), whammyActive(0), phraseState(kPhraseNone), fillState(0), streak(0) {}

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
    GemManager(const TrackConfig&, TrackDir*);
    ~GemManager();

    bool GetChordWidgetName(class Symbol, class Symbol, class Symbol&);
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
    void SetBonusGems(bool, const PlayerState&);
    void SetInCoda(bool);
    void PopSmasher(int);
    void UpdateGemStates();
    void ResetSmashers(bool);
    void UpdateSlotPositions();
    Hmx::Object* GetSmasherObj(int);
    void HideGems();

    TrackDir *mTrackDir;
    TrackConfig *mTrackConfig;
};

#endif // BANDTRACK_GEMMANAGER_H
