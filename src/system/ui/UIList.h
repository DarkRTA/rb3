#pragma once
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

/**
 * @brief A UI Object representing a list element.
 * Original _objects description:
 * "Component for displaying 1- or 2-dimensional lists of data.
 * Can be oriented horizontally or vertically, can scroll normally or
 * circularly, and can have any number of visible elements (even just
 * one, a.k.a. a spin button)."
 */
class UIList : public UIComponent,
               public UIListProvider,
               public ScrollSelect,
               public UIListStateCallback,
               public UITransitionHandler {
public:
    UIList();
    OBJ_CLASSNAME(UIList)
    OBJ_SET_TYPE(UIList)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual float GetDistanceToPlane(const Plane &, Vector3 &);
    virtual void DrawShowing();
    virtual RndDrawable *CollideShowing(const Segment &, float &, Plane &);
    virtual int CollidePlane(const Plane &);
    virtual ~UIList();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void Enter();
    virtual void Poll();
    virtual void Update();
    virtual void AdjustTrans(Transform &, const UIListElementDrawState &) {}
    virtual void AdjustTransSelected(Transform &) {}
    virtual int NumData() const;
    virtual void StartScroll(const UIListState &, int, bool);
    virtual void CompleteScroll(const UIListState &);
    virtual int SelectedAux() const;
    virtual void SetSelectedAux(int);
    virtual bool IsEmptyValue() const;
    virtual void FinishValueChange();

    void PreLoadWithRev(BinStream &, int);
    void Refresh(bool);
    void SetParent(UIList *);
    void CalcBoundingBox(Box &);
    void SetProvider(UIListProvider *);
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
    UIListState &GetListState();
    UIList *ChildList();
    UIList *ParentList();
    UIListDir *GetUIListDir() const;
    bool SetSelected(Symbol, bool, int);
    void SetSelectedSimulateScroll(int);
    bool SetSelectedSimulateScroll(Symbol, bool);
    void HandleSelectionUpdated();
    void Scroll(int);
    void AutoScroll();
    void StopAutoScroll();
    int NumProviderData() const;
    void BoundingBoxTriangles(std::vector<std::vector<Vector3> > &);
    const std::vector<UIListWidget *> &GetWidgets() const;
    void EnableData(Symbol);
    void DisableData(Symbol);
    void DimData(Symbol);
    void UnDimData(Symbol);
    void UpdateExtendedEntries(const UIListState &);
    void SetScrollUser(LocalUser *);
    void SetDrawManuallyControlledWidgets(bool);
    int CollidePlane(const std::vector<Vector3> &, const Plane &);

    static void CollectGarbage();

    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnSetData(DataArray *);
    DataNode OnSetSelected(DataArray *);
    DataNode OnSetSelectedSimulateScroll(DataArray *);
    DataNode OnScroll(DataArray *);
    DataNode OnSelectedSym(DataArray *);

    bool Circular() const { return mListState.mCircular; }
    int GridSpan() const { return mListState.GridSpan(); }

    UIListDir *mListDir; // 0x140
    std::vector<UIListWidget *> mWidgets; // 0x144
    UIListState mListState; // 0x14c
    int mUIListRev; // 0x190
    DataProvider *mDataProvider; // 0x194
    /** "Num data to show (only for milo)". Range from 1 to 1000 */
    int mNumData; // 0x198
    LocalUser *mUser; // 0x19c
    UIList *mParent; // 0x1a0
    /** "labels to be filled in by list provider at runtime" */
    ObjPtrList<UILabel> mExtendedLabelEntries; // 0x1a4
    /** "meshes to be filled in by list provider at runtime" */
    ObjPtrList<RndMesh> mExtendedMeshEntries; // 0x1b4
    /** "custom objects to be filled in by list provider at runtime" */
    ObjPtrList<Hmx::Object> mExtendedCustomEntries; // 0x1c4
    /** "Time to pause when auto scroll changes directions (seconds)" */
    float mAutoScrollPause; // 0x1d4
    int unk_0x1D8; // 0x1d8
    float unk_0x1DC; // 0x1dc
    u8 unk_0x1E0; // 0x1e0
    /** "Allow scrolling by pages?" */
    bool mPaginate; // 0x1e1
    /** "Should this list send UIComponentScroll* messages while auto-scrolling?" */
    bool mAutoScrollSendMessages; // 0x1e2
    bool mAutoScrolling; // 0x1e3
    bool unk_0x1E4; // 0x1e4 - scroll related
    bool mDrawManuallyControlledWidgets; // 0x1e5
    bool unk_0x1E6;
    bool mNeedsGarbageCollection; // 0x1e7

    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS

    static void Init();
    static void Register() { REGISTER_OBJ_FACTORY(UIList) }
    NEW_OBJ(UIList)

    // display num: "Number of rows/columns". range is 1-50
    // scroll time: "Time (seconds) to scroll one step - 0 for instant scrolling". Range
    // from 0 to 5
};
