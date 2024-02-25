#include "os/File.h"
#include "obj/Data.h"
#include "os/OSFuncs.h"
#include "os/Debug.h"

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

static DataNode OnFileGetBase(DataArray* da){
    return DataNode(FileGetBase(da->Str(1), 0));
}

static DataNode OnFileGetExt(DataArray* da){
    return DataNode(FileGetExt(da->Str(1)));
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

const char* FileGetBase(const char* file, char* base){
    static char my_path[256];
    const char* dir;
    char* ext;
    if(base == 0 && !MainThread())
        MILO_WARN("FileGetBase called from !MainThread with \"%s\"\n", file);
    if(base == 0) base = my_path;
    dir = strrchr(file, '/');
    if((dir != 0) || (dir = strrchr(file, '\\'), (dir != 0)))
        strcpy(base, dir + 1);
    else strcpy(base, file);
    ext = strrchr(base, '.');
    if(ext != 0) *ext = 0;
    return base;
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
