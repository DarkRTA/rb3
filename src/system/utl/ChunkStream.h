#pragma once
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

enum BufferState {
    kInvalid,
    kReading,
    kDecompressing,
    kReady,
};

struct DecompressTask {
    DecompressTask(int* size, char* data, BufferState* state, int out, int id, const char* name) : 
        mChunkSize(size), out_data(data), mState(state), mOutLen(out), mID(id), mFilename(name) {}
    DecompressTask() {}
    int* mChunkSize;
    char* out_data;
    BufferState* mState;
    int mOutLen;
    int mID;
    const char* mFilename;
};

/**
 * @brief BinStream derivative used to read RIFF files, compressed .milos, etc
 */
class ChunkStream : public BinStream {
public:
    class ChunkInfo {
    public:
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
    virtual EofType Eof();
    virtual bool Fail();
    virtual const char* Name() const;
    virtual bool Cached() const;
    virtual Platform GetPlatform() const;
    virtual void ReadImpl(void*, int);
    virtual void WriteImpl(const void*, int);
    virtual void SeekImpl(int, SeekType);

    void SetPlatform(Platform);
    static void DecompressChunk(DecompressTask&);
    void MaybeWriteChunk(bool);
    void ReadChunkAsync();
    int WriteChunk();
    void DecompressChunkAsync();
    
    static bool PollDecompressionWorker();

    File* mFile; // 0xc
    String mFilename; // 0x10
    bool mFail; // 0x1c
    FileType mType; // 0x20
    ChunkInfo mChunkInfo; // 0x24
    bool mIsCached; // 0x834
    Platform mPlatform; // 0x838
    int mBufSize; // 0x83c
    char* mBuffers[2]; // 0x840, 0x844
    char* mCurReadBuffer; // 0x848
    Timer mStartTime; // 0x84c
    int mRecommendedChunkSize; // 0x880
    int mLastWriteMarker; // 0x884
    int mCurBufferIdx; // 0x888
    BufferState mBuffersState[2]; // 0x88c, 0x890
    int* mBuffersOffset[2]; // 0x894, 0x898
    int mCurBufOffset; // 0x89c
    bool mChunkInfoPending; // 0x8a0
    int* mCurChunk; // 0x8a4
    int* mChunkEnd; // 0x8a8
    int mTell; // 0x8ac

    void* operator new(size_t t) {
        return _MemAllocTemp(t, 0);
    }
    DELETE_OVERLOAD
};

void DecompressMemHelper(const void*, int, void*, int&, const char*);
