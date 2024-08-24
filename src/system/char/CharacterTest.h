#ifndef CHAR_CHARACTERTEST_H
#define CHAR_CHARACTERTEST_H
#include "rndobj/Overlay.h"
#include "obj/ObjPtr_p.h"

// forward decs
class Character;
class CharDriver;
class CharClip;
class CharClipGroup;
class ClipDistMap;
class Waypoint;

class CharacterTest : public RndOverlay::Callback {
public:
    CharacterTest(Character*);
    virtual ~CharacterTest();
    virtual float UpdateOverlay(RndOverlay*, float);
    virtual DataNode Handle(DataArray*, bool);

    void Load(BinStream&);
    void Poll();
    void Draw();
    void PlayNew();
    void Recenter();
    void AddDefaults();
    void Walk();
    void TeleportTo(Waypoint*);
    void SetStartEndBeat(float, float, int);
    void SetMoveSelf(bool);

    NEW_POOL_OVERLOAD(CharacterTest)
    DELETE_POOL_OVERLOAD(CharacterTest)
    DECLARE_REVS;

    Character* mMe; // 0x4
    ObjPtr<CharDriver, ObjectDir> mDriver; // 0x8
    ObjPtr<CharClip, ObjectDir> mClip1; // 0x14
    ObjPtr<CharClip, ObjectDir> mClip2; // 0x20
    ObjPtr<CharClipGroup, ObjectDir> mFilterGroup; // 0x2c
    ObjPtr<Waypoint, ObjectDir> mTeleportTo; // 0x38
    ObjPtrList<Waypoint, ObjectDir> mWalkPath; // 0x44
    Symbol mShowDistMap; // 0x54
    int mTransition; // 0x58
    bool mCycleTransition; // 0x5c
    bool mMetronome; // 0x5d
    bool mZeroTravel; // 0x5e
    bool mShowScreenSize; // 0x5f
    bool mShowFootExtents; // 0x60
    float unk64; // 0x64
    int unk68; // 0x68
    ClipDistMap* unk6c; // 0x6c
    RndOverlay* mOverlay; // 0x70
};

bool PropSync(CharacterTest&, DataNode&, DataArray*, int, PropOp);

#endif