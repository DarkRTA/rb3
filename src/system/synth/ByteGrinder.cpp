#include "ByteGrinder.h"
#include "Data.h"
#include "string.h"
#include "sdk/MSL_C/MSL_Common/printf.h"
#include "Str.h"
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

    int i = da->Int(1) & 0xFF;
    bool hasEnoughElements = da->Size() > 2;

    int hashValue = hashMapping[i];

    if (hasEnoughElements) {
        i = da->Int(1);
        for (int idx = 0; idx < sizeof(hashMapping) / sizeof(*hashMapping); idx++) {
            hashMapping[idx] = (i >> 3) & 0x1F;
            i = (i * 0x19660D) + 0x3C6EF35F;
        }

        return DataNode(kDataInt, 0);
    }

    return DataNode(kDataInt, hashValue);
}

DataNode hashTo6Bits(DataArray* da) {
    static int hashMapping[0x100];

    int i = da->Int(1) & 0xFF;
    
    bool hasEnoughElements = da->Size() > 2;

    int hashValue = hashMapping[i];

    if (hasEnoughElements) {
        i = da->Int(1);
        for (int idx = 0; idx < sizeof(hashMapping) / sizeof(*hashMapping); idx++) {
            hashMapping[idx] = (i >> 2) & 0x3F;
            i = (i * 0x19660D) + 0x3C6EF35F;
        }
        return DataNode(kDataInt, 0);
    }
    return DataNode(kDataInt, hashValue);
}

DataNode getRandomSequence32A(DataArray* da){
    static int seed;
    static bool usedUp[0x20];
    bool enough = da->Size() > 1;
    
    if(enough){
        int dataint = da->Int(1);
        memset(usedUp, 0, 0x20);
        if(dataint != 0){
            seed = dataint;
        }
        return DataNode(kDataInt, 0x610A660F);
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
        return DataNode(kDataInt, idx);
    }
}

DataNode getRandomSequence32B(DataArray* da){
    static int seed;
    static bool usedUp[0x20];
    bool enough = da->Size() > 1;
    
    if(enough){
        int dataint = da->Int(1);
        memset(usedUp, 0, 0x20);
        if(dataint != 0){
            seed = dataint;
        }
        return DataNode(kDataInt, 0x610A660F);
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
        return DataNode(kDataInt, idx);
    }
}

DataNode op0(DataArray* da){
    int i1 = da->Int(1);
    int i2 = da->Int(2);
    return DataNode(kDataInt, ((i2 ^ i1) & 0xFF));
}

DataNode op1(DataArray* da){
    int i1 = da->Int(1);
    int i2 = da->Int(2);
    return DataNode(kDataInt, ((i2 & 0xFF) + (i1 & 0xFF) & 0xFF));
}

DataNode op2(DataArray* da){
    int i1 = da->Int(1);
    int i2 = da->Int(2);
    unsigned int ret = (i2 & 0xFF) | ((i2 << 8) & 0xFF00);
    ret >>= (i1 & 7) & 0xFF;
    return DataNode(kDataInt, (unsigned char)ret);
}

DataNode op3(DataArray* da){
    int i1 = da->Int(1);
    int i2 = da->Int(2);
    unsigned int ret = (i2 & 0xFF) | ((i2 & 0xFF) << 8);
    ret >>= (i1 == 0);
    return DataNode(kDataInt, (unsigned char)ret);
}

extern DataArray* DataReadString(const char*);

unsigned long ByteGrinder::pickOneOf32A(bool b, long l){
    DataArray* a;
    char script[256];
    if(b){
        sprintf(script, "{xa %d}");
        a = DataReadString(script);
    }
    else {
        a = DataReadString("{xa}");
    }
    unsigned long result = a->Evaluate(0).Int(nullptr);
    a->Release();
    return result;
}

unsigned long ByteGrinder::pickOneOf32B(bool b, long l){
    DataArray* a;
    char script[256];
    if(b){
        sprintf(script, "{ya %d}");
        a = DataReadString(script);
    }
    else {
        a = DataReadString("{ya}");
    }
    unsigned long result = a->Evaluate(0).Int(nullptr);
    a->Release();
    return result;
}

DataNode getRandomLong(DataArray* da){
    static unsigned long s_seed;
    bool enough = da->Size() > 1;
    if(enough){
        s_seed = s_seed * 0x19660D + 0x3C6EF35F;
    }
    return DataNode(kDataInt, s_seed);
}

DataNode magicNumberGenerator(DataArray* da){
    int magic = 0x5c5c5c5c;
    if(da->Int(2) == 2){
        magic = 0x36363636;
    }
    int idx = da->Int(1);
    int v = ((idx ^ magic) * 0x19660d + 0x3c6ef35f);
    if(da->Int(2) == 1){
        v = ((int)v * 0x19660d + 0x3c6ef35f);
    }
    return DataNode(kDataInt, v);
}

void ByteGrinder::Init(){
    char buf[32];
    sprintf(buf, "O%d");
}

void ByteGrinder::GrindArray(long seedA, long seedB, unsigned char* arrayToGrind, int arrayLen, long moggVersion){
    char script[256];
    DataArray* mainScriptArray;
    
    sprintf(script, "{ma %d 2}", seedA);
    mainScriptArray = DataReadString(script);
    mainScriptArray->Evaluate(0).Int(nullptr);
    mainScriptArray->Release();
    
    sprintf(script, "{za %d 2}", seedB);
    mainScriptArray = DataReadString(script);
    mainScriptArray->Evaluate(0).Int(nullptr);
    mainScriptArray->Release();

    String mainScript;
    int encMethod = GetEncMethod(moggVersion);
    mainScript = "($foo $bar){O68($ix 0){O64{>{O65 $bar}$ix}{O66{ma{O67 $bar $ix}}";
    if(encMethod != 0){
        mainScript = "($foo $bar){O68($ix 0){O64{>{O65 $bar}$ix}{O66{za{O67 $bar $ix}}";
    }
    
    pickOneOf32B(true, seedB);
    for(int i = 0; i < 0x20; i++){
        char block[256];
        char callName[16];
        sprintf(callName, "O%d", pickOneOf32B(false, 0));
        sprintf(block, "(%d{O70 $ix}{O69 $foo{%s{O67 $bar $ix}$foo}})", i, callName);
        mainScript += block;
    }

    if(encMethod != 0){
        pickOneOf32B(true, seedA);
        for(int i = 0x20; i < 0x40; i++){
            char block[256];
            char callName[16];
            sprintf(callName, "O%d", pickOneOf32B(false, 0) + 0x20);
            sprintf(block, "(%d{O70 $ix}{O69 $foo{%s{O67 $bar $ix}$foo}})", i, callName);
            mainScript += block;
        }
    }

    mainScript += "}{O70 $ix}}}$foo";
    mainScriptArray = DataReadString(mainScript.c_str());
    for(int i = 0; i < arrayLen; i++){
        char itoaBuffer[32];
        unsigned char w = arrayToGrind[i];
        String stringArgs("");
        snprintf(itoaBuffer, sizeof(itoaBuffer), "%d", w);
        stringArgs += itoaBuffer;
        stringArgs += " (";
        for(int j = 0; j < 0x10; j++){
            snprintf(itoaBuffer, sizeof(itoaBuffer), "%d", arrayToGrind[j]);
            stringArgs += itoaBuffer;
            stringArgs += " ";
        }
        stringArgs += ")";
        DataArray* args = DataReadString(stringArgs.c_str());
        arrayToGrind[i] = mainScriptArray->ExecuteScript(0, nullptr, args, 0).Int(nullptr);
        args->Release();
    }
    mainScriptArray->Release();
}
