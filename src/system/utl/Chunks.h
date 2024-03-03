#ifndef UTL_CHUNKS_H
#define UTL_CHUNKS_H
#include "utl/BinStream.h"
#include "utl/ChunkIDs.h"

class ChunkHeader {
public:
    ChunkID mID;
    int mLength;
    bool mIsList;

    ChunkHeader() : mID(), mLength(0), mIsList(0) {}
    ChunkHeader(const ChunkHeader& ch) : mID(ch.mID), mLength(ch.mLength), mIsList(ch.mIsList) {}
    ChunkHeader(BinStream& bs) : mID(), mLength(0), mIsList(0) { Read(bs); }
    ChunkHeader(ChunkID id, int len, bool list) : mID(id), mLength(len), mIsList(list) {}
    void Read(BinStream&);
    int Length(){ return mLength; }
    bool IsList(){ return mIsList; }
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

    IListChunk(BinStream&, bool);
    IListChunk(IListChunk&);
    ~IListChunk();
    void Init();
    void Reset();
    void Lock();
    void UnLock();
    const ChunkHeader* CurSubChunkHeader() const;
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
    virtual ~IDataChunk();
    virtual void Flush(){}
    virtual int Tell();
    virtual bool Eof();
    virtual bool Fail(); // weak
    virtual void ReadImpl(void*, int);
    virtual void WriteImpl(const void*, int){}
    virtual void SeekImpl(int, SeekType);

};

#endif
