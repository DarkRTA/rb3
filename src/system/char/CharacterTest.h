#ifndef CHAR_CHARACTERTEST_H
#define CHAR_CHARACTERTEST_H
#include "rndobj/Overlay.h"
#include "obj/ObjPtr_p.h"

// forward decs
class Character;
class CharDriver;
class CharClip;
class CharClipGroup;
class Waypoint;

class CharacterTest : public RndOverlay::Callback {
public:
    CharacterTest(Character*);
    virtual ~CharacterTest();
    virtual float UpdateOverlay(RndOverlay*, float);
    virtual DataNode Handle(DataArray*, bool);

    void* operator new(size_t s){
        return _PoolAlloc(s, sizeof(CharacterTest), FastPool);
    }

    void operator delete(void* v){
        _PoolFree(sizeof(CharacterTest), FastPool, v);
    }

    Character* mMe;
    ObjPtr<CharDriver, ObjectDir> mDriver;
    ObjPtr<CharClip, ObjectDir> mClip1;
    ObjPtr<CharClip, ObjectDir> mClip2;
    ObjPtr<CharClipGroup, ObjectDir> mFilterGroup;
    ObjPtr<Waypoint, ObjectDir> mTeleportTo;
    ObjPtrList<Waypoint, ObjectDir> mWalkPath;
    Symbol mShowDistMap;
    int mTransition;
    bool unk5c;
    bool unk5d;
    bool unk5e;
    bool unk5f;
    bool unk60;
    int unk64;
    int unk68;
    int unk6c;
    RndOverlay* mOverlay;
};

#endif