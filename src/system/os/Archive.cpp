#include "Archive.h"
#include "os/Debug.h"
#include "utl/FileStream.h"
#include "math/Sort.h"

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
        arkhdr >> mGuid >> mNumArkfiles >> mArkfileSizes;
        if(version == 3){
            for(int i = 0; i < mArkfileSizes.size(); i++){
                mArkfileNames.push_back(String(MakeString("%s_%d.ark", mBasename, i)));
            }
        }
        else arkhdr >> mArkfileNames;

        if(version < 6){
            for(int i = 0; i < mArkfileSizes.size(); i++){
                mArkfileCachePriority.push_back(-1);
            }
        }
        else arkhdr >> mArkfileCachePriority;

        mHashTable.Read(arkhdr, heap_headroom);

        arkhdr >> mFileEntries;
    }
}

void Archive::GetGuid(HxGuid& g) const {
    g = mGuid;
}

const char* Archive::GetArkfileName(int i) const {
    MILO_ASSERT(i < mArkfileNames.size(), 1227);
    return mArkfileNames[i].c_str();
}