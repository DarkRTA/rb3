#include "data.hpp"
#include "symbol.hpp"
#include "std/string.h"
#include "std/stdlib.h"
#include "common.hpp"

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

extern int gIndent;

// fn_80315A70
void DataArray::Print(TextStream& ts, DataType ty, bool b) const {
    DataNode* dn = mNodes;
    DataNode* dn_end = &mNodes[mNodeCount];
    char begin = '\0';
    char end = '\0';
    if(ty == 0x10){
        begin = '(';
        end = ')';
    }
    else if(ty == 0x11){
        begin = '{';
        end = '}';
    }
    else if(ty == 0x13){
        begin = '[';
        end = ']';
    }

    while(dn < dn_end){
        if (dn->GetType() & 0x10) break;
        dn++;
    }
    
    if((dn == dn_end) || !b){
        ts << begin;
        DataNode* lol = mNodes;
        if(lol->GetType() == 5){
            lol->Print(ts, b);
            lol++;
        }
        ts << " ";
        gIndent += 3;
        while(lol < dn_end){
            ts.Space(gIndent);
            lol->Print(ts, b);
            ts << " ";
            lol++;
        }
        gIndent -= 3;
        ts.Space(gIndent);
        ts << end;
    }
    else {
        ts << begin;
        for(DataNode* bruh = mNodes; bruh < dn_end; bruh++){
            if(bruh != mNodes) ts << "\n";
            bruh->Print(ts, b);
        }
        ts << end;
    }
}

extern DataNode* NodesAlloc(int);

DataArray::DataArray(int i) : symbol(), mNodeCount(i), mRefCount(1), mLine(0), mUnknown(0) {
    mNodes = NodesAlloc(i * sizeof(DataNode));
    for(int n = 0; n < i; n++){
        new (&mNodes[n]) DataNode();
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

// fn_80316CB0
void DataArray::SetFileLine(Symbol s, int i){
    symbol = s;
    mLine = i;
}

extern "C" void fn_80315CFC(DataArray*, int, DataNode*);

void fn_80315CFC(DataArray* da, int count, DataNode* dn) {
    // seems to reconstruct or add a DataNode to a DataArray
    int i = 0;
    int newNodeCount = da->mNodeCount + 1;
    DataNode* oldNodes = da->mNodes; // Save all nodes pointer
    // allocate new nodes
    da->mNodes = NodesAlloc(newNodeCount * sizeof(DataNode));
    
    for(i = 0; i < count; i++){
        new (&da->mNodes[i]) DataNode(oldNodes[i]);
    }
    for(; i < count + 1; i++){
        new (&da->mNodes[i]) DataNode(*dn);
    }
    for(; i < newNodeCount; i++){
        new (&da->mNodes[i]) DataNode(oldNodes[i - 1]);
    }
    for(i = 0; i < da->mNodeCount; i++){
        oldNodes[i].~DataNode();
    }

    // free old nodes
    NodesFree(da->mNodeCount * sizeof(DataNode), oldNodes);
    da->mNodeCount = newNodeCount;
}