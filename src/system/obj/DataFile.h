#ifndef OBJ_DATAFILE_H
#define OBJ_DATAFILE_H

#include "obj/Data.h"
#include "os/ThreadCall.h"
#include "utl/Loader.h"

class DataLoader;
typedef void(DataLoader::*DataLoaderStateFunc)(void);

class DataLoader : public Loader {
public:
    DataLoader(const FilePath&, LoaderPos, bool);
    virtual ~DataLoader();
    virtual bool IsLoaded() const;
    virtual const char* StateName() const { return "DataLoader"; }
    virtual void PollLoading();
    virtual void OpenFile();

    DataArray* Data();
    void LoadFile();
    void DoneLoading();
    void ThreadDone(DataArray*);

    String unk18;
    DataArray* unk24;
    File* fileobj;
    int filesize; // 0x2C
    void* unk30;
    bool unk34;
    class DataLoaderThreadObj* unk38;
    DataLoaderStateFunc ptmf; // 0x3C
};

class DataLoaderThreadObj : public ThreadCallback {
    public:
    DataLoaderThreadObj(DataLoader* dl, File* fi, void* _mem, int sz, bool b, const char* s) : unk4(dl),
        unk8(0), unkc(fi), mem(_mem), fsize(sz), unk18(s), unk1c(b) {}
    virtual ~DataLoaderThreadObj(){}
    virtual int ThreadStart();
    virtual void ThreadDone(int);

    DataLoader* unk4; // 0x4
    DataArray* unk8; // 0x8
    File* unkc; // 0xC
    int fsize; // 0x10
    void* mem; // 0x14
    const char* unk18; // 0x18
    bool unk1c; // 0x1c
};

DataArray* ReadCacheStream(BinStream&, const char*);
DataArray* ReadEmbeddedFile(const char*, bool);
DataArray* DataReadFile(const char*, bool);
DataArray* DataReadStream(BinStream*);
DataArray* ParseArray();
void DataWriteFile(const char*, const DataArray*, int);
DataArray* LoadDtz(const char*, int);

void BeginDataRead();
void FinishDataRead();

#endif
