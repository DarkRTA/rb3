// #include "typeprops.hpp"
#include "hmx/object.hpp"
#include "data.hpp"

DataNode* TypeProps::KeyValue(Symbol s, bool b){
    if(data != nullptr){
        for(int i = data->GetNodeCount() - 2; i >=0; i--){
            data->GetDataNodeValueAtIndex(i);
        }
    }
    else return nullptr;
}