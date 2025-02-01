#pragma once
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Font.h"
#include "rndobj/Mat.h"

class RndText;

/** "Class supporting font importing.  To be included in font resource file classes." */
class UIFontImporter : public virtual Hmx::Object {
public:
    enum FontQuality {
        kFontQuality_AntiAliased,
        kFontQuality_ClearType,
        kFontQuality_Default
    };

    enum FontSuperSample {
        kFontSuperSample_None,
        kFontSuperSample_2x,
        kFontSuperSample_4x
    };

    UIFontImporter();
    OBJ_CLASSNAME(UIFontImporter);
    OBJ_SET_TYPE(UIFontImporter);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~UIFontImporter();

    void GenerateBitmapFilename();
    RndText *GetGennedText(Symbol) const;
    void FontImporterSyncObjects();
    void SyncWithGennedFonts();
    void HandmadeFontChanged();
    Symbol GetMatVariationName(unsigned int) const;
    const char *GetResourcesPath();
    String GetBaseName() const;
    RndFont *GetGennedFont(unsigned int) const;
    RndText *FindTextForFont(RndFont *) const;
    RndFont *FindFontForMat(RndMat *) const;
    void AttachImporterToFont(RndFont *);
    void ImportSettingsFromFont(RndFont *);
    RndFont *GetGennedFont(Symbol) const;
    int GetMatVariationIdx(Symbol) const;
    RndMat *GetMatVariation(unsigned int) const;
    int NumMatVariations() const { return mMatVariations.size(); }
    int NumGennedFonts() const { return mGennedFonts.size(); }
    bool HandMadeFontExists() const { return mHandmadeFont; }

    DataNode OnShowFontPicker(DataArray *);
    DataNode OnGenerate(DataArray *);
    DataNode OnGenerateOG(DataArray *);
    DataNode OnForgetGened(DataArray *);
    DataNode OnAttachToImportFont(DataArray *);
    DataNode OnImportSettings(DataArray *);
    DataNode OnSyncWithResourceFile(DataArray *);
    DataNode OnGetResourcesPath(DataArray *);
    DataNode OnGetGennedBitmapPath(DataArray *);

    NEW_OVERLOAD;
    DELETE_OVERLOAD
    NEW_OBJ(UIFontImporter);
    static void Init() { REGISTER_OBJ_FACTORY(UIFontImporter); }

    /** "include uppercase letters" */
    bool mUpperCaseAthroughZ; // 0x8
    /** "include lowercase letters" */
    bool mLowerCaseAthroughZ; // 0x9
    /** "include the number 0-9" */
    bool mNumbers0through9; // 0xa
    /** "include punctuation characters" */
    bool mPunctuation; // 0xb
    /** "include uppercase euro chars" */
    bool mUpperEuro; // 0xc
    /** "include lowercase euro chars" */
    bool mLowerEuro; // 0xd
    /** "type in extra characters to include here" */
    String mPlus; // 0x10
    /** "type in characters to exclude here" */
    String mMinus; // 0x1c
    /** "name of the font" */
    String mFontName; // 0x28
    /** "default font size in percent screen height" */
    float mFontPctSize; // 0x34
    /** "italic variation?" */
    bool mItalics; // 0x38
    FontQuality mFontQuality; // 0x3c
    int mFontWeight; // 0x40
    /** "pitch and family of font - comes from font picker" */
    int mPitchAndFamily; // 0x44
    /** "character set for this font - comes from font picker" */
    int mFontCharset; // 0x48
    /** "our own supersampling that draws the font texture at 2 or 4x and scales down like
     * in photoshop.  Might improve anti-aliasing at small font sizes." */
    FontSuperSample mFontSupersample; // 0x4c
    /** "pixels of padding on the left side of each character" */
    int mLeft; // 0x50
    /** "pixels of padding on the left side of each character" */
    int mRight; // 0x54
    /** "pixels of padding on the left side of each character" */
    int mTop; // 0x58
    /** "pixels of padding on the left side of each character" */
    int mBottom; // 0x5c
    /** "fill texture with safe white color (235)" */
    bool mFillWithSafeWhite; // 0x60
    ObjPtr<RndFont> mFontToImportFrom; // 0x64
    /** "path to save bitmap to (i.e. ui/image/)" */
    String mBitmapSavePath; // 0x70
    /** "name of the bitmap file (i.e. Arial(12).BMP)" */
    String mBitMapSaveName; // 0x7c
    /** "the font(s) we've gen-ed for this resource file.  We will maintain a connection
     * to these objects when you re-generate" */
    ObjPtrList<RndFont> mGennedFonts; // 0x88
    /** "A font which we'll transfer the kerning info from for any gen-ed fonts" */
    ObjPtr<RndFont> mReferenceKerning; // 0x98
    /** "A list of materials we will expose for this font" */
    ObjPtrList<RndMat> mMatVariations; // 0xa4
    ObjPtr<RndMat> mDefaultMat; // 0xb4
    /** "If you want to handmake a font texture, assign it here and the importer will no
     * longer try to generate textures" */
    ObjPtr<RndFont> mHandmadeFont; // 0xc0
    bool mCheckNG; // 0xcc
    /** "You can pull in all the importer settings from another resource file by selecting
     * it above and hitting the sync button below" */
    String mSyncResource; // 0xd0
    /** "was the texture for this font last genned for an NG platform?" */
    bool mLastGenWasNG; // 0xdc

    // font point size: "the equivalent point size"
    // font pixel size: "the equivalent pixel size"
    // bold: "bold variation?"
};
