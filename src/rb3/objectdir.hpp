#ifndef RB3_OBJECTDIR_HPP
#define RB3_OBJECTDIR_HPP
#include "hmx/object.hpp"
#include "stringtable.hpp"
#include "filepath.hpp"

class ObjectDir : public virtual Hmx::Object {
public:
    ObjectDir();
    virtual Symbol ClassName() const; // fn_800103C8
    virtual void SetType(Symbol); // fn_800102A0
    virtual DataNode Handle(DataArray*, bool); // fn_80336C94
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp); // fn_80337B7C
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~ObjectDir();

    static ObjectDir* sMainDir;

    Hmx::Object* FindObject(const char*, bool);
    static Symbol StaticClassName();

    char kh[0x20]; // should be a KeylessHash<const char*, ObjectDir::Entry*>
    StringTable table;
    FilePath proxyFile;
    bool unk44;
    bool inlineProxyAllowed;
    int unk48;
    char subdirs[0x8]; // should be a vector
    bool unk54;
    int unk58;
    const char* pathName;
    FilePath fpath2;
    char vector2[0x8];
    int unk74;
    int unk78;
    const char* unk7c;

};

ObjectDir* GetObjectDir(DataNode*, DataArray*);
ObjectDir* GetObjectDirAtIndex(DataArray*, int);

#endif
