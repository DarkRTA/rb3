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
#include "ui/UIListElementDrawState.h"
#include "utl/BinStream.h"
#include "utl/MemMgr.h"

class UIListDir;

class UIList : public UIComponent, public UIListProvider, public ScrollSelect, public UIListStateCallback, public UITransitionHandler {
public:
    UIList();
    OBJ_CLASSNAME(UIList)
    OBJ_SET_TYPE(UIList)
    virtual DataNode Handle(DataArray*, bool);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual ~UIList();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();
    virtual void Update();
    virtual void AdjustTrans(Transform&, const UIListElementDrawState&){}
    virtual void AdjustTransSelected(Transform&){}
    virtual int NumData() const;
    virtual void StartScroll(const UIListState&, int, bool);
    virtual void CompleteScroll(const UIListState&);
    virtual int SelectedAux() const; 
    virtual void SetSelectedAux(int);
    virtual bool IsEmptyValue() const;
    virtual void FinishValueChange();    

    void PreLoadWithRev(BinStream&, int);
    void Refresh(bool);
    void SetParent(UIList*);
    void CalcBoundingBox(Box&);
    void SetProvider(UIListProvider*);
    void SetSelected(int, int);
    void SetNumDisplay(int);
    void SetGridSpan(int);
    void SetCircular(bool);
    void SetSpeed(float);
    int NumDisplay() const;
    float Speed() const;
    int FirstShowing() const;
    int Selected() const;
    int SelectedDisplay() const;
    int SelectedData() const;
    int SelectedPos() const;
    Symbol SelectedSym(bool) const;
    bool IsScrolling() const;
    UIListState& GetListState();

    static std::list<UIList*> sUIListSet;

    UIListDir* mListDir; // 0x140
    std::vector<UIListWidget*> mWidgets; // 0x144
    UIListState mListState; // 0x14c
    int mUIListRev; // 0x190
    DataProvider* mDataProvider; // 0x194
    int mNumData; // 0x198
    LocalUser* mUser; // 0x19c
    UIList* mParent; // 0x1a0
    ObjPtrList<UILabel, ObjectDir> mExtendedLabelEntries; // 0x1a4
    ObjPtrList<RndMesh, ObjectDir> mExtendedMeshEntries; // 0x1b4
    ObjPtrList<Hmx::Object, ObjectDir> mExtendedCustomEntries; // 0x1c4
    float mAutoScrollPause; // 0x1d4
    int unk_0x1D8; // 0x1d8
    float unk_0x1DC; // 0x1dc
    u8 unk_0x1E0; // 0x1e0
    bool mPaginate; // 0x1e1
    bool mAutoScrollSendMessages; // 0x1e2
    bool mAutoScrolling; // 0x1e3
    bool unk_0x1E4, unk_0x1E5, unk_0x1E6, unk_0x1E7;

    DELETE_OVERLOAD
    DECLARE_REVS

    static void Init();
    NEW_OBJ(UIList)
};

#endif // UI_UILIST_H
