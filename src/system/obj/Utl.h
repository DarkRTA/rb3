#ifndef OBJ_UTL_H
#define OBJ_UTL_H
#include "utl/Symbol.h"
#include "obj/Data.h"

// forward declarations
namespace Hmx {
    class Object;
}

void InitObject(Hmx::Object*);
const char* PathName(const Hmx::Object*);
const char* SafeName(Hmx::Object*);

bool RecurseSuperClassesSearch(Symbol, Symbol);
bool IsASubclass(Symbol, Symbol);

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

#endif
