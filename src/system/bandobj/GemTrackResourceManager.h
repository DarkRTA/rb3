#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Dir.h"
#include "bandobj/TrackPanelDirBase.h"

class GemTrackResourceManager : public Hmx::Object {
public:
    class SmasherPlateInfo {
    public:
        SmasherPlateInfo(Hmx::Object* o) : mSmasherPlate(o, 0), mTrackInst(kInstNone), mInUse(0) {}

        ObjPtr<RndDir, ObjectDir> mSmasherPlate; // 0x0
        TrackInstrument mTrackInst; // 0xc
        bool mInUse; // 0x10
    };

    GemTrackResourceManager(ObjectDir*);
    virtual ~GemTrackResourceManager();

    void InitSmasherPlates();
    RndDir* GetFreeSmasherPlate(TrackInstrument);
    void ReleaseSmasherPlate(RndDir*);

    ObjPtr<ObjectDir, ObjectDir> unk1c; // 0x1c
    std::vector<SmasherPlateInfo> unk28; // 0x28
};