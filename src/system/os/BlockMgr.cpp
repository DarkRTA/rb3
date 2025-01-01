#include "BlockMgr.h"
#include "obj/DataFunc.h"
#include "os/AsyncTask.h"
#include "os/CDReader.h"
#include "os/Debug.h"
#include "os/HDCache.h"
#include "utl/MemMgr.h"
#include "decomp.h"

#define kNumBlockBuffers 4

BlockMgr TheBlockMgr;
int gLastBlockNum = -1;
int gLastArkNum = -1;
const int kArkBlockSize = 0x10000;
static char* gBuffers;
int gCurrBuffNum;
int Block::sCurrTimestamp = 0;
Timer gReadTime;

namespace {
    bool gReadHD = false;
    static DataNode OnSpinUp(DataArray*){
        return TheBlockMgr.SpinUp();
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
    mBuffer = &gBuffers[GetFreeBuffer() * 0x10000];
    UpdateTimestamp();
}

void Block::UpdateTimestamp(){
    mTimestamp = ++sCurrTimestamp;
}

BlockRequest::BlockRequest(const AsyncTask& task) : mArkfileNum(task.mArkfileNum), mBlockNum(task.GetBlockNum()), mStr(task.GetStr()) {
    mTasks.push_back(task);
}

void BlockMgr::Init() {
    gBuffers = (char*)_MemAlloc(0x40000, 0x40);
    gCurrBuffNum = 0;
    mBlockCache.resize(4);
    mReadingBlock = nullptr;
    for (int i = 0; i < mBlockCache.size(); i++) {
        mBlockCache[i] = new Block();
    }
    TheHDCache.Init();
    DataRegisterFunc("disc_spin_up", OnSpinUp);
}

const char* BlockMgr::GetBlockData(int ark, int blk) {
    Block* blokc = FindBlock(ark, blk);
    if (blokc != nullptr && blokc != mReadingBlock) {
        blokc->UpdateTimestamp();
        return blokc->mBuffer;
    }
    return nullptr;
}

void BlockMgr::WriteBlock() {
    MILO_ASSERT(!mWritingBlock, 345);
    bool ret;
    Block* blk;
    do {
        blk = FindLRUBlock(true);
        if (blk == nullptr) return;
        blk->mWritten = true;
        ret = TheHDCache.WriteAsync(blk->mArkfileNum, blk->mBlockNum, blk->mBuffer);
    } while (!ret);
    mWritingBlock = blk;
}

void BlockMgr::ReadBlock() {
    MILO_ASSERT(mReadingBlock, 364);


    bool x;
    void* buf = (void*)mReadingBlock->mBuffer;
    u32 arknum = mReadingBlock->mArkfileNum; 
    u32 blknum = mReadingBlock->mBlockNum; 
    if (TheHDCache.ReadAsync(arknum, blknum, buf)) {
        gReadHD = true;
        x = false;
    } else {
        gReadHD = false;
        x = CDRead(arknum, blknum * 32, 32, buf);
    }
    if (!x) {
        mReadingBlock->UpdateTimestamp();
    } else {
        MILO_LOG("CD READING ERROR: %x\n", x);
        mReadingBlock = nullptr;
    }
}

Block* BlockMgr::FindBlock(int i1, int i2){
    for(int i = 0; i < mBlockCache.size(); i++){
        if(mBlockCache[i]->CheckMetadata(i1, i2)) return mBlockCache[i];
    }
    return nullptr;
}

Block* BlockMgr::FindLRUBlock(bool b) {
    int time = Block::sCurrTimestamp;
    Block* ret = nullptr;
    for(int i = 0; i < mBlockCache.size(); i++){
        if(mBlockCache[i] != mWritingBlock && mBlockCache[i] != mReadingBlock &&
            (!b || !mBlockCache[i]->mWritten && mBlockCache[i]->mTimestamp < time)
        ){
            ret = mBlockCache[i];
            time = mBlockCache[i]->mTimestamp;
        }
    }
    return ret;
}

Block* BlockMgr::FindMRUBlock() {
    int time = -1;
    Block* ret = nullptr;
    for(int i = 0; i < mBlockCache.size(); i++){
        if(mBlockCache[i]->mTimestamp > time){
            ret = mBlockCache[i];
            time = mBlockCache[i]->mTimestamp;

        }
    }
    return ret;
}

bool BlockMgr::SpinUp() {
    TheBlockMgr.Poll();
    if (UsingCD()) {
        if (mSpinDownTimer.Ms() > 120000.000f) {
            if (mReadingBlock == nullptr) {
                MILO_LOG("BlockMgr spinning up...\n");
                Block* blk = FindMRUBlock();
                mReadingBlock = blk;
                AsyncTask at(blk->mArkfileNum, blk->mBlockNum);
                AddTask(at);
                gReadHD = false;
                bool x = CDRead(mReadingBlock->mArkfileNum, ((mReadingBlock->mBlockNum + 1) << 5) - 1, 1, (void*)(mReadingBlock->mBuffer + 0xF800));
                if (!x) {
                    mReadingBlock->UpdateTimestamp();
                } else {
                    MILO_LOG("CD READING ERROR: %x\n", x);
                    mReadingBlock = nullptr;
                }  
            }
            return false;
        }
    }
    return true;
}

void BlockMgr::MarkDiscRead() { mSpinDownTimer.Restart(); }
