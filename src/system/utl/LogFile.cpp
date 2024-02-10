#include "LogFile.h"

LogFile::LogFile(const char* file_pattern) : mFilePattern(file_pattern), mSerialNumber(0), mDirty(0), mFile(0), mActive(0){

}

void LogFile::Reset(){
    AdvanceFile();
}

extern "C" void fn_802CF558(TextFileStream*);

void LogFile::Print(const char* str){
    if(mFile == 0) Reset();
    if(mFile != 0) {
        mFile->Print(str);
        fn_802CF558(mFile);
        mDirty = true;
    }
}

void LogFile::AdvanceFile(){
//     // Local variables
//     struct FileStat stat; // r1+0x8
//     const char * filename; // r31
}
