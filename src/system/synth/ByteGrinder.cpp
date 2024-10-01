#include "synth/ByteGrinder.h"

#include <string.h>
#include <stdio.h>
#include <vector>
#include "types.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "utl/Str.h"
#include "os/Debug.h"
#include "synth/tomcrypt/mycrypt.h"

static unsigned char gHvKeyGreen[64] = {
    0x01,0x22,0x00,0x38,0xd2,0x01,0x78,0x8b,0xdd,0xcd,0xd0,0xf0,0xfe,0x3e,0x24,0x7f,
    0x51,0x73,0xad,0xe5,0xb3,0x99,0xb8,0x61,0x58,0x1a,0xf9,0xb8,0x1e,0xa7,0xbe,0xbf,
    0xc6,0x22,0x94,0x30,0xd8,0x3c,0x84,0x14,0x08,0x73,0x7c,0xf2,0x23,0xf6,0xeb,0x5a,
    0x02,0x1a,0x83,0xf3,0x97,0xe9,0xd4,0xb8,0x06,0x74,0x14,0x6b,0x30,0x4c,0x00,0x91
};

namespace {
    int GetEncMethod(int ver){
        int ret = 0;
        switch(ver){
            case 0xc: case 0xd: ret = 0; break;
            case 0xe: ret = 1; break;
            case 0xf: ret = 2; break;
            case 0x10: ret = 3; break;
            default:
                MILO_WARN(" Wrong encryption version passed to ByteGrinder: [%d] !\n", ver);
                break;
        }
        return ret;
    }
}

DataNode hashTo5Bits(DataArray* da) {
    static unsigned long hashMapping[0x100];
    unsigned long seed = da->Int(1) & 0xFF;
    unsigned long ret = hashMapping[seed];

    if (da->Size() > 2) {
        seed = da->Int(1);
        int max = ARRAY_LENGTH(hashMapping);
        for (int idx = 0; idx < max; idx++) {
            hashMapping[idx] = (seed >> 3) & 0x1F;
            seed = (seed * 0x19660D) + 0x3C6EF35F;
        }
        return DataNode(kDataInt, 0);
    }
    return DataNode(kDataInt, ret);
}

DataNode hashTo6Bits(DataArray* da) {
    static unsigned long hashMapping[0x100];
    unsigned long seed = da->Int(1) & 0xFF;
    unsigned long ret = hashMapping[seed];

    if (da->Size() > 2) {
        seed = da->Int(1);
        int max = ARRAY_LENGTH(hashMapping);
        for (int idx = 0; idx < max; idx++) {
            hashMapping[idx] = (seed >> 2) & 0x3F;
            seed = (seed * 0x19660D) + 0x3C6EF35F;
        }
        return DataNode(kDataInt, 0);
    }
    return DataNode(kDataInt, ret);
}

DataNode getRandomSequence32A(DataArray* da){
    static unsigned long s_seed = 0x521;
    static bool usedUp[0x20];

    if(da->Size() > 1){
        int dataint = da->Int(1);
        memset(usedUp, 0, 0x20);
        if(dataint != 0){
            s_seed = dataint;
        }
        return DataNode(kDataInt, 0x610A660F);
    }
    else {
        bool loop = true;
        int idx = 0;
        while(loop){
            s_seed = s_seed * 0x19660D + 0x3C6EF35F;
            idx = (s_seed >> 2 & 0x1F);
            if(usedUp[idx] == false){
                loop = false;
                usedUp[idx] = true;
            }
        }
        return DataNode(kDataInt, idx);
    }
}

DataNode getRandomSequence32B(DataArray* da){
    static unsigned long s_seed = 0x303F;
    static bool usedUp[0x20];

    if(da->Size() > 1){
        int dataint = da->Int(1);
        memset(usedUp, 0, 0x20);
        if(dataint != 0){
            s_seed = dataint;
        }
        return DataNode(kDataInt, 0x610A660F);
    }
    else {
        bool loop = true;
        int idx = 0;
        while(loop){
            s_seed = s_seed * 0x19660D + 0x3C6EF35F;
            idx = (s_seed >> 2 & 0x1F);
            if(usedUp[idx] == false){
                loop = false;
                usedUp[idx] = true;
            }
        }
        return DataNode(kDataInt, idx);
    }
}

#define OP_ROT_L(byte, dist) (unsigned char)((byte << (dist & 31) | byte >> (8 - dist & 31)) & 255)
#define OP_ROT_R(byte, dist) (unsigned char)((byte >> (dist & 31) | byte << (8 - dist & 31)) & 255)

DataNode op0(DataArray* msg){
    unsigned long operand = msg->Int(1);
    unsigned long w = msg->Int(2);
    return DataNode(kDataInt, u8(w ^ operand));
}

DataNode op1(DataArray* msg){
    unsigned long operand = msg->Int(1);
    unsigned long w = msg->Int(2);
    return DataNode(kDataInt, u8(u8(w) + u8(operand)));
}

DataNode op2(DataArray* msg){
    unsigned long operand = msg->Int(1);
    unsigned long w = msg->Int(2);
    unsigned long ret = u8(w) | ((w << 8) & 0xFF00);
    ret >>= u8(operand & 7);
    return DataNode(kDataInt, u8(ret));
    // can we put the return value directly in the DataNode and still have the function match?
    // return DataNode(kDataInt, (BYTE(w) | ((w << 8) & 0xFF00)) >> BYTE(operand & 7));
}

DataNode op3(DataArray* msg){
    unsigned long operand = msg->Int(1);
    unsigned long w = msg->Int(2);
    unsigned long ret = u8(w) | ((w << 8) & 0xFF00);
    ret >>= (operand == 0);
    return DataNode(kDataInt, u8(ret)); 
}

DataNode op4(DataArray* msg){
    unsigned long operand = msg->Int(1);
    unsigned long w = msg->Int(2);
    // w & 0xFF = clrlwi r0, r3, 24
    // extlwi r5, r3, 24, 3
    // Output:
    // r5 = (r3 << 3) & 0xFFFFFF00;
    // Could also be:
    // r5 = (r3 << 3) & ~0xFF;
    // r5 = (r3 >> 29) & 0xFFFFFF00;
    // r5 = (r3 & 0xFFFFFFE0) << 3;
    // Other info: accesses bits 5-28

    // rlwimi r5, r3, 27, 31, 31
    // Output:
    // r5 = ((r3<< 27) & 0x1) | (r5 & 0xFFFFFFFE);
    // Could also be:
    // r5 = ((r3<< 27) & ~0xFFFFFFFE) | (r5 & ~0x1);
    unsigned long ret = ((u8(w) == 0) << 3) & ~0xFF;
    ret = ((u8(w) << 27) & 1) | (ret & ~0x1);
    ret >>= (operand == 0);
    return DataNode(kDataInt, u8(ret));
}

DataNode op5(DataArray* msg) {
    u32 operand = msg->Int(1);
    u32 w = msg->Int(2);
    u32 ret;
    // r5 = u8(r3 NOR r3)
    // r3 = (r31 << 29) >> 29;
    // r5 |= r5 << 8
    // r5 >>= r3
    // r0 = u8(r5)
    ret = u8(~(w | w));
    u32 r3 = (operand << 29) >> 29, r4 = ret << 8;
    ret |= r4; 
    ret >>= r3;
    return DataNode(u8(ret));
}

DataNode op6(DataArray* msg) {
    u32 operand = msg->Int(1);
    u32 w = msg->Int(2);
    return DataNode(u8(!w ^ operand));
}

DataNode op7(DataArray* msg) {
    u32 operand = msg->Int(1);
    u32 w = msg->Int(2);
    u32 ret = !w + u8(operand);
    return DataNode(u8(ret));
}

DataNode op8(DataArray* msg) {
    u32 op = msg->Int(1);
    u8 ret = u8(op) + u8(msg->Int(2));
    return DataNode(ret ^ u8(op));
}

DataNode op9(DataArray* msg) {
    u32 operand = msg->Int(1);
    u32 w = msg->Int(2);
    u8 a = u8(operand), b = u8(w);
    a ^= b;
    return DataNode(u8(a + b));
}

DataNode op10(DataArray* msg) {

}
DataNode op11(DataArray* msg) {

}
DataNode op12(DataArray* msg) {

}
DataNode op13(DataArray* msg) {

}
DataNode op14(DataArray* msg) {

}
DataNode op15(DataArray* msg) {

}
DataNode op16(DataArray* msg) {

}
DataNode op17(DataArray* msg) {

}
DataNode op18(DataArray* msg) {
    u32 operand = msg->Int(1);
    u32 w = msg->Int(2);
    u8 w2 = (w & 0xFF) << 8;
    u32 w3 = (w2 & 0xFF) | (w & 0xFFFFFF00);

    return DataNode(kDataInt, u8((w3 >> 5) + operand));
}
DataNode op19(DataArray* msg) {

}
DataNode op20(DataArray* msg) {

}
DataNode op21(DataArray* msg) {

}
DataNode op22(DataArray* msg) {

}
DataNode op23(DataArray* msg) {

}
DataNode op24(DataArray* msg) {

}
DataNode op25(DataArray* msg) {

}
DataNode op26(DataArray* msg) {

}
DataNode op27(DataArray* msg) {

}
DataNode op28(DataArray* msg) {

}
DataNode op29(DataArray* msg) {

}
DataNode op30(DataArray* msg) {

}
DataNode op31(DataArray* msg) {

}
DataNode op32(DataArray* msg) {

}
DataNode op33(DataArray* msg) {

}
DataNode op34(DataArray* msg) {

}
DataNode op35(DataArray* msg) {

}
DataNode op36(DataArray* msg) {

}
DataNode op37(DataArray* msg) {

}
DataNode op38(DataArray* msg) {

}
DataNode op39(DataArray* msg) {

}
DataNode op40(DataArray* msg) {

}
DataNode op41(DataArray* msg) {

}
DataNode op42(DataArray* msg) {

}
DataNode op43(DataArray* msg) {

}
DataNode op44(DataArray* msg) {

}
DataNode op45(DataArray* msg) {

}
DataNode op46(DataArray* msg) {

}
DataNode op47(DataArray* msg) {

}
DataNode op48(DataArray* msg) {

}
DataNode op49(DataArray* msg) {

}
DataNode op50(DataArray* msg) {

}
DataNode op51(DataArray* msg) {

}
DataNode op52(DataArray* msg) {

}
DataNode op53(DataArray* msg) {

}
DataNode op54(DataArray* msg) {

}
DataNode op55(DataArray* msg) {

}
DataNode op56(DataArray* msg) {

}
DataNode op57(DataArray* msg) {

}
DataNode op58(DataArray* msg) {

}
DataNode op59(DataArray* msg) {

}
DataNode op60(DataArray* msg) {

}
DataNode op61(DataArray* msg) {

}
DataNode op62(DataArray* msg) {

}
DataNode op63(DataArray* msg) {
    u32 operand = msg->Int(1);
    u32 w = msg->Int(2);

    u32 working2 = (u8(w) ^ 255);
    u32 working3 = (u8(w) << 8);
    return DataNode(kDataInt, u8(operand ^ ((working2 | working3) >> 6)));
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
    static unsigned long s_seed = 0x521;
    if(da->Size() > 1){
        s_seed = s_seed * 0x19660D + 0x3C6EF35F;
    }
    return DataNode(kDataInt, s_seed);
}

DataNode magicNumberGenerator(DataArray* da){
    long magic = 0x5c5c5c5c;
    if(da->Int(2) == 2){
        magic = 0x36363636;
    }
    int idx = da->Int(1);
    long v = ((idx ^ magic) * 0x19660d + 0x3c6ef35f);
    if(da->Int(2) == 1){
        v = (v * 0x19660d + 0x3c6ef35f);
    }
    return DataNode(kDataInt, v);
}

#pragma dont_inline on
void ByteGrinder::Init(){
    char functionName[0x100];
    // This *must* be written out in reverse to match
    functionName[2] = '\0';
    functionName[1] = 'a';
    functionName[0] = 'N';
    DataRegisterFunc(functionName, getRandomLong);
    functionName[0] = 'h';
    DataRegisterFunc(functionName, magicNumberGenerator);
    functionName[0] = 'm';
    DataRegisterFunc(functionName, hashTo5Bits);
    functionName[0] = 'z';
    DataRegisterFunc(functionName, hashTo6Bits);
    functionName[0] = 'x';
    DataRegisterFunc(functionName, getRandomSequence32A);
    functionName[0] = 'y';
    DataRegisterFunc(functionName, getRandomSequence32B);
    std::vector<DataFunc*> funPtrs;
    funPtrs.push_back(op0);
    funPtrs.push_back(op1);
    funPtrs.push_back(op2);
    funPtrs.push_back(op3);
    funPtrs.push_back(op4);
    funPtrs.push_back(op5);
    funPtrs.push_back(op6);
    funPtrs.push_back(op7);
    funPtrs.push_back(op8);
    funPtrs.push_back(op9);
    funPtrs.push_back(op10);
    funPtrs.push_back(op11);
    funPtrs.push_back(op12);
    funPtrs.push_back(op13);
    funPtrs.push_back(op14);
    funPtrs.push_back(op15);
    funPtrs.push_back(op16);
    funPtrs.push_back(op17);
    funPtrs.push_back(op18);
    funPtrs.push_back(op19);
    funPtrs.push_back(op20);
    funPtrs.push_back(op21);
    funPtrs.push_back(op22);
    funPtrs.push_back(op23);
    funPtrs.push_back(op24);
    funPtrs.push_back(op25);
    funPtrs.push_back(op26);
    funPtrs.push_back(op27);
    funPtrs.push_back(op28);
    funPtrs.push_back(op29);
    funPtrs.push_back(op30);
    funPtrs.push_back(op31);
    pickOneOf32A(true, 0xD5);
    for(int i = 0; i < funPtrs.size(); i++){
        sprintf(functionName, "O%d", pickOneOf32A(false, 0));
        DataRegisterFunc(functionName, funPtrs[i]);
    }
    funPtrs.clear();
    funPtrs.push_back(op32);
    funPtrs.push_back(op33);
    funPtrs.push_back(op34);
    funPtrs.push_back(op35);
    funPtrs.push_back(op36);
    funPtrs.push_back(op37);
    funPtrs.push_back(op38);
    funPtrs.push_back(op39);
    funPtrs.push_back(op40);
    funPtrs.push_back(op41);
    funPtrs.push_back(op42);
    funPtrs.push_back(op43);
    funPtrs.push_back(op44);
    funPtrs.push_back(op45);
    funPtrs.push_back(op46);
    funPtrs.push_back(op47);
    funPtrs.push_back(op48);
    funPtrs.push_back(op49);
    funPtrs.push_back(op50);
    funPtrs.push_back(op51);
    funPtrs.push_back(op52);
    funPtrs.push_back(op53);
    funPtrs.push_back(op54);
    funPtrs.push_back(op55);
    funPtrs.push_back(op56);
    funPtrs.push_back(op57);
    funPtrs.push_back(op58);
    funPtrs.push_back(op59);
    funPtrs.push_back(op60);
    funPtrs.push_back(op61);
    funPtrs.push_back(op62);
    funPtrs.push_back(op63);
    pickOneOf32A(true, 0x23E);
    for(int i = 0; i < funPtrs.size(); i++){
        sprintf(functionName, "O%d", pickOneOf32A(false, 0) + 32);
        DataRegisterFunc(functionName, funPtrs[i]);
    }
}
#pragma dont_inline reset

void ByteGrinder::GrindArray(long seedA, long seedB, unsigned char* arrayToGrind, int arrayLen, int moggVersion){
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

void ByteGrinder::HvDecrypt(unsigned char* inBlock, unsigned char* outBlock, int moggVer){
    symmetric_key key;
    int enc_method = GetEncMethod(moggVer);
    void* placeholder = operator new(0x20C);
    rijndael_setup(&gHvKeyGreen[enc_method * 0x10], 0x10, 0, &key);
    rijndael_ecb_decrypt(inBlock, outBlock, &key);
    delete placeholder;
}
