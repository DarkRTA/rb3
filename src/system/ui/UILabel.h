#pragma once
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

 /**
 * @brief A label.
 * Original _objects description:
 * "Simple label, provides localization of tokens"
 */
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
    static void Terminate();
    static bool sDebugHighlight;
    static bool sDeferUpdate;

    const char* GetDefaultText() const;
    int InqMinMaxFromWidthAndHeight(float, float, RndText::Alignment, Vector3&, Vector3&);
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
    void FitText();
    void UpdateAndDrawHighlightMesh();
    bool CheckValid(bool);

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
    ObjPtr<RndFont> mFont; // 0x120
    Symbol unk12c;
    /** "Localization token if localize is true" */
    Symbol mTextToken; // 0x130
    /** "Single-character icon" */
    String mIcon; // 0x134
    /** "Text size in percentage of screen height (i.e. 50% is half the screen height for the largest glyph)". Range is 1E-3 to 5 */
    float mTextSize; // 0x140
    /** "Space between lines" */
    float mLeading; // 0x144
    /** "Additional kerning applied to text object" */
    float mKerning; // 0x148
    /** "Italics for text object". Ranges from 0 to 100 */
    float mItalics; // 0x14c
    /** "Width of label". Ranges from 0 to 1000 */
    float mWidth; // 0x150
    /** "Height of label". Ranges from 0 to 1000 */
    float mHeight; // 0x154
    /** "Preallocated size of internal text object". Ranges from 0 to 1000 */
    short mFixedLength; // 0x158
    /** "Preallocated number of lines in internal text object". Ranges from 0 to 100 */
    short mReservedLine; // 0x15a
    /** "Optional text to append after truncation with kFitEllipsis" */
    class String mPreserveTruncText; // 0x15c
    /** "Controls transparency of label". Ranges from 0 to 1 */
    float mAlpha; // 0x168
    /** "Color override for this instance" */
    ObjPtr<UIColor> mColorOverride; // 0x16c
    /** "the material variation to use, populated from those setup in the resource file.  selecting none gives you the default material." */
    Symbol mFontMatVariation; // 0x178
    /** "the material variation to use from the alternate font. selecting none gives you the default material." */
    Symbol mAltMatVariation; // 0x17c
    /** "Text size of alternate style in percentage of screen height (i.e. 50% is half the screen height for the largest glyph)" */
    float mAltTextSize; // 0x180
    /** "Additional kerning applied to alt text object" */
    float mAltKerning; // 0x184
    /** "Color to use when in alt style" */
    ObjPtr<UIColor> mAltTextColor; // 0x188
    /** "Z-offset for alt text (to manually match up baselines)" */
    float mAltZOffset; // 0x194
    /** "Italics for text object's alt font". Ranges from 0 to 100 */
    float mAltItalics; // 0x198
    /** "Controls transparency of label's alt font". Ranges from 0 to 1 */
    float mAltAlpha; // 0x19c
    /** "How to fit text in the width/height specified" */
    unsigned char mFitType; // 0x1a0 - UILabel::FitType
    /** "Text alignment" */
    unsigned char mAlignment; // 0x1a1 - RndText::Alignment
    /** "Text case setting" */
    unsigned char mCapsMode; // 0x1a2 - RndText::CapsMode
    /** "Support markup?" */
    bool mMarkup : 1; // 0x1a3 >> 7
    /** "whether or not to use highlight mesh (if available)" */
    bool mUseHighlightMesh : 1; // 0x1a3 >> 6 & 1
    /** "Whether to parse <alt> tags for alt style" */
    bool mAltStyleEnabled : 1; // 0x1a3 >> 5 & 1
    /** "path to alt font resource file for this component" */
    class String mAltFontResourceName; // 0x1a4
    ObjDirPtr<ObjectDir> mObjDirPtr; // 0x1b0, unknown var name

    // edit text: "Milo-only preview text"
};
