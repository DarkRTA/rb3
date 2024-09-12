#pragma once
#include "track/TrackDir.h"
#include "bandobj/BandTrack.h"
#include "rndobj/Group.h"
#include "rndobj/Tex.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Env.h"
#include "rndobj/Cam.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PropAnim.h"
#include "track/TrackWidget.h"
#include "obj/Task.h"
#include "bandobj/ChordShapeGenerator.h"
#include "beatmatch/RGState.h"
#include "bandobj/FingerShape.h"

class GemTrackDir : public TrackDir, public BandTrack {
public:
    GemTrackDir();
    OBJ_CLASSNAME(GemTrackDir)
    OBJ_SET_TYPE(GemTrackDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~GemTrackDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void Poll();
    virtual void SyncFingerFeedback();
    virtual void SetDisplayRange(float);
    virtual void SetDisplayOffset(float, bool);
    virtual int SmasherPlate(); // change return type
    virtual float GetFretPosOffset(int) const;
    virtual int GetNumFretPosOffsets() const;
    virtual float GetCurrentChordLabelPosOffset() const;
    virtual int PrepareChordMesh(unsigned int);
    virtual int GetChordMesh(unsigned int, bool);
    virtual void SetUnisonProgress(float);
    virtual void ClearChordMeshRefCounts();
    virtual void DeleteUnusedChordMeshes();
    virtual void AddChordImpl(RndMesh*, TrackWidget*, TrackWidget*, TrackWidget*, float, const std::vector<int>&, class String);
    virtual int GetArpeggioShapePool();
    virtual bool IsBlackKey(int) const;
    virtual void KeyMissLeft();
    virtual void KeyMissRight();
    virtual bool IsActiveInSession() const;
    virtual void PlayIntro();
    virtual void TrackReset();
    virtual void ResetSmashers(bool);
    virtual void GameWon();
    virtual void Retract(bool);
    virtual void Extend(bool);
    virtual void SetStreak(int, int, int, bool);
    virtual void PeakState(bool, bool);
    virtual void SuperStreak(bool, bool);
    virtual void Deploy();
    virtual void EnterCoda();
    virtual void DisablePlayer(int);
    virtual void SetPlayerLocal(float);
    virtual ObjectDir* ThisDir();
    virtual ObjectDir* ThisDir() const; // fix ptr
    virtual void RefreshStreakMeter(int, int, int);
    virtual void SpotlightPhraseSuccess();
    virtual int AsGemTrackDir();
    virtual int AsRndDir();
    virtual void SetPerformanceMode(bool);
    virtual void SetInstrument(TrackInstrument);
    virtual void SetupInstrument();
    virtual void ResetEffectSelector();
    virtual void SetupSmasherPlate();
    virtual void ReleaseSmasherPlate();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk484; // 0x484
    int unk488; // 0x488
    int unk48c; // 0x48c
    int unk490; // 0x490
    int unk494; // 0x494
    float unk498; // 0x498
    float unk49c; // 0x49c
    float unk4a0; // 0x4a0
    ObjPtr<RndDir, ObjectDir> unk4a4; // 0x4a4
    ObjPtr<RndGroup, ObjectDir> unk4b0; // 0x4b0
    ObjPtr<RndTex, ObjectDir> unk4bc; // 0x4bc
    ObjPtr<RndMesh, ObjectDir> unk4c8; // 0x4c8
    ObjPtr<RndMat, ObjectDir> unk4d4; // 0x4d4
    ObjPtr<RndEnviron, ObjectDir> unk4e0; // 0x4e0
    ObjPtr<RndEnviron, ObjectDir> unk4ec; // 0x4ec
    ObjPtr<RndCam, ObjectDir> unk4f8; // 0x4f8
    ObjPtr<EventTrigger, ObjectDir> unk504; // 0x504
    ObjPtr<EventTrigger, ObjectDir> unk510; // 0x510
    ObjPtr<EventTrigger, ObjectDir> unk51c; // 0x51c
    ObjPtr<EventTrigger, ObjectDir> unk528; // 0x528
    ObjPtr<EventTrigger, ObjectDir> unk534; // 0x534
    ObjPtr<EventTrigger, ObjectDir> unk540; // 0x540
    ObjPtr<EventTrigger, ObjectDir> unk54c; // 0x54c
    ObjPtr<EventTrigger, ObjectDir> unk558; // 0x558
    ObjPtr<EventTrigger, ObjectDir> unk564; // 0x564
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > unk570; // 0x570
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > unk578; // 0x578
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > unk580; // 0x580
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > unk588; // 0x588
    std::vector<std::pair<ObjPtr<EventTrigger, ObjectDir>, ObjPtr<EventTrigger, ObjectDir> > > unk590; // 0x590
    std::vector<std::pair<ObjPtr<EventTrigger, ObjectDir>, ObjPtr<EventTrigger, ObjectDir> > > unk598; // 0x598
    std::vector<ObjPtr<EventTrigger, ObjectDir> > unk5a0; // 0x5a0
    ObjPtr<EventTrigger, ObjectDir> unk5a8; // 0x5a8
    ObjPtr<RndPropAnim, ObjectDir> unk5b4; // 0x5b4
    ObjPtr<RndGroup, ObjectDir> unk5c0; // 0x5c0
    ObjPtr<RndGroup, ObjectDir> unk5cc; // 0x5cc
    ObjPtr<RndPropAnim, ObjectDir> unk5d8; // 0x5d8
    ObjPtr<RndDir, ObjectDir> unk5e4; // 0x5e4
    ObjPtrList<TrackWidget, ObjectDir> unk5f0; // 0x5f0
    ObjPtr<Task, ObjectDir> unk600; // 0x600
    ObjPtr<Task, ObjectDir> unk60c; // 0x60c
    ObjPtr<Task, ObjectDir> unk618; // 0x618
    ObjPtr<Task, ObjectDir> unk624; // 0x624
    ObjPtr<RndMesh, ObjectDir> unk630; // 0x630
    ObjPtr<EventTrigger, ObjectDir> unk63c; // 0x63c
    ObjPtr<EventTrigger, ObjectDir> unk648; // 0x648
    ObjPtr<RndAnimatable, ObjectDir> unk654; // 0x654
    ObjPtr<RndAnimatable, ObjectDir> unk660; // 0x660
    ObjPtr<RndPropAnim, ObjectDir> unk66c; // 0x66c
    float unk678; // 0x678
    float unk67c; // 0x67c
    std::vector<RndDir*> unk680; // 0x680
    std::vector<EventTrigger*> unk688; // 0x688
    std::vector<EventTrigger*> unk690; // 0x690
    FingerShape* unk698; // 0x698
    std::vector<float> unk69c; // 0x69c
    float unk6a4; // 0x6a4
    ObjPtr<ChordShapeGenerator, ObjectDir> unk6a8; // 0x6a8
    std::map<unsigned int, std::pair<int, RndMesh*> > unk6b4; // 0x6b4
    std::map<unsigned int, std::pair<int, RndMesh*> > unk6cc; // 0x6cc
    int unk6e4; // 0x6e4
    bool unk6e8; // 0x6e8
    bool unk6e9; // 0x6e9
    bool unk6ea; // 0x6ea
    int unk6ec; // 0x6ec
    RGState unk6f0; // 0x6f0
};