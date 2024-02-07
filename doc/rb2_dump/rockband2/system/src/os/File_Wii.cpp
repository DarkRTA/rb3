/*
    Compile unit: C:\rockband2\system\src\os\File_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805B22EC -> 0x805B2644
*/
// Range: 0x805B22EC -> 0x805B247C
int FileGetStat(const char * iFilename /* r31 */, struct FileStat * iBuffer /* r30 */) {
    // Local variables
    class String qualName; // r1+0x8
    struct _FILE * file; // r31
    unsigned int size; // r0
    struct DVDFileInfo fileInfo; // r1+0x14
    long dvdFileNum; // r0
}

// Range: 0x805B247C -> 0x805B2484
int FileMkDir() {}

struct DVDDir {
    // total size: 0xC
    unsigned long entryNum; // offset 0x0, size 0x4
    unsigned long location; // offset 0x4, size 0x4
    unsigned long next; // offset 0x8, size 0x4
};
struct DVDDirEntry {
    // total size: 0xC
    unsigned long entryNum; // offset 0x0, size 0x4
    int isDir; // offset 0x4, size 0x4
    char * name; // offset 0x8, size 0x4
};
// Range: 0x805B2484 -> 0x805B25B8
void FileEnumerate(const char * dir /* r28 */, void (* cb)(char *, char *) /* r29 */, unsigned char recurse /* r30 */, const char * pattern /* r31 */) {
    // Local variables
    struct DVDDir dvddir; // r1+0x14
    struct DVDDirEntry dirent; // r1+0x8
    int rc; // r0
    char buf[1024]; // r1+0x20

    // References
    // -> class Archive * TheArchive;
}

// Range: 0x805B25B8 -> 0x805B2644
void FileQualifiedFilename(char * out /* r30 */, const char * in /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


