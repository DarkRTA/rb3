#pragma once
#include "midi/MidiParser.h"
#include "obj/Object.h"
#include "synth/Faders.h"
#include "obj/Dir.h"
#include "synth/Sequence.h"

class TambourineManager : public Hmx::Object {
public:
    TambourineManager(class VocalPlayer &);
    virtual ~TambourineManager();
    virtual DataNode Handle(DataArray *, bool);

    void PostLoad();
    void ComputeTambourinePoints();
    void PostDynamicAdd();
    void Start();
    void Restart();
    int TambourineSwing(int);
    void Jump(float);
    void SetPaused(bool);
    void SetTambourine(bool);
    void GameOver();
    void Rollback(float, float);
    void SetBank(ObjectDir *bank) { mBank = bank; }

    class VocalPlayer &mPlayerRef; // 0x1c
    bool mIsLocal; // 0x20
    ObjDirPtr<ObjectDir> mBank; // 0x24
    Sequence *mTambourineSequence; // 0x30
    Fader *mTambourineFader; // 0x34
    MidiParser *mTambourineParser; // 0x38
    std::vector<int> unk3c; // 0x3c
    int mTambourineIdx; // 0x44
    bool unk48; // 0x48
    int unk4c; // 0x4c
    int mTambourineWindowTicks; // 0x50
    float mTambourineCrowdSuccess; // 0x54
    float mTambourineCrowdFailure; // 0x58
    bool mTambourineActive; // 0x5c
    int unk60; // 0x60
    float mTambourinePoints; // 0x64
    int unk68; // 0x68
    std::vector<int> unk6c; // 0x6c
    bool unk74; // 0x74
    int unk78; // 0x78
    int unk7c; // 0x7c
    std::vector<int> mGemStates; // 0x80
};