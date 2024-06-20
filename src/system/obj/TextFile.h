#ifndef OBJ_TEXTFILE_H
#define OBJ_TEXTFILE_H
#include "utl/TextStream.h"
#include "obj/Object.h"
#include "os/File.h"

class TextFile : public Hmx::Object, public TextStream {
public:
    File* mFile;

    TextFile(): mFile(0) {}
    virtual ~TextFile(){ delete mFile; }
    OBJ_CLASSNAME(File);
    OBJ_SET_TYPE(TextFile);
    virtual DataNode Handle(DataArray*, bool);
    virtual void SetName(const char*, class ObjectDir*);
    virtual void Print(const char *);

    void GetAppendFile(const char*, const char*, int);
    
    NEW_OBJ(TextFile)
    static void Init(){ REGISTER_OBJ_FACTORY(TextFile); }

    DataNode OnPrint(DataArray*);
    DataNode OnPrintf(DataArray*);
    DataNode OnReflect(DataArray*);
};

#endif
