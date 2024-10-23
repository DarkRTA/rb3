#pragma once
#include "obj/Data.h"
#include "synth/Faders.h"
#include "synth/Stream.h"
#include "ui/UIPanel.h"

enum TestState {
    tsIdle = 0,
    tsPreRoll = 1,
    tsTesting = 2,
    tsPostTest = 3
};

class CalibrationPanel : public UIPanel {
public:
    CalibrationPanel();
    OBJ_CLASSNAME(CalibrationPanel);
    OBJ_SET_TYPE(CalibrationPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CalibrationPanel();
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    float GetAudioTimeMs() const;
    void SetTestState(TestState);
    void StopAudio();
    void UpdateAnimation();
    void UpdateLabel();
    void UpdateStream();
    int GetTestRep() const;
    void ScanHardwareModeInputs();
    float ReshapeTime(float);
    float HandlePreAndPostTestAnim(float);
    void UpdateProgress(bool);
    void InitializeVisuals();
    void StartAudio();
    void PrepareHwCalibrationState();
    void TerminateHwCalibrationState();
    void EndTest();

    DataNode OnInitializeContent(DataArray*);
    DataNode OnStartTest(DataArray*);
    
    static float kAnimPerceptualOffset;

    float mCycleTimeMs; // 0x38
    Stream* mStream; // 0x3c
    Fader* mFader; // 0x40
    bool unk44;
    std::vector<float> unk48;
    bool mHalfOffAnim; // 0x50
    bool mEnableVideo; // 0x51
    int mNumHits; // 0x54
    bool mEnableAudio; // 0x58
    float unk5c;
    TestState mTestState; // 0x60
    float unk64;
    bool mHardwareMode; // 0x68
    float mAnimCycleFrames; // 0x6c
    int mAnimNumCycles; // 0x70
    int mMaxSlack; // 0x74
    float mRestingFrame; // 0x78
    int unk7c;
    float unk80;
    float mVolDb; // 0x84
    int unk88;
    float unk8c;
    int unk90;
    int unk94;
    int unk98;
    int mPad; // 0x9c
    bool unka0; // maybe char instead?
    float unka4[5]; // 0xa4
    float unkb8[5]; // 0xb8
    bool unkcc;
    float unkd0;
    float unkd4;
    float unkd8;
    int unkdc;
    bool unke0;
    float unke4;
    int mTopOutliers; // 0xe8
    int mBottomOutliers; // 0xec
};