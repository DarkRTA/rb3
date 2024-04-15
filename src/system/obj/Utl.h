#ifndef OBJ_UTL_H
#define OBJ_UTL_H
#include "utl/Symbol.h"
#include "obj/Data.h"
#include <vector>

// forward declarations
namespace Hmx {
    class Object;
}
class ObjectDir;

void InitObject(Hmx::Object*);
const char* PathName(const Hmx::Object*);
const char* SafeName(Hmx::Object*);
DataNode ObjectList(ObjectDir*, Symbol, bool); // i think???
DataNode MakeFileList(const char*, bool, bool (*)(char*));
DataNode MakeFileListFullPath(const char*);

void ListSuperClasses(Symbol, std::vector<Symbol>&);
void RecurseSuperClasses(Symbol, std::vector<Symbol>&);
bool RecurseSuperClassesSearch(Symbol, Symbol);
bool IsASubclass(Symbol, Symbol);
void ReplaceObject(Hmx::Object*, Hmx::Object*, bool, bool, bool);
void CopyTypeProperties(Hmx::Object*, Hmx::Object*);
void ReserveToFit(ObjectDir*, ObjectDir*, int);
int SubDirStringUsed(ObjectDir*);
int SubDirHashUsed(ObjectDir*);
const char* NextName(const char*, ObjectDir*);
bool StringMatchesFilter(const char*, const char*);
int GetPropSize(Hmx::Object*, DataArray*, int);
bool IsPropPathValid(Hmx::Object*, DataArray*);
bool PathCompare(DataArray*, DataArray*);
DataNode* GetPropertyVal(Hmx::Object*, DataArray*, bool);

// mergefilter classes go here
class MergeFilter {
public:
    enum Action { kMerge, kReplace, kKeep, kIgnore };
    enum Subdirs { kNoSubdirs, kAllSubdirs, kInlineSubdirs };

    MergeFilter();
    MergeFilter(Action a, Subdirs s) : mAction(a), mSubdirs(s) {}
    virtual ~MergeFilter(){}
    virtual Action Filter(Hmx::Object*, Hmx::Object*, class ObjectDir*){ return mAction; }
    virtual Action FilterSubDir(class ObjectDir*, class ObjectDir*);

    Action DefaultSubdirAction(class ObjectDir*, Subdirs);

    Action mAction;
    Subdirs mSubdirs;
};

class DataMergeFilter : public MergeFilter {
public:
    DataMergeFilter(const DataNode&, Subdirs);
    virtual ~DataMergeFilter();
    virtual Action Filter(Hmx::Object*, Hmx::Object*, class ObjectDir*);

    DataType mType;
    DataFunc* mFunc;
    Hmx::Object* mObj;
};


// apparently uncommenting this breaks TypeProps.cpp, which is just lovely
// #include "obj/Object.h" // if i put this earlier, then i get circular dependencies with objects' SetType for using PathName
// i need this here so that CopyType can be included for this function prototype
// void CopyObject(Hmx::Object*, Hmx::Object*, Hmx::Object::CopyType, bool);

#endif
