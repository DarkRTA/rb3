#ifndef OBJ_UTL_H
#define OBJ_UTL_H
#include "utl/Symbol.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include <vector>

typedef bool FileCallbackFunc(char*);

void InitObject(Hmx::Object*);
// const char* PathName(const Hmx::Object*); // declared in ObjMacros.h instead, which you can just include obj/Object.h for anyway

/** Get this Object's name.
 * @param [in] obj The Object.
 * @returns The Object's name, or "NULL" if the object doesn't exist.
*/
const char* SafeName(Hmx::Object* obj);

DataNode ObjectList(class ObjectDir*, Symbol, bool);
DataNode MakeFileList(const char*, bool, FileCallbackFunc*);
DataNode MakeFileListFullPath(const char*);

/** Given a Symbol for a class name, fill out the classes vector with all of its superclass names.
 * @param [in] classSym The class name, in Symbol form.
 * @param [out] classes The vector of this class's superclasses.
*/
void RecurseSuperClasses(Symbol classSym, std::vector<Symbol>& classes);

/** Given a Symbol for a class name, fill out the classes vector with all of its superclass names, plus "Object".
 * @param [in] classSym The class name, in Symbol form.
 * @param [out] classes The vector of this class's superclasses.
*/
void ListSuperClasses(Symbol classSym, std::vector<Symbol>& classes);

/** Search for parent class searchClass in the collection of classSym's superclasses.
 * @param [in] classSym The class name, in Symbol form.
 * @param [in] searchClass The superclass to search for in classSym's hierarchy.
 * @returns True if searchClass exists in classSym's superclass hierarchy, false if not.
*/
bool RecurseSuperClassesSearch(Symbol classSym, Symbol searchClass);

/** Determine whether or not child is a subclass of parent.
 * @param [in] child The child class's name, in Symbol form.
 * @param [in] parent The potential parent class's name, in Symbol form.
 * @returns True if child is a subclass of parent, false if not.
*/
bool IsASubclass(Symbol child, Symbol parent);

/** Replaces the Object from with to.
 * @param [in] from The Object to be replaced.
 * @param [in] to The Object serving as the replacement.
 * @param [in] copyDeep If true, the full Object will be copied over rather than just its references.
*/
void ReplaceObject(Hmx::Object* from, Hmx::Object* to, bool copyDeep, bool deleteFrom, bool setProxyFile);

void CopyTypeProperties(Hmx::Object*, Hmx::Object*);
void ReserveToFit(class ObjectDir*, class ObjectDir*, int);
int SubDirStringUsed(class ObjectDir*);
int SubDirHashUsed(class ObjectDir*);
const char* NextName(const char*, class ObjectDir*);
bool StringMatchesFilter(const char*, const char*);
int GetPropSize(Hmx::Object*, DataArray*, int);
bool IsPropPathValid(Hmx::Object*, DataArray*);
bool PathCompare(DataArray*, DataArray*);
DataNode* GetPropertyVal(Hmx::Object*, DataArray*, bool);
Hmx::Object* CopyObject(Hmx::Object*, Hmx::Object*, Hmx::Object::CopyType, bool);
Hmx::Object* CloneObject(Hmx::Object*, bool);
void FileCallbackFullPath(const char*, const char*);
void FileCallback(const char*, const char*);

void WalkProps(DataArray*, std::list<Symbol>&, std::list<Symbol>*);
void EditorBlockProps(DataArray*, std::list<Symbol>&, std::list<Symbol>*);
void ListProperties(std::list<Symbol>&, Symbol, Symbol, std::list<Symbol>*);

// mergefilter classes go here
class MergeFilter {
public:
    enum Action { kMerge, kReplace, kKeep, kIgnore };
    enum Subdirs { kNoSubdirs, kAllSubdirs, kInlineSubdirs, kSubdir3, kSubdir4 };

    MergeFilter() : mAction(kMerge), mSubdirs(kNoSubdirs) {}
    MergeFilter(Action a, Subdirs s) : mAction(a), mSubdirs(s) {}
    virtual ~MergeFilter(){}
    virtual Action Filter(Hmx::Object*, Hmx::Object*, class ObjectDir*){ return mAction; }
    virtual Action FilterSubdir(class ObjectDir* o1, class ObjectDir*){
        return DefaultSubdirAction(o1, mSubdirs);
    }

    static Action DefaultSubdirAction(class ObjectDir*, Subdirs);

    Action mAction;
    Subdirs mSubdirs;
};

class DataMergeFilter : public MergeFilter {
public:
    inline DataMergeFilter(const DataNode&, Subdirs);
    virtual ~DataMergeFilter(){}
    virtual Action Filter(Hmx::Object*, Hmx::Object*, class ObjectDir*);

    DataType mType;
    DataFunc* mFunc;
    Hmx::Object* mObj;
    int mInt;
};

void MergeObject(Hmx::Object*, Hmx::Object*, ObjectDir*, MergeFilter::Action);
void MergeObject(Hmx::Object*, Hmx::Object*, ObjectDir*, MergeFilter&);
void MergeObjectsRecurse(ObjectDir*, ObjectDir*, MergeFilter&, bool);
void MergeDirs(ObjectDir*, ObjectDir*, MergeFilter&);

#endif
