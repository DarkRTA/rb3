#include "obj/Utl.h"
#include "obj/Object.h"
#include "obj/Dir.h"

#include "decomp.h"

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

int SubDirStringUsed(ObjectDir* dir){
    if(!dir) return 0;
    else {
        int size = dir->mStringTable.UsedSize();
        for(int i = 0; i < dir->mSubDirs.size(); i++){
            ObjectDir* iterDir = dir->mSubDirs[i].mDir;
            size += SubDirStringUsed(iterDir);
        }
        return size;
    }
}

bool StringMatchesFilter(const char* c1, const char* c2){
    String lower1(c1);
    String lower2(c2);
    lower1.ToLower();
    lower2.ToLower();
    if(lower2.find('*') != String::npos) return FileMatch(lower1.c_str(), lower2.c_str());
    else return lower1.contains(lower2.c_str());
}

int GetPropSize(Hmx::Object* o, DataArray* arr, int size){
    DataArrayPtr ptr(new DataArray(size));
    for(int x = 0; x < size; x++){
        ptr.Node(x) = arr->Node(x);
    }
    return o->PropertySize(ptr.mData);
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
