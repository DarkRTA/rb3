#ifndef MATH_FILECHECKSUM_H
#define MATH_FILECHECKSUM_H

struct FileChecksum {
    // total size: 0x18
    const char * file; // offset 0x0, size 0x4
    unsigned char checksum[20]; // offset 0x4, size 0x14
};

struct ChecksumData {
    ChecksumData(){}
    ChecksumData(FileChecksum* f1, FileChecksum* f2) : start(f1), end(f2) {}
    // total size: 0x8
    struct FileChecksum * start; // offset 0x0, size 0x4
    struct FileChecksum * end; // offset 0x4, size 0x4
};

void SetFileChecksumData(FileChecksum*, int);
void ClearFileChecksumData();
bool HasFileChecksumData();
unsigned char* GetFileChecksum(const char*, bool);

#endif
