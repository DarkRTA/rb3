#include "char/CharCollide.h"

CharCollide::CharCollide() : mShape(kSphere), mFlags(0), mMesh(this, 0), unk188(0) {
    for(int i = 0; i < 2; i++){
        mLength[i] = 0;
        mRadius[i] = 0;
    }
    CopyOriginalToCur();
    for(int i = 0; i < 8; i++){
        unk_structs[i].unk0 = 0;
        unk_structs[i].vec.Zero();
    }
    unk148.Reset();
}

CharCollide::~CharCollide(){
    
}

SAVE_OBJ(CharCollide, 0x58)