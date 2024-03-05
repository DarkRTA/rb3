#include "obj/Data.h"
#include <stdlib.h>
#include <string.h>
#include <list>
#include "utl/MemMgr.h"
#include "obj/Object.h"
#include "utl/Symbol.h"
#include "os/Debug.h"
#include "math/MathFuncs.h"

std::list<bool> gDataArrayConditional;
Symbol DataArray::gFile;
bool gNodesLinearAlloc;
int gLinearNodesMemSize;
void* gLinearNodesMemPos;
int gNumLinearAllocs;
void * gLinearNodesMem;
DataArray* gCallStack[100];
DataArray** gCallStackPtr;
int gPreExecuteLevel;
int gIndent;

bool strncat_tofit(char* c, int& ri, const char* cc, int i){
    int len = strlen(cc);
    if(ri + len < i){
        strcat(&c[ri], cc);
        ri += len;
        return true;
    }
    else return false;
}

void DataAppendStackTrace(char* msg){
    if(gCallStack > gCallStackPtr){
        strcat(msg, "\n\nData Stack Trace");
        bool msg_full = false;
        int msg_len = strlen(msg);
        char visualStudioFmt[14] = "\n   %s(%d):%s";

        DataArray** ptr = gCallStackPtr;
        while(&gCallStack[gPreExecuteLevel + 3U] < ptr - 1){
            DataArray* a = *ptr;
            String s;
            if(0 < a->Size()){
                a->Node(0).Print(s, true);
            }
            if(!msg_full){
                if(!strncat_tofit(msg, msg_len, MakeString(visualStudioFmt, a->mFile.Str(), (int)a->mLine, s.c_str()), 0x400)){
                    TheDebug << MakeString("%s", msg);
                    gCallStackPtr++;
                    msg_full = true;
                    strcat(msg, "\n   ... %d omitted stack frames");
                }
            }
            if(msg_full){
                TheDebug << MakeString(visualStudioFmt, a->mFile.Str(), (int)a->mLine, s.c_str());
            }
            *ptr = a;
        }
        if(msg_full){
            TheDebug << MakeString("\n");
        }
    }
}

DataNode& DataArray::Node(int i) const {
    bool allgood = false;
    if(i >= 0 && i < mSize) allgood = true;
    if(!allgood) MILO_FAIL("Array doesn't have node %d (file %s, line %d)", i, mFile.mStr, (int)mLine);
    return mNodes[i];
}

DataNode& DataArray::Node(int i) {
    bool allgood = false;
    if(i >= 0 && i < mSize) allgood = true;
    if(!allgood) MILO_FAIL("Array doesn't have node %d (file %s, line %d)", i, mFile.mStr, (int)mLine);
    return mNodes[i];
}

void DataArray::Print(TextStream &ts, DataType type, bool b) const {
    DataNode *lol;
    DataNode *dn = mNodes;
    DataNode *dn_end = &mNodes[mSize];
    MILO_ASSERT(type & kDataArray, 0xA6);
    char begin = '\0';
    char end = '\0';
    if (type == kDataArray) {
        begin = '(';
        end = ')';
    } else if (type == kDataCommand) {
        begin = '{';
        end = '}';
    } else if (type == kDataProperty) {
        begin = '[';
        end = ']';
    }
    else MILO_FAIL("Unrecognized array type %d", type);

    while (dn < dn_end) {
        if (dn->Type() & 0x10)
            break;
        dn++;
    }

    if ((dn != dn_end) && !b) {
        ts << begin;
        lol = mNodes;
        if (lol->Type() == kDataSymbol) {
            lol->Print(ts, b);
            lol++;
        }
        ts << " ";
        gIndent += 3;
        while (lol < dn_end) {
            ts.Space(gIndent);
            lol->Print(ts, b);
            ts << " ";
            lol++;
        }
        gIndent -= 3;
        ts.Space(gIndent);
        ts << end;
    } else {
        ts << begin;
        for (lol = mNodes; lol < dn_end; lol++) {
            if (lol != mNodes)
                ts << "\n";
            lol->Print(ts, b);
        }
        ts << end;
    }
}

void* NodesLinearAlloc(int i){
    MILO_ASSERT(gLinearNodesMemSize > 0, 0x108);
    void* oldpos = gLinearNodesMemPos;
    (char*)gLinearNodesMemPos += i;
    gNumLinearAllocs++;
    // MILO_ASSERT((gLinearNodesMemPos - &gLinearNodesMem[0]) <= gLinearNodesMemSize, 1);
    return oldpos;
}

void* NodesAlloc(int i){
    if(gNodesLinearAlloc) return NodesLinearAlloc(i);
    else return _MemOrPoolAlloc(i, FastPool);
}

// extern char *lbl_8091A478; // 4 bytes long

// // this probably isn't a pointer
// extern char *lbl_8091A484; // 0x14 bytes long
// extern "C" bool fn_80315C7C(void *);

// // fn_80315C7C

// // Checks if v is within a memory region
// bool fn_80315C7C(void *v) {
//     return (v >= lbl_8091A478) && (v < &lbl_8091A478[(int)lbl_8091A484]);
// }

void NodesFree(int i, DataNode* n){
    _MemOrPoolFree(i, FastPool, n);
}

void DataArray::Insert(int count, const DataNode &dn) {
    int i = 0;
    int newNodeCount = mSize + 1;
    DataNode *oldNodes = mNodes; // Save all nodes pointer
    // allocate new nodes
    mNodes = (DataNode*)NodesAlloc(newNodeCount * sizeof(DataNode));

    for (i = 0; i < count; i++) {
        new (&mNodes[i]) DataNode(oldNodes[i]);
    }
    for (; i < count + 1; i++) {
        new (&mNodes[i]) DataNode(dn);
    }
    for (; i < newNodeCount; i++) {
        new (&mNodes[i]) DataNode(oldNodes[i - 1]);
    }
    for (i = 0; i < mSize; i++) {
        oldNodes[i].~DataNode();
    }

    // free old nodes
    NodesFree(mSize * sizeof(DataNode), oldNodes);
    mSize = newNodeCount;
}

void DataArray::InsertNodes(int count, const DataArray *da) {
    if ((da == 0) || (da->Size() == 0))
        return;
    int i = 0;
    int dacnt = da->Size();
    int newNodeCount = mSize + dacnt;
    DataNode *oldNodes = mNodes; // Save all nodes pointer
    // allocate new nodes
    mNodes = (DataNode*)NodesAlloc(newNodeCount * sizeof(DataNode));

    for (i = 0; i < count; i++) {
        new (&mNodes[i]) DataNode(oldNodes[i]);
    }

    for (; i < count + dacnt; i++) {
        new (&mNodes[i]) DataNode(da->Node(i - count));
    }

    for (; i < newNodeCount; i++) {
        new (&mNodes[i]) DataNode(oldNodes[i - dacnt]);
    }
    for (i = 0; i < mSize; i++) {
        oldNodes[i].~DataNode();
    }
    NodesFree(mSize * sizeof(DataNode), oldNodes);
    mSize = newNodeCount;
}

// fn_80315F74
void DataArray::Resize(int i) {
    DataNode *oldNodes = mNodes;
    mNodes = (DataNode*)NodesAlloc(i * sizeof(DataNode));
    int min = Minimum<int>(mSize, i);
    int cnt = 0;
    for (cnt = 0; cnt < min; cnt++) {
        new (&mNodes[cnt]) DataNode(oldNodes[cnt]);
    }
    for (; cnt < i; cnt++) {
        new (&mNodes[cnt]) DataNode();
    }
    for (cnt = 0; cnt < mSize; cnt++) {
        oldNodes[cnt].~DataNode();
    }
    NodesFree(mSize * sizeof(DataNode), oldNodes);
    mSize = i;
    mDeprecated = 0;
}

void DataArray::Remove(int index) {
    MILO_ASSERT(index < mSize, 0x1B0);
    DataNode *oldNodes = mNodes;
    int newCnt = mSize - 1;
    mNodes = (DataNode*)NodesAlloc(newCnt * sizeof(DataNode));
    int cnt = 0;
    for (cnt = 0; cnt < index; cnt++) {
        new (&mNodes[cnt]) DataNode(oldNodes[cnt]);
    }
    for (; index < newCnt; index++) {
        new (&mNodes[index]) DataNode(oldNodes[index + 1]);
    }
    for (int j = 0; j < mSize; j++) {
        oldNodes[j].~DataNode();
    }
    NodesFree(mSize * sizeof(DataNode), oldNodes);
    mSize = newCnt;
}

void DataArray::Remove(const DataNode &dn) {
    int searchType = dn.mValue.integer;
    for (int lol = mSize - 1; lol >= 0; lol--) {
        if (mNodes[lol].mValue.integer == searchType) {
            Remove(lol);
            return;
        }
    }
}

bool DataArray::Contains(const DataNode &dn) const {
    int searchType = dn.mValue.integer;
    for (int lol = mSize - 1; lol >= 0; lol--) {
        if (mNodes[lol].mValue.integer == searchType) {
            return true;
        }
    }
    return false;
}

DataArray* DataArray::FindArray(int tag, bool fail) const {
    DataNode* dn;
    DataNode* dn_end = &mNodes[mSize];
    for(dn = mNodes; dn < dn_end; dn++){
        if(dn->Type() == kDataArray){
            const DataArray* arr = dn->mValue.array;
            if(arr->Node(0).mValue.integer == tag){
                return (DataArray*)arr;
            }
        }
    }
    if(fail) MILO_FAIL("Couldn't find %d in array (file %s, line %d)", tag, mFile.mStr, mLine);
    return 0;
}

DataArray* DataArray::FindArray(Symbol tag, bool fail) const {
    DataArray* found = FindArray((int)tag.mStr, false);
    if(found == 0 && fail) MILO_FAIL("Couldn't find %s in array (file %s, line %d)", tag.mStr, mFile.mStr, mLine);
    return found;
}

DataArray *DataArray::FindArray(Symbol s1, Symbol s2) const {
    return FindArray(s1, true)->FindArray(s2, true);
}

DataArray *DataArray::FindArray(Symbol s1, Symbol s2, Symbol s3) const {
    return FindArray(s1, true)->FindArray(s2, true)->FindArray(s3, true);
}

DataArray *DataArray::FindArray(Symbol s, const char *c) const {
    return FindArray(s, Symbol(c));
}

bool DataArray::FindData(Symbol s, const char *&ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != 0) {
        ret = arr->Str(1);
        return true;
    } else
        return false;
}

bool DataArray::FindData(Symbol s, Symbol &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = (arr->Sym(1));
        return true;
    } else
        return false;
}

bool DataArray::FindData(Symbol s, String &ret, bool b) const {
    const char *c;
    bool found = FindData(s, c, b);
    if (found) {
        ret = c;
        return true;
    } else
        return false;
}

bool DataArray::FindData(Symbol s, int &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = arr->Int(1);
        return true;
    } else
        return false;
}

bool DataArray::FindData(Symbol s, float &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = arr->Float(1);
        return true;
    } else
        return false;
}

bool DataArray::FindData(Symbol s, bool &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = arr->Int(1);
        return true;
    } else
        return false;
}

DataArray* DataArray::Clone(bool b1, bool b2, int i){
    DataArray* da = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(mSize + i);
    for(int i = 0; i < mSize; i++){
        da->mNodes[i] = (b2) ? mNodes[i].Evaluate() : mNodes[i];
        if(b1){
            if(da->mNodes[i].Type() == kDataArray){
                DataArray* cloned = da->mNodes[i].LiteralArray(0)->Clone(true, b2, 0);
                da->mNodes[i] = DataNode(cloned, kDataArray);
                cloned->Release();
            }
        }
    }
    return da;
}

DataArray::DataArray(int size)
    : mFile(), mSize(size), mRefs(1), mLine(0), mDeprecated(0) {
    mNodes = (DataNode*)NodesAlloc(size * sizeof(DataNode));
    for (int n = 0; n < size; n++) {
        new (&mNodes[n]) DataNode();
    }
}

DataArray::DataArray(const void *glob, int size)
    : mFile(), mSize(-size), mRefs(1), mLine(0), mDeprecated(0) {
    mNodes = (DataNode*)NodesAlloc(size);
    memcpy(mNodes, glob, size);
}

DataArray::~DataArray() {
    if (mSize < 0)
        NodesFree(-mSize, mNodes);
    else {
        for (int i = 0; i < mSize; i++) {
            mNodes[i].~DataNode();
        }
        NodesFree(mSize * sizeof(DataNode), mNodes);
    }
}

void DataArray::SetFileLine(Symbol s, int i) {
    mFile = s;
    mLine = i;
}

int DataArray::NodeCmp(const void* a, const void* b){
    const DataNode* anode = (const DataNode*)a;
    const DataNode* bnode = (const DataNode*)b;
    switch(anode->Type()){
        case kDataFloat:
        case kDataInt:
            float a = anode->LiteralFloat(0);
            float b = bnode->LiteralFloat(0);
            if(a < b) return -1;
            return a != b;
        case kDataString:
        case kDataSymbol:
            return stricmp(anode->Str(0), bnode->Str(0));
        case kDataArray:
            return NodeCmp(&(anode->Array(0)->Node(0)), &(bnode->Array(0)->Node(0)));
        case kDataObject:
            return stricmp(anode->GetObj(0) ? anode->GetObj(0)->Name() : "", bnode->GetObj(0) ? bnode->GetObj(0)->Name() : "");
        default:
            MILO_WARN("could not sort array, bad type");
            return 0;
    }
}

void DataArray::SortNodes() {
    if (mSize <= 0)
        return;
    qsort(mNodes, mSize, 8, NodeCmp);
}

void DataArrayGlitchCB(float f, void* v){
    DataArray* arr = ((DataArray*)v);
    arr->Node(0).Print(TheDebug, true);
    TheDebug << MakeString(" took %.2f ms (File: %s Line: %d)\n", f, arr->File(), arr->Line());
}

void DataArray::Save(BinStream &bs) const {
    bs << mSize << mLine << mDeprecated;
    for (int i = 0; i < mSize; i++) {
        bs << mNodes[i];
    }
}

void DataArray::SaveGlob(BinStream &bs, bool b) const {
    if (b) {
        int i = -1 - mSize;
        bs << i;
        bs.Write(mNodes, i);
    } else {
        bs << mSize;
        bs.Write(mNodes, -mSize);
    }
}

// // fn_80317B9C
// void DataArray::LoadGlob(BinStream &bs, bool b) {
//     unsigned int v;
//     NodesFree(-mSize, mNodes);
//     if (b) {
//         bs >> v;
//         mSize = -(v + 1);
//         mNodes = NodesAlloc(-mSize);
//         bs.Read(mNodes, v);
//     } else {
//         bs >> mSize;
//         mNodes = NodesAlloc(-mSize);
//         bs.Read(mNodes, -mSize);
//     }
// }

// // extern void DataPushVar(DataNode *dn);
// // extern void DataPopVar();
// // extern Hmx::Object *DataSetThis(Hmx::Object *);

// // DataNode DataArray::ExecuteScript(int i, Hmx::Object *obj, const DataArray *da, int j) {
// //     int arrCnt;
// //     int nodeCnt = mSize;

// //     arrCnt = 0;
// //     if (i < nodeCnt - 1) {
// //         if (mNodes[i].GetType() == kDataArray) {
// //             void *arr = mNodes[i].GetDataNodeVal().dataArray;
// //             arrCnt = ((DataArray *)arr)->GetNodeCount();
// //             for (int cnt = 0; cnt < arrCnt; cnt++) {
// //                 DataNode *var = ((DataArray *)arr)->GetVarAtIndex(cnt);
// //                 DataPushVar(var);
// //                 DataNode *eval = EvaluateNodeAtIndex((DataArray *)da, cnt + j);
// //                 *var = *eval;
// //             }
// //             i++;
// //         }
// //     }
// //     DataNode ret = DataNode();
// //     if (i >= nodeCnt) {
// //         ret = DataNode(0);
// //     } else {
// //         Hmx::Object *setThis = DataSetThis(obj);
// //         ret = RunCommandsFromIndex(i);
// //         DataSetThis(setThis);
// //     }
// //     while (arrCnt-- != 0) {
// //         DataPopVar();
// //     }
// //     return ret;
// // }

TextStream& operator<<(TextStream& ts, const DataArray* da){
    if(da) da->Print(ts, kDataArray, false);
    else ts << "<null>";
    return ts;
}

BinStream &operator>>(BinStream &bs, DataArray *&da) {
    bool b;
    bs >> b;
    if (b) {
        da = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(0);
        da->Load(bs);
    } else
        da = nullptr;
    return bs;
}

BinStream &operator<<(BinStream &bs, const DataArray *da) {
    if (da != 0) {
        bs << true;
        da->Save(bs);
    } else
        bs << false;
    return bs;
}
