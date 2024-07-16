#include "HDCache.h"
#include "os/Debug.h"
#include "os/OSFuncs.h"
#include "os/Archive.h"
#include "utl/Option.h"

HDCache TheHDCache;

HDCache::HDCache() : mBlockState(0), mWriteFileIdx(0), unk18(-1), unk20(0), unk24(0), unk28(-1), unk2c(-1), mLockId(0),
    unk34(0), mCritSec(0), mHdrIdx(0), mHdrBuf(0), unk64(0) {

}

HDCache::~HDCache() { }

void HDCache::Init(){
    mCritSec = new CriticalSection();
    if(TheArchive){
        OptionBool("no_hdcache", true);
        int numarkfiles = TheArchive->mNumArkfiles;
        mReadArkFiles.resize(numarkfiles);
        mWriteArkFiles.resize(numarkfiles);
        FileStream* fs = OpenHeader();
        if(fs){
            if(fs->Tell() == 0){

            }
        }
    }
}

bool HDCache::LockCache(){
    CritSecTracker cst(mCritSec);
    if(mLockId == 0 || mLockId == CurrentThreadId()){
        mLockId = CurrentThreadId();
        unk34++;
        return true;
    }
    else return false;
}

void HDCache::UnlockCache(){
    CritSecTracker cst(mCritSec);
    MILO_ASSERT(mLockId == CurrentThreadId(), 0xF9);
    if(!unk34--) mLockId = 0;
}
