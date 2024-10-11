#include "bandobj/BandLabel.h"
#include "ui/UI.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

INIT_REVS(BandLabel);

void BandLabel::Init(){
    TheUI->InitResources("BandLabel");
    Register();
}

BandLabel::BandLabel() : UITransitionHandler(this), unk1e8(""), unk1f4(0) {

}

BandLabel::~BandLabel(){

}

BEGIN_COPYS(BandLabel)
    COPY_SUPERCLASS(UILabel)
    CREATE_COPY(BandLabel)
    CopyHandlerData(c);
END_COPYS

void BandLabel::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty){
    UILabel::CopyMembers(o, ty);
    CREATE_COPY_AS(BandLabel, label);
    MILO_ASSERT(label, 0x36);
    COPY_MEMBER_FROM(label, mInAnim);
    COPY_MEMBER_FROM(label, mOutAnim);
}

SAVE_OBJ(BandLabel, 0x44);

BEGIN_LOADS(BandLabel)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandLabel::PreLoad(BinStream& bs){
    Hmx::Color col;
    LOAD_REVS(bs);
    ASSERT_REVS(0x11, 0);
    bool b87 = false;
    if(gRev < 0xB){
        if(gRev <= 6){
            LOAD_SUPERCLASS(RndTransformable)
            LOAD_SUPERCLASS(RndDrawable)
        }
        else UILabel::PreLoad(bs);

        if(gRev > 5){
            if(gRev < 10){
                bool b88;
                bs >> b88;
                bs >> mWidth;
                bs >> mHeight;
                if(b88) mFitType = 1;
                else mFitType = 0;
            }
            else {
                int i50;
                bs >> i50;
                bs >> mWidth;
                bs >> mHeight;
                mFitType = i50;
            }
        }
        else mFitType = 0;

        if(gRev < 8 && mFitType == 1){
            Hmx::Matrix3 m;
            m.Identity();
            SetLocalRot(m);
        }
        if(gRev > 4) bs >> mLeading;
        if(gRev > 3) bs >> (int&)mAlignment;
        if(gRev < 2){
            int i,j,k,l;
            bs >> i >> j >> k >> l;
        }
        if(gRev <= 6){
            Symbol s; bs >> s;
            SetType(s);
        }
        if(gRev != 0) bs >> b87;
        else b87 = false;
        if(gRev <= 6) bs >> mTextToken;
        if(gRev < 10){ int i; bs >> i; }
        if(gRev > 8) bs >> col;
        if(gRev > 9){
            bs >> mKerning;
            bs >> mTextSize;
        }
    }
    else {
        UILabel::PreLoad(bs);
        if(gRev < 0xE){
            int i6c; bs >> i6c;
            mFitType = i6c;
            bs >> mWidth;
            bs >> mHeight;
            if(mFitType == 0){
                mHeight = 0;
                mWidth = 0;
            }
        }
        if(gRev < 0xD){
            bs >> mLeading;
            bs >> (int&)mAlignment;
        }
        if(gRev < 0xF){
            int i, j, k, l;
            bs >> i >> j >> k >> l;
        }
        if(gRev < 0xD){
            bs >> b87;
            bs >> mKerning;
            bs >> mTextSize;
        }
        if(gRev < 0xE){ int i; bs >> i; }
        if(gRev < 0xF) bs >> col;
    }
    if(gRev < 0xD){
        int capsmode = 0;
        if(b87) capsmode = 2;
        mCapsMode = capsmode;
    }
    if(gRev == 0xF) LoadOldBandTextComp(bs);
    if(gRev >= 0x11) LoadHandlerData(bs);
}

void BandLabel::LoadOldBandTextComp(BinStream& bs){
    int rev;
    bs >> rev;
    Symbol s;
    if(rev > 2) MILO_WARN("Can't load new BandTextComp");
    else {
        if(rev < 1){
            int a,b,c,d;
            bs >> a >> b >> c >> d;
        }
        bs >> s;
        if(s == custom_colors){
            int dummy;
            int num = 4;
            if(rev >= 2) bs >> num;
            for(int i = 0; i < num; i++) bs >> dummy;
        }
    }
}

void BandLabel::Poll(){
    UILabel::Poll();
    if(unk1dc.size() >= 2){
        float val = 0;
        float uisecs = TheTaskMgr.UISeconds() * 1000.0f;
        unk1dc.AtFrame(uisecs, val);
        SetTokenFmt(unk1e4, LocalizeSeparatedInt(val));
        if(uisecs > unk1dc.LastFrame()){
            unk1dc.clear();
            TheUI->Handle(BandLabelCountDoneMsg(this), false);
        }
    }
    UpdateHandler();
}

void BandLabel::Count(int i1, int i2, float f, Symbol s){
    unk1dc.clear();
    Key<float> key;
    key.value = TheTaskMgr.UISeconds() * 1000.0f;
    key.frame = i1;
    unk1dc.push_back(key);
    key.value += f;
    key.frame = i2;
    unk1dc.push_back(key);
    unk1e4 = s;
}

void BandLabel::FinishCount(){
    if(unk1dc.size() >= 2){
        Key<float>& key = unk1dc[1];
        SetTokenFmt(unk1e4, LocalizeSeparatedInt(key.value));
        unk1dc.clear();
    }
}

bool BandLabel::IsEmptyValue() const { return unk114 == gNullStr; }

void BandLabel::FinishValueChange(){
    UILabel::SetDisplayText(unk1e8.c_str(), unk1f4);
    UITransitionHandler::FinishValueChange();
}

void BandLabel::SetDisplayText(const char* cc, bool b){
    unk1e8 = cc;
    unk1f4 = b;
    UITransitionHandler::StartValueChange();
}

BEGIN_HANDLERS(BandLabel)
    HANDLE_ACTION(start_count, Count(_msg->Int(2), _msg->Int(3), _msg->Float(4), _msg->Sym(5)))
    HANDLE_ACTION(finish_count, FinishCount())
    HANDLE_SUPERCLASS(UILabel)
    HANDLE_CHECK(0x162)
END_HANDLERS

BEGIN_PROPSYNCS(BandLabel)
    SYNC_PROP_SET(in_anim, GetInAnim(), SetInAnim(_val.Obj<RndAnimatable>()))
    SYNC_PROP_SET(out_anim, GetOutAnim(), SetOutAnim(_val.Obj<RndAnimatable>()))
    SYNC_SUPERCLASS(UILabel)
END_PROPSYNCS
