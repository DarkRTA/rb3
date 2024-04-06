#ifndef UTL_CHUNKSTREAM_H
#define UTL_CHUNKSTREAM_H

#include "obj/Object.h"
#include "os/File.h"
#include "os/System.h"
#include "os/Timer.h"
#include "utl/BinStream.h"
#include "utl/Str.h"
#include "milo_types.h"

BinStream& MarkChunk(BinStream&);
BinStream& ReadChunks(BinStream&, void*, int, int);
BinStream& WriteChunks(BinStream&, const void*, int, int);

#define kChunkSizeMask 0x00ffffff
#define kChunkUnusedMask 0xfe000000
#define CHUNKSTREAM_Z_ID 0xCBBEDEAF
#define kChunkIDMask 0xC0BEDEAF

enum DecompressionState {
    kUnk0,
    kUnk1,
    kDecompressing,
    kReady,
};

struct DecompressTask {
    int* mChunkSize;
    int out_data;
    int* mState;
    int mOutLen;
    uint mID;
    const char* mFilename;
};

class ChunkStream : public BinStream {
public:
    class ChunkInfo { public:
        ChunkInfo(bool);
        int mID; // offset 0x0, size 0x4
        int mChunkInfoSize; // offset 0x4, size 0x4
        int mNumChunks; // offset 0x8, size 0x4
        int mMaxChunkSize; // offset 0xC, size 0x4
        int mChunks[512]; // offset 0x10, size 0x800
    };

    enum FileType {
        kRead = 0,
        kWrite = 1,
    };

    ChunkStream(const char *, FileType, int, bool, Platform, bool);
    virtual ~ChunkStream();
    virtual void Flush();
    virtual int Tell();
    virtual bool Eof();
    virtual bool Fail();
    virtual const char* Name() const;
    virtual bool Cached() const;
    virtual int GetPlatform() const;
    virtual void ReadImpl(void*, int);
    virtual void WriteImpl(const void*, int);
    virtual void SeekImpl(int, SeekType);

    void SetPlatform(Platform);
    static void DecompressChunk(DecompressTask&);
    void MaybeWriteChunk(bool);
    void ReadChunkAsync();
    uint WriteChunk();

    File * mFile;
    String mFilename;
    bool mFail;
    FileType mType;
    ChunkInfo mChunkInfo;
    bool mIsCached;
    Platform mPlatform;
    int mCurBufSize;
    char* mBuffers[2];
    int mCurReadBuffer;
    Timer mStartTime;
    int b[2];
    int mCurBufferIdx;
    DecompressionState* mBuffersState;
    int pad;
    int** mBuffersOffset;
    int c;
    int mCurBufOffset;
    bool mChunkInfoPending;
    int* mCurChunk;
    int* mChunkEnd;
    int mTell; // which is different from mCurBufOffset... why?

    void *operator new(size_t t) {
        return _MemAllocTemp(t, 0);
    }
};

void DecompressMemHelper(const void*, int, void*, int&, const char*);

#endif // UTL_CHUNKSTREAM_H
