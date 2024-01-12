#include "bytegrinder.hpp"
#include "data.hpp"
#include "string.h"

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