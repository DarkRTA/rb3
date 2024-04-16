#include "ChunkStream.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Compress.h"
#include "utl/MemMgr.h"
#include <list>
#include <string.h>
#include "math/MathFuncs.h"
#include "os/File.h"
#include "os/Endian.h"

namespace {std::list<DecompressTask> gDecompressionQueue;}

BinStream& MarkChunk(BinStream& bs) {
    ChunkStream* cs = dynamic_cast<ChunkStream*>(&bs);
    if (cs) cs->MaybeWriteChunk(false);
    return bs;
}

BinStream& ReadChunks(BinStream& bs, void* data, int total_len, int max_chunk_size) {
    int curr_size = 0;
    while(curr_size != total_len){
        int len_left = Minimum(total_len - curr_size, max_chunk_size);
        char* dataAsChars = (char*)data;
        bs.Read(&dataAsChars[curr_size], len_left);
        curr_size += len_left;
        while(bs.Eof() == TempEof) Timer::Sleep(0);
    }
    return bs;
}

BinStream& WriteChunks(BinStream& bs, const void* data, int total_len, int max_chunk_size) {
    int curr_size = 0;
    while (curr_size != total_len) {
        int len_left = Minimum(total_len - curr_size, max_chunk_size);
        const char* dataChars = (const char*)data;
        bs.Write(&dataChars[curr_size], len_left);
        curr_size += len_left;
        if (bs.GetPlatform() == kPlatformWii) MarkChunk(bs);
    }
    return bs;
}

ChunkStream::ChunkStream(const char* c2, FileType type, int i, bool b1, Platform plat, bool b2) : BinStream(false), mFilename(c2), mType(type), mChunkInfo(b1), mIsCached(b2), mStartTime() {
    mRecommendedChunkSize = i;
    mLastWriteMarker = 0;
    mCurBufferIdx = -1;
    mCurBufOffset = 0;
    mTell = 0;
    SetPlatform(plat);
    for(int bufCnt = 0; bufCnt < 2; bufCnt++){
        mBuffersState[bufCnt] = kInvalid;
        mBuffersOffset[bufCnt] = 0;
        mBuffers[bufCnt] = 0;
    }
    mCurReadBuffer = 0;
    int size = 0xA04;
    if (type == kRead) size = 2; 
    File* f = NewFile(c2, size);
    mFile = f;
    mFail = !f;
    if (!mFail) {
        if (type == kWrite) {
            mFile->Write(&mChunkInfo, 0x810);
            mBufSize = mRecommendedChunkSize * 2;
            mBuffers[0] = (char*)_MemAllocTemp(mBufSize, 0);
            mBuffers[1] = (char*)_MemAllocTemp(mBufSize, 0);
            mCurBufferIdx = 0;
        } else {
            mChunkInfoPending = true;
            mFile->ReadAsync(&mChunkInfo, 0x810);
        }
    }
}

void ChunkStream::SetPlatform(Platform plat) {
    if (plat == kPlatformNone) {
        plat = ConsolePlatform();
    }
    mLittleEndian = PlatformLittleEndian(plat);
    mPlatform = plat;
}

ChunkStream::~ChunkStream() {
    if (!mFail && mType == kWrite) {
        MaybeWriteChunk(true);
        if (mChunkInfo.mNumChunks == 0x200) MILO_WARN("%s is %d compressed bytes too large", mFilename, mChunkInfo.mChunks[0x1ff]);
        mFile->Seek(0,0);
        for (int i = 0; i < mChunkInfo.mNumChunks; i++) {
            EndianSwapEq(mChunkInfo.mChunks[i]);
        }
        EndianSwapEq(mChunkInfo.mID);
        EndianSwapEq(mChunkInfo.mChunkInfoSize);
        EndianSwapEq(mChunkInfo.mNumChunks);
        EndianSwapEq(mChunkInfo.mMaxChunkSize);
        memset((void*)&mChunkInfo.mChunks[mChunkInfo.mNumChunks], 0, (0x200 - mChunkInfo.mNumChunks) * 4);
        mFile->Write(&mChunkInfo, 2064);
    }
    delete mFile;
    for (int i = 0; i < 2; i++) {
        MILO_ASSERT(mBuffersState[i] != kDecompressing, 398);
        delete mBuffers[i];
    }
}

void ChunkStream::ReadImpl(void* Pv, int bytes) {
    MILO_ASSERT(mCurBufferIdx != -1, 455);
    MILO_ASSERT(mBuffersState[mCurBufferIdx] == kReady, 456);
    MILO_ASSERT(mBuffersOffset[mCurBufferIdx] == mCurChunk, 457);
    MILO_ASSERT(mCurBufOffset + bytes <= (*mCurChunk & kChunkSizeMask), 458);
    memcpy(Pv, (void*)(mCurReadBuffer + mCurBufOffset), bytes);
    mCurBufOffset += bytes;
    mTell += bytes;
}

void ChunkStream::WriteImpl(const void* Pv, int bytes) {
    if (mCurBufOffset + bytes > mBufSize) {
        while (mCurBufOffset + bytes > mBufSize) mBufSize += mBufSize;
        void* a = _MemAllocTemp(mBufSize, 0);
        memcpy(a, mBuffers[0], mCurBufOffset);
        _MemFree(mBuffers[0]);
        mBuffers[0] = (char*)a;
        _MemFree(mBuffers[1]);
        mBuffers[1] = (char*)_MemAllocTemp(mBufSize, 0);
    }
    memcpy(mBuffers[0] + mCurBufOffset, Pv, bytes);
    mCurBufOffset += bytes;
}

void ChunkStream::Flush() { return; }

void ChunkStream::SeekImpl(int offset, BinStream::SeekType s) {
    if (s == kSeekCur && offset >= 0) {
        MILO_ASSERT(mCurBufOffset + offset <= *mCurChunk, 493);
        mCurBufOffset += offset;
    } else MILO_FAIL("Can only seek forward from current position on chunkstream");
}

int ChunkStream::Tell() {
    if (mType == kRead) return mTell;
    else MILO_FAIL("Can't tell on chunkstream"); return 0;
}

void ChunkStream::ReadChunkAsync() {
    int chunkIdx = 1;
    int idx = (mCurBufferIdx + 1) > 1;
    if(mBuffersState[idx] != kInvalid){
        chunkIdx = 2;
        idx = (mCurBufferIdx + 2) > 1;
        if(mBuffersState[idx] != kInvalid) chunkIdx = 3;
    }
    if(mBuffersState[idx] == kInvalid){
        if(&mCurChunk[chunkIdx] != mChunkEnd){
            if(mChunkInfo.mID = 0xCABEDEAF || mCurChunk[chunkIdx] != 0){
                mFile->ReadAsync(mBuffers[idx], chunkIdx);
            }
            else mFile->ReadAsync(mBuffers[idx], mBufSize);
            mBuffersOffset[idx] = &mCurChunk[chunkIdx];
            mBuffersState[idx] = kReading;
        }
    }
}

EofType ChunkStream::Eof() {
    MILO_ASSERT(!mFail && mType == kRead, 552);
    if (mChunkInfoPending) {
        int x;
        if (mFile->ReadDone(x) == 0) return TempEof;
        mChunkInfoPending = false;
        EndianSwapEq(mChunkInfo.mID);
        EndianSwapEq(mChunkInfo.mChunkInfoSize);
        EndianSwapEq(mChunkInfo.mNumChunks);
        EndianSwapEq(mChunkInfo.mMaxChunkSize);
        for (int i = 0; i < mChunkInfo.mNumChunks; i++) {
            EndianSwapEq(mChunkInfo.mChunks[i]);
        }
        if ((mChunkInfo.mID & 0xf0ffffff) != kChunkIDMask) {
            mChunkInfo.mID = 0xCABEDEAF;
            mChunkInfo.mChunkInfoSize = 0;
            mChunkInfo.mNumChunks = 1;
            mChunkInfo.mMaxChunkSize = mFile->Size();
            MILO_ASSERT((mChunkInfo.mMaxChunkSize & ~kChunkSizeMask) == 0, 583);
            mChunkInfo.mChunks[0] = mChunkInfo.mMaxChunkSize;
        }
        if (strstr(mFilename.c_str(), ".milo_")) {
            const char* aaa = mFilename.c_str();
            mIsCached = true;
            if (strstr(aaa, ".milo_xbox")) {
                SetPlatform(kPlatformXBox);
            } else if (strstr(aaa, ".milo_ps3")) {
                SetPlatform(kPlatformPS3);
            } else if (strstr(aaa, ".milo_wii")) {
                SetPlatform(kPlatformWii);
            } else SetPlatform(kPlatformPC);
        } else {
            mIsCached = false;
            SetPlatform(kPlatformPS2);
        }
    }
}

bool ChunkStream::Fail() { return mFail; }

char* unused = "mCurBufOffset == (*mCurChunk & kChunkSizeMask)";

void ChunkStream::MaybeWriteChunk(bool b) {
    if (mChunkInfo.mNumChunks < 2 && 0x1fff < mCurBufOffset) b = true;


    if (mChunkInfo.mNumChunks > 0x200) MILO_FAIL("%s has %d chunks, max is %d", mFilename, mChunkInfo.mNumChunks, 0x200);
    WriteChunk();
}

uint ChunkStream::WriteChunk() {
    MILO_ASSERT(mCurBufOffset < kChunkSizeMask, 778);
    int result = mCurBufOffset;
    char* test = mBuffers[0];
    int size;
    int flags; // ?
    int sagasasdgg = 0;
    if (mChunkInfo.mID == 0xCDBEDEAF) {
        int dingus = mBufSize - 4;
        int dongus = (int)mBuffers[1];
        dongus = result;
        EndianSwapEq(dongus);
        CompressMem(mBuffers[0], result, (void*)(dongus + 1), dingus,NULL);
        // float x, y = x = 176.0f;
        if (/*x / y <= 1.1*/ false) {
            sagasasdgg = 0x1000000;
        } else {
            result = dingus + 4;
            test = (char*)dongus;
        }
    }
    if (result != mFile->Write(test, result)) {
        mFail = true;
    }
    MILO_ASSERT((size & ~kChunkSizeMask) == 0, 820);
    MILO_ASSERT((flags & (kChunkSizeMask|kChunkUnusedMask)) == 0, 822);
    MILO_ASSERT((result & kChunkUnusedMask) == 0, 827);
    return result | sagasasdgg;
}

void DecompressMemHelper(const void* a, int b, void* c, int& dstLen, const char* fname) {
    int expectedDstLen = *((int*)a);
    EndianSwapEq(expectedDstLen);
    DecompressMem((void*)((int)a + 4), b - 4, c, dstLen, false, fname);
    MILO_ASSERT(dstLen == expectedDstLen, 949);
}

void ChunkStream::DecompressChunk(DecompressTask& task) {
    MILO_ASSERT(*task.mState == kDecompressing, 955);
    int data = *task.mChunkSize & kChunkSizeMask;
    MILO_ASSERT((data & ~kChunkSizeMask) == 0, 959);
    int out_len = task.mOutLen;
    uint id = task.mID;
    if (id == 0xCDBEDEAF) {
        DecompressMemHelper((void*)(task.out_data + (out_len - data) + 10), data, (void*)task.out_data, out_len, task.mFilename);
    } else if (id == 0xCCBEDEAF) {
        DecompressMem((void *)(task.out_data + (out_len - data) + 10), data - 0x12, (void*)task.out_data, out_len, false, task.mFilename);
    } else {
        MILO_ASSERT(task.mID == CHUNKSTREAM_Z_ID, 977);
        DecompressMem((void *)(task.out_data + (task.mOutLen - data)), data, (void*)task.out_data, out_len, false, task.mFilename);
    }
    *task.mChunkSize = out_len;
    *task.mState = 3;
}

ChunkStream::ChunkInfo::ChunkInfo(bool isCompressed) {
    uint id = 0xCABEDEAF;
    if (isCompressed) id = 0xCDBEDEAF;
    mID = id;
    mChunkInfoSize = 0x810;
    mNumChunks = 0;
    mMaxChunkSize = 0;
    mChunks[0] = 0;
}

int ChunkStream::GetPlatform() const { return mPlatform; }
bool ChunkStream::Cached() const { return mIsCached; }
const char* ChunkStream::Name() const { return mFilename.c_str(); }
