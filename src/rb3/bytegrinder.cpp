#include "bytegrinder.hpp"
#include "data.hpp"
#include "string.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"

namespace {
    int GetEncMethod(int ver){
        int ret = 0;
        switch(ver){
            case 0xc: case 0xd: ret = 0; break;
            case 0xe: ret = 1; break;
            case 0xf: ret = 2; break;
            case 0x10: ret = 3; break;
        }
        return ret;
    }
}

DataNode hashTo5Bits(DataArray *da) {
    static int hashMapping[0x100];

    int i = da->GetIntAtIndex(1) & 0xFF;
    bool hasEnoughElements = da->GetNodeCount() > 2;

    int hashValue = hashMapping[i];

    if (hasEnoughElements) {
        i = da->GetIntAtIndex(1);
        for (int idx = 0; idx < sizeof(hashMapping) / sizeof(*hashMapping); idx++) {
            hashMapping[idx] = (i >> 3) & 0x1F;
            i = (i * 0x19660D) + 0x3C6EF35F;
        }

        return DataNode(kDataInt, 0);
    }

    return DataNode(kDataInt, (void*)hashValue);
}

DataNode hashTo6Bits(DataArray* da) {
    static int hashMapping[0x100];

    int i = da->GetIntAtIndex(1) & 0xFF;
    
    bool hasEnoughElements = da->GetNodeCount() > 2;

    int hashValue = hashMapping[i];

    if (hasEnoughElements) {
        i = da->GetIntAtIndex(1);
        for (int idx = 0; idx < sizeof(hashMapping) / sizeof(*hashMapping); idx++) {
            hashMapping[idx] = (i >> 2) & 0x3F;
            i = (i * 0x19660D) + 0x3C6EF35F;
        }
        return DataNode(kDataInt, 0);
    }
    return DataNode(kDataInt, (void*)hashValue);
}

DataNode getRandomSequence32A(DataArray* da){
    static int seed;
    static bool usedUp[0x20];
    bool enough = da->GetNodeCount() > 1;
    
    if(enough){
        int dataint = da->GetIntAtIndex(1);
        memset(usedUp, 0, 0x20);
        if(dataint != 0){
            seed = dataint;
        }
        return DataNode(kDataInt, (void*)0x610A660F);
    }
    else {
        bool loop = true;
        int idx = 0;
        while(loop){
            seed = seed * 0x19660D + 0x3C6EF35F;
            idx = (seed >> 2 & 0x1F);
            if(usedUp[idx] == false){
                loop = false;
                usedUp[idx] = true;
            }
        }
        return DataNode(kDataInt, (void*)idx);
    }
}

DataNode getRandomSequence32B(DataArray* da){
    static int seed;
    static bool usedUp[0x20];
    bool enough = da->GetNodeCount() > 1;
    
    if(enough){
        int dataint = da->GetIntAtIndex(1);
        memset(usedUp, 0, 0x20);
        if(dataint != 0){
            seed = dataint;
        }
        return DataNode(kDataInt, (void*)0x610A660F);
    }
    else {
        bool loop = true;
        int idx = 0;
        while(loop){
            seed = seed * 0x19660D + 0x3C6EF35F;
            idx = (seed >> 2 & 0x1F);
            if(usedUp[idx] == false){
                loop = false;
                usedUp[idx] = true;
            }
        }
        return DataNode(kDataInt, (void*)idx);
    }
}

DataNode op0(DataArray* da){
    int i1 = da->GetIntAtIndex(1);
    int i2 = da->GetIntAtIndex(2);
    return DataNode(kDataInt, (void*)((i2 ^ i1) & 0xFF));
}

DataNode op1(DataArray* da){
    int i1 = da->GetIntAtIndex(1);
    int i2 = da->GetIntAtIndex(2);
    return DataNode(kDataInt, (void*)((i2 & 0xFF) + (i1 & 0xFF) & 0xFF));
}

DataNode op2(DataArray* da){
    int i1 = da->GetIntAtIndex(1);
    int i2 = da->GetIntAtIndex(2);
    return DataNode(kDataInt, (void*)((i2 ^ 0xFF | (i2 ^ 0xFF) << 8) >> (i1 & 7) & 0xFF));
}

DataNode op3(DataArray* da){
    int i1 = da->GetIntAtIndex(1);
    int i2 = da->GetIntAtIndex(2);
    return DataNode(kDataInt, (void*)((i2 ^ 0xFF | (i2 ^ 0xFF) << 8) >> (i1 != 0) & 0xFF));
}

extern DataArray* DataReadString(const char*);

int ByteGrinder::pickOneOf32A(bool b, long l){
    DataArray* arr;
    char buf[256];
    if(b){
        sprintf(buf, "{xa %d}");
        arr = DataReadString(buf);
    }
    else {
        arr = DataReadString("{xa}");
    }
    DataNode* node = EvaluateNodeAtIndex(arr, 0);
    int i = node->Int(nullptr);
    arr->DecRefCount();
    return i;
}

int ByteGrinder::pickOneOf32B(bool b, long l){
    DataArray* arr;
    char buf[256];
    if(b){
        sprintf(buf, "{ya %d}");
        arr = DataReadString(buf);
    }
    else {
        arr = DataReadString("{ya}");
    }
    DataNode* node = EvaluateNodeAtIndex(arr, 0);
    int i = node->Int(nullptr);
    arr->DecRefCount();
    return i;
}