#pragma once
#include "bandtrack/VocalTrack.h"
#include "beatmatch/VocalNote.h"
#include "game/TrainerPanel.h"
#include "game/VocalPlayer.h"

class VocalTrainerPanel : public TrainerPanel {
public:
    VocalTrainerPanel();
    OBJ_CLASSNAME(VocalTrainerPanel);
    OBJ_SET_TYPE(VocalTrainerPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~VocalTrainerPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void StartSectionImpl();

    void AddBeatMask(int);
    void CopyTubes(int);
    void Loop();
    void UpdateScore();
    void ClearTubes();

    std::vector<VocalPhrase> mPatternPhrases[3]; // 0x54
    std::vector<VocalPhrase> mPatternLyricPhrases[2]; // 0x6c
    std::vector<VocalNote> mPatternNotes[3]; // 0x7c
    VocalTrack *mTrack; // 0x94
    VocalPlayer *mVocalPlayer; // 0x98
    int unk9c;
    int unka0;
    int unka4;
    VocalNoteList *unka8[3]; // 0xa8
    VocalNoteList *unkb4[3]; // 0xb4
    bool unkc0;
    bool unkc1;
    int unkc4;
    int unkc8;
    float unkcc;
    float unkd0;
};