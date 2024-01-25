#ifndef RB3_OBJECTDIR_HPP
#define RB3_OBJECTDIR_HPP
#include "hmx/object.hpp"
#include "stringtable.hpp"
#include "filepath.hpp"

class ObjectDir : public virtual Hmx::Object {
public:
    ObjectDir();

    static ObjectDir* sMainDir;

    Hmx::Object* FindObject(const char*, bool);

    char kh[0x20]; // should be a KeylessHash<const char*, ObjectDir::Entry*>
    StringTable table;
    FilePath fpath;
    bool unk44, unk45;
    int unk48;
    char list1[0x8];
    bool unk54;
    int unk58;
    const char* unk5c;
    FilePath fpath2;
    char list2[0x8];
    int unk74;
    int unk78;
    const char* unk7c;

};

ObjectDir* GetObjectDir(DataNode*, DataArray*);
ObjectDir* GetObjectDirAtIndex(DataArray*, int);

#endif
