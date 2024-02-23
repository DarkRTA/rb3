#include "obj/Data.h"
#include <stdlib.h>
#include <string.h>
#include <list>
#include "utl/MemMgr.h"
#include "obj/Object.h"
#include "utl/Symbol.h"
#include "os/Debug.h"

std::list<bool> gDataArrayConditional;
Symbol DataArray::gFile;
bool gNodesLinearAlloc;
int gLinearNodesMemSize;
void* gLinearNodesMemPos;
int gNumLinearAllocs;
void * gLinearNodesMem;

bool strncat_tofit(char* c, int& ri, const char* cc, int i){
    int len = strlen(cc);
    if(ri + len < i){
        strcat(&c[ri], cc);
        ri += len;
        return true;
    }
    else return false;
}

const char *UnusedStackTraceFxn() {
    return "\n\nData Stack Trace";
}

const char *UnusedStackFrameFxn() {
    return "\n   ... %d omitted stack frames";
}

extern int gIndent;

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

// // fn_80315CFC
// void DataArray::Insert(int count, const DataNode &dn) {
//     int i = 0;
//     int newNodeCount = mSize + 1;
//     DataNode *oldNodes = mNodes; // Save all nodes pointer
//     // allocate new nodes
//     mNodes = NodesAlloc(newNodeCount * sizeof(DataNode));

//     for (i = 0; i < count; i++) {
//         new (&mNodes[i]) DataNode(oldNodes[i]);
//     }
//     for (; i < count + 1; i++) {
//         new (&mNodes[i]) DataNode(dn);
//     }
//     for (; i < newNodeCount; i++) {
//         new (&mNodes[i]) DataNode(oldNodes[i - 1]);
//     }
//     for (i = 0; i < mSize; i++) {
//         oldNodes[i].~DataNode();
//     }

//     // free old nodes
//     NodesFree(mSize * sizeof(DataNode), oldNodes);
//     mSize = newNodeCount;
// }

// // fn_80315E1C
// void DataArray::InsertNodes(int count, const DataArray *da) {
//     if ((da == 0) || (da->Size() == 0))
//         return;
//     int i = 0;
//     int dacnt = da->Size();
//     int newNodeCount = mSize + dacnt;
//     DataNode *oldNodes = mNodes; // Save all nodes pointer
//     // allocate new nodes
//     mNodes = NodesAlloc(newNodeCount * sizeof(DataNode));

//     for (i = 0; i < count; i++) {
//         new (&mNodes[i]) DataNode(oldNodes[i]);
//     }

//     for (; i < count + dacnt; i++) {
//         new (&mNodes[i]) DataNode(da->Node(i - count));
//     }

//     for (; i < newNodeCount; i++) {
//         new (&mNodes[i]) DataNode(oldNodes[i - dacnt]);
//     }
//     for (i = 0; i < mSize; i++) {
//         oldNodes[i].~DataNode();
//     }
//     NodesFree(mSize * sizeof(DataNode), oldNodes);
//     mSize = newNodeCount;
// }

// // fn_80315F74
// void DataArray::Resize(int i) {
//     DataNode *oldNodes = mNodes;
//     mNodes = NodesAlloc(i * sizeof(DataNode));
//     int min = Minimum(mSize, i);
//     int cnt = 0;
//     for (cnt = 0; cnt < min; cnt++) {
//         new (&mNodes[cnt]) DataNode(oldNodes[cnt]);
//     }
//     for (; cnt < i; cnt++) {
//         new (&mNodes[cnt]) DataNode();
//     }
//     for (cnt = 0; cnt < mSize; cnt++) {
//         oldNodes[cnt].~DataNode();
//     }
//     NodesFree(mSize * sizeof(DataNode), oldNodes);
//     mSize = i;
//     mDeprecated = 0;
// }

// // fn_80316064
// void DataArray::Remove(int i) {
//     DataNode *oldNodes = mNodes;
//     int newCnt = mSize - 1;
//     mNodes = NodesAlloc(newCnt * sizeof(DataNode));
//     int cnt = 0;
//     for (cnt = 0; cnt < i; cnt++) {
//         new (&mNodes[cnt]) DataNode(oldNodes[cnt]);
//     }
//     for (; i < newCnt; i++) {
//         new (&mNodes[i]) DataNode(oldNodes[i + 1]);
//     }
//     for (int j = 0; j < mSize; j++) {
//         oldNodes[j].~DataNode();
//     }
//     NodesFree(mSize * sizeof(DataNode), oldNodes);
//     mSize = newCnt;
// }

// // fn_80316150
// void DataArray::Remove(const DataNode &dn) {
//     int searchType = dn.mValue.integer;
//     for (int lol = mSize - 1; lol >= 0; lol--) {
//         if (mNodes[lol].mValue.integer == searchType) {
//             Remove(lol);
//             return;
//         }
//     }
// }

// // fn_80315F74
// void DataArray::Resize(int i) {
//     DataNode *oldNodes = mNodes;
//     mNodes = NodesAlloc(i * sizeof(DataNode));
//     int min = MIN(mSize, i);
//     int cnt = 0;
//     for (cnt = 0; cnt < min; cnt++) {
//         new (&mNodes[cnt]) DataNode(oldNodes[cnt]);
//     }
//     for (; cnt < i; cnt++) {
//         new (&mNodes[cnt]) DataNode();
//     }
//     for (cnt = 0; cnt < mSize; cnt++) {
//         oldNodes[cnt].~DataNode();
//     }
//     NodesFree(mSize * sizeof(DataNode), oldNodes);
//     mSize = i;
//     mDeprecated = 0;
// }

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

// // // fn_803169C4
// // DataArray *DataArray::Clone(bool b1, bool b2, int i) {
// //     DataArray *da = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(mSize + i);
// //     for (int i = 0; i < mSize; i++) {
// //         DataNode evaluated;
// //         if (b2) {
// //             DataNode *dn = &mNodes[i];
// //             evaluated = dn->Evaluate();
// //         } else
// //             evaluated = &mNodes[i];
// //         da->mNodes[i] = *evaluated;
// //         if (b1) {
// //             if (da->mNodes[i].GetType() == 0x10) {
// //                 DataArray *arr = da->mNodes[i].LiteralArray(0);
// //                 DataArray *cloned = arr->Clone(true, b2, 0);
// //                 da->mNodes[i] = DataNode(cloned, (DataType)0x10);
// //                 cloned->DecRefCount();
// //             }
// //         }
// //     }
// //     return da;
// // }

// DataArray::DataArray(int size)
//     : mFile(), mSize(size), mRefs(1), mLine(0), mDeprecated(0) {
//     mNodes = NodesAlloc(size * sizeof(DataNode));
//     for (int n = 0; n < size; n++) {
//         new (&mNodes[n]) DataNode();
//     }
// }

DataArray::DataArray(const void *glob, int size)
    : mFile(), mSize(-size), mRefs(1), mLine(0), mDeprecated(0) {
    mNodes = (DataNode*)NodesAlloc(size);
    memcpy(mNodes, glob, size);
}

// DataArray::~DataArray() {
//     if (mSize < 0)
//         NodesFree(-mSize, mNodes);
//     else {
//         for (int i = 0; i < mSize; i++) {
//             mNodes[i].~DataNode();
//         }
//         NodesFree(mSize * sizeof(DataNode), mNodes);
//     }
// }

void DataArray::SetFileLine(Symbol s, int i) {
    mFile = s;
    mLine = i;
}

// int NodeCmp(const void *a, const void *b) {
//     DataNode *da = (DataNode *)a;
//     DataNode *db = (DataNode *)b;
//     switch (da->Type()) {
//     case kDataFloat:
//     case kDataInt:
//         double d1 = da->LiteralFloat(nullptr);
//         double d2 = db->LiteralFloat(nullptr);
//         if (d1 < d2)
//             return -1;
//         return (d1 != d2);
//     case kDataString:
//     case kDataSymbol:
//         return stricmp(da->Str(nullptr), db->Str(nullptr));
//     case kDataArray:
//         return NodeCmp(
//             &(da->Array(nullptr)->Node(0)), &(db->Array(nullptr)->Node(0))
//         );
//     case kDataObject:
//         Hmx::Object *obj = da->GetObj(nullptr);
//         char *c1;
//         char *c2;
//         if (obj != nullptr) {
//             c1 = (char *)(da->GetObj(nullptr)->Name());
//         } else
//             c1 = '\0';
//         obj = db->GetObj(nullptr);
//         if (obj != nullptr) {
//             c2 = (char *)(db->GetObj(nullptr)->Name());
//         } else
//             c2 = '\0';
//         return stricmp(c1, c2);
//     default:
//         return 0;
//     }
// }

// void DataArray::SortNodes() {
//     if (mSize <= 0)
//         return;
//     qsort(mNodes, mSize, 8, NodeCmp);
// }

// BinStream &operator<<(BinStream &bs, const DataNode *dn);

// // fn_803171F8
// void DataArray::Save(BinStream &bs) const {
//     bs << mSize << mLine << mDeprecated;
//     for (int i = 0; i < mSize; i++) {
//         bs << &mNodes[i];
//     }
// }

// // fn_80317278
// BinStream &operator<<(BinStream &bs, const DataNode *dn) {
//     dn->Save(bs);
//     return bs;
// }

// // fn_80317AE0
// BinStream &operator>>(BinStream &bs, DataNode *dn) {
//     dn->Load(bs);
//     return bs;
// }

// // fn_80317B18
// void DataArray::SaveGlob(BinStream &bs, bool b) const {
//     if (b) {
//         int i = -1 - mSize;
//         bs << (unsigned int)i;
//         bs.Write(mNodes, i);
//     } else {
//         bs << mSize;
//         bs.Write(mNodes, -mSize);
//     }
// }

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

// // fn_80317E5C
// TextStream &operator<<(TextStream &ts, const DataArray *da) {
//     if (da != nullptr)
//         da->Print(ts, kDataArray, false);
//     else
//         ts << "<null>";
//     return ts;
// }

// // fn_80317EB8
// BinStream &operator>>(BinStream &bs, DataArray *&da) {
//     bool b;
//     bs >> b;
//     if (b) {
//         da = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(0);
//         da->Load(bs);
//     } else
//         da = nullptr;
//     return bs;
// }

// // fn_80317F3C
// BinStream &operator<<(BinStream &bs, const DataArray *da) {
//     if (da != nullptr) {
//         bs << (char)1;
//         da->Save(bs);
//     } else
//         bs << (char)0;
//     return bs;
// }
