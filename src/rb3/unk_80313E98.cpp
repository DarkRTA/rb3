#include "data.hpp"
#include "symbol.hpp"
#include "std/string.h"
#include "std/stdlib.h"

// fn_80313F64
Symbol GetStringStrummedSymbol(){
    static Symbol lbl_8091A254("string_strummed");
    return lbl_8091A254;
}

// fn_80313FB0
Symbol GetStringStoppedSymbol(){
    static Symbol lbl_8091A258("string_stopped");
    return lbl_8091A258;
}

// fn_803140C8
Symbol GetRGAccelerometerSymbol(){
    static Symbol lbl_8091A25C("rg_accelerometer");
    return lbl_8091A25C;
}

// fn_803141A0
Symbol GetRGConnectedAccessoriesSymbol(){
    static Symbol lbl_8091A260("rg_connected_accessories");
    return lbl_8091A260;
}

// fn_80314278
Symbol GetRGPitchBend(){
    static Symbol lbl_8091A264("rg_pitch_bend");
    return lbl_8091A264;
}

// fn_80314350
Symbol GetRGMutingSymbol(){
    static Symbol lbl_8091A268("rg_muting");
    return lbl_8091A268;
}

// fn_80314428
Symbol GetRGStompBoxSymbol(){
    static Symbol lbl_8091A26C("rg_stomp_box");
    return lbl_8091A26C;
}

// fn_80314500
Symbol GetRGProgramChangeSymbol(){
    static Symbol lbl_8091A270("rg_program_change");
    return lbl_8091A270;
}

// fn_803145D8
Symbol GetRGSwingSymbol(){
    static Symbol lbl_8091A274("rg_swing");
    return lbl_8091A274;
}

// fn_803146D0
Symbol GetRGFretButtonDownSymbol(){
    static Symbol lbl_8091A278("rg_fret_button_down");
    return lbl_8091A278;
}

// fn_803147C8
Symbol GetRGFretButtonUpSymbol(){
    static Symbol lbl_8091A27C("rg_fret_button_up");
    return lbl_8091A27C;
}

// fn_80315324
Symbol GetKeyboardKeyReleasedSymbol(){
    static Symbol lbl_808FC8B4("keyboard_key_released");
    return lbl_808FC8B4;
}

// fn_803153FC
Symbol GetKeyboardModSymbol(){
    static Symbol lbl_808FC8B8("keyboard_mod");
    return lbl_808FC8B8;
}

// fn_803154D4
Symbol GetKeyboardExpressionPedalSymbol(){
    static Symbol lbl_808FC8BC("keyboard_expression_pedal");
    return lbl_808FC8BC;
}

// fn_803155AC
Symbol GetKeyboardConnectedAccessoriesSymbol(){
    static Symbol lbl_808FC8C0("keyboard_connected_accessories");
    return lbl_808FC8C0;
}

// fn_80315684
Symbol GetKeyboardSustainSymbol(){
    static Symbol lbl_808FC8C4("keyboard_sustain");
    return lbl_808FC8C4;
}

// fn_8031575C
Symbol GetKeyboardStompBoxSymbol(){
    static Symbol lbl_808FC8C8("keyboard_stomp_box");
    return lbl_808FC8C8;
}

// fn_80315874
Symbol GetKeysAccelerometerSymbol(){
    static Symbol lbl_808FC8CC("keys_accelerometer");
    return lbl_808FC8CC;
}

// fn_8031594C
Symbol GetKeyboardLowHandPlacementSymbol(){
    static Symbol lbl_808FC8D0("keyboard_low_hand_placement");
    return lbl_808FC8D0;
}

// fn_80315A24
Symbol GetKeyboardHighHandPlacementSymbol(){
    static Symbol lbl_808FC8D4("keyboard_high_hand_placement");
    return lbl_808FC8D4;
}

extern DataNode* NodesAlloc(int);

DataArray::DataArray(int i) : symbol(), mNodeCount(i), mRefCount(1), mLine(0), mUnknown(0) {
    mNodes = NodesAlloc(i * sizeof(DataNode));
    for(int n = 0; n < i; n++){
        DataNode* dn = &mNodes[n];
        if(dn != nullptr) dn = new DataNode();
    }
}

DataArray::DataArray(const void* v, int i) : symbol(), mNodeCount(-i), mRefCount(1), mLine(0), mUnknown(0) {
    mNodes = NodesAlloc(i);
    memcpy(mNodes, v, i);
}

extern void NodesFree(int, DataNode*);

DataArray::~DataArray(){
    if(mNodeCount < 0) NodesFree(-mNodeCount, mNodes);
    else {
        for(int i = 0; i < mNodeCount; i++){
            delete &mNodes[i];
        }
        NodesFree(mNodeCount * sizeof(DataNode), mNodes);
    }
}

int NodeCmp(const void* a, const void* b){
    DataNode* da = (DataNode*)a;
    DataNode* db = (DataNode*)b;
    switch(da->GetType()){
        case FLOAT_VALUE: 
        case EMPTY:
            double d1 = da->LiteralFloat(nullptr);
            double d2 = db->LiteralFloat(nullptr);
            if(d1 < d2) return -1;
            return (d1 != d2);
        case STRING_VALUE:
        case SYMBOL:
            const char* s1 = da->Str(nullptr);
            const char* s2 = db->Str(nullptr);
            return stricmp(s1, s2);
        default:
            return 0;
    }
}

void DataArray::SortNodes(){
    if(mNodeCount <= 0) return;
    qsort(mNodes, mNodeCount, 8, NodeCmp);
}

// fn_80317B18
void DataArray::SaveGlob(BinStream& bs, bool b) const {
    if(b){
        int i = -1 - mNodeCount;
        bs.WriteWord(i);
        bs.Write(mNodes, i);
    }
    else {
        bs.WriteHalfWord(mNodeCount);
        bs.Write(mNodes, -mNodeCount);
    }
}

// fn_80317B9C
void DataArray::LoadGlob(BinStream& bs, bool b){
    int v;
    NodesFree(-mNodeCount, mNodes);
    if(b){
        bs.ReadWord(&v);
        mNodeCount = -(v + 1);
        mNodes = NodesAlloc(-mNodeCount);
        bs.Read(mNodes, v);
    }
    else {
        bs.ReadHalfWord(&mNodeCount);
        mNodes = NodesAlloc(-mNodeCount);
        bs.Read(mNodes, -mNodeCount);
    }
}