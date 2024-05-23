#ifndef OBJ_DATAFILE_H
#define OBJ_DATAFILE_H

#include "obj/Data.h"
#include "utl/Loader.h"

class DataLoader : public Loader {
public:
    DataLoader(const FilePath&, LoaderPos, bool);
    virtual bool IsLoaded() const;
    virtual void PollLoading();

    int unk14;
    String unk18;
    int unk24;
    int unk28;
    int unk2c;
    int unk30;
    bool unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
};

extern "C" void DataFail(const char*);
extern "C" int DataInput(void*, int);
DataArray* ReadEmbeddedFile(const char*, bool);
DataArray* DataReadFile(const char*, bool);
DataArray* DataReadStream(BinStream*);
DataArray* ParseArray();
void DataWriteFile(const char*, const DataArray*, int);
void* LoadDtz(const char*, int);

void BeginDataRead();
void FinishDataRead();

#endif
