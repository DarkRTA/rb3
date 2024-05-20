#ifndef UI_UIFONTIMPORTER_H
#define UI_UIFONTIMPORTER_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Font.h"
#include "rndobj/Mat.h"

class UIFontImporter : public virtual Hmx::Object {
public:
    UIFontImporter();
    OBJ_CLASSNAME(UIFontImporter);
    OBJ_SET_TYPE(UIFontImporter);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~UIFontImporter();

    void GenerateBitmapFilename();

    DELETE_OVERLOAD;
    
    bool mUpperCaseAthroughZ;
    bool mLowerCaseAthroughZ;
    bool mNumbers0through9;
    bool mPunctuation;
    bool mUpperEuro;
    bool mLowerEuro;
    String mPlus;
    String mMinus;
    String mFontName;
    float mFontPctSize;
    bool mItalics;
    int mFontQuality;
    int unk40;
    int mPitchAndFamily;
    int mFontCharset;
    int mFontSupersample;
    int mLeft;
    int mRight;
    int mTop;
    int mBottom;
    bool mFillWithSafeWhite;
    ObjPtr<RndFont, ObjectDir> mFontToImportFrom;
    String mBitmapSavePath;
    String mBitMapSaveName;
    ObjPtrList<RndFont, ObjectDir> mGennedFonts;
    ObjPtr<RndFont, ObjectDir> mReferenceKerning;
    ObjPtrList<RndMat, ObjectDir> mMatVariations;
    ObjPtr<RndMat, ObjectDir> unkb4;
    ObjPtr<RndFont, ObjectDir> mHandmadeFont;
    bool unkcc;
    String mResourceName;
    bool mLastGennedNG;
};

#endif
