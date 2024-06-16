#pragma once

#include "os/AsyncFile.h"
#include "revolution/dvd/dvdfs.h"
#include "utl/MemMgr.h"

class AsyncFileHolmes : public AsyncFile {
    AsyncFileHolmes(const char*, int);
    virtual ~AsyncFileHolmes() { Terminate(); }
    virtual int GetFileHandle(DVDFileInfo*&);
    virtual int Truncate(int);
    virtual void _OpenAsync();
    virtual bool _OpenDone();
    virtual void _WriteAsync(const void*, int);
    virtual bool _WriteDone();
    virtual void _SeekToTell();
    virtual void _ReadAsync(void*, int);
    virtual bool _ReadDone();
    virtual void _Close();

    int mHolmesHandle;

    DELETE_OVERLOAD
};