#ifndef OBJ_DATAFILE_H
#define OBJ_DATAFILE_H

#include "obj/Data.h"
#include "os/ThreadCall.h"
#include "utl/Loader.h"

class DataLoader : public Loader {
public:
    DataLoader(const FilePath&, LoaderPos, bool);
    virtual ~DataLoader();
    virtual bool IsLoaded() const;
    virtual void PollLoading();

    DataArray* Data();
    void OpenFile();
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
    void (DataLoader::*ptmf)(void); // 0x3C
};

class DataLoaderThreadObj : public ThreadCallback {
    public:
    DataLoaderThreadObj(DataLoader* dl, DataArray* da, File* fi, int sz, const char* s, void* _mem, bool b) : unk4(dl), 
        unk8(da), unkc(fi), mem(_mem), fsize(sz), unk18(s), unk1c(b) {}
    virtual ~DataLoaderThreadObj();
    virtual void ThreadStart();
    virtual void ThreadDone(int);

    DataLoader* unk4; // 0x4
    DataArray* unk8; // 0x8
    File* unkc; // 0xC
    void* mem; // 0x10
    int fsize; // 0x14
    const char* unk18;
    bool unk1c;
};

extern "C" void DataFail(const char*);
extern "C" int DataInput(void*, int);
DataArray* ReadCacheStream(BinStream&, const char*);
DataArray* ReadEmbeddedFile(const char*, bool);
DataArray* DataReadFile(const char*, bool);
DataArray* DataReadStream(BinStream*);
DataArray* ParseArray();
void DataWriteFile(const char*, const DataArray*, int);
void* LoadDtz(const char*, int);

void BeginDataRead();
void FinishDataRead();

#endif
