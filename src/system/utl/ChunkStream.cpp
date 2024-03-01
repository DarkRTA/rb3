#include "ChunkStream.h"
#include "os/Debug.h"
#include "os/System.h"
#include "string.h"
#include <list>

extern File* NewFile(const char*, int);
template <typename T> extern void EndianSwapEq(T&);

namespace {std::list<DecompressTask> gDecompressionQueue;}

/*BinStream& MarkChunk(BinStream& bs) {
    ChunkStream potato = dynamic_cast<ChunkStream>(bs);
    if (potato) potato.MaybeWriteChunk(false);
    return bs;
}*/

BinStream& ReadChunks(BinStream& bs, void*, int, int) {

}

BinStream& WriteChunks(BinStream& bs, const void*, int, int) {

}

ChunkStream::ChunkStream(const char* c, FileType type, int i, bool b1, Platform plat, bool b2) : BinStream(false), mFilename(c), mChunkInfo(b2) {
    SetPlatform(plat);
    File* f = NewFile(c, type == kRead ? 2 : 2564);
    mFile = f;
    mFail = !f;
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
        int i;
        for (i = 0; i < mChunkInfo.mNumChunks; i++) {
            EndianSwapEq(mChunkInfo.mChunks[i]);
        }
        EndianSwapEq(mChunkInfo.mID);
        EndianSwapEq(mChunkInfo.mChunkInfoSize);
        EndianSwapEq(mChunkInfo.mNumChunks);
        EndianSwapEq(mChunkInfo.mMaxChunkSize);
        i = mChunkInfo.mNumChunks;
        memset((void*)&mChunkInfo.mChunks[i], 0, (0x200 - i) * 4);
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
    if (mCurBufSize < mCurBufOffset + bytes) {

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

}

bool ChunkStream::Eof() {
    MILO_ASSERT(!mFail && mType == kRead, 552);
    if (mChunkInfoPending) {
        int x;
        if (mFile->ReadDone(x) == 0) return 2;
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

void ChunkStream::MaybeWriteChunk(bool b) {
    if (mChunkInfo.mNumChunks < 2 && 0x1fff < mCurBufOffset) b = true;


    if (mChunkInfo.mNumChunks > 0x200) MILO_FAIL("%s has %d chunks, max is %d", mFilename, mChunkInfo.mNumChunks, 0x200);
    WriteChunk();
}

void ChunkStream::DecompressChunk(DecompressTask& task) {
    MILO_ASSERT(*task.mState == kDecompressing, 955);
    int data = *task.mChunkSize & kChunkSizeMask;
    MILO_ASSERT((data & ~kChunkSizeMask) == 0, 959);
    int out_len = task.mOutLen;
    uint id = task.mID;
    if (id == 0xCDBEDEAF) {

    } else if (id == 0xCCBEDEAF) {

    } else {
        MILO_ASSERT(task.mID == CHUNKSTREAM_Z_ID, 977);
    }
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
