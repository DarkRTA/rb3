#include "utl/LogFile.h"
#include "os/File_Wii.h"
#include "utl/MakeString.h"

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

void LogFile::AdvanceFile(){
    FileStat stat;
    if(mDirty || !mFile){
        delete mFile;
        mFile = 0;
        const char* str;
        while(true){
            str = MakeString(mFilePattern.mStr, mSerialNumber);
            if(FileGetStat(str, &stat) < 0) break;
            mSerialNumber++;
        }
        mFile = new TextFileStream(str, false);
        mDirty = false;
    }
}
