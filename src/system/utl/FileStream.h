#ifndef UTL_FILESTREAM_H
#define UTL_FILESTREAM_H
#include "os/File.h"
#include "utl/BinStream.h"
#include "utl/Str.h"
#include "math/StreamChecksum.h"
#include "utl/MemMgr.h"

class FileStream : public BinStream {
public:
    enum FileType {
        kRead = 0,
        kWrite = 1,
        kReadNoArk = 2,
        kAppend = 3,
    };

    FileStream(const char *, FileType, bool);
    FileStream(File *, bool);
    virtual ~FileStream();
    virtual void Flush();
    virtual int Tell();
    virtual EofType Eof();
    virtual bool Fail();
    virtual const char *Name() const;
    virtual void ReadImpl(void *, int);
    virtual void WriteImpl(const void *, int);
    virtual void SeekImpl(int, SeekType);

    void DeleteChecksum();
    void StartChecksum();
    bool ValidateChecksum();

    int Size() { return (mFile) ? mFile->Size() : 0; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    File *mFile;
    class String mFilename;
    bool mFail;
    StreamChecksumValidator *mChecksumValidator;
    int mBytesChecksummed;
};

#endif
