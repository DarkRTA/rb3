#ifndef OS_MAPFILEWII_H
#define OS_MAPFILEWII_H
#include "utl/Str.h"
#include "os/File.h"

class WiiMapFile {
public:
    WiiMapFile(const char*);
    ~WiiMapFile();
    const char* GetFunction(unsigned int, bool);
    void ReadLine(char*, int);

    static bool ParseStack(const char*, unsigned int*, int, char*);

    File* mFile;
    int mStart;
};

bool HasMoreParams(String);
int GetVarLength(String&);
void AddParams(String&, String&, String);

void TryDemangleParams(String&, String&, String, String);
void TryDemangleClassAndFunc(String);
void TryDemangle(char*, const char*, bool);

#endif
