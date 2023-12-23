#include "data.hpp"
#include "hmx/object.hpp"
#include "varstack.hpp"

void DataMergeTags(DataArray* da, DataArray* db){
    if(da == 0 || db == 0 || db == da){
        return;
    }
    else for(int i = 0; i < db->GetNodeCount(); i++){
        DataNode* dn_b = db->GetNodeAtIndex(i);
        if(dn_b->GetType() == 0x10){
            DataArray* inner_arr = dn_b->value.dataArray;
            if(inner_arr->GetNodeCount() != 0){
                DataArray* found = da->FindArray(inner_arr->GetDataNodeValueAtIndex(0).intVal, false);
                if(found == 0){
                    da->Resize(da->GetNodeCount() + 1);
                    *(da->GetNodeAtIndex(da->GetNodeCount() - 1)) = DataNode(inner_arr, kDataArray);
                }
                else DataMergeTags(found, inner_arr);
            }
        }
    }
}

void DataReplaceTags(DataArray* da, DataArray* db){
    if(da == 0 || db == 0 || db == da){
        return;
    }
    for(int i = 0; i < da->GetNodeCount(); i++){
        DataNode* dn_a = da->GetNodeAtIndex(i);
        if(dn_a->GetType() == 0x10){
            DataArray* inner_arr = dn_a->value.dataArray;
            if(inner_arr->GetNodeCount() != 0){
                DataArray* found = db->FindArray(inner_arr->GetDataNodeValueAtIndex(0).intVal, false);
                if(found != 0){
                    DataReplaceTags(inner_arr, found);
                    int inner_cnt = inner_arr->GetNodeCount();
                    found->Resize(inner_cnt);
                    for(int j = 0; j < inner_cnt; j++){
                        *found->GetNodeAtIndex(j) = *inner_arr->GetNodeAtIndex(j);
                    }
                    found->SetFileLine(inner_arr->GetSymbol(), inner_arr->GetLine());
                    *dn_a = DataNode(found, kDataArray);
                }
            }
        }
    }
}

extern Hmx::Object* gDataThis;

Hmx::Object* DataThis(){
    return gDataThis;
}

extern VarStack* gVarStackPtr;

void DataPushVar(DataNode* dn){
    gVarStackPtr++;
    gVarStackPtr->ptr = dn;
    gVarStackPtr->node = *dn;
}

void DataPopVar(){
    *gVarStackPtr->ptr = gVarStackPtr->node;
    gVarStackPtr->node = DataNode(0);
    gVarStackPtr--;
}