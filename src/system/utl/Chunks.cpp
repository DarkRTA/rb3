#include "utl/Chunks.h"
#include "utl/ChunkIDs.h"

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
