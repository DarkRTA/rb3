#include "utl/Chunks.h"
#include "utl/ChunkIDs.h"
#include "os/Debug.h"
#include <string.h>

void ChunkHeader::Read(BinStream& bs){
    bs.Read((void*)mID.Str(), 4);
    bs >> mLength;
    bool listCmp = strncmp(mID.Str(), kListChunkID.Str(), 4) == 0;
    if(!listCmp){
        bool riffCmp = strncmp(mID.Str(), kRiffChunkID.Str(), 4) == 0;
        if(!riffCmp){
            mIsList = false;
            return;
        }
    }
    bs.Read((void*)mID.Str(), 4);
    mIsList = true;
    mLength -= 4;
    MILO_ASSERT(mLength == 0 || mLength >= kDataHeaderSize, 0x26);
}

const char* listbegin = "LIST:";
const char* start = "<";
const char* end = ">";

IDataChunk::IDataChunk(IListChunk& chunk) : BinStream(true), mParent(&chunk), mBaseBinStream(chunk.mBaseBinStream), mHeader(0), mFailed(0), mEof(0) {
    MILO_ASSERT(mParent->CurSubChunkHeader(), 0x47);
    mHeader = new ChunkHeader(*mParent->CurSubChunkHeader());
    MILO_ASSERT(!mHeader->IsList(), 0x49);
    int tell = mBaseBinStream.Tell();
    mStartMarker = tell;
    mEndMarker = tell + mHeader->Length();
    mParent->Lock();
}

IDataChunk::~IDataChunk(){
    if(mParent) mParent->UnLock();
    delete mHeader;
}

void IDataChunk::SeekImpl(int iOffset, SeekType t){
    if(!Fail()){
        switch(t){
            case BinStream::kSeekBegin: 
                MILO_ASSERT(iOffset >= 0, 0x79);
                if(iOffset > mHeader->Length()) mFailed = true;
                mBaseBinStream.Seek(iOffset + mStartMarker, kSeekBegin);
                break;
            case BinStream::kSeekCur: 
                mBaseBinStream.Seek(iOffset, kSeekCur);
                break;
            case BinStream::kSeekEnd: 
                MILO_ASSERT(iOffset <= 0, 0x8A);
                if(iOffset < -mHeader->Length()) mFailed = true;
                mBaseBinStream.Seek(iOffset + mEndMarker, kSeekBegin);
                break;
            default: break;
        }
        mEof = mBaseBinStream.Eof() != 0;
    }
}

int IDataChunk::Tell(){
    if(Fail()) return -1;
    else return mBaseBinStream.Tell() - mStartMarker;
}

void IDataChunk::ReadImpl(void* data, int bytes){
    int tell = mBaseBinStream.Tell();
    if(bytes < mEndMarker - tell){
        mBaseBinStream.Read(data, bytes);
    }
    else {
        mBaseBinStream.Read(data, mEndMarker - tell);
        mEof = true;
    }
}

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

IListChunk::IListChunk(IListChunk& chunk) : mParent(&chunk), mBaseBinStream(chunk.mBaseBinStream), mHeader(0), mLocked(0), mSubHeader(), mRecentlyReset(1) {
    mHeader = new ChunkHeader(*mParent->CurSubChunkHeader());
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

ChunkHeader* IListChunk::Next(){
    MILO_ASSERT(!mLocked, 0x133);
    mRecentlyReset = false;
    if(mSubChunkMarker >= mEndMarker){
        mSubChunkValid = false;
        return 0;
    }
    else {
        mSubChunkValid = true;
        mBaseBinStream.Seek(mSubChunkMarker, BinStream::kSeekBegin);
        mSubHeader.Read(mBaseBinStream);
        int sublen = (mSubHeader.IsList()) ? 12 : 8;
        
        ChunkID theID = mSubHeader.mID;
        int newlen = mSubHeader.Length() + sublen;
        bool trackID = strncmp(theID.Str(), kMidiTrackChunkID.Str(), 4) == 0;
        if(!trackID){
            int tmp = newlen >> 0x1FU;
            newlen += ((newlen & 1) ^ tmp) - tmp;
        }

        mSubChunkMarker += newlen;
        return &mSubHeader;
    }
}

ChunkHeader* IListChunk::Next(ChunkID id){
    MILO_ASSERT(!mLocked, 0x155);
    while(Next()){
        ChunkID theID = mSubHeader.mID;
        bool sub = strncmp(id.Str(), theID.Str(), 4) == 0;
        if(sub) return &mSubHeader;
    }
    return 0;
}

void IListChunk::Lock(){
    MILO_ASSERT(mLocked == false, 0x165);
    mLocked = true;
}

void IListChunk::UnLock(){
    MILO_ASSERT(mLocked == true, 0x16F);
    mLocked = false;
}
