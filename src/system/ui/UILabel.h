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

    NEW_OVERLOAD
    DELETE_OVERLOAD

    const char* GetDefaultText() const;
    void Terminate();
    void LabelUpdate(bool, bool);
    void AdjustHeight(bool);
    void SetFloat(const char*, float);
    void SetTextToken(Symbol);
    void CenterWithLabel(UILabel*, bool, float);
    RndText* TextObj();

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

    NEW_OBJ(UILabel)
    static void Init();
    static bool sDeferUpdate;
};

#endif // UI_UILABEL_H
