#include "os/File.h"
#include "obj/Data.h"

static char gRoot[256];
static char gExecRoot[256];
static char gSystemRoot[256];

const char* FileRoot(){
    return gRoot;
}

const char* FileExecRoot(){
    return gExecRoot;
}

const char* FileSystemRoot(){
    return gSystemRoot;
}

static DataNode OnFileExecRoot(DataArray* da){
    return DataNode(gExecRoot);
}

static DataNode OnFileRoot(DataArray* da){
    return DataNode(gRoot);
}

static DataNode OnFileGetDrive(DataArray* da){
    return DataNode(FileGetDrive(da->Str(1)));
}

static DataNode OnFileGetPath(DataArray* da){
    return DataNode(FileGetPath(da->Str(1), 0));
}

const char* FileGetPath(const char* arg1, char* arg2){
    static char static_path[256];
    char *p2;
    if (arg2 == 0)
        arg2 = static_path;
    if (arg1 != 0) {
        strcpy(arg2, arg1);
        p2 = arg2 + strlen(arg2);
        p2--;
        while (p2 >= arg2 && *p2 != '/' && *p2 != '\\') {
            p2--;
        }
        if (p2 >= arg2) {
            if ((p2 == arg2) || (p2[-1] == ':'))
                p2[1] = '\0';
            else
                *p2 = '\0';
            return arg2;
        }
    }
    *arg2 = '.';
    arg2[1] = '\0';
    return arg2;
}

const char* FileGetExt(const char* root) {
    const char *end = root + strlen(root);
    for (const char *search = end - 1; search >= root; search--) {
        if (*search == '.') {
            return search + 1;
        } else if (*search == '/' || *search == '\\') {
            return end;
        }
    }
    return end;
}

const char* FileGetDrive(const char* file){
    static char drive[256];
    const char* p = strchr(file, ':');
    if(p != 0){
        strncpy(drive, file, p - file);
        drive[p - file] = '\0';
    }
    else drive[0] = '\0';
    return drive;
}

const char* FileGetName(const char* file){
    static char path[256];
    const char* dir = strrchr(file, '/');
    if((dir != 0) || (dir = strrchr(file, '\\'), (dir != 0))){
        strcpy(path, dir + 1);
    }
    else strcpy(path, file);
    return path;
}
