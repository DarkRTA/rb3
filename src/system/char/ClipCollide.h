#ifndef CHAR_CLIPCOLLIDE_H
#define CHAR_CLIPCOLLIDE_H
#include "obj/Object.h"
#include <vector>
#include "obj/ObjPtr_p.h"

// forward decs
class RndGraph;
class Character;
class Waypoint;
class CharClip;

class ClipCollide : public Hmx::Object {
public:

    // a la RB2 dump
    struct Report {
        // total size: 0x160
        char name[32]; // offset 0x0, size 0x20
        char charPath[256]; // offset 0x20, size 0x100
        char clip[32]; // offset 0x120, size 0x20
        class Waypoint * waypoint; // offset 0x140, size 0x4
        class Symbol position; // offset 0x144, size 0x4
        class Vector3 pos; // offset 0x150, size 0x10
    };

    ClipCollide();
    virtual ~ClipCollide();
    OBJ_CLASSNAME(ClipCollide)
    OBJ_SET_TYPE(ClipCollide)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void SetTypeDef(DataArray*);

    std::vector<Report> mReports;
    RndGraph* mGraph;
    ObjPtr<Character, ObjectDir> mChar;
    String mCharPath;
    ObjPtr<Waypoint, ObjectDir> mWaypoint;
    Symbol mPosition;
    ObjPtr<CharClip, ObjectDir> mClip;
    String mReportString;
    bool mWorldLines;
    bool mMoveCamera;
    Symbol mMode;
};

#endif
