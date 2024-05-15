#ifndef OBJ_DATAFILE_H
#define OBJ_DATAFILE_H

#include "obj/Data.h"
#include "utl/Loader.h"

extern "C" void DataFail(const char*);
extern "C" int DataInput(void*, int);
DataArray* ReadEmbeddedFile(const char*, bool);
DataArray* DataReadFile(const char*, bool);
DataArray* DataReadStream(BinStream*);
DataArray* ParseArray();
void DataWriteFile(const char*, const DataArray*, int);
void* LoadDtz(const char*, int);

class DataLoader : public Loader {
public:
    DataLoader(const FilePath&, LoaderPos, bool);
    virtual bool IsLoaded() const;
    virtual void PollLoading();
};

#endif
