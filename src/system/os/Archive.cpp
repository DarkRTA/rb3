#include "Archive.h"
#include "os/Debug.h"
#include "utl/FileStream.h"

ArkHash::ArkHash() {

}

Archive::Archive(const char* c, int i) : mArkName(c), i(0), b(false) {Read(i);} 

void Archive::GetFileInfo(const char*, int&, unsigned long long&, int&, int&) {
    
}

BinStream& operator>>(BinStream& bs, FileEntry& f) {
    bs >> f.mOffset;
    bs >> f.mFilename;
    bs >> f.unk_c;
    /*if (f.mOffset.notbig.lo < 0) {
        MILO_FAIL("operator>>(BinStream&,FileEntry&): file offset > 32 bits. will overflow FileEntryWiiShip::mOffset. high dword:0x%08x)\n", f.mOffset.notbig.hi);
    }*/
    return bs;
}

void Archive::Read(int i) {
    TheDebug << "Reading the archive\n";
    FileStream arkhdr(MakeString("%s.hdr", mArkName), FileStream::kReadNoArk, true);
    MILO_ASSERT(!arkhdr.Fail(), 723);
    arkhdr.EnableReadEncryption();
    int x; arkhdr >> x;
    if (x == 6) {
        MILO_FAIL(" ERROR: %s  unsupported archive version %d", mArkName, x);
        return;
    }
    arkhdr >> mGuid;
    arkhdr >> unk_0;
    arkhdr >> unk_4;
}

void Archive::GetGuid(HxGuid& g) const {
    g = mGuid;
}

const char* Archive::GetArkfileName(int i) const {
    MILO_ASSERT(i < mFilenames.size(), 1227);
    return mFilenames[i].c_str();
}