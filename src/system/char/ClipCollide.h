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

    void SyncChar();
    void SyncWaypoint();
    void ClearReport();
    void SyncMode();
    void Demonstrate();
    bool ValidWaypoint(Waypoint*);
    bool ValidClip(CharClip*);
    void TestChars();
    void TestWaypoints();
    void TestClips();
    ObjectDir* Clips();
    void Collide();

    DataNode OnVenueName(DataArray*);
    DataNode OnListClips(DataArray*);
    DataNode OnListWaypoints(DataArray*);
    DataNode OnListReport(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<Report> mReports; // 0x1c
    RndGraph* mGraph; // 0x24
    ObjPtr<Character, ObjectDir> mChar; // 0x28
    String mCharPath; // 0x34
    ObjPtr<Waypoint, ObjectDir> mWaypoint; // 0x40
    Symbol mPosition; // 0x4c
    ObjPtr<CharClip, ObjectDir> mClip; // 0x50
    String mReportString; // 0x5c
    bool mWorldLines; // 0x68
    bool mMoveCamera; // 0x69
    Symbol mMode; // 0x6c
};

#endif
