#include "os/File_Wii.h"
#include "os/Archive.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/HolmesClient.h"
#include "os/System.h"
#include "revolution/dvd/dvd.h"
#include "revolution/dvd/dvdfs.h"
#include <cstring>

bool FileIsLocal(const char* file){
    return FileIsDLC(file);
}

bool FileIsDLC(const char* file){
    bool nand = !strncmp(file, "nand/", 5);
    if(nand){
        MILO_WARN("File accessed via nand/ path %s", file);
        return true;
    }
    else return !strncmp(file, "dlc/", 4);
}

int FileGetStat(const char* iFilename, FileStat* iBuffer) {
    String s;
    FileQualifiedFilename(s, iFilename);
    if (UsingCD()) {
        DVDFileInfo fi;
        if (DVDOpen(const_cast<char*>(s.c_str()), &fi)) {
            iBuffer->st_ctime = 1000;
            iBuffer->st_atime = 1000;
            iBuffer->st_mtime = 1000;
            iBuffer->st_mode = 0;
            iBuffer->st_size = fi.length;
            DVDClose(&fi);
            return 0;
        } else return -1;
    } else {
        iBuffer = HolmesClientGetStat(s.c_str(), *iBuffer);
        return (int)iBuffer;
    }
}

int FileDelete(){ return -1; }
int FileMkDir(){ return -1; }

void FileEnumerate(const char* c1, void(*v)(const char*, const char*), bool b1, const char* c2, bool b2) {
    if (UsingCD()) TheArchive->Enumerate(c1, v, b1, c2);
    else HolmesClientEnumerate(c1, v, b1, c2, b2);
}

void FileQualifiedFilename(char* out, int, const char* in) {
    MILO_ASSERT(in && out, 173);
    if (UsingCD()) strcpy(out, in);
    else {
        String s(in);
        strcpy(out, FileMakePath(HolmesFileShare(), s.c_str(), NULL));
        for (;*out != 0; ) {
            if (*out == '/') *out = '\\';
            out++;
        }
    }
}
