#pragma once
#include "rndobj/Dir.h"
#include "ui/UIListProvider.h"
#include "ui/UIListState.h"
#include "ui/UIListWidget.h"

enum UIListOrientation {
    kUIListVertical,
    kUIListHorizontal
};

/** "Top-level resource object for UILists" */
class UIListDir : public RndDir, public UIListProvider, public UIListStateCallback {
public:
    UIListDir();
    OBJ_CLASSNAME(UIListDir)
    OBJ_SET_TYPE(UIListDir)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual ~UIListDir();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SyncObjects();
    virtual void DrawShowing();
    virtual void Poll();
    virtual void StartScroll(const UIListState &, int, bool);
    virtual void CompleteScroll(const UIListState &);
    virtual int NumData() const;
    virtual float GapSize(int, int, int, int) const;
    virtual bool IsActive(int) const;

    UIListOrientation Orientation() const;
    float ElementSpacing() const;
    UIList *SubList(int, std::vector<UIListWidget *> &);
    void CompleteScroll(const UIListState &, std::vector<UIListWidget *> &);
    void CreateElements(UIList *, std::vector<UIListWidget *> &, int);
    void FillElements(const UIListState &, std::vector<UIListWidget *> &);
    void FillElement(const UIListState &, std::vector<UIListWidget *> &, int);
    void PollWidgets(std::vector<UIListWidget *> &);
    void ListEntered();
    void StartScroll(const UIListState &, std::vector<UIListWidget *> &, int, bool);
    void Reset();
    void DrawWidgets(
        const UIListState &,
        std::vector<UIListWidget *> &,
        const Transform &,
        UIComponent::State,
        Box *,
        bool
    );
    void BuildDrawState(
        UIListWidgetDrawState &, const UIListState &, UIComponent::State, float
    ) const;
    void SetElementPos(Vector3 &, float, int, float, float) const;

    DECLARE_REVS;
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(UIListDir)
    static void Init() { REGISTER_OBJ_FACTORY(UIListDir) }

    /** "scroll direction of list" */
    UIListOrientation mOrientation; // 0x194
    /** "Number of elements to fade from beginning/end of list". Ranges from 0 to 10. */
    int mFadeOffset; // 0x198
    /** "spacing between elements". Ranges from 0 to 1000. */
    float mElementSpacing; // 0x19c
    /** "point during scroll when highlight changes". Ranges from 0 to 1. */
    float mScrollHighlightChange; // 0x1a0
    /** "draw widgets in preview mode?" */
    bool mTestMode; // 0x1a4
    UIListState mTestState; // 0x1a8
    /** "total number of data elements" */
    int mTestNumData; // 0x1ec
    /** "test gaps between elements". Ranges from 0 to 1000. */
    float mTestGapSize; // 0x1f0
    UIComponent::State mTestComponentState; // 0x1f4
    /** "test disable every other element" */
    bool mTestDisableElements; // 0x1f8
    std::vector<UIListWidget *> unk1fc; // 0x1fc
    int mDirection; // 0x204

    // test num display: "number of elements to draw"
    // test scroll time: "test scroll time"
};
