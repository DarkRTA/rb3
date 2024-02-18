#ifndef RB3_FILECACHEFILE_HPP
#define RB3_FILECACHEFILE_HPP
#include "os/File.h"
#include "utl/Str.h"

class FileCacheFile : File {
public:
    FileCacheFile(); // fn_802FB6C4 - should be FileCacheFile(FileCacheEntry*)

    virtual ~FileCacheFile(); // fn_802FB744
    virtual String GetStringMember(); // fn_802E780C
    virtual int Read(void *, int); // fn_802FB7D4
    virtual bool ReadAsync(void *, int); // fn_802FB8A0
    virtual int V_Unk5(char *, int); // links to fn_8077BAA0, which returns 0
    virtual bool Write(const void *, int); // links to fn_8077BAA0, which returns 0
    virtual unsigned int Seek(int, int); // fn_802FBAC0
    virtual unsigned int Tell(); // fn_800BB518 - same fn addr as MemStream::Tell, returns
                                 // this + 0x10
    virtual void Flush(); // fn_8076F540, returns void
    virtual bool Eof(); // fn_802FBB78
    virtual bool Fail(); // fn_802FBBC4
    virtual unsigned int Size(); // fn_802FBBBC
    virtual unsigned int UncompressedSize(); // links to fn_8077BAA0, which returns 0
    virtual int ReadDone(int &); // fn_802FBA18

    virtual int V_Unk16(int *); // links to fn_8077BAA0, which returns 0
    virtual void V_Unk17(); // links to fn_8077BAA0, which returns 0

    // FileCacheEntry* unk4;
};

#endif
