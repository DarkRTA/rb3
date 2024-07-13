#include "obj/DataUtl.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/DataFunc.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "obj/TextFile.h"
#include "os/Debug.h"
#include "utl/Loader.h"
#include "utl/Option.h"
#include <map>

#define VAR_STACK_SIZE 100

std::map<Symbol, DataArray*> gMacroTable;
class ObjectDir* gDataDir;
Hmx::Object* gDataThis;
static bool gDataMacroWarning = true;
struct VarStack {
    DataNode* var;
    DataNode value;
};
VarStack gVarStack[VAR_STACK_SIZE];
VarStack* gVarStackPtr = gVarStack;

Loader* DataFactory(const FilePath& f, LoaderPos l) { return new DataLoader(f, l, true); }

void DataInit() {
    DataInitFuncs();
    TheLoadMgr.RegisterFactory("dta", DataFactory);
    TheLoadMgr.RegisterFactory("dtx", DataFactory);
    TextFile::Init();
    gDataMacroWarning = OptionBool("no_macro_warn", true);
    ObjectDir::PreInit(0x4e1d, 0x249f0);
}

void DataTerminate() {
    for (std::map<Symbol, DataArray*>::iterator i = gMacroTable.begin(); i != gMacroTable.end(); i++) {
        DataArray* x = i->second;
        if (i->second) {
            if (!--i->second->mRefs) delete x;
            i->second = NULL;
        }
    }
    gMacroTable.clear();
    gDataThis = NULL;
    gDataDir = NULL;
    DataTermFuncs();
}

void DataMacroWarning(bool b){
    gDataMacroWarning = b;
}

void DataSetMacro(Symbol key, DataArray* macro){
    DataArray*& val = gMacroTable[key];
    if(val) val->Release();
    if(macro){
        if(val && gDataMacroWarning) MILO_WARN("Resetting macro %s (file %s, line %d)", key, macro->File(), macro->Line());
        val = macro;
        macro->AddRef();
    }
    else val = 0;
}

DataArray* DataGetMacro(Symbol s){
    const std::map<Symbol, DataArray*>::iterator it = gMacroTable.find(s);
    if(it == gMacroTable.end()) return 0;
    else return it->second;
}

Symbol DataGetMacroByInt(int value, const char* prefix){
    for(std::map<Symbol, DataArray*>::iterator it = gMacroTable.begin(); it != gMacroTable.end(); it++){
        DataArray* macro_array = (*it).second;
        if(macro_array->Size() != 0){
            DataNode& node = (*it).second->Node(0);
            if(node.Type() == kDataInt){
                if(node.Int(0) == value){
                    String name((*it).first);
                    if(name.find(prefix) == 0){
                        return (*it).first;
                    }
                }
            }
        }
    }
    return gNullStr;
}

void DataMergeTags(DataArray *dest, DataArray *src) {
    MILO_ASSERT(dest, 200);
    if(dest == 0 || src == 0 || src == dest) return;
    else for(int i = 0; i < src->Size(); i++){
        DataNode* node = &src->Node(i);
        if(node->Type() == kDataArray){
            DataArray* arr = node->mValue.array;
            if(arr->Size() != 0){
                DataArray* found = dest->FindArray(CONST_ARRAY(arr)->Node(0).mValue.integer, false);
                if(found == 0){
                    dest->Resize(dest->Size() + 1);
                    dest->Node(dest->Size() - 1) = DataNode(arr, kDataArray);
                }
                else DataMergeTags(found, arr);
            }
        }
    }
}

void DataReplaceTags(DataArray *dest, DataArray *src) {
    if (dest == 0 || src == 0 || src == dest) {
        return;
    }
    for (int i = 0; i < dest->Size(); i++) {
        DataNode *node = &dest->Node(i);
        if (node->Type() == kDataArray) {
            DataArray *arr = node->mValue.array;
            if (arr->Size() != 0) {
                DataArray *found =
                    src->FindArray(CONST_ARRAY(arr)->Node(0).mValue.integer, false);
                if (found != 0) {
                    DataReplaceTags(arr, found);
                    int inner_cnt = arr->Size();
                    found->Resize(inner_cnt);
                    for (int j = 0; j < inner_cnt; j++) {
                        found->Node(j) = arr->Node(j);
                    }
                    found->SetFileLine(arr->File(), arr->Line());
                    *node = DataNode(found, kDataArray);
                }
            }
        }
    }
}

#pragma push
#pragma pool_data off
Hmx::Object* DataSetThis(Hmx::Object* o){
    Hmx::Object* old;
    ObjectDir* dir;
    if(o == gDataThis) return o;
    if(o) dir = o->DataDir();
    else dir = ObjectDir::Main();
    gDataDir = dir;
    old = gDataThis;
    gDataThis = o;
    static DataNode& thisVar = DataVariable("this");
    thisVar = DataNode(o);
    o = old;
    return o;
}
#pragma pop

Hmx::Object *DataThis() {
    return gDataThis;
}

void DataPushVar(DataNode* var){
    gVarStackPtr++;
    MILO_ASSERT(gVarStackPtr - gVarStack < VAR_STACK_SIZE, 0x137);
    gVarStackPtr->var = var;
    gVarStackPtr->value = *var;
}

void DataPopVar(){
    MILO_ASSERT(gVarStackPtr > gVarStack, 0x13E);
    *gVarStackPtr->var = gVarStackPtr->value;
    gVarStackPtr->value = DataNode(0);
    gVarStackPtr--;
}