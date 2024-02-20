#ifndef OBJ_TEXTFILE_H
#define OBJ_TEXTFILE_H
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "obj/Object.h"
#include "obj/Utl.h"
#include "os/File.h"
#include "os/System.h"

class TextFile : public Hmx::Object, TextStream {
public:
    File* mFile;

    TextFile(): mFile(0) {}
    virtual ~TextFile(){ delete mFile; }
    virtual Symbol ClassName() const{ return StaticClassName(); }
    virtual void SetType(Symbol s){
        static DataArray* types = SystemConfig("objects", StaticClassName(), "types");
        if(s.IsNull()) SetTypeDef(0);
        else {
            DataArray* found = types->FindArray(s, false);
            if(found != 0){
                SetTypeDef(found);
            }
            else {
                PathName(this);
                ClassName();
                SetTypeDef(0);
            }
        }
    }
    virtual DataNode Handle(DataArray*, bool);
    virtual void SetName(const char*, ObjectDir*);
    virtual void Print(const char *);

    static Symbol StaticClassName(){
        static Symbol name("File");
        return name;
    }
    static TextFile* NewObject(){ return new TextFile(); }
    // static Init

    DataNode OnPrint(DataArray*);
    DataNode OnPrintf(DataArray*);
    DataNode OnReflect(DataArray*);
};

#endif
