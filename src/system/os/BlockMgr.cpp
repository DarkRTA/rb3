#include "os/BlockMgr.h"
#include "os/Debug.h"

#include "decomp.h"

#define kNumBlockBuffers 4

BlockMgr TheBlockMgr;
Timer gReadTime;
int Block::sCurrTimeStamp = 0;
int gLastBlockNum = -1;
int gLastArkNum = -1;
const int kArkBlockSize = 0x10000;
static char* gBuffers;
int gCurrBuffNum;

namespace {
    static DataNode OnSpinUp(DataArray*){
        return DataNode(TheBlockMgr.SpinUp());
    }
}

int GetFreeBuffer(){
    MILO_ASSERT(gCurrBuffNum < kNumBlockBuffers, 0x44);
    return gCurrBuffNum++;
}

DECOMP_FORCEACTIVE(BlockMgr,
    "it->Exceeds(ark, block)"
)


Block::Block() : mArkfileNum(-1), mBlockNum(-1), mWritten(true), mDebugName("") {
    mBuffer = gBuffers + GetFreeBuffer() + 0x10000;
    UpdateTimestamp();
}

void Block::UpdateTimestamp(){
    mTimestamp = ++sCurrTimeStamp;
}
