#ifndef UI_UILIST_H
#define UI_UILIST_H

#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "types.h"
#include "ui/ScrollSelect.h"
#include "ui/UIComponent.h"
#include "ui/UILabel.h"
#include "ui/UIListProvider.h"
#include "ui/UIListState.h"
#include "ui/UITransitionHandler.h"
#include "utl/BinStream.h"
#include "utl/MemMgr.h"

class UIList : public UIComponent, public UIListProvider, public ScrollSelect, public UIListStateCallback, public UITransitionHandler {
    public:
    UIList();
    virtual ~UIList();
    OBJ_CLASSNAME(UIList)
    OBJ_SET_TYPE(UIList)
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    virtual void Update();

    virtual short NumData() const;

    virtual bool IsEmptyValue() const;
    
    virtual int SelectedAux() const; 
    virtual void SetSelectedAux(int);

    void PreLoadWithRev(BinStream&, int);
    void Refresh(bool);

    int unk_0x140;
    std::vector<int> unk_0x144;
    UIListState unk_0x14C;
    int mRev; // 0x190
    int unk_0x194, unk_0x198, unk_0x19C, unk_0x1A0;


    ObjPtrList<UILabel, ObjectDir> unk_0x1A4;
    ObjPtrList<RndMesh, ObjectDir> unk_0x1B4;
    ObjPtrList<Hmx::Object, ObjectDir> unk_0x1C4;
    float unk_0x1D4;
    int unk_0x1D8;
    float unk_0x1DC;
    u8 unk_0x1E0, unk_0x1E1;
    bool unk_0x1E2;
    u8 unk_0x1E3, unk_0x1E4, unk_0x1E5, unk_0x1E6, unk_0x1E7;

    DELETE_OVERLOAD
    DECLARE_REVS

    static void Init();
    NEW_OBJ(UIList)
};

#endif // UI_UILIST_H
