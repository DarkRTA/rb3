#include "ui/UIFontImporter.h"
#include "ui/UILabel.h"
#include "ui/UILabelDir.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"
#include "utl/ClassSymbols.h"

int gREV = 9;

// idk what to name this, it's mainly used when assigning to mFontPctSize
inline float fabs720(int i){
    return fabs_f(i / 720.0f);
}

UIFontImporter::UIFontImporter() : mUpperCaseAthroughZ(1), mLowerCaseAthroughZ(1), mNumbers0through9(1), mPunctuation(1), mUpperEuro(1), mLowerEuro(1),
    mPlus(""), mMinus(""), mFontName("Arial"), mFontPctSize(fabs720(-0xc)), mItalics(0), mFontQuality(0), unk40(400), mPitchAndFamily(0x22), mFontCharset(0), mFontSupersample(0),
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
        mFontPctSize = fabs720(-i);
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
        ObjPtr<RndMat, class ObjectDir> o(this, 0);
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
        for(ObjPtrList<RndMat, class ObjectDir>::iterator it = mMatVariations.begin(); it != mMatVariations.end(); it){
            RndMat* old = *it;
            it = mMatVariations.erase(it);
            delete old;
        }
        int idx = 0;
        for(ObjPtrList<RndFont, class ObjectDir>::iterator it = mGennedFonts.begin(); it != mGennedFonts.end(); ++it){
            RndFont* font = *it;
            RndMat* mat = (*it)->mMat;
            if(idx == 0){
                class String name = GetBaseName();
                class String matname = name + ".mat";
                mat->SetName(matname.c_str(), Dir());
                unkb4 = mat;
                class String fontname = name + ".font";
                font->SetName(fontname.c_str(), Dir());
                RndText* text = FindTextForFont(font);
                if(text){
                    class String textname = name + ".txt";
                    text->SetName(textname.c_str(), Dir());
                    class String textstr(text->unk_cc.c_str());
                    if(textstr.find("_default") != String::npos){
                        textstr = textstr.substr(0, textstr.find("_default"));
                        text->SetText(textstr.c_str());
                    }
                }
            }
            else {
                class String name = GetBaseName();
                class String matname = mat->Name();
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
RndFont* UIFontImporter::GetGennedFont(unsigned int ui) const {
    if(ui >= mGennedFonts.size()) return 0;
    ObjPtrList<RndFont, class ObjectDir>::iterator it = mGennedFonts.begin();
    while(ui-- > 0) it++;
    return *it;
}

RndText* UIFontImporter::FindTextForFont(RndFont* font) const {
    if(font){
        std::vector<ObjRef*>::const_reverse_iterator it = font->Refs().rbegin();
        std::vector<ObjRef*>::const_reverse_iterator itEnd = font->Refs().rend();
        for(; it != itEnd; ++it){
            Hmx::Object* owner = (*it)->RefOwner();
            if(owner){
                if(owner->ClassName() == Text){
                    return dynamic_cast<RndText*>(owner);
                }
            }
        }
    }
    return 0;
}

RndFont* UIFontImporter::FindFontForMat(RndMat* mat) const {
    if(mat){
        std::vector<ObjRef*>::const_reverse_iterator it = mat->Refs().rbegin();
        std::vector<ObjRef*>::const_reverse_iterator itEnd = mat->Refs().rend();
        for(; it != itEnd; ++it){
            Hmx::Object* owner = (*it)->RefOwner();
            if(owner){
                if(owner->ClassName() == Font){
                    return dynamic_cast<RndFont*>(owner);
                }
            }
        }
    }
    return 0;
}

DataNode UIFontImporter::OnAttachToImportFont(DataArray* da){
    AttachImporterToFont(mFontToImportFrom);
    return DataNode(0);
}

DataNode UIFontImporter::OnImportSettings(DataArray* da){
    ImportSettingsFromFont(mFontToImportFrom);
    return DataNode(0);
}

const char* UIFontImporter::GetResourcesPath(){
    DataArray* arr = SystemConfig(objects, UILabel::StaticClassName())->FindArray(resources_path, false);
    if(!arr) return 0;
    else {
        const char* str = arr->Str(1);
        if(*str == '\0') return 0;
        else {
            return FileMakePath(MakeString("%s/%s", FileRoot(), "ui/"), str, 0);
        }
    }
}

DataNode UIFontImporter::OnGetResourcesPath(DataArray* da){
    const char* path = GetResourcesPath();
    if(path) return DataNode(FileRelativePath(FileRoot(), path));
    else return DataNode("");
}

DataNode UIFontImporter::OnGetGennedBitmapPath(DataArray* da){
    RndFont* font = GetGennedFont(0);
    RndTex* tex = 0;
    if(font){
        RndMat* mat = font->mMat;
        if(mat){
            RndTex* thetex = mat->mDiffuseTex;
            if(thetex) tex = thetex;
        }
    }
    if(tex) return DataNode(tex->mFilepath.c_str());
    else return DataNode("");
}

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

void UIFontImporter::GenerateBitmapFilename(){
    const char* mult = "";
    if(mFontSupersample == 1) mult = "2x";
    else if(mFontSupersample == 2) mult = "4x";
    const char* b = "";
    class String s28(MakeString("%.2f", mFontPctSize * 100.0f));
    s28.ReplaceAll('.', '_');
    if(unk40 > 400) b = "B";
    const char* i = mItalics ? "I" : "";
    mBitMapSaveName = MakeString("%s(%s)%s%s%s.BMP", mFontName.c_str(), s28.c_str(), i, b, mult);
    mBitMapSaveName.ReplaceAll(' ', '_');
}

DataNode UIFontImporter::OnShowFontPicker(DataArray*){ return DataNode(0); }
DataNode UIFontImporter::OnGenerate(DataArray*){ return DataNode(0); }
DataNode UIFontImporter::OnGenerateOG(DataArray*){ return DataNode(0); }

DataNode UIFontImporter::OnForgetGened(DataArray* da){
    mGennedFonts.clear();
    return DataNode(0);
}

void UIFontImporter::ImportSettingsFromFont(RndFont* font){
    bool has_import_font = false;
    if(font){
        Symbol imported_font("imported_font");
        if(font->Type() == imported_font) has_import_font = true;
    }
    if(has_import_font){
        SetProperty("font_name", DataNode(font->Property("font_name", true)->Str(0)));
        SetProperty("font_size", DataNode(fabs720(-font->Property("font_size", true)->Int(0)))); 
        SetProperty("bold", DataNode(font->Property("bold", true)->Int(0)));
        SetProperty("italics", DataNode(font->Property("italics", true)->Int(0)));
        SetProperty("left", DataNode(font->Property("left", true)->Int(0)));
        SetProperty("right", DataNode(font->Property("right", true)->Int(0)));
        SetProperty("top", DataNode(font->Property("top", true)->Int(0)));
        SetProperty("bottom", DataNode(font->Property("bottom", true)->Int(0)));
    }
    else MILO_WARN("Can't import settings from Font because it doesnt have import_font type");
}

void UIFontImporter::AttachImporterToFont(RndFont* font){
    if(font){
        if(font->Dir() != Dir()) MILO_WARN("Cannot attach font %s to font resource %s because its in a different dir.  Notify a programmer!");
        else {
            mGennedFonts.clear();
            mMatVariations.clear();
            unkb4 = font->mMat;
            mGennedFonts.push_back(font);
            mReferenceKerning = font;
            ImportSettingsFromFont(font);
        }
    }
}

RndFont* UIFontImporter::GetGennedFont(Symbol s) const {
    if(s.Null()) return *mGennedFonts.begin();
    else {
        int idx = GetMatVariationIdx(s);
        if(idx == -1) return 0;
        else return FindFontForMat(GetMatVariation(idx));
    }
}

RndText* UIFontImporter::GetGennedText(Symbol s) const {
    return FindTextForFont(GetGennedFont(s));
}

RndMat* UIFontImporter::GetMatVariation(unsigned int ui) const {
    if(ui >= mMatVariations.size()) return 0;
    ObjPtrList<RndMat, class ObjectDir>::iterator it = mMatVariations.begin();
    while(ui-- > 0) it++;
    return *it;
}

Symbol UIFontImporter::GetMatVariationName(unsigned int ui) const {
    if(ui >= mMatVariations.size()) return Symbol();
    ObjPtrList<RndMat, class ObjectDir>::iterator it = mMatVariations.begin();
    while(ui-- > 0) it++;
    class String s18((*it)->Name());
    if(s18.rfind(".") != String::npos){
        s18 = s18.substr(0, s18.rfind("."));
    }
    return Symbol(s18.c_str());
}

int UIFontImporter::GetMatVariationIdx(Symbol s) const {
    int size = mMatVariations.size();
    for(int ret = 0; ret < size; ret++){
        if(GetMatVariationName(ret) == s) return ret;
    }
    return -1;
}

// fn_8055D7F8
void UIFontImporter::HandmadeFontChanged(){
    if(mHandmadeFont){
        if(mGennedFonts.size() > 0){
            RndFont* frontfont = *mGennedFonts.begin();
            if(frontfont != mHandmadeFont){
                RndText* text = FindTextForFont(frontfont);
                delete frontfont;
                if(text) delete text;
            }
            mGennedFonts.Set(mGennedFonts.begin(), mHandmadeFont);
            ObjPtrList<RndFont, class ObjectDir>::iterator it = mGennedFonts.begin();
            it++;
            for(; it != mGennedFonts.end(); it){
                if(mHandmadeFont == *it){
                    mGennedFonts.erase(it);
                    break;
                }
                else it++;
            }
        }
        else mGennedFonts.push_back(mHandmadeFont);
        mReferenceKerning = mHandmadeFont;
        mLowerEuro = false;
        mUpperEuro = false;
        mPunctuation = false;
        mNumbers0through9 = false;
        mLowerCaseAthroughZ = false;
        mUpperCaseAthroughZ = false;
        mMinus = "";
        std::vector<unsigned short> thechars(mHandmadeFont->mChars);
        mPlus = WideVectorToASCII(thechars);
    }
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