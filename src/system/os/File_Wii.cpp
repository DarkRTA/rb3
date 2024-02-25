#include "os/File_Wii.h"
#include "os/Debug.h"

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

int FileDelete(){ return -1; }
int FileMkDir(){ return -1; }
