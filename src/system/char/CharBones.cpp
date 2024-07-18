#include "char/CharBones.h"

void TestDstComplain(Symbol s){
    MILO_NOTIFY_ONCE("src %s not in dst, punting animation", s);
}

CharBones* gPropBones;

CharBones::CharBones() : mCompression(kCompressNone), mStart(0), mTotalSize(0) {
    for(int i = 0; i < NUM_TYPES; i++){
        mCounts[i] = 0;
        mOffsets[i] = 0;
    }
}

CharBones::Type CharBones::TypeOf(Symbol s){
    for(const char* p = s.Str(); p != 0; p++){
        if(*p == '.'){
            switch(p[1]){
                case 'p': return TYPE_POS;
                case 's': return TYPE_SCALE;
                case 'q': return TYPE_QUAT;
                case 'r':
                    unsigned char next = p[3];
                    if(next + 0x88U <= 2)
                        return (Type)(next - 0x75);
                default: break;
            }
        }
    }
    MILO_FAIL("Unknown bone suffix in %s", s);
    return NUM_TYPES;
}

const char* CharBones::SuffixOf(CharBones::Type t){
    static const char* suffixes[NUM_TYPES] = {
        "pos", "scale", "quat", "rotx", "roty", "rotz"
    };
    MILO_ASSERT(t < TYPE_END, 0x66);
    return suffixes[t];
}

DECOMP_FORCEACTIVE(CharBones, " (added:", " ", ", ", ")", " (removed:", " (weights:", ":", "->")

Symbol CharBones::ChannelName(const char* cc, CharBones::Type t){
    MILO_ASSERT(t < TYPE_END, 0x6F);
    char buf[256];
    strcpy(buf, cc);
    char* chr = strchr(buf, '.');
    if(!chr){
        chr = buf + strlen(buf);
        *chr = '.';
    }
    strcpy(chr + 1, SuffixOf(t));
    return Symbol(buf);
}

void CharBones::ClearBones(){
    mBones.clear();
    for(int i = 0; i < NUM_TYPES; i++){
        mCounts[i] = 0;
        mOffsets[i] = 0;
    }
    mTotalSize = 0;
    mCompression = kCompressNone;
    ReallocateInternal();
}

void CharBones::ReallocateInternal(){}

void CharBones::SetWeights(float f){
    SetWeights(f, mBones);
}

void CharBones::AddBones(const std::vector<Bone>& vec){
    for(std::vector<Bone>::const_iterator it = vec.begin(); it != vec.end(); ++it){
        AddBoneInternal(*it);
    }
    ReallocateInternal();
}

void CharBones::AddBones(const std::list<Bone>& bones){
    for(std::list<Bone>::const_iterator it = bones.begin(); it != bones.end(); ++it){
        AddBoneInternal(*it);
    }
    ReallocateInternal();
}

void CharBones::ListBones(std::list<Bone>& bones) const {
    for(int i = 0; i < mBones.size(); i++){
        bones.push_back(mBones[i]);
    }
}

void CharBones::Zero(){
    memset(mStart, 0, mTotalSize);
}

    // enum CompressionType {
    //     kCompressNone,
    //     kCompressRots,
    //     kCompressVects,
    //     kCompressQuats,
    //     kCompressAll
    // };

int CharBones::TypeSize(int i) const {
    if(i < 2){
        if(mCompression < kCompressVects) return 0xC;
        else return 6;
    }
    if(i != 2){
        if(mCompression == kCompressNone) return 4;
        else return 2;
    }
    if(mCompression > kCompressVects) return 4;
    if(mCompression == kCompressNone) return 0x10;
    return 8;
}

int CharBones::FindOffset(Symbol s) const {
    Type ty = TypeOf(s);
    int nextcount = mCounts[ty + 1];
    int size = TypeSize(ty);
    int count = mCounts[ty];
    int offset = mOffsets[ty];
    for(int i = 0; i < nextcount - count; i++){
        if(mBones[count << 3].name == s) return offset;
        else offset += size;
    }
    return -1;
}

void CharBones::SetWeights(float wt, std::vector<Bone>& bones){
    for(int i = 0; i < bones.size(); i++){
        bones[i].weight = wt;
    }
}

void* CharBones::FindPtr(Symbol s) const {
    int offset = FindOffset(s);
    if(offset == -1) return 0;
    else return (void*)&mStart[offset];
}

void CharBones::SetCompression(CompressionType ty){
    if(ty != mCompression){
        mCompression = ty;
        RecomputeSizes();
    }
}

void CharBones::Print(){
    for(std::vector<Bone>::iterator it = mBones.begin(); it != mBones.end(); ++it){
        MILO_LOG("%s %.2f: %s\n", (*it).name, (*it).weight, StringVal((*it).name));
    }
}

CharBonesAlloc::~CharBonesAlloc(){

}

CharBonesObject::~CharBonesObject(){

}