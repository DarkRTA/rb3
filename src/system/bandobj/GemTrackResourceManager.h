#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Dir.h"

class GemTrackResourceManager : public Hmx::Object {
public:
    class SmasherPlateInfo {
    public:
        SmasherPlateInfo(Hmx::Object* o) : unk0(o, 0), unkc(-1), mInUse(0) {}
        ObjPtr<RndDir, ObjectDir> unk0; // 0x0
        int unkc;
        bool mInUse; // 0x10
    };

    GemTrackResourceManager(ObjectDir*);
    virtual ~GemTrackResourceManager();

    void InitSmasherPlates();

    ObjPtr<ObjectDir, ObjectDir> unk1c; // 0x1c
    std::vector<SmasherPlateInfo> unk28; // 0x28
};