#include "utl/Chunks.h"
#include "utl/ChunkIDs.h"
#include "os/Debug.h"

IListChunk::IListChunk(BinStream& bs, bool b) : mParent(0), mBaseBinStream(bs), mHeader(0), 
    mLocked(0), mSubHeader(), mRecentlyReset(1) {
    if(b){
        mHeader = new ChunkHeader(mBaseBinStream);
    }
    else {
        int tell1 = bs.Tell();
        bs.Seek(0, BinStream::kSeekEnd);
        int tell2 = bs.Tell();
        bs.Seek(tell1, BinStream::kSeekBegin);
        mHeader = new ChunkHeader(kListChunkID, tell2 - tell1, true);
    }
    mStartMarker = mBaseBinStream.Tell();
    Init();
}

IListChunk::IListChunk(IListChunk& chunk) : mParent(chunk.mParent), mBaseBinStream(chunk.mBaseBinStream), mHeader(chunk.mHeader), mLocked(0), mSubHeader(), mRecentlyReset(1) {
    mHeader = new ChunkHeader(*CurSubChunkHeader());
    mStartMarker = mBaseBinStream.Tell();
    Init();
}

IListChunk::~IListChunk(){
    if(mParent) mParent->UnLock();
    delete mHeader;
}

void IListChunk::Init(){
    MILO_ASSERT(mHeader->IsList(), 0x100);
    mEndMarker = mStartMarker + mHeader->Length();
    if(mParent) mParent->Lock();
    Reset();
}

void IListChunk::Reset(){
    MILO_ASSERT(!mLocked, 0x111);
    mBaseBinStream.Seek(mStartMarker, BinStream::kSeekBegin);
    mSubChunkMarker = mStartMarker;
    mSubChunkValid = false;
    mRecentlyReset = true;
}

const ChunkHeader* IListChunk::CurSubChunkHeader() const {
    MILO_ASSERT(mRecentlyReset == false, 0x121);
    if(!mSubChunkValid) return 0;
    else return &mSubHeader;
}
