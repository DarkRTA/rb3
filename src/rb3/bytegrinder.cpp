#include "bytegrinder.hpp"
#include "data.hpp"
#include "string.h"
#include "sdk/MSL_C/MSL_Common/printf.h"
#include "string.hpp"
#include <vector>

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
    unsigned int ret = (i2 & 0xFF) | ((i2 << 8) & 0xFF00);
    ret >>= (i1 & 7) & 0xFF;
    return DataNode(kDataInt, (void*)(unsigned char)ret);
}

DataNode op3(DataArray* da){
    int i1 = da->GetIntAtIndex(1);
    int i2 = da->GetIntAtIndex(2);
    unsigned int ret = (i2 & 0xFF) | ((i2 & 0xFF) << 8);
    ret >>= (i1 == 0);
    return DataNode(kDataInt, (void*)(unsigned char)ret);
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

DataNode getRandomLong(DataArray* da){
    static int seed;
    bool enough = da->GetNodeCount() > 1;
    if(enough){
        seed = seed * 0x19660D + 0x3C6EF35F;
    }
    return DataNode(kDataInt, (void*)seed);
}

DataNode magicNumberGenerator(DataArray* da){
    int magic = 0x5c5c5c5c;
    if(da->GetIntAtIndex(2) == 2){
        magic = 0x36363636;
    }
    int idx = da->GetIntAtIndex(1);
    void* v = (void*)((idx ^ magic) * 0x19660d + 0x3c6ef35f);
    if(da->GetIntAtIndex(2) == 1){
        v = (void*)((int)v * 0x19660d + 0x3c6ef35f);
    }
    return DataNode(kDataInt, v);
}

void ByteGrinder::Init(){
    char buf[32];
    sprintf(buf, "O%d");
}

void ByteGrinder::GrindArray(long l1, long l2, unsigned char* uc, int len, long l3){
    char buf1[268];
    char buf_loop1_1[16];
    char buf_loop2_2[256];
    char buf_loop1_2[256];
    char buf_loop2_1[16];
    char buf3[32];
    
    sprintf(buf1, "{ma %d 2}", l1);
    DataArray* arr = DataReadString(buf1);
    EvaluateNodeAtIndex(arr, 0)->Int(nullptr);
    arr->DecRefCount();

    sprintf(buf1, "{za %d 2}", l2);
    arr = DataReadString(buf1);
    EvaluateNodeAtIndex(arr, 0)->Int(nullptr);
    arr->DecRefCount();

    String str;
    int enc_method = GetEncMethod(l3);
    str = "($foo $bar){O68($ix 0){O64{>{O65 $bar}$ix}{O66{ma{O67 $bar $ix}}";
    if(enc_method != 0){
        str = "($foo $bar){O68($ix 0){O64{>{O65 $bar}$ix}{O66{za{O67 $bar $ix}}";
    }
    
    pickOneOf32B(true, l2);
    for(int i = 0; i < 0x20; i++){
        sprintf(buf_loop1_1, "O%d", pickOneOf32B(false, 0));
        sprintf(buf_loop1_2, "(%d{O70 $ix}{O69 $foo{%s{O67 $bar $ix}$foo}})", i, buf_loop1_1);
        str += buf_loop1_2;
    }

    if(enc_method != 0){
        pickOneOf32B(true, l1);
        for(int i = 0x20; i < 0x40; i++){
            sprintf(buf_loop2_1, "O%d", pickOneOf32B(false, 0) + 0x20);
            sprintf(buf_loop2_2, "(%d{O70 $ix}{O69 $foo{%s{O67 $bar $ix}$foo}})", i , buf_loop2_1);
            str += buf_loop2_2;
        }
    }

    str += "}{O70 $ix}}}$foo";
    arr = DataReadString(str.c_str());
    for(int i = 0; i < len; i++){
        {
            unsigned char c = uc[i];
            String inner_str("");
            snprintf(buf3, sizeof(buf3), "%d", c);
            inner_str += buf3;
            inner_str += " (";
            for(int j = 0; j < 0x10; j++){
                snprintf(buf3, sizeof(buf3), "%d", uc[j]);
                inner_str += buf3;
                inner_str += " ";
            }
            inner_str += ")";
            DataArray* arr_inner = DataReadString(inner_str.c_str());
            {
                DataNode exec = arr->ExecuteScript(0, nullptr, arr_inner, 0);
                uc[i] = exec.Int(nullptr);
            }
            arr_inner->DecRefCount();
        }
    }
    arr->DecRefCount();

}