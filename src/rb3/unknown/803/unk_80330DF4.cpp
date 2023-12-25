#include "hmx/object.hpp"
#include "data.hpp"
#include "common.hpp"

DataNode Hmx::Object::OnGetArray(const DataArray* da){
    DataArray* arr = da->GetArrayAtIndex(2);
    int size = PropertySize(arr);
    DataArray* cloned = arr->Clone(true, false, 1);
    {
    DataNode size_node(size);
    DataNode* node = cloned->GetNodeAtIndex(cloned->GetNodeCount() - 1);
    *node = size_node;
    }
    InsertProperty(cloned, *EvaluateNodeAtIndex((DataArray*)da, 3));
    cloned->DecRefCount();
    return DataNode(size);
}

void Hmx::Object::SetTypeDef(DataArray* da){
    if(arr != da){
        if(arr != nullptr){
            arr->DecRefCount();
            arr = 0;
        }
        props.ClearAll();
        arr = da;
        if(da != nullptr) da->IncRefCount();
    }
}

extern const char* gNullStr;

Hmx::Object::Object(){
    arr = 0;
    name = gNullStr;
    unk10 = 0;
}

DataNode* Hmx::Object::Property(Symbol s, bool b){
    static DataArrayPtr d(DataNode(1));
    {
    DataNode sym_node(s);
    DataNode* ptr_node = d.GetNodeAtIndex(0);
    *ptr_node = sym_node;
    }
    return Property(d.arr, b);
}

bool Hmx::Object::SyncProperty(DataNode& dn, DataArray* da, int i, PropOp op){
    if(da->GetNodeCount() == i){
        return true;
    }
    else {
        Symbol asdf = da->GetSymAtIndex(i);
        return false;
    }
}

extern char* PathName(const Hmx::Object*);

DataNode* Hmx::Object::Property(DataArray* da, bool b){
    static DataNode n;
    if(SyncProperty(n, da, 0, (PropOp)1)) return &n;
    else {
        return nullptr;
    }
}

// int ** __thiscall Hmx::Object::Property(Object *this,DataArray *param_1,bool param_2)

// {
//   int iVar1;
//   int **ppiVar2;
//   int *piVar3;
//   undefined3 in_register_00000014;
  
//   if (@GUARD@Property__Q23Hmx6ObjectFP9DataArrayb@n == '\0') {
//     @LOCAL@Property__Q23Hmx6ObjectFP9DataArrayb@n = 0;
//     DAT_80712e64 = 0;
//     __register_global_object
//               (&@LOCAL@Property__Q23Hmx6ObjectFP9DataArrayb@n,DataNode::~DataNode,@13677);
//     @GUARD@Property__Q23Hmx6ObjectFP9DataArrayb@n = '\x01';
//   }
//   iVar1 = (**(code **)(*(int *)this + 0x24))
//                     (this,&@LOCAL@Property__Q23Hmx6ObjectFP9DataArrayb@n,param_1,0,1);
//   if (iVar1 != 0) {
//     return (int **)&@LOCAL@Property__Q23Hmx6ObjectFP9DataArrayb@n;
//   }
//   DataNode::Sym(*(DataNode **)param_1,param_1);
//   ppiVar2 = (int **)TypeProps::KeyValue((TypeProps *)(this + 4),(Symbol)0xe0,false);
//   if (((ppiVar2 == (int **)0x0) && (*(DataArray **)(this + 0x10) != (DataArray *)0x0)) &&
//      (piVar3 = (int *)DataArray::FindArray(*(DataArray **)(this + 0x10),(Symbol)0xdc,param_2),
//      piVar3 != (int *)0x0)) {
//     ppiVar2 = (int **)DataNode::Evaluate((DataNode *)(*piVar3 + 8));
//   }
//   if (ppiVar2 != (int **)0x0) {
//     if (*(short *)(param_1 + 8) == 1) {
//       return ppiVar2;
//     }
//     if ((*(short *)(param_1 + 8) == 2) && (ppiVar2[1] == (int *)0x10)) {
//       piVar3 = *ppiVar2;
//       iVar1 = DataNode::Int((DataNode *)(*(int *)param_1 + 8),param_1);
//       return (int **)(*piVar3 + iVar1 * 8);
//     }
//   }
//   if (CONCAT31(in_register_00000014,param_2) != 0) {
//     PathName(this);
//   }
//   return (int **)0x0;
// }