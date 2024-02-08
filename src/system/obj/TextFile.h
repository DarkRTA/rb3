#ifndef OBJ_TEXTFILE_H
#define OBJ_TEXTFILE_H
#include "symbol.hpp"
#include "TextStream.h"
#include "hmx/object.hpp"

class TextFile : public Hmx::Object, TextStream {
public:
    int unk20; // likely a ptr to some class

    TextFile(){ unk20 = 0; }
    virtual ~TextFile();
    virtual Symbol ClassName() const; // fn_8033CE5C
    virtual void SetType(Symbol); // fn_8033CE60
    virtual DataNode Handle(DataArray*, bool); // fn_8033CA48
    virtual void SetName(const char*, ObjectDir*); // fn_8033C93C
    virtual void Print(const char *); // fn_8033C990

    static Symbol StaticClassName(){
        static Symbol name("File");
        return name;
    }
    static TextFile* NewObject(){ return new TextFile(); }

    DataNode OnPrint(DataArray*);
    DataNode OnPrintf(DataArray*);
    DataNode OnReflect(DataArray*);
};

#endif
