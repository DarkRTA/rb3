#pragma once
#include "obj/Data.h"
#include "rndobj/Overlay.h"
#include "char/CharDriver.h"
#include "obj/ObjPtr_p.h"

// forward decs
class Character;
class CharClip;
class CharClipGroup;
class ClipDistMap;
class Waypoint;

class CharacterTest : public RndOverlay::Callback {
public:
    CharacterTest(Character *);
    virtual ~CharacterTest();
    virtual float UpdateOverlay(RndOverlay *, float);
    virtual DataNode Handle(DataArray *, bool);

    void Load(BinStream &);
    void Poll();
    void Draw();
    void PlayNew();
    /** "Recenters character at his last set waypoint" */
    void Recenter();
    void AddDefaults();
    void Walk();
    void TeleportTo(Waypoint *);
    void SetStartEndBeat(float, float, int);
    void SetMoveSelf(bool);
    void Sync();
    void SetDistMap(Symbol);
    ObjectDir *Clips() const { return mDriver ? mDriver->ClipDir() : nullptr; }

    DataNode OnGetFilteredClips(DataArray *);

    NEW_POOL_OVERLOAD(CharacterTest)
    DELETE_POOL_OVERLOAD(CharacterTest)
    DECLARE_REVS;

    Character *mMe; // 0x4
    /** "The driver to animate" */
    ObjPtr<CharDriver> mDriver; // 0x8
    /** "Clip to play" */
    ObjPtr<CharClip> mClip1; // 0x14
    /** "Clip to transition to, if any" */
    ObjPtr<CharClip> mClip2; // 0x20
    /** "If set, group to use as filter for clips" */
    ObjPtr<CharClipGroup> mFilterGroup; // 0x2c
    /** "Teleport to this Waypoint" */
    ObjPtr<Waypoint> mTeleportTo; // 0x38
    ObjPtrList<Waypoint> mWalkPath; // 0x44
    /** "Displays the transition distance map between clip1 and clip2, raw means the raw
     * graph, no nodes". Options are: none, nodes, raw */
    Symbol mShowDistMap; // 0x54
    /** "Which transition to use between clip1 and clip2" */
    int mTransition; // 0x58
    /** "Cycle through all the transitions" */
    bool mCycleTransition; // 0x5c
    /** "Click on every beat transition" */
    bool mMetronome; // 0x5d
    /** "Character does not travel, constantly zeros out position and facing" */
    bool mZeroTravel; // 0x5e
    /** "graphically displays the screensize and lod next to the character" */
    bool mShowScreenSize; // 0x5f
    bool mShowFootExtents; // 0x60
    float unk64; // 0x64
    int unk68; // 0x68
    ClipDistMap *unk6c; // 0x6c
    RndOverlay *mOverlay; // 0x70

    // bool move_self: "Move ourselves around when playing animations, if true, the anim
    // bar won't work backwards" script zero: "Teleports character to the origin" script
    // add default rigging: "Adds default objects like main drivers and twist servos"
};

bool PropSync(CharacterTest &, DataNode &, DataArray *, int, PropOp);
