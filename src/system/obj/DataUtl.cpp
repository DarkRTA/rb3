#include "Data.h"
#include "hmx/object.hpp"
#include "varstack.hpp"
#include "DataUtl.h"
#include "textfile.hpp"

void DataMergeTags(DataArray *dest, DataArray *src) {
    if(dest == 0 || src == 0 || dest == src) return;
    else for(int i = 0; i < src->Size(); i++){
        DataNode node = src->Node(i);
        if(node.Type() == kDataArray){
            DataArray* arr = node.mValue.array;
            if(arr->Size() != 0){
                DataArray* found = dest->FindArray(arr->Node(i).mValue.integer, false);
                if(found == 0){
                    dest->Resize(dest->Size() + 1);
                    dest->Node(dest->Size() - 1) = DataNode(arr, kDataArray);
                }
                else DataMergeTags(found, arr);
            }
        }
    }
}

// void DataReplaceTags(DataArray *da, DataArray *db) {
//     if (da == 0 || db == 0 || db == da) {
//         return;
//     }
//     for (int i = 0; i < da->Size(); i++) {
//         DataNode *dn_a = da->Node(i);
//         if (dn_a->GetType() == kDataArray) {
//             DataArray *inner_arr = dn_a->value.dataArray;
//             if (inner_arr->Size() != 0) {
//                 DataArray *found =
//                     db->FindArray(inner_arr->GetDataNodeValueAtIndex(0).intVal, false);
//                 if (found != 0) {
//                     DataReplaceTags(inner_arr, found);
//                     int inner_cnt = inner_arr->Size();
//                     found->Resize(inner_cnt);
//                     for (int j = 0; j < inner_cnt; j++) {
//                         *found->Node(j) = *inner_arr->Node(j);
//                     }
//                     found->SetFileLine(inner_arr->GetSymbol(), inner_arr->GetLine());
//                     *dn_a = DataNode(found, kDataArray);
//                 }
//             }
//         }
//     }
// }

// extern Hmx::Object *gDataThis;

// Hmx::Object *DataThis() {
//     return gDataThis;
// }

// extern VarStack *gVarStackPtr;

// void DataPushVar(DataNode *dn) {
//     gVarStackPtr++;
//     gVarStackPtr->ptr = dn;
//     gVarStackPtr->node = *dn;
// }

// void DataPopVar() {
//     *gVarStackPtr->ptr = gVarStackPtr->node;
//     gVarStackPtr->node = DataNode(0);
//     gVarStackPtr--;
// }