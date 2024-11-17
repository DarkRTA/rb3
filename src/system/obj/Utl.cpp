#include "obj/Utl.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/File.h"
#include "os/System.h"
#include "utl/MakeString.h"
#include "utl/Symbols.h"
#include "decomp.h"
#include <algorithm>

int gCopyMax;
std::list<String> sFilePaths;
std::list<Symbol> sFiles;
FileCallbackFunc* sCBack;

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
    DataArray* cfg = SystemConfig("objects", sym);
    DataArray* found = cfg->FindArray("superclasses", false);
    if(found){
        for(int i = 1; i < found->Size(); i++){
            Symbol foundSym = found->Sym(i);
            if(classes.end() == std::find(classes.begin(), classes.end(), foundSym)){
                classes.push_back(foundSym);
            }
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

void ReplaceObject(Hmx::Object* from, Hmx::Object* to, bool b1, bool deleteFrom, bool b3){
    const char* name = from->Name();
    ObjectDir* dir = from->Dir();
    from->SetName(0, 0);
    to->SetName(name, dir);
    if(b1) CopyObject(from, to, Hmx::Object::kCopyDeep, b3);
    const std::vector<ObjRef*>& refs = from->Refs();
    while(!refs.empty()){
        ObjRef* cur = refs.back();
        cur->Replace(from, to);
    }
    if(deleteFrom) delete from;
}

void CopyTypeProperties(Hmx::Object* from, Hmx::Object* to){
    bool bbb = false;
    if(from->ClassName() != to->ClassName()){
        if(!from->Type().Null()) bbb = true;
    }
    if(bbb){
        std::list<Symbol> fromProps;
        std::list<Symbol> toProps;
        std::list<Symbol> fromArrayProps;
        std::list<Symbol> toArrayProps;
        DataArray* fromTypeArr = SystemConfig(objects, from->ClassName())->FindArray(types, from->Type());
        DataArray* fromTypeEditor = fromTypeArr->FindArray(editor, false);
        if(fromTypeEditor){
            WalkProps(fromTypeEditor, fromProps, &fromArrayProps);
        }
        ListProperties(toProps, to->ClassName(), to->Type(), &toArrayProps);

        fromProps.sort();
        toProps.sort();
        fromArrayProps.sort();
        toArrayProps.sort();

        for(std::list<Symbol>::iterator fromIt = fromProps.begin(), toIt = toProps.begin(); fromIt != fromProps.end() && toIt != toProps.end(); ++fromIt){
            Symbol prop = *fromIt;
            DataArray* fromValArr = fromTypeArr->FindArray(prop, false);
            if(fromValArr){
                for(; toIt != toProps.end() && *toIt < prop; ++toIt);
                if(toIt != toProps.end()){
                    if(*toIt == prop){
                        DataNode* fromVal = from->Property(prop, true);
                        DataType fromType = fromVal->Type();
                        DataType toType = to->Property(prop, true)->Type();
                        if(fromType == toType){
                            to->SetProperty(prop, *fromVal);
                        }
                        else if(fromType == kDataSymbol && toType == kDataObject){
                            if(!fromVal->Sym().Null()){
                                Hmx::Object* objProp = from->Dir()->FindObject(fromVal->Sym().mStr, false);
                                if(objProp){
                                    to->SetProperty(prop, objProp);
                                }
                                else {
                                    MILO_WARN("Trying to convert Symbol prop to Object prop, but cannot find Object '%s'", fromVal->Sym().mStr);
                                }
                            }
                        }
                        else {
                            MILO_LOG("mismatched property %s, from: %d, to: %d\n", prop.mStr, fromType, toType);
                        }
                    }
                }
            }
        }

        for(std::list<Symbol>::iterator fromIt = fromArrayProps.begin(), toIt = toArrayProps.begin(); fromIt != fromArrayProps.end() && toIt != toArrayProps.end(); ++fromIt){
            Symbol prop = *fromIt;
            DataArray* fromValArr = fromTypeArr->FindArray(prop, false);
            if(fromValArr){
                for(; toIt != toArrayProps.end() && *toIt < prop; ++toIt);
                if(toIt != toArrayProps.end()){
                    if(*toIt == prop){
                        DataArray* fromPropArr = from->Property(prop, true)->Array();
                        DataArrayPtr propIdx(prop, 0);
                        DataArrayPtr propTag(prop);
                        while(to->PropertySize(propTag) != 0){
                            to->RemoveProperty(propIdx);
                        }
                        for(int i = 0; i < fromPropArr->Size(); i++){
                            propIdx->Node(1) = i;
                            to->InsertProperty(propIdx, *from->Property(propIdx, true));
                        }
                    }
                }
            }
        }
    }
}

MergeFilter::Action MergeFilter::DefaultSubdirAction(ObjectDir* dir, Subdirs subdirs){
    switch(subdirs){
        case kNoSubdirs: return kKeep;
        case kAllSubdirs: return kMerge;
        case kSubdir3: return kReplace;
        case kInlineSubdirs:
            if(dir->InlineSubDirType() == kInlineNever || dir->InlineSubDirType() == kInlineCachedShared)
                return kKeep;
        case kSubdir4:
            if(dir->InlineSubDirType() == kInlineNever || dir->InlineSubDirType() == kInlineCachedShared)
                return kReplace;
        default: break;
    }
    return kMerge;
}

void MergeObject(Hmx::Object* o1, Hmx::Object* o2, ObjectDir* dir, MergeFilter::Action act){
    if(o1 == o2 || act == MergeFilter::kIgnore) return;
    if(o2){
        const std::vector<ObjRef*>& refs = o1->Refs();
        while(!refs.empty()){
            refs.back()->Replace(o1, o2);
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
        std::vector<ObjRef*>::reverse_iterator itStart = fromDir->mRefs.rbegin();
        std::vector<ObjRef*>::reverse_iterator itEnd = fromDir->mRefs.rend();
        while(itStart != itEnd){
            Hmx::Object* owner = (*itStart)->RefOwner();
            if(owner && owner->Dir() == fromDir){
                (*itStart)->Replace(fromDir, toDir);
                itStart = fromDir->mRefs.rbegin();
                itEnd = fromDir->mRefs.rend();
            }
            else {
                ++itStart;
            }
        }
    }
    for(ObjectDir::Entry* entry = fromDir->mHashTable.Begin(); entry != 0; entry = fromDir->mHashTable.Next(entry)){
        Hmx::Object* curObj = entry->obj;
        if(curObj){
            Hmx::Object* foundObj = toDir->FindObject(curObj->Name(), false);
            MergeObject(curObj, foundObj, toDir, filt);
        }
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

void ReserveToFit(ObjectDir* src, ObjectDir* dst, int extraObjects){
    int stringSize = dst->StrTableUsedSize() + SubDirStringUsed(src) + extraObjects * 10;
    int hashSize = (dst->HashTableUsedSize() + SubDirHashUsed(src) + extraObjects) * 2;
    dst->Reserve(hashSize, stringSize);
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

Hmx::Object* CopyObject(Hmx::Object* from, Hmx::Object* to, Hmx::Object::CopyType ty, bool setProxyFile){
    to->Copy(from, ty);
    if(setProxyFile){
        ObjectDir* dir2 = dynamic_cast<ObjectDir*>(to);
        if(dir2){
            ObjectDir* dir1 = dynamic_cast<ObjectDir*>(from);
            dir2->SetProxyFile(dir1->ProxyFile(), false);
        }
    }
    else CopyTypeProperties(from, to);
    return to;
}

Hmx::Object* CloneObject(Hmx::Object* from, bool instance){
    MILO_ASSERT(from, 0x32D);
    CopyObject(from, Hmx::Object::NewObject(from->ClassName()), instance ? Hmx::Object::kCopyShallow : Hmx::Object::kCopyDeep, true);
}

const char* NextName(const char* old_name, ObjectDir* dir){
    if(!dir->FindObject(old_name, false)) return old_name;
    const char* base = FileGetBase(old_name, 0);
    const char* ext = FileGetExt(old_name);
    char* ptr;
    for(ptr = (char*)base + strlen(base); (base < ptr && (ptr[-1] - 0x30U <= 9)); ptr--);
    int atoied = 0;
    if(*ptr != '\0') atoied = atoi(ptr);
    char buf[128];
    do {
        atoied++;
        sprintf(ptr, "%02d", atoied);
        if(*ext != '\0'){
            sprintf(buf, "%s.%s", ptr, ext);
        }
        else {
            strcpy(buf, ptr);
        }
    } while(dir->FindObject(buf, false));

    return MakeString(buf);
}

bool StringMatchesFilter(const char* c1, const char* c2){
    String lower1(c1);
    String lower2(c2);
    lower1.ToLower();
    lower2.ToLower();
    if(lower2.find('*') != String::npos) return FileMatch(lower1.c_str(), lower2.c_str());
    else return lower1.contains(lower2.c_str());
}

DECOMP_FORCEACTIVE(Utl, "types")

void WalkProps(DataArray* ed, std::list<Symbol>& props, std::list<Symbol>* arrayProps){
    for(int i = 1; i < ed->Size(); i++){
        DataArray* arr = ed->Array(i);
        bool canpush = (arr->Type(1) == kDataSymbol) && arr->Sym(1) != "script";
        if(canpush) props.push_back(arr->Sym(0));
        else if(arr->Type(1) == kDataArray) {
            if(arr->Array(1)->Sym(0) == "indent"){
                WalkProps(arr->Array(1), props, arrayProps);
            }
            else if(arrayProps && arr->Array(1)->Sym(0) == "array"){
                arrayProps->push_back(arr->Sym(0));
            }
        }
    }
}

void EditorBlockProps(DataArray* editDefn, std::list<Symbol>& props, std::list<Symbol>* arrayProps){
    DataArray* ed = editDefn->FindArray("editor", false);
    if(ed) WalkProps(ed, props, arrayProps);
}

DECOMP_FORCEACTIVE(Utl, "Character")

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
    int ret = o->PropertySize(ptr);
    return ret;
}

bool IsPropPathValid(Hmx::Object* o, DataArray* prop){
    for(int i = 0; i < prop->Size(); i++){
        if(prop->Type(i) == kDataInt){
            if(prop->Int(i) + 1 > GetPropSize(o, prop, i))
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

DataNode* GetPropertyVal(Hmx::Object* o, DataArray* prop, bool fail){
    if(IsPropPathValid(o, prop)){
        return o->Property(prop, fail);
    }
    else return 0;
}

DataNode ObjectList(ObjectDir* dir, Symbol s, bool b){
    std::list<const char*> sList;
    if(dir){
        for(ObjDirItr<Hmx::Object> it(dir, true); it != 0; ++it){
            if(IsASubclass(it->ClassName(), s)){
                sList.push_back(it->Name());
            }
        }
    }
    DataArrayPtr ptr(new DataArray(b + sList.size()));
    int idx = 0;
    if(b) ptr->Node(idx++) = "";
    for(std::list<const char*>::iterator it = sList.begin(); it != sList.end(); ++it){
        ptr->Node(idx++) = *it;
    }
    ptr->SortNodes();
    return ptr;
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
    sFilePaths.sort();
    sFilePaths.unique();
    DataArrayPtr ptr(new DataArray(sFilePaths.size()));
    int idx = 0;
    for(std::list<String>::iterator it = sFilePaths.begin(); it != sFilePaths.end(); ++it){
        ptr->Node(idx) = *it;
        idx++;
    }
    sFilePaths.clear();
    return ptr;
}

void FileCallback(const char* cc1, const char* cc2){
    if(!sCBack){
        sFiles.push_back(FileGetBase(cc2, 0));
    }
    else {
        char buf[256];
        strcpy(buf, MakeString("%s/%s", cc1, cc2));
        if((*sCBack)(buf)){
            sFiles.push_back(FileGetBase(buf, 0));
        }
    }
}

struct SymbolSort {
    bool operator()(Symbol s1, Symbol s2){ return strcmp(s1.mStr, s2.mStr) < 0; }
};

DataNode MakeFileList(const char* cc, bool b, FileCallbackFunc* callback){
    char buf[256];
    strcpy(buf, cc);
    sCBack = callback;
    sFiles.clear();
    FileRecursePattern(buf, &FileCallback, true);
    sCBack = nullptr;
    if(b) sFiles.push_back(Symbol());
    sFiles.sort(SymbolSort());
    sFiles.unique();
    DataArrayPtr ptr(new DataArray(sFiles.size()));
    int idx = 0;
    for(std::list<Symbol>::iterator it = sFiles.begin(); it != sFiles.end(); ++it){
        ptr->Node(idx) = *it;
        idx++;
    }
    sFiles.clear();
    return ptr;
}