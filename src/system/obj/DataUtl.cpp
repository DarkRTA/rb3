#include "obj/DataUtl.h"

#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/TextFile.h"
#include "varstack.hpp"

void DataMergeTags(DataArray *dest, DataArray *src) {
    if(dest == 0 || src == 0 || dest == src) return;
    else for(int i = 0; i < src->Size(); i++){
        DataNode* node = &src->Node(i);
        if(node->Type() == kDataArray){
            DataArray* arr = node->mValue.array;
            if(arr->Size() != 0){
                DataArray* found = dest->FindArray(arr->Union(0).integer, false);
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
                    src->FindArray(arr->Union(0).integer, false);
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

extern Hmx::Object *gDataThis;

Hmx::Object *DataThis() {
    return gDataThis;
}

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
