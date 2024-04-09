#ifndef OBJ_DATAFILE_H
#define OBJ_DATAFILE_H

#include "obj/Data.h"

extern "C" void DataFail(const char*);
extern "C" int DataInput(void*, int);
int ReadEmbeddedFile(const char*, bool);
DataArray* DataReadFile(const char*, bool);
void DataWriteFile(const char*, const DataArray*, int);
void* LoadDtz(const char*, int);

#endif
