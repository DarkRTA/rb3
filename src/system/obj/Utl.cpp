#include "obj/Utl.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"
#include "decomp.h"
#include <algorithm>

int gCopyMax;
std::list<String> sFilePaths;
std::list<Symbol> sFiles;

DECOMP_FORCEACTIVE(Utl,
    "mem_copy",
    "fast",
    "main",
    "%d,%d,%d,%d\n"
)

void InitObject(Hmx::Object* obj){
    static DataArray* objects = SystemConfig("objects");
    static Symbol initSym("init");
    DataArray* found2 = objects->FindArray(obj->ClassName(), true)->FindArray(initSym, false);
    if(found2 != 0) found2->ExecuteScript(1, obj, 0, 1);
}

const char* PathName(const Hmx::Object* o){
    if(o) return ((Hmx::Object*)o)->FindPathName();
    else return "NULL Object";
}

const char* SafeName(Hmx::Object* obj){
    if(obj) return obj->Name();
    else return "NULL";
}

void RecurseSuperClasses(Symbol sym, std::vector<Symbol>& classes){
    DataArray* found = SystemConfig("objects", sym)->FindArray("superclasses", false);
    if(found){
        for(int i = 1; i < found->Size(); i++){
            Symbol foundSym = found->Sym(i);
            // if some currently unknown condition is met, THEN push back
            // update: condition appears to be std::find
            classes.push_back(foundSym);
            RecurseSuperClasses(foundSym, classes);
        }
    }
}

DECOMP_FORCEACTIVE(Utl,
    "Object",
    "ext",
    "."
)

void ListSuperClasses(Symbol sym, std::vector<Symbol>& classes){
    RecurseSuperClasses(sym, classes);
    classes.push_back(Symbol("Object"));
}

bool RecurseSuperClassesSearch(Symbol s1, Symbol s2){
    DataArray* found = SystemConfig("objects")->FindArray(s1, false);
    if(!found) return false;
    DataArray* foundAgain = found->FindArray("superclasses", false);
    if(foundAgain){
        for(int i = 1; i < foundAgain->Size(); i++){
            Symbol foundSym = foundAgain->Sym(i);
            if(s2 == foundSym) return true;
            if(RecurseSuperClassesSearch(foundSym, s2)) return true;
        }
    }
    return false;
}

bool IsASubclass(Symbol child, Symbol parent){
    if((parent == "Object") || (child == parent)) return true;
    else return RecurseSuperClassesSearch(child, parent);
}

void ReplaceObject(Hmx::Object* from, Hmx::Object* to, bool b1, bool b2, bool b3){
    const char* name = from->Name();
    ObjectDir* dir = from->Dir();
    from->SetName(0, 0);
    to->SetName(name, dir);
    if(b1) CopyObject(from, to, Hmx::Object::kCopyDeep, b3);
    // for(std::vector<ObjRef*>::iterator it = from->Refs().begin(); it != from->Refs().end(); it++){
    //     (*it)->Replace(from, to);
    // }
    while(!from->Refs().empty()){
        from->Refs().back()->Replace(from, to);
    }
    if(b2) delete from;
}

MergeFilter::Action MergeFilter::DefaultSubdirAction(ObjectDir* dir, Subdirs subdirs){
    switch(subdirs){
        case kNoSubdirs: return kKeep;
        case kAllSubdirs: return kMerge;
        case kSubdir3: return kReplace;
        case kInlineSubdirs:
            if(dir->InlineSubDirType() == kInlineNever || dir->InlineSubDirType() == kInline3)
                return kKeep;
        case kSubdir4:
            if(dir->InlineSubDirType() == kInlineNever || dir->InlineSubDirType() == kInline3)
                return kReplace;
        default: break;
    }
    return kMerge;
}

void MergeObject(Hmx::Object* o1, Hmx::Object* o2, ObjectDir* dir, MergeFilter::Action act){
    if(o1 == o2 || act == MergeFilter::kIgnore) return;
    if(o2){
        for(std::vector<ObjRef*>::const_reverse_iterator it = o1->Refs().rbegin(); it != o1->Refs().rend(); it++){
            (*it)->Replace(o1, o2);
        }
        if(act == MergeFilter::kMerge) o2->Copy(o1, Hmx::Object::kCopyFromMax);
        else if(act == MergeFilter::kReplace) o2->Copy(o1, Hmx::Object::kCopyDeep);
    }
    else if(act != MergeFilter::kKeep){
        o1->SetName(o1->Name(), dir);
    }    
}

void MergeObject(Hmx::Object* o1, Hmx::Object* o2, ObjectDir* dir, MergeFilter& filt){
    if(o2 != o1) MergeObject(o1, o2, dir, filt.Filter(o1, o2, dir));
}

void MergeObjectsRecurse(ObjectDir* fromDir, ObjectDir* toDir, MergeFilter& filt, bool b){
    if(!b){
        switch(filt.FilterSubdir(fromDir, toDir)){
            case MergeFilter::kReplace:
                if(!toDir->HasSubDir(fromDir))
                    toDir->AppendSubDir(ObjDirPtr<ObjectDir>(fromDir));
                return;
            case MergeFilter::kKeep: return;
            default: break;
        }
        for(std::vector<ObjRef*>::const_reverse_iterator it = fromDir->Refs().rbegin(); it != fromDir->Refs().rend(); ++it){
            Hmx::Object* owner = (*it)->RefOwner();
            if(owner && owner->Dir() == fromDir){
                (*it)->Replace(fromDir, toDir);
            }
        }
    }
    for(ObjectDir::Entry* entry = fromDir->mHashTable.FirstFromStart(); entry != 0; entry = fromDir->mHashTable.FirstFromNext(entry)){
        Hmx::Object* curObj = entry->obj;
        if(curObj) MergeObject(curObj, toDir->FindObject(curObj->Name(), false), toDir, filt);
    }
    for(int i = 0; i < fromDir->mSubDirs.size(); i++){
        ObjDirPtr<ObjectDir>& oPtr = fromDir->mSubDirs[i];
        if(oPtr) MergeObjectsRecurse(oPtr, toDir, filt, false);
    }
}

void MergeDirs(ObjectDir* fromDir, ObjectDir* toDir, MergeFilter& filt){
    MILO_ASSERT(fromDir && toDir, 0x2D7);
    MergeObject(fromDir, toDir, toDir, filt);
    CopyTypeProperties(fromDir, toDir);
    MergeObjectsRecurse(fromDir, toDir, filt, true);
}

void ReserveToFit(ObjectDir* dir1, ObjectDir* dir2, int i){
    dir2->Reserve((SubDirHashUsed(dir1) + i + dir2->mHashTable.mNumEntries) * 2, i * 10 + dir2->mStringTable.UsedSize() + SubDirStringUsed(dir1));
}

int SubDirStringUsed(ObjectDir* dir){
    if(!dir) return 0;
    else {
        int size = dir->mStringTable.UsedSize();
        for(std::vector<ObjDirPtr<ObjectDir> >::iterator it = dir->mSubDirs.begin(); it != dir->mSubDirs.end(); ++it){
            size += SubDirStringUsed(*it);
        }
        return size;
    }
}

int SubDirHashUsed(ObjectDir* dir){
    if(!dir) return 0;
    else {
        int size = dir->mHashTable.mNumEntries;
        for(std::vector<ObjDirPtr<ObjectDir> >::iterator it = dir->mSubDirs.begin(); it != dir->mSubDirs.end(); ++it){
            size += SubDirHashUsed(*it);
        }
        return size;
    }
}

Hmx::Object* CopyObject(Hmx::Object* o1, Hmx::Object* o2, Hmx::Object::CopyType ty, bool b){
    o2->Copy(o1, ty);
    if(b){
        ObjectDir* dir2 = dynamic_cast<ObjectDir*>(o2);
        if(dir2){
            ObjectDir* dir1 = dynamic_cast<ObjectDir*>(o1);
            dir2->SetProxyFile(dir1->ProxyFile(), false);
        }
    }
    else CopyTypeProperties(o1, o2);
    return o2;
}

void CloneObject(Hmx::Object* from, bool b){
    MILO_ASSERT(from, 0x32D);
    CopyObject(from, Hmx::Object::NewObject(from->ClassName()), (Hmx::Object::CopyType)b, true);
}

const char* NextName(const char* name, ObjectDir* dir){
    if(dir->FindObject(name, false)){
        const char* base = FileGetBase(name, 0);
        const char* ext = FileGetExt(name);
        // for(char* p = strlen(base); )
    }
    else return name;
}

bool StringMatchesFilter(const char* c1, const char* c2){
    String lower1(c1);
    String lower2(c2);
    lower1.ToLower();
    lower2.ToLower();
    if(lower2.find('*') != String::npos) return FileMatch(lower1.c_str(), lower2.c_str());
    else return lower1.contains(lower2.c_str());
}

void WalkProps(DataArray* ed, std::list<Symbol>& props, std::list<Symbol>* arrayProps){
    for(int i = 0; i < ed->Size(); i++){
        DataArray* arr = ed->Array(i);
        bool canpush = (arr->Type(1) == kDataSymbol) || arr->Sym(1) != "script";
        if(canpush) props.push_back(arr->Sym(0));
        else if(arr->Type(1) == kDataArray) {
            if(arr->Array(1)->Sym(0) == "indent"){
                WalkProps(arr->Array(1), props, arrayProps);
            }
            else if(arrayProps || arr->Array(1)->Sym(0) == "array"){
                arrayProps->push_back(arr->Sym(0));
            }
        }
    }
}

void EditorBlockProps(DataArray* editDefn, std::list<Symbol>& props, std::list<Symbol>* arrayProps){
    DataArray* ed = editDefn->FindArray("editor", false);
    if(ed) WalkProps(ed, props, arrayProps);
}

void ListProperties(std::list<Symbol>& props, Symbol classnm, Symbol type, std::list<Symbol>* arrayProps){
    DataArray* cfg = SystemConfig(objects, classnm);
    if(type != gNullStr){
        DataArray* typesArr = cfg->FindArray("types", false);
        if(typesArr) typesArr = typesArr->FindArray(type, false);
        else typesArr = 0;
        EditorBlockProps(typesArr, props, arrayProps);
    }
    EditorBlockProps(cfg, props, arrayProps);
    std::vector<Symbol> superclasses;
    ListSuperClasses(classnm, superclasses);
    for(std::vector<Symbol>::iterator it = superclasses.begin(); it != superclasses.end(); ++it){
        EditorBlockProps(SystemConfig(objects, *it), props, arrayProps);
    }
}

int GetPropSize(Hmx::Object* o, DataArray* arr, int size){
    DataArrayPtr ptr(new DataArray(size));
    for(int x = 0; x < size; x++){
        ptr->Node(x) = arr->Node(x);
    }
    return o->PropertySize(ptr);
}

bool IsPropPathValid(Hmx::Object* o, DataArray* arr){
    for(int i = 0; i < arr->Size(); i++){
        if(arr->Type(i) == kDataInt){
            if(arr->Int(i) + 1 > GetPropSize(o, arr, i))
                return false;
        }
    }
    return true;
}

bool PathCompare(DataArray* arr1, DataArray* arr2){
    if(arr1 == arr2) return true;
    if(!arr1 || !arr2) return false;
    int arr1size = arr1->Size();
    if(arr1size != arr2->Size()) return false;
    for(int i = 0; i < arr1size; i++){
        DataType arr1type = CONST_ARRAY(arr1)->Node(i).Type();
        if(arr1type != CONST_ARRAY(arr2)->Node(i).Type()) return false;
        else switch(arr1type){
            case kDataSymbol:
            case kDataString:
                if(arr1->Str(i) != arr2->Str(i)) return false;
                break;
            case kDataInt:
                if(arr1->Int(i) != arr2->Int(i)) return false;
                break;
            default: break;
        }
    }
    return true;
}

DataNode* GetPropertyVal(Hmx::Object* o, DataArray* arr, bool b){
    if(IsPropPathValid(o, arr)){
        return o->Property(arr, b);
    }
    else return 0;
}

DataNode ObjectList(ObjectDir* dir, Symbol s, bool b){
    std::list<const char*> sList;
    for(ObjDirItr<Hmx::Object> it(dir, true); it != 0; ++it){
        if(IsASubclass(it->ClassName(), s)){
            sList.push_back(it->Name());
        }
    }
    DataArrayPtr ptr(new DataArray(1));
    if(b) ptr->Node(0) = DataNode("");
    int i = b;
    for(std::list<const char*>::iterator it = sList.begin(); it != sList.end(); ++it){
        ptr->Node(i++) = DataNode(*it);
    }
    ptr->SortNodes();
    return DataNode(ptr);
}

void FileCallbackFullPath(const char* cc1, const char* cc2){
    String str(MakeString("%s/%s/%s", FileRoot(), cc1, cc2));
    str.ReplaceAll('\\', '/');
    sFilePaths.push_back(str);
}

DataNode MakeFileListFullPath(const char* cc){
    char buf[256];
    strcpy(buf, cc);
    sFilePaths.clear();
    FileRecursePattern(buf, &FileCallbackFullPath, true);
    // std::stable_sort()
}