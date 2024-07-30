#include "os/File.h"
#include "obj/Data.h"
#include "os/OSFuncs.h"
#include "os/Debug.h"
#include "utl/FilePath.h"
#include <vector>
#include "os/System.h"
#include "utl/Loader.h"
#include "obj/DataFunc.h"
#include "utl/Option.h"

int File::sOpenCount[4];
std::vector<File*> gFiles;
File* gOpenCaptureFile;
int gCaptureFileMode;
static char gRoot[256];
static char gExecRoot[256];
static char gSystemRoot[256];
std::vector<String> gDirList;
int kNoHandle;
DataArray* gFrameRateArray;
bool gNullFiles;

void DirListCB(const char* cc1, const char* cc2){
    gDirList.push_back(String(cc2));
}

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

static DataNode OnFileMatch(DataArray* da){
    return DataNode(FileMatch(da->Str(1), da->Str(2)));
}

static DataNode OnFileAbsolutePath(DataArray* da){
    return DataNode(FileMakePath(da->Str(1), da->Str(2), 0));
}

static DataNode OnFileRelativePath(DataArray* da){
    return DataNode(FileRelativePath(da->Str(1), da->Str(2)));
}

static DataNode OnWithFileRoot(DataArray* da){
    FilePathTracker fpt(da->Str(1));
    int i;
    int thresh = da->Size() - 1;
    for(i = 2; i < thresh; i++){
        da->Command(i)->Execute();
    }
    DataNode ret = da->Evaluate(i);
    return ret;
}

static DataNode OnSynchProc(DataArray* da){
    TheDebug.Fail(MakeString("calling synchproc on non-pc platform"));
    return DataNode("");
}

static DataNode OnToggleFakeFileErrors(DataArray* da){
    return DataNode(0);
}

void OnFrameRateRecurseCB(const char* cc1, const char* cc2){
    MILO_ASSERT(gFrameRateArray, 0x148);
    String str(cc2);
    const char* keepStr = MakeString("_keep_%s.dta", PlatformSymbol(TheLoadMgr.GetPlatform()));
    int theStrLen = strlen(str.c_str());
    int keepLen = strlen(keepStr);
    str = str.substr(0, theStrLen - keepLen);
    gFrameRateArray->Insert(gFrameRateArray->Size(), DataNode(str));
}

static DataNode OnEnumerateFrameRateResults(DataArray* da){
    DataNode ret(new DataArray(0), kDataArray);
    gFrameRateArray = ret.Array(0);
    FileRecursePattern(MakeString("ui/framerate/venue_test/*%s", MakeString("_keep_%s.dta", PlatformSymbol(TheLoadMgr.GetPlatform()))), OnFrameRateRecurseCB, false);
    gFrameRateArray = 0;
    return ret;
}

extern void HolmesClientInit();

void FileInit(){
    strcpy(gRoot, ".");
    strcpy(gExecRoot, ".");
    strcpy(gSystemRoot, FileMakePath(gExecRoot, "../../system/run", 0));
    FilePath::sRoot.Set(gRoot, gRoot);
    DataRegisterFunc("file_root", OnFileRoot);
    DataRegisterFunc("file_exec_root", OnFileExecRoot);
    DataRegisterFunc("file_get_drive", OnFileGetDrive);
    DataRegisterFunc("file_get_path", OnFileGetPath);
    DataRegisterFunc("file_get_base", OnFileGetBase);
    DataRegisterFunc("file_get_ext", OnFileGetExt);
    DataRegisterFunc("file_match", OnFileMatch);
    DataRegisterFunc("file_absolute_path", OnFileAbsolutePath);
    DataRegisterFunc("file_relative_path", OnFileRelativePath);
    DataRegisterFunc("with_file_root", OnWithFileRoot);
    DataRegisterFunc("synch_proc", OnSynchProc);
    DataRegisterFunc("toggle_fake_file_errors", OnToggleFakeFileErrors);
    DataRegisterFunc("enumerate_frame_rate_results", OnEnumerateFrameRateResults);
    HolmesClientInit();
    const char* optionStr = OptionStr("file_order", 0);
    if(optionStr && *optionStr){
        gOpenCaptureFile = NewFile(optionStr, 0xA04);
        MILO_ASSERT(gOpenCaptureFile, 0x1AE);
    }
}

void FileTerminate(){
    delete gOpenCaptureFile;
    gOpenCaptureFile = 0;
    *gRoot = 0;
    *gExecRoot = 0;
    *gSystemRoot = 0;
}

File* NewFile(const char* cc, int i){
    File* retFile = 0;
    if(gNullFiles){
        return new NullFile();
    }
    else {
        if(!MainThread()){
            MILO_WARN("NewFile(%s) from !MainThread()", cc);
        }
        if(!cc || !*cc) return 0;
        else {
            if(strstr(cc, "/band3_ng/")){
                MILO_WARN("Loading files from the wrong branch: %s", cc);
                return 0;
            }
            else {
                
            }
        }
    }
}

bool FileExists(const char* filepath, int iMode){
    MILO_ASSERT((iMode & ~FILE_OPEN_NOARK) == 0, 0x2D5);
    File* theFile = NewFile(filepath, iMode | 0x40002);
    if(theFile){
        delete theFile;
        return true;
    }
    else return false;
}

bool FileReadOnly(const char*){ return true; }

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

static bool FileMatchInternal(const char *arg0, const char *arg1, bool arg2) {
    for (; *arg0 != 0; arg0++) {
        if (FileMatch(arg0, arg1))
            return true;
        if (!arg2 && (*arg0 == '/' || *arg0 == '\\'))
            return false;
    }
    return (*arg1 == *arg0);
}

bool FileMatch(const char *param1, const char *param2) {
    if (param2 == 0)
        return false;
    while (*param2 != '\0') {
        if (*param2 == '*')
            return FileMatchInternal(param1, param2 + 1, 0);
        if (*param2 == '&')
            return FileMatchInternal(param1, param2 + 1, 1);
        if (*param1 == '\0')
            break;
        if (*param2 == '?') {
            if ((*param1 == '\\') || (*param1 == '/'))
                return 0;
        } else if ((*param2 == '/') || (*param2 == '\\')) {
            if ((*param1 != '/') && (*param1 != '\\'))
                return 0;
        } else if (*param2 != *param1)
            return 0;
        param2++;
        param1++;
    }
    return (*param2 - *param1) == 0;
}
