#ifndef UTL_CHUNKS_H
#define UTL_CHUNKS_H
#include "utl/BinStream.h"
#include "utl/ChunkIDs.h"
#include <string.h>

#define kDataHeaderSize 8

inline bool CheckChunkID(const char* str, const char* id){
    return strncmp(str, id, 4) == 0;
}

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

    // prolly not the function name, it's inlined in debug
    unsigned int GetNewLength(){
        unsigned int sublen = mIsList ? 12 : 8;
        return mLength + sublen;
    }
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
    ChunkHeader* Next();
    ChunkHeader* Next(ChunkID);
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
    virtual bool Eof(){ return mEof != 0; }
    virtual bool Fail(){ return mFailed; }
    virtual void ReadImpl(void*, int);
    virtual void WriteImpl(const void*, int){}
    virtual void SeekImpl(int, SeekType);

};

#endif
