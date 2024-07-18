#ifndef UTL_FILEPATH_H
#define UTL_FILEPATH_H
#include "utl/Str.h"
#include "os/File.h"
#include "utl/BinStream.h"

class FilePath : public String {
public:
    static FilePath sRoot;
    static FilePath sNull;

    FilePath(const String & str) : String(str) { }
    FilePath(const char* str){
        Set(sRoot.c_str(), str);
    }
    FilePath(const char* cc, const char* cc2){ Set(cc, cc2); }
    FilePath(){ }
    virtual ~FilePath(){ }

    void Set(const char *, const char *); // fn_8034C91C - the only not-weak method here

    // FilePath *operator=(const FilePath &);
    const char* FilePathRelativeToRoot(){ return FileRelativePath(sRoot.c_str(), this->c_str()); }
    void SetRoot(const char* str){ Set(sRoot.c_str(), str); }
};

inline TextStream& operator<<(TextStream& ts, FilePath& fp){
    return ts << fp.FilePathRelativeToRoot();
    // return ts; // commented out to get RndTex::Print to match
}

inline BinStream& operator>>(BinStream& bs, FilePath& fp){
    char buf[0x100];
    bs.ReadString(buf, 0x100);
    fp.SetRoot(buf);
    return bs;
}

class FilePathTracker {
public:
    FilePathTracker(const char* root) {
        mOldRoot = FilePath::sRoot;
        FilePath::sRoot.Set(FileRoot(), root);
    }

    ~FilePathTracker(){
        FilePath::sRoot = mOldRoot;
    }

    FilePath mOldRoot;
};

#endif
