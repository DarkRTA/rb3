#ifndef RB3_UIPANEL_HPP
#define RB3_UIPANEL_HPP
#include "hmx/object.hpp"
#include "string.hpp"
#include "filepath.hpp"

class UIPanel : public virtual Hmx::Object {
public:
    UIPanel();
    virtual ~UIPanel();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Load(BinStream&);
    virtual void SetTypeDef(DataArray *);
    virtual void DataDir();

    int unk8;
    int unkc;
    String str;
    int unk1c;
    char unk20, unk21, unk22, unk23;
    int unk24;
    FilePath fpath;
};

#endif
