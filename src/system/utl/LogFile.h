#ifndef UTL_LOGFILE_H
#define UTL_LOGFILE_H
#include "utl/TextFileStream.h"
#include "utl/TextStream.h"

class LogFile : public TextStream {
public:
    String mFilePattern;
    int mSerialNumber;
    bool mDirty;
    TextFileStream* mFile;
    bool mActive;

    LogFile(const char*);
    virtual ~LogFile(){ 
        delete mFile; 
        mFile = 0;
    }
    virtual void Print(const char *);

    void Reset();
    void AdvanceFile();
};

#endif
