#include "os/File.h"
#include "obj/Data.h"
#include "os/OSFuncs.h"
#include "os/ArkFile.h"
#include "os/AsyncFile.h"
#include "os/Debug.h"
#include "utl/FilePath.h"
#include <vector>
#include "os/BlockMgr.h"
#include "os/System.h"
#include "os/FileCache.h"
#include "os/PlatformMgr.h"
#include "utl/Loader.h"
#include "obj/DataFunc.h"
#include "utl/Option.h"
#include <ctype.h>

std::vector<File *> gFiles(0x80); // 0x10...?
File *gOpenCaptureFile; // 0x18
int gCaptureFileMode;
static char gRoot[256]; // 0x20
static char gExecRoot[256]; // 0x120
static char gSystemRoot[256]; // 0x220
std::vector<String> gDirList;
int kNoHandle;
DataArray *gFrameRateArray;
bool gNullFiles;
const int File::MaxFileNameLen = 0x100;

void DirListCB(const char *cc1, const char *cc2) {
    gDirList.push_back(String(cc2));
}

#pragma push
#pragma force_active on
inline const char *FileRoot() {
    return gRoot;
}
#pragma pop

const char *FileExecRoot() {
    return gExecRoot;
}

const char *FileSystemRoot() {
    return gSystemRoot;
}

static DataNode OnFileExecRoot(DataArray *da) {
    return gExecRoot;
}

static DataNode OnFileRoot(DataArray *da) {
    return gRoot;
}

static DataNode OnFileGetDrive(DataArray *da) {
    return FileGetDrive(da->Str(1));
}

static DataNode OnFileGetPath(DataArray *da) {
    return FileGetPath(da->Str(1), 0);
}

static DataNode OnFileGetBase(DataArray *da) {
    return FileGetBase(da->Str(1), 0);
}

static DataNode OnFileGetExt(DataArray *da) {
    return FileGetExt(da->Str(1));
}

static DataNode OnFileMatch(DataArray *da) {
    return FileMatch(da->Str(1), da->Str(2));
}

static DataNode OnFileAbsolutePath(DataArray *da) {
    return FileMakePath(da->Str(1), da->Str(2), 0);
}

static DataNode OnFileRelativePath(DataArray *da) {
    return FileRelativePath(da->Str(1), da->Str(2));
}

static DataNode OnWithFileRoot(DataArray *da) {
    FilePathTracker fpt(da->Str(1));
    int thresh = da->Size() - 1;
    int i;
    for (i = 2; i < thresh; i++) {
        da->Command(i)->Execute();
    }
    DataNode ret = da->Evaluate(i);
    return ret;
}

static DataNode OnSynchProc(DataArray *da) {
    MILO_FAIL("calling synchproc on non-pc platform");
    return "";
}

static DataNode OnToggleFakeFileErrors(DataArray *da) {
    return 0;
}

DECOMP_FORCEACTIVE(File, "_keep_%s.dta")

void OnFrameRateRecurseCB(const char *cc1, const char *cc2) {
    MILO_ASSERT(gFrameRateArray, 0x148);
    String str(cc2);
    const char *keepStr =
        MakeString("_keep_%s.dta", PlatformSymbol(TheLoadMgr.GetPlatform()));
    int theStrLen = strlen(str.c_str());
    int keepLen = strlen(keepStr);
    str = str.substr(0, theStrLen - keepLen);
    gFrameRateArray->Insert(gFrameRateArray->Size(), DataNode(str));
}

static DataNode OnEnumerateFrameRateResults(DataArray *da) {
    DataNode ret(new DataArray(0), kDataArray);
    gFrameRateArray = ret.Array();
    FileRecursePattern(
        MakeString(
            "ui/framerate/venue_test/*%s",
            MakeString("_keep_%s.dta", PlatformSymbol(TheLoadMgr.GetPlatform()))
        ),
        OnFrameRateRecurseCB,
        false
    );
    gFrameRateArray = 0;
    return ret;
}

extern void HolmesClientInit();

void FileInit() {
    strcpy(gRoot, ".");
    strcpy(gExecRoot, ".");
    strcpy(gSystemRoot, FileMakePath(gExecRoot, "../../system/run", 0));
    ResetRoot(gRoot);
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
#ifdef MILO_DEBUG
    DataRegisterFunc("toggle_fake_file_errors", OnToggleFakeFileErrors);
    DataRegisterFunc("enumerate_frame_rate_results", OnEnumerateFrameRateResults);
    HolmesClientInit();
#endif
    const char *optionStr = OptionStr("file_order", 0);
    if (optionStr && *optionStr) {
        gOpenCaptureFile = NewFile(optionStr, 0xA04);
        MILO_ASSERT(gOpenCaptureFile, 0x1AE);
    }
}

void FileTerminate() {
    RELEASE(gOpenCaptureFile);
    *gRoot = 0;
    *gExecRoot = 0;
    *gSystemRoot = 0;
}

File *NewFile(const char *cc, int i) {
#ifdef MILO_DEBUG
    if(gNullFiles) return new NullFile();
#endif
    if (!MainThread()) {
        MILO_WARN("NewFile(%s) from !MainThread()", cc);
    }
    if (!cc || !*cc) return nullptr;
    else {
        if (strstr(cc, "/band3_ng/")) {
            MILO_WARN("Loading files from the wrong branch: %s", cc);
            return nullptr;
        } else {
            if(!ThePlatformMgr.AreSFXEnabled() && strstr(cc, ".wav")) return nullptr;
            else if(strstr(cc, "_norm.")) return nullptr;
            else if(strstr(cc, "_spec.")) return nullptr;
            else {
                if(i & 2U){
                    char buf[256];
                    cc = FileLocalize(cc, buf);
                }
                if(FileIsLocal(cc)) i |= 0x10000;

                File *retFile;
                if(i & 2U && !(i & 0x20000U)){
                    retFile = FileCache::GetFileAll(cc);
                    if(retFile) return retFile;
                }
                if(UsingCD() && i & 2U && !(i & 0x10000U)){
                    retFile = new ArkFile(cc, i);
                }
                else {
                    i &= 0xfffcffff;
                    retFile = AsyncFile::New(cc, i);
                }
                if(retFile->Fail()){
                    RELEASE(retFile);
                    return retFile;
                }
                else {
                    if(gOpenCaptureFile != 0 && i & 2U && gCaptureFileMode == 0){
                        char buf[256];
                        sprintf(buf, "'%s'\n", FileMakePath(".", cc, 0));
                        gOpenCaptureFile->Write(buf, strlen(buf));
                        gOpenCaptureFile->Flush();
                    }
                }
                return retFile;
            }
        }
    }
}

bool FileExists(const char *filepath, int iMode) {
    MILO_ASSERT((iMode & ~FILE_OPEN_NOARK) == 0, 0x2D5);
    File *theFile = NewFile(filepath, iMode | 0x40002);
    if (theFile) {
        delete theFile;
        return true;
    } else
        return false;
}

bool FileReadOnly(const char *) {
    return true;
}

void FileQualifiedFilename(String& str, const char* cc){
    char buf[256];
    FileQualifiedFilename(buf, 0x100, cc);
    str = buf;
}

void FileNormalizePath(const char* cc){
    for(char* ptr = (char*)cc; *ptr != '\0'; ptr++){
        if(*ptr == '\\') *ptr = '/';
        else *ptr = tolower(*ptr);
    }
}

const char* FileMakePath(const char* root, const char* file, char* buffer){
    MILO_ASSERT(root && file, 800);
    if(!buffer){
        static char static_buffer[256];
        buffer = static_buffer;
    }
    char buf[256];
    if(file >= buffer && file < buffer + 4){
        strcpy(buf, file);
        file = buf;
    }
    else if(root >= buffer && root < buffer + 4){
        strcpy(buf, root);
        root = buf;
    }
    const char* fileDrive = FileGetDrive(file);
    if(*fileDrive != '\0'){
        file += strlen(fileDrive) + 1;
    }
    char* c = buffer;
    if(*file == '/' || *file == '\\' || *file == '\0'){
        if(*fileDrive != '\0'){
            sprintf(buffer, "%s:%s", buffer, file);
            c = buffer + strlen(fileDrive) + 1;
        }
        else {
            const char* rootDrive = FileGetDrive(root);
            if(*rootDrive != '\0'){
                sprintf(buffer, "%s:%s", buffer, file);
                c = buffer + strlen(rootDrive) + 1;
            }
            else strcpy(buffer, file);
        }
    }
    else {
        sprintf(buffer, "%s/%s", root, file);
        const char* rootDrive = FileGetDrive(root);
        if(*rootDrive != '\0'){
            c = buffer + strlen(rootDrive) + 1;
        }
    }
    FileNormalizePath(buffer);
    char curC3Ptr = *c;
    char* dirs[32];
    const char** endDir = (const char**)&dirs[0];
    for(char* p = (char*)strtok(c, "/"); p != nullptr; p = strtok(nullptr, "/")){
        if(*p != '.') *endDir++ = p;
        else if(p[1] == '.' && p[2] == '\0'){
            if(endDir != dirs && *endDir[-1] != '.') endDir--;
            else *endDir++ = p;
        }
    }
    MILO_ASSERT(endDir - dirs <= 32, 0x37D);
    if(endDir == dirs){
        if(curC3Ptr == '/'){
            *c++ = '/';
        }
        else *c++ = '.';
    }
    else {
        for(const char** dir = (const char**)&dirs[0]; dir != endDir; dir++){
            if(dir != dirs || curC3Ptr == '/'){
                *c++ = '/';
            }
            for(char* p = (char*)*dir; *p != '\0'; p++){
                *c++ = *p;
            }
        }
    }
    MILO_ASSERT(c - buffer < File::MaxFileNameLen, 0x393);
    *c = '\0';
    return buffer;
}

const char* FileRelativePath(const char* root, const char* filepath){
    MILO_ASSERT(root && filepath, 0x3A3);
    if(*filepath == nullptr) return filepath;
    char rootBuf[256];
    char fpBuf[256];
    strcpy(rootBuf, root);
    strcpy(fpBuf, filepath);
    std::list<const char*> list218;
    std::list<const char*> list220;
    for(const char* tok = strtok(rootBuf, "/"); tok != nullptr; tok = strtok(nullptr, "/")){
        list218.push_back(tok);
    }
    for(const char* tok = strtok(fpBuf, "/"); tok != nullptr; tok = strtok(nullptr, "/")){
        list220.push_back(tok);
    }
    static char relative[256];
    if(!list220.empty() && !list218.empty()){
        if(strcmp(list220.back(), list218.back()) != 0) return filepath;
        while(list218.size() != 0 && list220.size() != 0 &&
            strcmp(list220.back(), list218.back()) == 0){
            list218.pop_back();
            list220.pop_back();
        }
        char* p = relative;
        while(list218.size() != 0){
            if(p != relative){
                *p++ = '/';
            }
            *p++ = '.';
            *p++ = '.';
            list218.pop_back();
        }
        while(list220.size() != 0){
            if(p != relative){
                *p++ = '/';
            }
            for(const char* pp = list220.back(); *pp != nullptr; pp++){
                *p++ = *pp;
            }
            list220.pop_back();
        }
        MILO_ASSERT(p - relative < sizeof(relative), 0x3ED);
        if(p == relative){
            *p++ = '.';
        }
        *p = '\0';
    }
    return relative;
}

const char *FileGetPath(const char *arg1, char *arg2) {
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

const char *FileGetExt(const char *root) {
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

const char *FileGetDrive(const char *file) {
    static char drive[256];
    const char *p = strchr(file, ':');
    if (p != 0) {
        strncpy(drive, file, p - file);
        drive[p - file] = '\0';
    } else
        drive[0] = '\0';
    return drive;
}

const char *FileGetBase(const char *file, char *base) {
    static char my_path[256];
    const char *dir;
    char *ext;
    if (base == 0 && !MainThread())
        MILO_WARN("FileGetBase called from !MainThread with \"%s\"\n", file);
    if (base == 0)
        base = my_path;
    dir = strrchr(file, '/');
    if ((dir != 0) || (dir = strrchr(file, '\\'), (dir != 0)))
        strcpy(base, dir + 1);
    else
        strcpy(base, file);
    ext = strrchr(base, '.');
    if (ext != 0)
        *ext = 0;
    return base;
}

const char *FileGetName(const char *file) {
    static char path[256];
    const char *dir = strrchr(file, '/');
    if ((dir != 0) || (dir = strrchr(file, '\\'), (dir != 0))) {
        strcpy(path, dir + 1);
    } else
        strcpy(path, file);
    return path;
}

int GetUnusedFile(){
    for(int i = 0; i < gFiles.size(); i++){
        if(!gFiles[i]) return i;
    }
    MILO_FAIL("Can't open file, too many already open!!!");
    return -1;
}

int FileOpen(const char* iFilename, int iMode){
    int file = GetUnusedFile();
    if(file == -1) return file;
    else {
        gFiles[file] = NewFile(iFilename, iMode);
        int ret = -1;
        if(gFiles[file]) ret = file;
        file = ret;
    }
    return file;
}

int FileClose(int iFd){
    MILO_ASSERT_RANGE(iFd, 0, gFiles.size(), 0x49E);
    MILO_ASSERT(gFiles[iFd] != NULL, 0x49F);
    RELEASE(gFiles[iFd]);
    return 1;
}

int FileWrite(int iFd, void* iBuff, unsigned int iLen){
    MILO_ASSERT_RANGE(iFd, 0, gFiles.size(), 0x4C1);
    MILO_ASSERT(gFiles[iFd] != NULL, 0x4C2);
    return gFiles[iFd]->Write(iBuff, iLen);
}

const char* FileLocalize(const char* iFilename, char* buffer){
    if(SystemLanguage().Null()) return iFilename;
    if(!SystemLanguage().Null()){
        for(const char* p = iFilename; *p != '\0'; p++){
            if(*p == '/' && p[1] == 'e' && p[2] == 'n' && p[3] == 'g' && p[4] == '/'){
                static char mybuffer[256];
                if(!buffer) buffer = mybuffer;
                strcpy(buffer, iFilename);
                memcpy((void*)buffer[(int)p[1 - (int)iFilename]], (const void*)SystemLanguage().mStr, 3);
                return buffer;
            }
        }
    }
    return iFilename;
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

void FileDiscSpinUp() { TheBlockMgr.SpinUp(); }

// the weird __rs in the debug symbols here, is for a FileStat&
// so BinStream >> FileStat