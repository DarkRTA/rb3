#pragma once
#include "utl/Symbol.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include <vector>

typedef bool FileCallbackFunc(char *);

void InitObject(Hmx::Object *);
// const char* PathName(const Hmx::Object*); // declared in ObjMacros.h instead, which you
// can just include obj/Object.h for anyway

/** Get this Object's name.
 * @param [in] obj The Object.
 * @returns The Object's name, or "NULL" if the object doesn't exist.
 */
const char *SafeName(Hmx::Object *obj);

/** Gets a list of every Object inside ObjectDir dir that is a subclass of class with name
 * parentSym. The list is in DataArray form, with each node containing the qualifying
 * Object's names.
 * @param [in] dir The ObjectDir to search for Objects in.
 * @param [in] parentSym The parent class in Symbol form to search for subclasses of.
 * @param [in] b TODO: currently unknown
 * @returns A DataNode housing the aforementioned DataArray.
 */
DataNode ObjectList(class ObjectDir *dir, Symbol parentSym, bool b);

DataNode MakeFileList(const char *, bool, FileCallbackFunc *);
DataNode MakeFileListFullPath(const char *);

/** Given a Symbol for a class name, fill out the classes vector with all of its
 * superclass names.
 * @param [in] classSym The class name, in Symbol form.
 * @param [out] classes The vector of this class's superclasses.
 */
void RecurseSuperClasses(Symbol classSym, std::vector<Symbol> &classes);

/** Given a Symbol for a class name, fill out the classes vector with all of its
 * superclass names, plus "Object".
 * @param [in] classSym The class name, in Symbol form.
 * @param [out] classes The vector of this class's superclasses.
 */
void ListSuperClasses(Symbol classSym, std::vector<Symbol> &classes);

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
 * @param [in] copyDeep If true, the full Object will be copied over rather than just its
 * references.
 * @param [in] deleteFrom If true, delete from after the replacement has occurred.
 * @param [in] setProxyFile If true, set to's proxy file to from's - only used if copyDeep
 * is true!
 */
void ReplaceObject(
    Hmx::Object *from, Hmx::Object *to, bool copyDeep, bool deleteFrom, bool setProxyFile
);

/** Copy the type properties (TypeProps) from Object from into Object to.
 * @param [in] from The Object to copy type props from.
 * @param [in] to The Object to copy type props into.
 */
void CopyTypeProperties(Hmx::Object *from, Hmx::Object *to);

/** Reserve enough entries in dst's hash and string tables to fit src's entries, plus any
 * extras.
 * @param [in] src The ObjectDir to determine how much space to reserve with.
 * @param [in] dst The ObjectDir to reserve entries in.
 * @param [in] extraObjects The number of extra objects to allocate space for in dst, in
 * addition to src's entries.
 */
void ReserveToFit(class ObjectDir *src, class ObjectDir *dst, int extraObjects);

/** Get the number of used string table entries across and ObjectDir and all of its
 * subdirs.
 * @param [in] dir The ObjectDir to count string table entries from.
 * @returns The number of used string table entries across dir and all of its subdirs.
 */
int SubDirStringUsed(class ObjectDir *dir);

/** Get the number of used hash table entries across and ObjectDir and all of its subdirs.
 * @param [in] dir The ObjectDir to count hash table entries from.
 * @returns The number of used hash table entries across dir and all of its subdirs.
 */
int SubDirHashUsed(class ObjectDir *dir);

const char *NextName(const char *, class ObjectDir *);
bool StringMatchesFilter(const char *, const char *);
int GetPropSize(Hmx::Object *, DataArray *, int);
bool IsPropPathValid(Hmx::Object *, DataArray *);
bool PathCompare(DataArray *, DataArray *);
DataNode *GetPropertyVal(Hmx::Object *, DataArray *, bool);

/** Copy Object from into Object to.
 * @param [in] from The Object to copy from.
 * @param [in] to The Object to copy into.
 * @param [in] ty The copy type.
 * @param [in] setProxyFile If true, set to's proxy file to from's. If false, copy from's
 * type properties into to's.
 * @returns The newly copied Object.
 */
Hmx::Object *CopyObject(
    Hmx::Object *from, Hmx::Object *to, Hmx::Object::CopyType ty, bool setProxyFile
);

/** Create a clone of an Object.
 * @param [in] from The Object to clone.
 * @param [in] instance If true, create a shallow copy. If false, create a deep copy.
 * @returns The newly cloned Object.
 */
Hmx::Object *CloneObject(Hmx::Object *from, bool instance);

void FileCallbackFullPath(const char *, const char *);
void FileCallback(const char *, const char *);
void WalkProps(DataArray *, std::list<Symbol> &, std::list<Symbol> *);
void EditorBlockProps(DataArray *, std::list<Symbol> &, std::list<Symbol> *);
void ListProperties(std::list<Symbol> &, Symbol, Symbol, std::list<Symbol> *);

// mergefilter classes go here
class MergeFilter {
public:
    enum Action {
        kMerge,
        kReplace,
        kKeep,
        kIgnore
    };
    enum Subdirs {
        kNoSubdirs,
        kAllSubdirs,
        kInlineSubdirs,
        kSubdir3,
        kSubdir4
    };

    MergeFilter() : mAction(kMerge), mSubdirs(kNoSubdirs) {}
    MergeFilter(Action a, Subdirs s) : mAction(a), mSubdirs(s) {}
    virtual ~MergeFilter() {}
    virtual Action Filter(Hmx::Object *, Hmx::Object *, class ObjectDir *) {
        return mAction;
    }
    virtual Action FilterSubdir(class ObjectDir *o1, class ObjectDir *) {
        return DefaultSubdirAction(o1, mSubdirs);
    }

    static Action DefaultSubdirAction(class ObjectDir *, Subdirs);

    Action mAction;
    Subdirs mSubdirs;
};

class DataMergeFilter : public MergeFilter {
public:
    inline DataMergeFilter(const DataNode &, Subdirs);
    virtual ~DataMergeFilter() {}
    virtual Action Filter(Hmx::Object *, Hmx::Object *, class ObjectDir *);

    DataType mType;
    DataFunc *mFunc;
    Hmx::Object *mObj;
    int mInt;
};

void MergeObject(Hmx::Object *, Hmx::Object *, ObjectDir *, MergeFilter::Action);
void MergeObject(Hmx::Object *, Hmx::Object *, ObjectDir *, MergeFilter &);
void MergeObjectsRecurse(ObjectDir *, ObjectDir *, MergeFilter &, bool);
void MergeDirs(ObjectDir *, ObjectDir *, MergeFilter &);
