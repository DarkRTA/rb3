#ifndef OBJ_OBJECT_H
#define OBJ_OBJECT_H
#include "Data.h"

// remove these once you #include the appropriate files
class Symbol; 
class String;
class TextStream;
class BinStream;

// forward declarations
class TypeProps;
class ObjectDir;
namespace Hmx {
    class Object;
}

enum PropOp {
    kPropGet = 1,
    kPropSet = 2,
    kPropInsert = 4,
    kPropRemove = 8,
    kPropSize = 16,
    kPropHandle = 32,
};

class ObjRef {
public:
    ObjRef();
    virtual ~ObjRef();
    virtual Hmx::Object* RefOwner() = 0;
    virtual void Replace(Hmx::Object*, Hmx::Object*) = 0;
    virtual bool IsDirPtr(){ return 0; }
};

class Hmx::Object : public ObjRef {
public:
    TypeProps mTypeProps; // RB2 has this protected

    // RB2 has the following members private
    DataArray* mTypeDef;
    char* mNote;
    const char* mName;
    ObjectDir* mDir;
    vector<ObjRef*> mRefs; // thank you stlport, very cool

    // o7 farts, you will be missed
    enum CopyType {
        kCopyDeep = 0,
        kCopyShallow = 1,
        kCopyFromMax = 2,
    };

    Object();
    Object(const Object&);
    virtual ~Object();
    virtual Hmx::Object* RefOwner(){}
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Print(){}
    virtual void Export(DataArray*, bool){}
    virtual void V_Unk14(){}
    virtual void V_Unk15(){}
    virtual void SetTypeDef(DataArray *);
    virtual void SetName(const char*, ObjectDir*);
    virtual ObjectDir* DataDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&){}
    virtual char* FindPathName();

    const char* Name();
    // T* New<T>();
    // vector& Refs();
    Object* NewObject();

};

#endif