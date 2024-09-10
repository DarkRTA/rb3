#pragma once
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/MatAnim.h"
#include "bandobj/CrowdMeterIcon.h"

class BandCrowdMeter : public RndDir {
public:
    class IconData {
    public:
        IconData(BandCrowdMeter*, CrowdMeterIcon*, RndGroup*);

        ObjPtr<CrowdMeterIcon, ObjectDir> unk0; // 0x0
        ObjPtr<RndGroup, ObjectDir> unkc; // 0xc
        bool unk18; // 0x18
        bool unk19; // 0x19
        bool unk1a; // 0x1a
        bool unk1b; // 0x1b
        float unk1c; // 0x1c
        bool unk20; // 0x20
    };

    BandCrowdMeter();
    OBJ_CLASSNAME(BandCrowdMeterDir);
    OBJ_SET_TYPE(BandCrowdMeterDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~BandCrowdMeter();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void Poll();

    bool Disabled() const;
    CrowdMeterIcon* PlayerIcon(int);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<IconData> unk18c; // 0x18c
    bool unk194; // 0x194
    float unk198; // 0x198
    bool unk19c; // 0x19c
    std::vector<Hmx::Color> unk1a0; // 0x1a0
    int unk1a8; // 0x1a8
    int unk1ac; // 0x1ac
    ObjPtrList<RndGroup, ObjectDir> unk1b0; // 0x1b0
    ObjPtr<EventTrigger, ObjectDir> unk1c0; // 0x1c0
    ObjPtr<EventTrigger, ObjectDir> unk1cc; // 0x1cc
    ObjPtr<EventTrigger, ObjectDir> unk1d8; // 0x1d8
    ObjPtr<EventTrigger, ObjectDir> unk1e4; // 0x1e4
    ObjPtr<EventTrigger, ObjectDir> unk1f0; // 0x1f0
    ObjPtr<EventTrigger, ObjectDir> unk1fc; // 0x1fc
    std::vector<ObjPtr<EventTrigger, ObjectDir> > unk208; // 0x208
    ObjPtr<EventTrigger, ObjectDir> unk210; // 0x210
    ObjPtr<EventTrigger, ObjectDir> unk21c; // 0x21c
    ObjPtr<EventTrigger, ObjectDir> unk228; // 0x228
    int unk234; // 0x234
    ObjPtr<RndMatAnim, ObjectDir> unk238; // 0x238
    float unk244; // 0x244
    float unk248[5]; // 0x248
};