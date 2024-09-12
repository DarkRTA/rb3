#pragma once
#include "bandobj/BandTrack.h"
#include "bandobj/PitchArrow.h"
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "rndobj/Text.h"

class VocalTrackDir : public RndDir, public BandTrack {
public:
    VocalTrackDir();
    OBJ_CLASSNAME(VocalTrackDir)
    OBJ_SET_TYPE(VocalTrackDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~VocalTrackDir(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void TrackReset();
    virtual void ResetSmashers(bool);
    virtual void PlayIntro();
    virtual void Deploy();
    virtual void SetPlayerLocal(float);
    virtual ObjectDir* ThisDir();
    virtual ObjectDir* ThisDir() const; // fix ptr
    virtual void SpotlightPhraseSuccess();
    virtual int AsVocalTrackDir();
    virtual int AsRndDir();
    virtual void Reset();
    virtual void Retract(bool);
    virtual void Extend(bool);
    virtual void RefreshCrowdRating(float, CrowdMeterState);
    virtual void SetPerformanceMode(bool);
    virtual void SetTambourine(bool);
    virtual void TutorialReset();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    float unk2a0; // 0x2a0
    bool unk2a4; // 0x2a4
    bool unk2a5; // 0x2a5
    bool unk2a6; // 0x2a6
    bool unk2a7; // 0x2a7
    int unk2a8; // 0x2a8
    int unk2ac; // 0x2ac
    int unk2b0; // 0x2b0
    std::map<int, Hmx::Color> unk2b4; // 0x2b4
    std::map<int, float> unk2cc; // 0x2cc
    ObjPtr<RndDir, ObjectDir> unk2e4; // 0x2e4
    ObjPtr<RndDir, ObjectDir> unk2f0; // 0x2f0
    float unk2fc; // 0x2fc
    float unk300; // 0x300
    float unk304; // 0x304
    ObjPtrList<RndTransformable, ObjectDir> unk308; // 0x308
    ObjPtr<Hmx::Object, ObjectDir> unk318; // 0x318
    ObjPtr<RndDir, ObjectDir> unk324; // 0x324
    ObjPtr<EventTrigger, ObjectDir> unk330; // 0x330
    ObjPtr<EventTrigger, ObjectDir> unk33c; // 0x33c
    ObjPtr<BandLabel, ObjectDir> unk348; // 0x348
    ObjPtr<EventTrigger, ObjectDir> unk354; // 0x354
    ObjPtr<EventTrigger, ObjectDir> unk360; // 0x360
    ObjPtr<EventTrigger, ObjectDir> unk36c; // 0x36c
    ObjPtr<PitchArrow, ObjectDir> unk378; // 0x378
    ObjPtr<PitchArrow, ObjectDir> unk384; // 0x384
    ObjPtr<PitchArrow, ObjectDir> unk390; // 0x390
    bool unk39c; // 0x39c
    float unk3a0; // 0x3a0
    ObjPtr<RndMesh, ObjectDir> unk3a4; // 0x3a4
    ObjPtr<RndMesh, ObjectDir> unk3b0; // 0x3b0
    bool unk3bc; // 0x3bc
    float unk3c0; // 0x3c0
    ObjPtr<RndMesh, ObjectDir> unk3c4; // 0x3c4
    bool unk3d0; // 0x3d0
    float unk3d4; // 0x3d4
    ObjPtr<RndMesh, ObjectDir> unk3d8; // 0x3d8
    ObjPtr<RndMesh, ObjectDir> unk3e4; // 0x3e4
    ObjPtr<RndMesh, ObjectDir> unk3f0; // 0x3f0
    float unk3fc; // 0x3fc
    ObjPtr<RndMesh, ObjectDir> unk400; // 0x400
    bool unk40c; // 0x40c
    float unk410; // 0x410
    float unk414; // 0x414
    float unk418; // 0x418
    float unk41c; // 0x41c
    float unk420; // 0x420
    float unk424; // 0x424
    float unk428; // 0x428
    float unk42c; // 0x42c
    Symbol unk430; // 0x430
    ObjPtr<Hmx::Object, ObjectDir> unk434; // 0x434
    ObjPtr<Hmx::Object, ObjectDir> unk440; // 0x440
    ObjPtr<Hmx::Object, ObjectDir> unk44c; // 0x44c
    ObjPtr<RndText, ObjectDir> unk458; // 0x458
    ObjPtr<RndText, ObjectDir> unk464; // 0x464
    ObjPtr<RndText, ObjectDir> unk470; // 0x470
    ObjPtr<RndText, ObjectDir> unk47c; // 0x47c
    float unk488; // 0x488
    float unk48c; // 0x48c
    float unk490; // 0x490
    int unk494; // 0x494
    ObjPtr<RndAnimatable, ObjectDir> unk498; // 0x498
    ObjPtr<RndAnimatable, ObjectDir> unk4a4; // 0x4a4
    bool unk4b0; // 0x4b0
    int unk4b4; // 0x4b4
    int unk4b8; // 0x4b8
    int unk4bc; // 0x4bc
    int unk4c0; // 0x4c0
    int unk4c4; // 0x4c4
    int unk4c8; // 0x4c8
    int unk4cc; // 0x4cc
    int unk4d0; // 0x4d0
    int unk4d4; // 0x4d4
    ObjPtr<RndGroup, ObjectDir> unk4d8; // 0x4d8
    ObjPtr<RndGroup, ObjectDir> unk4e4; // 0x4e4
    ObjPtr<RndGroup, ObjectDir> unk4f0; // 0x4f0
    ObjPtr<RndGroup, ObjectDir> unk4fc; // 0x4fc
    ObjPtr<RndGroup, ObjectDir> unk508; // 0x508
    ObjPtr<RndGroup, ObjectDir> unk514; // 0x514
    ObjPtr<RndGroup, ObjectDir> unk520; // 0x520
    ObjPtr<RndGroup, ObjectDir> unk52c; // 0x52c
    ObjPtr<RndGroup, ObjectDir> unk538; // 0x538
    ObjPtr<RndGroup, ObjectDir> unk544; // 0x544
    ObjPtr<RndGroup, ObjectDir> unk550; // 0x550
    ObjPtr<RndGroup, ObjectDir> unk55c; // 0x55c
    ObjPtr<RndGroup, ObjectDir> unk568; // 0x568
    ObjPtr<RndGroup, ObjectDir> unk574; // 0x574
    ObjPtr<RndMat, ObjectDir> unk580; // 0x580
    ObjPtr<RndMat, ObjectDir> unk58c; // 0x58c
    ObjPtr<RndMat, ObjectDir> unk598; // 0x598
    ObjPtr<RndMat, ObjectDir> unk5a4; // 0x5a4
    ObjPtr<RndMat, ObjectDir> unk5b0; // 0x5b0
    ObjPtr<RndMat, ObjectDir> unk5bc; // 0x5bc
    ObjPtr<RndMat, ObjectDir> unk5c8; // 0x5c8
    ObjPtr<RndMat, ObjectDir> unk5d4; // 0x5d4
    ObjPtr<RndMat, ObjectDir> unk5e0; // 0x5e0
    ObjPtr<RndMat, ObjectDir> unk5ec; // 0x5ec
    ObjPtr<RndMat, ObjectDir> unk5f8; // 0x5f8
    ObjPtr<RndMat, ObjectDir> unk604; // 0x604
    ObjPtr<RndMat, ObjectDir> unk610; // 0x610
    ObjPtr<RndGroup, ObjectDir> unk61c; // 0x61c
    ObjPtr<RndTransformable, ObjectDir> unk628; // 0x628
    ObjPtr<RndTransformable, ObjectDir> unk634; // 0x634
    ObjPtr<RndTransformable, ObjectDir> unk640; // 0x640
    ObjPtr<RndGroup, ObjectDir> unk64c; // 0x64c
    ObjPtr<RndGroup, ObjectDir> unk658; // 0x658
    ObjPtr<RndGroup, ObjectDir> unk664; // 0x664
    ObjPtr<RndGroup, ObjectDir> unk670; // 0x670
    ObjPtr<RndGroup, ObjectDir> unk67c; // 0x67c
    ObjPtr<RndGroup, ObjectDir> unk688; // 0x688
    float unk694; // 0x694
    float unk698; // 0x698
    float unk69c; // 0x69c
    float unk6a0; // 0x6a0
    ObjPtr<RndMat, ObjectDir> unk6a4; // 0x6a4
    ObjPtr<RndMat, ObjectDir> unk6b0; // 0x6b0
    float unk6bc; // 0x6bc
    float unk6c0; // 0x6c0
    int unk6c4; // 0x6c4
    bool unk6c8; // 0x6c8
    ObjPtr<RndGroup, ObjectDir> unk6cc; // 0x6cc
    float unk6d8; // 0x6d8
    float unk6dc; // 0x6dc
    bool unk6e0; // 0x6e0
};