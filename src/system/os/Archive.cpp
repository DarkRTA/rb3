#include "Archive.h"
#include "os/Debug.h"
#include "utl/FileStream.h"
#include "math/Sort.h"

bool gDebugArkOrder = false;
int kArkBlockSize = 0x10000;

ArkHash::ArkHash() : mHeap(0), mHeapEnd(0), mFree(0), mTable(0), mTableSize(0) {

}

int ArkHash::GetHashValue(const char* c) const {
    int hashIdx = HashString(c, mTableSize);
    MILO_ASSERT(hashIdx < mTableSize, 0x107);
    while(mTable[hashIdx]){
        if(strcmp(mTable[hashIdx], c) == 0) return hashIdx;
        if(++hashIdx == mTableSize) hashIdx = 0;
    }
    return -1;
}

Archive::Archive(const char* c, int i) : mBasename(c), mMode(kRead), mIsPatched(false){
    Read(i);
}

void Archive::GetFileInfo(const char* file, int& arkfileNum, unsigned long long& byteOffset, int& fileSize, int& fileUCSize) {
    
}

BinStream& operator>>(BinStream& bs, FileEntry& f) {
    bs >> f.mOffset >> f.mHashedName >> f.mHashedPath >> f.mSize >> f.mUCSize;
    if(f.mOffset != 0){
        MILO_FAIL("operator>>(BinStream&,FileEntry&): file offset > 32 bits. will overflow FileEntryWiiShip::mOffset. high dword:0x%08x)\n", f.mOffset);
    }
    return bs;
}

void Archive::Read(int heap_headroom) {
    TheDebug << MakeString("Reading the archive\n");
    FileStream arkhdr(MakeString("%s.hdr", mBasename), FileStream::kReadNoArk, true);
    MILO_ASSERT(!arkhdr.Fail(), 723);
    arkhdr.EnableReadEncryption();
    int version;
    arkhdr >> version;
    if(version != 6){
        MILO_FAIL(" ERROR: %s  unsupported archive version %d", mBasename, version);
        return;
    }
    else {
        arkhdr >> mGuid;
        arkhdr >> mNumArkfiles >> mArkfileSizes;

        if(version == 3){
            for(int i = 0; i < mArkfileSizes.size(); i++){
                mArkfileNames.push_back(String(MakeString("%s_%d.ark", mBasename, i)));
            }
        }
        else arkhdr >> mArkfileNames;

        if(version > 5) arkhdr >> mArkfileCachePriority;
        else {
            for(int i = 0; i < mArkfileSizes.size(); i++){
                mArkfileCachePriority.push_back(-1);
            }
        }

        mHashTable.Read(arkhdr, heap_headroom);

        arkhdr >> mFileEntries;
    }
}

bool Archive::DebugArkOrder(){ return gDebugArkOrder; }

bool Archive::HasArchivePermission(int i) const {
    for(int x = unk64, idx = 0; x > 0; x--, idx++){
        if(i == unk60[idx]) return true;
    }
    return false;
}

void Archive::SetArchivePermission(int i, const int* ci){
    unk64 = i;
    unk60 = ci;
}

int Archive::GetArkfileCachePriority(int arkfileNum) const {
    MILO_ASSERT(arkfileNum < mArkfileCachePriority.size(), 0x4BB);
    return mArkfileCachePriority[arkfileNum];
}

int Archive::GetArkfileNumBlocks(int file) const {
    return (mArkfileSizes[file] - 1) / kArkBlockSize + 1;
}

void Archive::GetGuid(HxGuid& g) const {
    g = mGuid;
}

const char* Archive::GetArkfileName(int i) const {
    MILO_ASSERT(i < mArkfileNames.size(), 1227);
    return mArkfileNames[i].c_str();
}