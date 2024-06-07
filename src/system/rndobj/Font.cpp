#include "rndobj/Font.h"
#include "rndobj/Mat.h"

RndFont::RndFont() : mMat(this, 0), mTextureOwner(this, this), unk4c(0), mBaseKerning(0.0f), mCellSize(1.0f, 1.0f), mDeprecatedSize(0.0f), mMonospace(0), unk6c(0.0f, 0.0f), mPacked(0), unk78(this, 0) {

}

void RndFont::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mTextureOwner == from){
        if(!to) mTextureOwner = this;
        else {
            mTextureOwner = dynamic_cast<RndFont*>(to)->mTextureOwner;
        }
    }
}

RndFont::~RndFont(){
    
}