#ifndef RB3_FILE_OPS_HPP
#define RB3_FILE_OPS_HPP

void FileQualifiedFilename(char*, int, const char*);
extern "C" char* FileGetPath(char*, char*);
extern "C" char* FileGetDrive(char*);
extern "C" char* FileGetBase(char*, char*);
extern "C" char* FileGetExt(char*);
extern "C" char* FileGetName(char*);
extern "C" bool FileMatch(const char*, const char*);

#endif
