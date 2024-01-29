#include "propsync.hpp"
#include "symbols.hpp"

bool PropSync(String& str, DataNode& node, DataArray* da, int i, PropOp op){
    da->GetNodeCount();
    if(op == (PropOp)1) node = DataNode(str.c_str());
    else str = node.Str(0);
    return true;
}

bool PropSync(Sphere& sphere, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(sphere.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(sphere.y, node, da, i + 1, op);
        }
        if(sym == SymZ){
            return PropSync(sphere.z, node, da, i + 1, op);
        }
        if(sym == SymRadius){
            return PropSync(sphere.radius, node, da, i + 1, op);
        }
        else return false;
    }
    return true;
}

bool PropSync(Vector2& vec, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(vec.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(vec.y, node, da, i + 1, op);
        }
        else return false;
    }
    return true;
}

bool PropSync(Vector3& vec, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(vec.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(vec.y, node, da, i + 1, op);
        }
        if(sym == SymZ){
            return PropSync(vec.z, node, da, i + 1, op);
        }
        else return false;
    }
    return true;
}

// undefined4
// PropSync(Vector2 *param_1,DataNode *param_2,DataArray *param_3,int param_4,PropOp param_5)

// {
//   int iVar1;
//   undefined4 uVar2;
//   undefined4 local_28;
//   Symbol aSStack_24 [16];
  
//   iVar1 = DataArray::GetNodeCount(param_3);
//   if (param_4 == iVar1) {
//     uVar2 = 1;
//   }
//   else {
//     local_28 = DataArray::GetSymAtIndex(param_3,param_4);
//     Symbol::operator=(aSStack_24,(Symbol *)&local_28);
//     iVar1 = Symbol::operator==(aSStack_24,(Symbol *)&SymX);
//     if (iVar1 == 0) {
//       iVar1 = Symbol::operator==(aSStack_24,(Symbol *)&SymY);
//       if (iVar1 == 0) {
//         uVar2 = 0;
//       }
//       else {
//         uVar2 = PropSync((float *)(param_1 + 4),param_2,param_3,param_4 + 1,param_5);
//       }
//     }
//     else {
//       uVar2 = PropSync((float *)param_1,param_2,param_3,param_4 + 1,param_5);
//     }
//   }
//   return uVar2;
// }