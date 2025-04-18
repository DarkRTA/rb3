#pragma once
#include "obj/Object.h"
#include <vector>
#include "obj/ObjPtr_p.h"

// forward decs
class RndGraph;
class Character;
class Waypoint;
class CharClip;

/** "Analyzes character clips in a venue" */
class ClipCollide : public Hmx::Object {
public:
    // a la RB2 dump
    struct Report {
        // total size: 0x160
        char name[32]; // offset 0x0, size 0x20
        char charPath[256]; // offset 0x20, size 0x100
        char clip[32]; // offset 0x120, size 0x20
        class Waypoint *waypoint; // offset 0x140, size 0x4
        class Symbol position; // offset 0x144, size 0x4
        class Vector3 pos; // offset 0x150, size 0x10
    };

    ClipCollide();
    virtual ~ClipCollide();
    OBJ_CLASSNAME(ClipCollide)
    OBJ_SET_TYPE(ClipCollide)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual void SetTypeDef(DataArray *);

    void SyncChar();
    void SyncWaypoint();
    void ClearReport();
    void SyncMode();
    /** "Run the animation" */
    void Demonstrate();
    bool ValidWaypoint(Waypoint *);
    bool ValidClip(CharClip *);
    /** "Test all the characters against all the waypoints in this venue" */
    void TestChars();
    /** "Test the current character against all the waypoints in the venue" */
    void TestWaypoints();
    /** "Test all clips for the current character and waypoint" */
    void TestClips();
    ObjectDir *Clips();
    /** "Run the collision" */
    void Collide();
    void AddReport(Vector3);
    void PickReport(const char *);

    DataNode OnVenueName(DataArray *);
    DataNode OnListClips(DataArray *);
    DataNode OnListWaypoints(DataArray *);
    DataNode OnListReport(DataArray *);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(ClipCollide)
    static void Init() { REGISTER_OBJ_FACTORY(ClipCollide) }

    std::vector<Report> mReports; // 0x1c
    RndGraph *mGraph; // 0x24
    /** "Pointer to the character to move around" */
    ObjPtr<Character> mChar; // 0x28
    String mCharPath; // 0x34
    /** "Waypoint to stand at" */
    ObjPtr<Waypoint> mWaypoint; // 0x40
    /** "Where in the waypoint to stand". Options are: front, back, left, right */
    Symbol mPosition; // 0x4c
    /** "Clip to test" */
    ObjPtr<CharClip> mClip; // 0x50
    String mReportString; // 0x5c
    /** "show red world lines" */
    bool mWorldLines; // 0x68
    /** "move the camera when you pick a report" */
    bool mMoveCamera; // 0x69
    /** "mode to run in" */
    Symbol mMode; // 0x6c

    // pick character: "Changes the character to one of the listed ones"
    // pick report: "Pick a report entry to look at"
};
