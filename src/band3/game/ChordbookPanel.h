#pragma once
#include "ChordPreview.h"
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/RGState.h"
#include "game/BandUser.h"
#include "game/FretHand.h"
#include "game/GemPlayer.h"
#include "game/TrainerProgressMeter.h"
#include "obj/Data.h"
#include "rndobj/Dir.h"
#include "track/TrackDir.h"
#include "track/TrackWidget.h"
#include "ui/UIPanel.h"
#include "beatmatch/BeatMatchControllerSink.h"

class ChordbookPanel : public UIPanel, public BeatMatchControllerSink {
public:
    class ChordInfo {
    public:
        ChordInfo() : shape(0), label(""), gemId(-1), startMs(0), endMs(0) {}
        ~ChordInfo() {}
        unsigned int shape; // 0x0
        String label; // 0x4
        FretHand fretHand; // 0x10
        int gemId; // 0x40
        float startMs; // 0x44
        float endMs; // 0x48
    };
    class FingerStep {
    public:
        FingerStep() : unk0(0), unk4(0), unk5(0) {}
        int unk0; // state
        unsigned char unk4; // strings
        bool unk5; // strum
    };
    ChordbookPanel();
    OBJ_CLASSNAME(ChordbookPanel);
    OBJ_SET_TYPE(ChordbookPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~ChordbookPanel();
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void FinishLoad();
    virtual bool Swing(int, bool, bool, bool, bool, GemHitFlags);
    virtual void FretButtonDown(int, int);
    virtual void FretButtonUp(int);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    GemPlayer *GetChordbookPlayer() const;
    void CreateController();
    void StartChordbook();
    bool HasChords() const;
    void PushSkipDialog();
    void ResetSkipDialog();
    void ExitChordbook();
    bool ProfileCheckComplete(Symbol, GemPlayer *);
    void StrumString(int);
    void SetFret(int, int);
    void SetCorrect(int, bool);
    bool ChordComplete() const;
    ChordInfo &CurrentChord();
    Symbol RGFingerStep(int);
    Symbol RGStringToken(int, bool);
    void DisplayChord(unsigned int);
    void PickFretboardView(const GameGem &);

    DataNode OnDisplayChord(const DataArray *);
    DataNode OnGetComplete(const DataArray *);
    DataNode OnSkipConfirm(DataArray *);
    DataNode OnSkipCancel(DataArray *);

    bool mStartChordbook; // 0x3c
    GemPlayer *mGemPlayer; // 0x40
    BandUser *unk44; // 0x44
    Symbol mSongName; // 0x48
    TrackDir *unk4c; // 0x4c
    RndDir *mChordLegend; // 0x50
    GameGemList *mGameGemList; // 0x54
    TrackWidget *mChordWid; // 0x58
    TrackWidget *mFretWid; // 0x5c
    TrackWidget *mLabelWid; // 0x60
    unsigned int mNumSteps; // 0x64
    BeatMatchController *mController; // 0x68
    int mCurrentChord; // 0x6c
    int unk70;
    int unk74;
    unsigned int mNumChords; // 0x78
    ChordInfo mChords[20]; // 0x7c
    bool unk66c; // 0x66c
    int unk670;
    bool unk674;
    unsigned char mFret[6]; // 0x675
    float mStringSwings[6]; // 0x67c
    unsigned char mCorrect; // 0x694
    unsigned char mInUse; // 0x695
    unsigned char mStrum; // 0x696
    FingerStep mStep[5]; // 0x698
    ChordPreview *mChordPreview; // 0x6c0
    bool unk6c4;
    bool unk6c5;
    int unk6c8;
    int unk6cc;
    int unk6d0;
    int unk6d4;
    int unk6d8;
    TrainerProgressMeter *mProgressMeter; // 0x6dc
    RGState mState; // 0x6e0
    bool mRelearnChords; // 0x6f8
    bool mLefty; // 0x6f9
};