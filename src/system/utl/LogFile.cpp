#include "utl/LogFile.h"

LogFile::LogFile(const char* file_pattern) : mFilePattern(file_pattern), mSerialNumber(0), mDirty(0), mFile(0), mActive(0){

}

void LogFile::Reset(){
    AdvanceFile();
}

void LogFile::Print(const char* str){
    if(mFile == 0) Reset();
    if(mFile != 0) {
        mFile->Print(str);
        mFile->mFile.Flush();
        mDirty = true;
    }
}
