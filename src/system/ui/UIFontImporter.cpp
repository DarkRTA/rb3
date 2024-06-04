#include "ui/UIFontImporter.h"
#include "ui/UILabelDir.h"
#include "utl/Symbols.h"

int gREV = 9;

UIFontImporter::UIFontImporter() : mUpperCaseAthroughZ(1), mLowerCaseAthroughZ(1), mNumbers0through9(1), mPunctuation(1), mUpperEuro(1), mLowerEuro(1),
    mPlus(""), mMinus(""), mFontName("Arial"), mItalics(0), mFontPctSize(0.0f), mFontQuality(0), unk40(400), mPitchAndFamily(0x22), mFontCharset(0), mFontSupersample(0),
    mLeft(0), mRight(0), mTop(0), mBottom(0), mFillWithSafeWhite(0), mFontToImportFrom(this, 0), mBitmapSavePath("ui/image/"), mBitMapSaveName("temp.BMP"),
    mGennedFonts(this, kObjListNoNull), mReferenceKerning(this, 0), mMatVariations(this, kObjListNoNull), unkb4(this, 0), mHandmadeFont(this, 0),
    unkcc(0), mResourceName(), mLastGennedNG(1) {
    DataArray* cfg = SystemConfig(objects, StaticClassName())->FindArray(default_bitmap_path, false);
    if(cfg) mBitmapSavePath = cfg->Str(1);
    GenerateBitmapFilename();
}

UIFontImporter::~UIFontImporter(){
    
}

BEGIN_COPYS(UIFontImporter)
    CREATE_COPY(UIFontImporter)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mLowerCaseAthroughZ)
        COPY_MEMBER(mUpperCaseAthroughZ)
        COPY_MEMBER(mNumbers0through9)
        COPY_MEMBER(mPunctuation)
        COPY_MEMBER(mUpperEuro)
        COPY_MEMBER(mLowerEuro)
        COPY_MEMBER(mPlus)
        COPY_MEMBER(mMinus)
        COPY_MEMBER(mFontName)
        COPY_MEMBER(mFontPctSize)
        COPY_MEMBER(unk40)
        COPY_MEMBER(mFontQuality)
        COPY_MEMBER(mPitchAndFamily)
        COPY_MEMBER(mFontQuality)
        COPY_MEMBER(mFontCharset)
        COPY_MEMBER(mBitmapSavePath)
        COPY_MEMBER(mBitMapSaveName)
        COPY_MEMBER(mFontSupersample)
        COPY_MEMBER(mItalics)
        COPY_MEMBER(mLeft)
        COPY_MEMBER(mRight)
        COPY_MEMBER(mTop)
        COPY_MEMBER(mBottom)
        COPY_MEMBER(mFillWithSafeWhite)
        COPY_MEMBER(mGennedFonts)
        COPY_MEMBER(mReferenceKerning)
        COPY_MEMBER(mMatVariations)
        COPY_MEMBER(unkb4)
        COPY_MEMBER(mHandmadeFont)
        COPY_MEMBER(mResourceName)
        COPY_MEMBER(mLastGennedNG)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(UIFontImporter, 0x6DB)

BEGIN_LOADS(UIFontImporter)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, gREV);
    bs >> mLowerCaseAthroughZ >> mUpperCaseAthroughZ >> mNumbers0through9 >> mPunctuation >> mUpperEuro >> mLowerEuro;
    bs >> mPlus;
    bs >> mMinus;
    bs >> mFontName;
    if(rev <= 4){
        int i;
        bs >> i;
        mFontPctSize = __fabs(i / 720.0f);
    }
    else bs >> mFontPctSize;
    bs >> unk40 >> mItalics >> mPitchAndFamily >> mFontQuality >> mFontCharset;
    if(rev > 1) bs >> mFontSupersample;
    bs >> mBitmapSavePath;
    bs >> mBitMapSaveName;
    bs >> mLeft >> mRight >> mTop >> mBottom >> mFillWithSafeWhite;
    if(rev < 8) bs >> mFontToImportFrom;
    if(rev > 2){
        bs >> mGennedFonts;
        bs >> mReferenceKerning;
    }
    if(rev == 3){
        ObjPtr<RndMat, ObjectDir> o(this, 0);
        bs >> o;
    }
    if(rev > 3) bs >> mMatVariations;
    if(rev > 5) bs >> unkb4;
    if(rev > 6) bs >> mHandmadeFont;
    if(rev > 7) bs >> mResourceName;
    if(rev > 8) bs >> mLastGennedNG;
END_LOADS

DataNode UIFontImporter::OnSyncWithResourceFile(DataArray* da){
    // ObjDirPtr<UILabelDir> oPtr;
    return DataNode(0);
}

BEGIN_HANDLERS(UIFontImporter)
    HANDLE(show_font_picker, OnShowFontPicker)
    HANDLE(generate, OnGenerate)
    HANDLE(generate_og, OnGenerateOG)
    HANDLE(forget_gened_fonts, OnForgetGened)
    HANDLE(attach_to_importfont, OnAttachToImportFont)
    HANDLE(import_from_importfont, OnImportSettings)
    HANDLE(sync_with_resource, OnSyncWithResourceFile)
    HANDLE(get_resources_path, OnGetResourcesPath)
    HANDLE(get_bitmap_path, OnGetGennedBitmapPath)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xA2C)
END_HANDLERS

BEGIN_PROPSYNCS(UIFontImporter)
    SYNC_PROP(UPPER_CASE_A_Z, mUpperCaseAthroughZ)
    SYNC_PROP(lower_case_a_z, mLowerCaseAthroughZ)
    SYNC_PROP(numbers_0_9, mNumbers0through9)
    SYNC_PROP(punctuation, mPunctuation)
    SYNC_PROP(UPPER_EURO, mUpperEuro)
    SYNC_PROP(lower_euro, mLowerEuro)
    SYNC_PROP(plus, mPlus)
    SYNC_PROP(minus, mMinus)
    SYNC_PROP(font_name, mFontName)
    SYNC_PROP_MODIFY(font_pct_size, mFontPctSize, GenerateBitmapFilename())
    // font_point_size
    // font_pixel_size
    // bold
    SYNC_PROP_MODIFY(italics, mItalics, GenerateBitmapFilename())
    SYNC_PROP(font_quality, mFontQuality)
    SYNC_PROP(pitch_and_family, mPitchAndFamily)
    SYNC_PROP(font_charset, mFontCharset)
    SYNC_PROP_MODIFY(font_supersample, mFontSupersample, GenerateBitmapFilename())
    SYNC_PROP(left, mLeft)
    SYNC_PROP(right, mRight)
    SYNC_PROP(top, mTop)
    SYNC_PROP(bottom, mBottom)
    SYNC_PROP(fill_with_safe_white, mFillWithSafeWhite)
    SYNC_PROP(font_to_import_from, mFontToImportFrom)
    SYNC_PROP(bitmap_save_path, mBitmapSavePath)
    SYNC_PROP(bitmap_save_name, mBitMapSaveName)
    SYNC_PROP(gened_fonts, mGennedFonts)
    SYNC_PROP(reference_kerning, mReferenceKerning)
    SYNC_PROP_MODIFY_ALT(mat_variations, mMatVariations, SyncWithGennedFonts())
    SYNC_PROP_MODIFY_ALT(handmade_font, mHandmadeFont, HandmadeFontChanged())
    SYNC_PROP(resource_name, mResourceName)
    SYNC_PROP(last_genned_ng, mLastGennedNG)
END_PROPSYNCS