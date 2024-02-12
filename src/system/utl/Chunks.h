#ifndef UTL_CHUNKS_H
#define UTL_CHUNKS_H
#include "ChunkIDs.h"
#include "BinStream.h"

class ChunkHeader {
public:
    ChunkID mID;
    int mLength;
    bool mIsList;
};

class IListChunk {
public:
    IListChunk* mParent;
    BinStream& mBaseBinStream;
    ChunkHeader* mHeader;
    int mStartMarker;
    int mEndMarker;
    bool mLocked;
    ChunkHeader mSubHeader;
    bool mSubChunkValid;
    bool mRecentlyReset;
    int mSubChunkMarker;
};

class IDataChunk : public BinStream {
public:
    IListChunk* mParent;
    BinStream& mBaseBinStream;
    ChunkHeader* mHeader;
    int mStartMarker;
    int mEndMarker;
    bool mFailed;
    bool mEof;

    IDataChunk(IListChunk&);
};

#endif
