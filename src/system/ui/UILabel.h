#ifndef UI_UILABEL_H
#define UI_UILABEL_H

#include "milo_types.h"
#include "rndobj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Font.h"
#include "rndobj/Text.h"
#include "ui/UIComponent.h"
#include "ui/UIColor.h"
#include "utl/MemMgr.h"
#include "obj/Dir.h"
#include "os/DateTime.h"
#include "ui/UILabelDir.h"

class UILabelDir;

class UILabel : public UIComponent {
public:

    enum FitType {
        kFitWrap = 0,
        kFitStretch = 1,
        kFitJust = 2,
        kFitEllipsis = 3,
    };

    UILabel();
    OBJ_CLASSNAME(UILabel);
    OBJ_SET_TYPE(UILabel);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual void Draw();
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight();
    virtual ~UILabel();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Poll();
    virtual bool CanHaveFocus();
    virtual void CopyMembers(const UIComponent*, Hmx::Object::CopyType);
    virtual void Update();
    virtual void SetCreditsText(DataArray*, class UIListSlot*) {MILO_ASSERT(false, 78);}
    virtual void SetDisplayText(const char*, bool);

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD

    NEW_OBJ(UILabel)
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(UILabel)
    }
    static bool sDebugHighlight;
    static bool sDeferUpdate;

    const char* GetDefaultText() const;
    int InqMinMaxFromWidthAndHeight(float, float, RndText::Alignment, Vector3&, Vector3&);
    void Terminate();
    void LabelUpdate(bool, bool);
    void AdjustHeight(bool);
    void SetFloat(const char*, float);
    void SetTextToken(Symbol);
    void CenterWithLabel(UILabel*, bool, float);
    void SetEditText(const char*);
    void SetUseHighlightMesh(bool);
    Symbol TextToken() const;
    RndText* TextObj();
    void SetColorOverride(UIColor*);
    float GetDrawWidth();
    float GetDrawHeight();
    float Alpha(){ return mAlpha; }
    float AltAlpha(){ return mAltAlpha; }
    void SetAlpha(float f){ mAlpha = f; }
    void SetAltAlpha(float f){ mAltAlpha = f; }
    void SetTokenFmt(const DataArray*);
    void SetTokenFmtImp(Symbol, const DataArray*, const DataArray*, int, bool);
    void SetInt(int, bool);
    void SetIcon(char);
    void AppendIcon(char);
    void SetDateTime(const DateTime&, Symbol);
    void SetSubtitle(const DataArray*);
    RndText::Alignment Alignment() const { return (RndText::Alignment)mAlignment; }
    void SetAlignment(RndText::Alignment);
    void SetCapsMode(RndText::CapsMode);
    void SetFitType(FitType);
    void OnSetIcon(const char*);
    void AltFontResourceFileUpdated(bool);
    RndFont* AltFont();
    RndFont* Font();
    void UpdateAndDrawHighlightMesh();

    template <class T1> void SetTokenFmt(Symbol s, T1 t1) {
        SetTokenFmt(DataArrayPtr(DataNode(s), DataNode(t1)));
    }

    template <class T1, class T2> void SetTokenFmt(Symbol s, T1 t1, T2 t2) {
        SetTokenFmt(DataArrayPtr(DataNode(s), DataNode(t1), DataNode(t2)));
    }

    template <class T1, class T2, class T3> void SetTokenFmt(Symbol s, T1 t1, T2 t2, T3 t3) {
        SetTokenFmt(DataArrayPtr(DataNode(s), DataNode(t1), DataNode(t2), DataNode(t3)));
    }

    bool HasHighlightMesh() const {
        return mLabelDir->HighlighMeshGroup() != 0;
    }

    DataNode OnSetTokenFmt(const DataArray*);
    DataNode OnSetInt(const DataArray*);
    DataNode OnGetMaterialVariations(const DataArray*);
    DataNode OnGetAltMaterialVariations(const DataArray*);

    UILabelDir* mLabelDir; // 0x10c
    RndText* mText; // 0x110 - TrackWidget* in bank 5
    class String unk114; // 0x114
    ObjPtr<RndFont, class ObjectDir> mFont; // 0x120
    Symbol unk12c;
    Symbol mTextToken; // 0x130
    class String mIcon; // 0x134
    float mTextSize; // 0x140
    float mLeading; // 0x144
    float mKerning; // 0x148
    float mItalics; // 0x14c
    float mWidth; // 0x150
    float mHeight; // 0x154
    short mFixedLength; // 0x158
    short mReservedLine; // 0x15a
    class String mPreserveTruncText; // 0x15c
    float mAlpha; // 0x168
    ObjPtr<UIColor, class ObjectDir> mColorOverride; // 0x16c
    Symbol mFontMatVariation; // 0x178
    Symbol mAltMatVariation; // 0x17c
    float mAltTextSize; // 0x180
    float mAltKerning; // 0x184
    ObjPtr<UIColor, class ObjectDir> mAltTextColor; // 0x188
    float mAltZOffset; // 0x194
    float mAltItalics; // 0x198
    float mAltAlpha; // 0x19c
    unsigned char mFitType; // 0x1a0 - UILabel::FitType
    unsigned char mAlignment; // 0x1a1 - RndText::Alignment
    unsigned char mCapsMode; // 0x1a2 - RndText::CapsMode
    bool mMarkup : 1; // 0x1a3 >> 7
    bool mUseHighlightMesh : 1; // 0x1a3 >> 6 & 1
    bool mAltStyleEnabled : 1; // 0x1a3 >> 5 & 1
    class String mAltFontResourceName; // 0x1a4
    ObjDirPtr<class ObjectDir> mObjDirPtr; // 0x1b0, unknown var name
};

#endif // UI_UILABEL_H
