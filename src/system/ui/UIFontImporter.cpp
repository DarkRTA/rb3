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

// fn_8055B51C
void UIFontImporter::FontImporterSyncObjects(){
    if(!unkb4 && mMatVariations.size() > 0 && mGennedFonts.size() > 0){
        for(ObjPtrList<RndMat, ObjectDir>::iterator it = mMatVariations.begin(); it != mMatVariations.end(); it){
            RndMat* old = *it;
            it = mMatVariations.erase(it);
            delete old;
        }
        int idx = 0;
        for(ObjPtrList<RndFont, ObjectDir>::iterator it = mGennedFonts.begin(); it != mGennedFonts.end(); ++it){
            RndFont* font = *it;
            RndMat* mat = (*it)->mMat;
            if(idx == 0){
                String name = GetBaseName();
                String matname = name + ".mat";
                mat->SetName(matname.c_str(), Dir());
                unkb4 = mat;
                String fontname = name + ".font";
                font->SetName(fontname.c_str(), Dir());
                RndText* text = FindTextForFont(font);
                if(text){
                    String textname = name + ".txt";
                    text->SetName(textname.c_str(), Dir());
                    String textstr(text->unk_cc.c_str());
                    if(textstr.find("_default") != String::npos){
                        textstr = textstr.substr(0, textstr.find("_default"));
                        text->SetText(textstr.c_str());
                    }
                }
            }
            else {
                String name = GetBaseName();
                String matname = mat->Name();
                if(matname.find(name.c_str()) == 0){
                    matname = matname.substr(name.length() + 1, matname.length() - name.length() - 1);
                }
                mat->SetName(matname.c_str(), Dir());
                mMatVariations.push_back(mat);
            }
            idx++;
        }
        FormatString fstr(MakeString("Upgraded font resource to new material variation setup.  Please resave %s", Dir()->mPathName));
        TheDebugNotifier << fstr.Str();
    }
}

// fn_8055B9E4 - get genned font

DataNode UIFontImporter::OnSyncWithResourceFile(DataArray* da){
    if(!mResourceName.empty()){
        const char* milopath = MakeString("%s/%s.milo", GetResourcesPath(), mResourceName);
        ObjDirPtr<UILabelDir> labelDir(0);
        labelDir.LoadFile(FilePath(FileRoot(), milopath), false, true, kLoadFront, false);
        labelDir.PostLoad(0);
        if(labelDir.IsLoaded()){
            mLowerCaseAthroughZ = labelDir->mLowerCaseAthroughZ;
            mUpperCaseAthroughZ = labelDir->mUpperCaseAthroughZ;
            mNumbers0through9 = labelDir->mNumbers0through9;
            mPunctuation = labelDir->mPunctuation;
            mUpperEuro = labelDir->mUpperEuro;
            mLowerEuro = labelDir->mLowerEuro;
            mPlus = labelDir->mPlus;
            mMinus = labelDir->mMinus;
            mFontName = labelDir->mFontName;
            mFontPctSize = labelDir->mFontPctSize;
            unk40 = labelDir->unk40;
            mFontQuality = labelDir->mFontQuality;
            mPitchAndFamily = labelDir->mPitchAndFamily;
            mFontQuality = labelDir->mFontQuality;
            mFontCharset = labelDir->mFontCharset;
            mBitmapSavePath = labelDir->mBitmapSavePath;
            mBitMapSaveName = labelDir->mBitMapSaveName;
            mFontSupersample = labelDir->mFontSupersample;
            mItalics = labelDir->mItalics;
            mLeft = labelDir->mLeft;
            mRight = labelDir->mRight;
            mTop = labelDir->mTop;
            mBottom = labelDir->mBottom;
            mFillWithSafeWhite = labelDir->mFillWithSafeWhite;
            if(mReferenceKerning && labelDir->mReferenceKerning){
                std::vector<RndFont::KernInfo> kerninfo;
                labelDir->mReferenceKerning->GetKerning(kerninfo);
                mReferenceKerning->SetKerning(kerninfo);
                mReferenceKerning->SetBaseKerning(labelDir->mReferenceKerning->mBaseKerning);
            }
        }
    }
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