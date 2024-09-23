#ifndef BANDOBJ_BANDLABEL_H
#define BANDOBJ_BANDLABEL_H
#include "ui/UITransitionHandler.h"
#include "ui/UILabel.h"
#include "math/Key.h"

class BandLabel : public UILabel, public UITransitionHandler {
public:
    BandLabel();
    OBJ_CLASSNAME(BandLabel);
    OBJ_SET_TYPE(BandLabel);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~BandLabel();
    virtual void Poll();
    virtual void SetDisplayText(const char*, bool);
    virtual void Count(int, int, float, Symbol);
    virtual void FinishCount();
    virtual bool IsEmptyValue() const;
    virtual void FinishValueChange();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static void LoadOldBandTextComp(BinStream&);
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandLabel);
    }
    NEW_OBJ(BandLabel);

    Keys<float, float> unk1dc; // 0x1dc
    Symbol unk1e4; // 0x1e4
    String unk1e8; // 0x1e8
    bool unk1f4; // 0x1f4
};

#endif // BANDOBJ_BANDLABEL_H