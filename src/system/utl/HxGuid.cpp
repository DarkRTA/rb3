#include "utl/HxGuid.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "math/Rand.h"

CriticalSection gGuidCrit;

HxGuid::HxGuid(){
    Clear();
}

void HxGuid::Generate(){
    Clear();
    {
        CritSecTracker tracker(&gGuidCrit);
        mData[0] = RandomInt();
        mData[1] = RandomInt();
        mData[2] = RandomInt();
        mData[3] = RandomInt();
    }
    if(IsNull()){
        MILO_WARN("Generated HxGuid is Null.  Will try again...\n");
        Generate();
    }
}

void HxGuid::Clear(){
    mData[0] = mData[1] = mData[2] = mData[3] = 0;
}

bool HxGuid::IsNull() const {
    return (mData[0] == 0 && mData[1] == 0 && mData[2] == 0 && mData[3] == 0);
}

int HxGuid::Chunk32(int i) const {
    MILO_ASSERT(( 0) <= (i) && (i) < ( 4), 0x4F);
    return mData[i];
}

const char* HxGuid::ToString() const {
    return MakeString("%08x%08x%08x%08x", mData[0], mData[1], mData[2], mData[3]);
}

bool HxGuid::operator==(const HxGuid& hx) const {
    return (mData[0] == hx.mData[0] && mData[1] == hx.mData[1] && mData[2] == hx.mData[2] && mData[3] == hx.mData[3]);
}

bool HxGuid::operator<(const HxGuid& hx) const {
    bool b1, b2, b3, b4, b5, ret;
    ret = true;
    if(mData[0] >= hx.mData[0]){
        b5 = false;
        if(mData[0] == hx.mData[0]){
            b4 = true;
            if(mData[1] >= hx.mData[1]){
                b3 = false;
                if(mData[1] == hx.mData[1]){
                    b2 = true;
                    if(mData[2] >= hx.mData[2]){
                        b1 = (mData[2] == hx.mData[2] && mData[3] < hx.mData[3]);
                        if(!b1) b2 = false;
                    }
                    if(b2) b3 = true;
                }
                if(!b3) b4 = false;
            }
            if(b4) b5 = true;
        }
        if(!b5) ret = false;
    }
    return ret;
}

int HxGuid::SaveSize(){
    return 0x14;
}

static const char* unusedHxGuidStrings[] = { "%04x", "hex.length() == 32" };

#define kGuidRev 1

BinStream& operator<<(BinStream& bs, const HxGuid& hx){
    int rev = kGuidRev;
    bs << rev;
    bs << hx.mData[0] << hx.mData[1] << hx.mData[2] << hx.mData[3];
    return bs;
}

BinStream& operator>>(BinStream& bs, HxGuid& hx){
    int rev;
    bs >> rev;
    MILO_ASSERT(rev <= kGuidRev, 0xC6);
    bs >> hx.mData[0] >> hx.mData[1] >> hx.mData[2] >> hx.mData[3];
    return bs;
}
