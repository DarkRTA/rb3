#include "utl/FileStream.h"

FileStream::FileStream(File* f, bool b) : BinStream(b), mFilename(), mChecksum(0), mBytesChecksummed(0) {
    mFile = f;
    mFail = false;
}

FileStream::~FileStream(){
    if(*mFilename.c_str() != '\0'){
        delete mFile;
    }    
    DeleteChecksum();
}
