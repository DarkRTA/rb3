#include "char/CharBones.h"
#include "char/CharClip.h"
#include "decomp.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "math/Vec.h"
#include "utl/MakeString.h"
#include "utl/Symbols.h"

void TestDstComplain(Symbol s) {
    MILO_NOTIFY_ONCE("src %s not in dst, punting animation", s);
}

CharBones *gPropBones;

CharBones::CharBones() : mCompression(kCompressNone), mStart(0), mTotalSize(0) {
    for (int i = 0; i < NUM_TYPES; i++) {
        mCounts[i] = 0;
        mOffsets[i] = 0;
    }
}

CharBones::Type CharBones::TypeOf(Symbol s) {
    for (const char *p = s.Str(); *p != 0; p++) {
        if (*p == '.') {
            switch (p[1]) {
            case 'p':
                return TYPE_POS;
            case 's':
                return TYPE_SCALE;
            case 'q':
                return TYPE_QUAT;
            case 'r': {
                // check if rot is x, y, or z
                unsigned char next = p[3];
                if ((unsigned char)(next - 'x') <= 2)
                    return (Type)((char)next - 'u');
            }
            default:
                break;
            }
        }
    }
    MILO_FAIL("Unknown bone suffix in %s", s);
    return NUM_TYPES;
}

const char *CharBones::SuffixOf(CharBones::Type t) {
    static const char *suffixes[NUM_TYPES] = { "pos",  "scale", "quat",
                                               "rotx", "roty",  "rotz" };
    MILO_ASSERT(t < TYPE_END, 0x66);
    return suffixes[t];
}

DECOMP_FORCEACTIVE(
    CharBones, " (added:", " ", ", ", ")", " (removed:", " (weights:", ":", "->"
)

Symbol CharBones::ChannelName(const char *cc, CharBones::Type t) {
    MILO_ASSERT(t < TYPE_END, 0x6F);
    char buf[256];
    strcpy(buf, cc);
    char *chr = strchr(buf, '.');
    if (!chr) {
        chr = buf + strlen(buf);
        *chr = '.';
    }
    strcpy(chr + 1, SuffixOf(t));
    return Symbol(buf);
}

void CharBones::ClearBones() {
    mBones.clear();
    for (int i = 0; i < NUM_TYPES; i++) {
        mCounts[i] = 0;
        mOffsets[i] = 0;
    }
    mTotalSize = 0;
    mCompression = kCompressNone;
    ReallocateInternal();
}

void CharBones::ReallocateInternal() {}

void CharBones::SetWeights(float f) { SetWeights(f, mBones); }

void CharBones::AddBones(const std::vector<Bone> &vec) {
    for (std::vector<Bone>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        AddBoneInternal(*it);
    }
    ReallocateInternal();
}

void CharBones::AddBones(const std::list<Bone> &bones) {
    for (std::list<Bone>::const_iterator it = bones.begin(); it != bones.end(); ++it) {
        AddBoneInternal(*it);
    }
    ReallocateInternal();
}

void CharBones::ListBones(std::list<Bone> &bones) const {
    for (int i = 0; i < mBones.size(); i++) {
        bones.push_back(mBones[i]);
    }
}

void CharBones::Zero() { memset(mStart, 0, mTotalSize); }

int CharBones::TypeSize(int i) const {
    switch (i) {
    case TYPE_POS:
    case TYPE_SCALE:
        if (mCompression >= kCompressVects)
            return 6;
        else
            return 12;
    case TYPE_QUAT:
        if (mCompression >= kCompressQuats)
            return 4;
        else if (mCompression != kCompressNone)
            return 8;
        else
            return 16;

    default:
        if (mCompression != kCompressNone)
            return 2;
        else
            return 4;
    }
}

int CharBones::FindOffset(Symbol s) const {
    Type ty = TypeOf(s);
    int nextcount = mCounts[ty + 1];
    int size = TypeSize(ty);
    int count = mCounts[ty];
    int offset = mOffsets[ty];
    for (int i = 0; i < nextcount - count; i++) {
        if (mBones[count << 3].name == s)
            return offset;
        else
            offset += size;
    }
    return -1;
}

void CharBones::SetWeights(float wt, std::vector<Bone> &bones) {
    for (int i = 0; i < bones.size(); i++) {
        bones[i].weight = wt;
    }
}

void *CharBones::FindPtr(Symbol s) const {
    int offset = FindOffset(s);
    if (offset == -1)
        return 0;
    else
        return (void *)&mStart[offset];
}

void CharBones::RecomputeSizes() {
    mPosOffset = 0;
    for (int i = 0; i < NUM_TYPES; i++) {
        int diff = mCounts[i + 1] - mCounts[i];
        mOffsets[i + 1] = mOffsets[i] + diff * TypeSize(i);
    }
    mTotalSize = mEndOffset + 0xFU & 0xFFFFFFF0; // round up to the nearest 0x10,
                                                 // alignment moment
}

void CharBones::SetCompression(CompressionType ty) {
    if (ty != mCompression) {
        mCompression = ty;
        RecomputeSizes();
    }
}

DECOMP_FORCEACTIVE(CharBones, "!mCompression && !bones.mCompression")

const char *CharBones::StringVal(Symbol s) {
    void *ptr = FindPtr(s);
    CharBones::Type t = TypeOf(s);
    if (t < 2) {
        if (mCompression >= 2) {
            Vector3 vshort((short *)ptr);
            return MakeString("%g %g %g", vshort.x, vshort.y, vshort.z);
        } else {
            Vector3 *vptr = (Vector3 *)vptr;
            return MakeString("%g %g %g", vptr->x, vptr->y, vptr->z);
        }
    } else if (t == 2) {
        Hmx::Quat q;
        Hmx::Quat *qPtr = (Hmx::Quat *)ptr;
        if (mCompression >= 3) {
            ByteQuat *bqPtr = (ByteQuat *)qPtr;
            bqPtr->ToQuat(q);
        } else if (mCompression != kCompressNone) {
            ShortQuat *sqPtr = (ShortQuat *)qPtr;
            sqPtr->ToQuat(q);
        } else
            q = *qPtr;
        Vector3 v40;
        MakeEuler(q, v40);
        v40 *= RAD2DEG;
        return MakeString(
            "quat(%g %g %g %g) euler(%g %g %g)", q.x, q.y, q.z, q.w, v40.x, v40.y, v40.z
        );
    } else {
        float floatVal;
        if (mCompression != kCompressNone) {
            floatVal = *((short *)ptr) * 0.00061035156f;
        } else {
            floatVal = *((float *)ptr);
        }
        floatVal *= RAD2DEG;
        if (mCompression != kCompressNone) {
            return MakeString("deg %g raw %d", floatVal, *((short *)ptr));
        } else {
            return MakeString("deg %g rad %g", floatVal, *((float *)ptr));
        }
    }
}

void CharBones::Print() {
    for (std::vector<Bone>::iterator it = mBones.begin(); it != mBones.end(); ++it) {
        MILO_LOG("%s %.2f: %s\n", it->name, it->weight, StringVal(it->name));
    }
}

DECOMP_FORCEACTIVE(
    CharBones, "!mCompression", "false", "newSize == 4", "oldSize == 2", "end >= start"
)

void CharBones::ScaleAdd(CharClip *clip, float f1, float f2, float f3) {
    clip->ScaleAdd(*this, f1, f2, f3);
}

CharBonesAlloc::~CharBonesAlloc() { _MemFree(mStart); }

void CharBonesAlloc::ReallocateInternal() {
    _MemFree(mStart);
    mStart = (char *)_MemAlloc(mTotalSize, 0);
}

BinStream &operator>>(BinStream &bs, CharBones::Bone &bone) {
    bs >> bone.name;
    bs >> bone.weight;
    return bs;
}

BEGIN_CUSTOM_PROPSYNC(CharBones::Bone)
    SYNC_PROP(name, o.name)
    SYNC_PROP(weight, o.weight)
    SYNC_PROP_SET(preview_val, gPropBones->StringVal(o.name), )
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharBonesObject)
    gPropBones = this;
    if (sym == bones)
        return PropSync(mBones, _val, _prop, _i + 1, _op);
END_PROPSYNCS
