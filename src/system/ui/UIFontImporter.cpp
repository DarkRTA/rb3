#include "ui/UIFontImporter.h"
#include "utl/Symbols.h"

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