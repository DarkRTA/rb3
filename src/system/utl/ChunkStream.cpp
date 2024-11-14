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
#include "decomp.h"

namespace {
    std::list<DecompressTask> gDecompressionQueue;
}

BinStream& MarkChunk(BinStream& bs) {
    ChunkStream* cs = dynamic_cast<ChunkStream*>(&bs);
    if (cs) cs->MaybeWriteChunk(false);
    return bs;
}

BinStream& ReadChunks(BinStream& bs, void* data, int total_len, int max_chunk_size) {
    int curr_size = 0;
    while(curr_size != total_len){
        int len_left = Min(total_len - curr_size, max_chunk_size);
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
        int len_left = Min(total_len - curr_size, max_chunk_size);
        const char* dataChars = (const char*)data;
        bs.Write(&dataChars[curr_size], len_left);
        curr_size += len_left;
        if (bs.GetPlatform() == kPlatformWii) MarkChunk(bs);
    }
    return bs;
}

ChunkStream::ChunkStream(const char* file, FileType type, int chunkSize, bool compress, Platform plat, bool cached) : BinStream(false),
    mFilename(file), mType(type), mChunkInfo(compress), mIsCached(cached), mStartTime(), mRecommendedChunkSize(chunkSize),
    mLastWriteMarker(0), mCurBufferIdx(-1), mCurBufOffset(0), mTell(0) {
    SetPlatform(plat);
    for(int bufCnt = 0; bufCnt < 2; bufCnt++){
        mBuffersState[bufCnt] = kInvalid;
        mBuffersOffset[bufCnt] = 0;
        mBuffers[bufCnt] = 0;
    }
    mCurReadBuffer = 0;
    int size = 0xA04;
    if (type == kRead) size = 2;
    mFile = NewFile(file, size);
    mFail = !mFile;
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
        int* chunks = mChunkInfo.mChunks;
        for (int i = 0; i < mChunkInfo.mNumChunks; i++) {
            EndianSwapEq(chunks[i]);
        }
        EndianSwapEq(mChunkInfo.mID);
        EndianSwapEq(mChunkInfo.mChunkInfoSize);
        EndianSwapEq(mChunkInfo.mNumChunks);
        EndianSwapEq(mChunkInfo.mMaxChunkSize);
        memset((void*)&mChunkInfo.mChunks[mChunkInfo.mNumChunks], 0, (0x200 - mChunkInfo.mNumChunks) * 4);
        mFile->Write(&mChunkInfo, 2064);
    }
    if(mFile) delete mFile;
    for (int i = 0; i < 2; i++) {
        MILO_ASSERT(mBuffersState[i] != kDecompressing, 398);
        _MemFree(mBuffers[i]);
    }
}

void ChunkStream::ReadImpl(void* data, int bytes) {
    MILO_ASSERT(mCurBufferIdx != -1, 455);
    MILO_ASSERT(mBuffersState[mCurBufferIdx] == kReady, 456);
    MILO_ASSERT(mBuffersOffset[mCurBufferIdx] == mCurChunk, 457);
    MILO_ASSERT(mCurBufOffset + bytes <= (*mCurChunk & kChunkSizeMask), 458);
    memcpy(data, (void*)(mCurReadBuffer + mCurBufOffset), bytes);
    mCurBufOffset += bytes;
    mTell += bytes;
}

void ChunkStream::WriteImpl(const void* data, int bytes) {
    if (mCurBufOffset + bytes > mBufSize) {
        while (mCurBufOffset + bytes > mBufSize) mBufSize += mBufSize;
        void* a = _MemAllocTemp(mBufSize, 0);
        memcpy(a, mBuffers[0], mCurBufOffset);
        _MemFree(mBuffers[0]);
        mBuffers[0] = (char*)a;
        _MemFree(mBuffers[1]);
        mBuffers[1] = (char*)_MemAllocTemp(mBufSize, 0);
    }
    memcpy(mBuffers[0] + mCurBufOffset, data, bytes);
    mCurBufOffset += bytes;
}

void ChunkStream::Flush(){}

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
    int bufIdx = 1;
    int idx;
    for(; bufIdx <= 2; bufIdx++){
        idx = (mCurBufferIdx + bufIdx) % 2;
        if(mBuffersState[idx] == kInvalid) break;
    }
    if(mBuffersState[idx] == kInvalid){
        int* thechunk = &mCurChunk[bufIdx];
        if(thechunk != mChunkEnd){
            int thechunkval = *thechunk;
            int sizemask = thechunkval & kChunkSizeMask;
            bool maskexists = (thechunkval >> 24) & 1;
            if(mChunkInfo.mID != 0xCABEDEAF && !maskexists){
                mFile->ReadAsync(mBuffers[idx] + mBufSize - sizemask, sizemask);
            }
            else mFile->ReadAsync(mBuffers[idx], sizemask);
            mBuffersOffset[idx] = &mCurChunk[bufIdx];
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
            mIsCached = true;
            if(strstr(mFilename.c_str(), ".milo_xbox")) SetPlatform(kPlatformXBox);
            else if(strstr(mFilename.c_str(), ".milo_ps3")) SetPlatform(kPlatformPS3);
            else if(strstr(mFilename.c_str(), ".milo_wii")) SetPlatform(kPlatformWii);
            else SetPlatform(kPlatformPC);
        }
        else {
            mIsCached = false;
            SetPlatform(kPlatformPC);
        }

        mBufSize = mChunkInfo.mMaxChunkSize;
        if(mChunkInfo.mID != 0xCABEDEAF) mBufSize += 0x800;
        int cap = Min(2, mChunkInfo.mNumChunks);
        for(int i = 0; i < cap; i++){
            mBuffers[i] = (char*)_MemAllocTemp(mBufSize, 0);
        }        
        int* chunks = mChunkInfo.mChunks;
        mChunkEnd = chunks + mChunkInfo.mNumChunks;
        mCurChunk = chunks - 1;
        mCurBufOffset = mChunkInfo.mMaxChunkSize & kChunkSizeMask;
        mCurBufferIdx = 1;
        mFile->Seek(mChunkInfo.mChunkInfoSize, 0);
        ReadChunkAsync();
    }

    if(mCurBufOffset < (*mCurChunk & kChunkSizeMask)){
        return NotEof;
    }
    else {
        MILO_ASSERT(mCurBufOffset == (*mCurChunk & kChunkSizeMask), 0x28B);
        if(mBuffersOffset[mCurBufferIdx] == mCurChunk){
            mBuffersState[mCurBufferIdx] = kInvalid;
        }
        if(mCurChunk + 1 == mChunkEnd) return RealEof;
        else {
            int x;
            if(mFile->ReadDone(x)){
                DecompressChunkAsync();
                ReadChunkAsync();
                PollDecompressionWorker();
            }
            int idx = (mCurBufferIdx + 1) % 2;
            if(mBuffersState[idx] != kReady) return TempEof;
            else {
                mCurBufferIdx = idx;
                mCurChunk++;
                mCurBufOffset = 0;
                mCurReadBuffer = mBuffers[idx];
                return NotEof;
            }
        }
    }
}

bool ChunkStream::Fail() { return mFail; }

DECOMP_FORCEACTIVE(ChunkStream,
    "mCurBufOffset == (*mCurChunk & kChunkSizeMask)"
)

void ChunkStream::MaybeWriteChunk(bool b) {
    if (mChunkInfo.mNumChunks < 2 && 0x2000 <= mCurBufOffset) b = true;
    if(mCurBufOffset >= mRecommendedChunkSize || b){
        bool maxchunks = mChunkInfo.mNumChunks == 511;
        if(!b && maxchunks) return;
        if((mCurBufOffset >= mRecommendedChunkSize + 0x2000) && (0x2000 <= mLastWriteMarker) && !maxchunks){
            int __n = mCurBufOffset - mLastWriteMarker;
            void* __dest = _MemAllocTemp(__n, 0);
            memcpy(__dest, mBuffers[0] + mLastWriteMarker, __n);
            mCurBufOffset = mLastWriteMarker;
            mLastWriteMarker = 0;
            MaybeWriteChunk(true);
            mCurBufOffset = __n;
            memcpy(mBuffers[0], __dest, __n);
            _MemFree(__dest);
            if(!b) return;
        }
        MILO_ASSERT_FMT(mChunkInfo.mNumChunks < 512, "%s has %d chunks, max is %d", mFilename, mChunkInfo.mNumChunks, 512);
        unsigned int wrote = WriteChunk();
        int mask = wrote & kChunkSizeMask;
        mChunkInfo.mChunks[mChunkInfo.mNumChunks++] = wrote;
        mChunkInfo.mMaxChunkSize = Max<int>(mask, mCurBufOffset, mChunkInfo.mMaxChunkSize);
        mCurBufOffset = 0;
    }
    mLastWriteMarker = mCurBufOffset;
}

int ChunkStream::WriteChunk() {
    MILO_ASSERT(mCurBufOffset < kChunkSizeMask, 778);
    int size = mCurBufOffset;
    int flags = 0;
    int* firstbuf = (int*)mBuffers[0];
    if(mChunkInfo.mID == 0xCDBEDEAF){
        int l38 = mBufSize - 4;
        int* secondbuf = (int*)mBuffers[1];
        *secondbuf = size;
        EndianSwapEq(*secondbuf);
        CompressMem(mBuffers[0], size, secondbuf + 1, l38, 0);
        if(((float)mCurBufOffset / (float)l38) > 1.1f && mChunkInfo.mNumChunks != 0){
            size = l38 + 4;
            firstbuf = secondbuf;
        }
        else flags |= 0x1000000;
    }
    if(size != mFile->Write(firstbuf, size)){
        mFail = true;
    }
    MILO_ASSERT((size & ~kChunkSizeMask) == 0, 820);
    MILO_ASSERT((flags & (kChunkSizeMask|kChunkUnusedMask)) == 0, 822);
    int result = size | flags;
    MILO_ASSERT((result & kChunkUnusedMask) == 0, 827);
    return result;
}

void ChunkStream::DecompressChunkAsync(){
    int bufIdx = 1;
    int idx;
    for(; bufIdx <= 2; bufIdx++){
        idx = (mCurBufferIdx + bufIdx) % 2;
        if(mBuffersState[idx] == kReading) break;
    }
    BufferState* state = &mBuffersState[idx];
    if(*state == kReading){
        bool maskexists = (mCurChunk[bufIdx] >> 24) & 1;
        if(mChunkInfo.mID != 0xCABEDEAF && !maskexists){
            *state = kDecompressing;
            DecompressTask dtask(&mCurChunk[bufIdx], mBuffers[idx], state, mBufSize, mChunkInfo.mID, mFilename.c_str());
            gDecompressionQueue.push_back(dtask);
        }
        else {
            *state = kReady;
        }
    }
}

bool ChunkStream::PollDecompressionWorker(){
    if(gDecompressionQueue.size() != 0){
        DecompressTask task = gDecompressionQueue.front();
        gDecompressionQueue.pop_front();
        DecompressChunk(task);
        return true;
    }
    return false;
}

void DecompressMemHelper(const void* srcData, int srcLen, void* dstData, int& dstLen, const char* fname) {
    int expectedDstLen = *((int*)srcData);
    EndianSwapEq(expectedDstLen);
    DecompressMem((void*)((int)srcData + 4), srcLen - 4, dstData, dstLen, false, fname);
    MILO_ASSERT(dstLen == expectedDstLen, 949);
}

void ChunkStream::DecompressChunk(DecompressTask& task) {
    MILO_ASSERT(*task.mState == kDecompressing, 955);
    int data = *task.mChunkSize & kChunkSizeMask;
    MILO_ASSERT((data & ~kChunkSizeMask) == 0, 959);
    int id = task.mID;
    int out_len = task.mOutLen;
    if (id == 0xCDBEDEAF) {
        char* dataOffset = &task.out_data[task.mOutLen] - data;
        DecompressMemHelper(dataOffset, data, task.out_data, out_len, task.mFilename);
    } else if (id == 0xCCBEDEAF) {
        char* dataOffset = &task.out_data[task.mOutLen] - data;
        DecompressMem(dataOffset + 10, data - 0x12, task.out_data, out_len, false, task.mFilename);
    } else {
        MILO_ASSERT(task.mID == CHUNKSTREAM_Z_ID, 977);
        char* dataOffset = &task.out_data[task.mOutLen];
        DecompressMem(dataOffset - data, data, task.out_data, out_len, false, task.mFilename);
    }
    *task.mChunkSize = out_len;
    *task.mState = kReady;
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
