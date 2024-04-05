#ifndef OBJ_DATAFILE_H
#define OBJ_DATAFILE_H

extern "C" void DataFail(const char*);
extern "C" int DataInput(void*, int);
int ReadEmbeddedFile(const char*, bool);
int DataReadFile(const char*, bool);
void* LoadDtz(const char*, int);

#endif
