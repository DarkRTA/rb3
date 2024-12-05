#include "decomp.h"
#include "obj/Data.h"
#include <stdlib.h>
#include <string.h>
#include <list>
#include "math/Utl.h"
#include "obj/Object.h"
#include "obj/DataFile.h"
#include "obj/DataFunc.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include "utl/Symbol.h"

int gIndent;

std::list<bool> gDataArrayConditional;

Symbol DataArray::gFile;
DataFunc* DataArray::sDefaultHandler;

DataFunc* gPreExecuteFunc;
int gPreExecuteLevel;

DataArray* gCallStack[HANDLE_STACK_SIZE];
DataArray** gCallStackPtr = gCallStack;

char* gLinearNodesMem;
char* gLinearNodesMemPos;
int gNumLinearAllocs;
int gLinearNodesMemSize;
bool gNodesLinearAlloc;

class DataCallStackFrame {
public:
    DataCallStackFrame(DataArray* arr) {
        MILO_ASSERT(gCallStackPtr - gCallStack < HANDLE_STACK_SIZE, 48);
        *gCallStackPtr++ = arr;

        if (gPreExecuteFunc && (gCallStackPtr - gCallStack) <= gPreExecuteLevel) {
            gPreExecuteFunc(arr);
        }
    }

    ~DataCallStackFrame() {
        if (--gCallStackPtr == gCallStack) {
            gPreExecuteFunc = nullptr;
        }
    }

private:
};

// required to match `__FUNCTION__` strings
DECOMP_FORCEBLOCK(DataArray, (std::vector<Vector3>& v),
    v.erase(v.begin(), v.end());
)

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
    if(gCallStackPtr <= gCallStack){
        return;
    }

    strcat(msg, "\n\nData Stack Trace");

    bool msg_full = false;
    int msg_len = strlen(msg);

    for (DataArray **ptr = gCallStackPtr - 1; ptr >= gCallStack; ptr--){
        DataArray* a = *ptr;

        String s;
        if(a->Size() > 0){
            a->Node(0).Print(s, true);
        }

        char visualStudioFmt[] = "\n   %s(%d):%s";
        if(!msg_full){
            if(!strncat_tofit(msg, msg_len, MakeString(visualStudioFmt, a->mFile.Str(), (int)a->mLine, s.c_str()), 0x400)){
                TheDebug << MakeString("%s", msg);
                msg_full = true;
                strcat(msg, MakeString("\n   ... %d omitted stack frames", (ptr - gCallStack) + 1));
            }
        }

        if(msg_full){
            TheDebug << MakeString(visualStudioFmt, a->mFile.Str(), (int)a->mLine, s.c_str());
        }
    }

    if(msg_full){
        TheDebug << MakeString("\n");
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
    DataNode *i = mNodes;
    DataNode *end = &mNodes[mSize];
    MILO_ASSERT(type & kDataArray, 0xA6);
    char open = '\0';
    char close = '\0';
    if (type == kDataArray) {
        open = '(';
        close = ')';
    } else if (type == kDataCommand) {
        open = '{';
        close = '}';
    } else if (type == kDataProperty) {
        open = '[';
        close = ']';
    } else {
        MILO_FAIL("Unrecognized array type %d", type);
    }

    i = mNodes;
    while (i < end) {
        if (i->Type() & kDataArray)
            break;
        i++;
    }

    if ((i != end) && !b) {
        ts << open;
        i = mNodes;
        if (i->Type() == kDataSymbol) {
            i->Print(ts, b);
            i++;
        }
        ts << "\n";
        gIndent += 3;
        while (i < end) {
            ts.Space(gIndent);
            i->Print(ts, b);
            ts << "\n";
            i++;
        }
        gIndent -= 3;
        ts.Space(gIndent);
        ts << close;
    } else {
        ts << open;
        for (i = mNodes; i < end; i++) {
            if (i != mNodes) {
                ts << " ";
            }
            i->Print(ts, b);
        }
        ts << close;
    }
}

bool DataArray::PrintUnused(TextStream& ts, DataType ty, bool b) const {
    bool ret = false;
    for(int i = 0; i < mSize; i++){
        ret |= mNodes[i].PrintUnused(ts, b);
    }
    return ret;
}

DECOMP_FORCEACTIVE(DataArray,
    "gLinearNodesMemSize == 0"
)

void* NodesLinearAlloc(int i){
    MILO_ASSERT(gLinearNodesMemSize > 0, 264);
    gNumLinearAllocs++;
    void* oldpos = gLinearNodesMemPos;
    gLinearNodesMemPos += i;
    MILO_ASSERT((gLinearNodesMemPos - &gLinearNodesMem[0]) <= gLinearNodesMemSize, 268);
    return oldpos;
}

void* NodesAlloc(int i){
    if(gNodesLinearAlloc) return NodesLinearAlloc(i);
    else return _MemOrPoolAlloc(i, FastPool);
}

inline bool AddrIsInLinearMem(void* mem) {
    return mem >= gLinearNodesMem && mem < gLinearNodesMem + gLinearNodesMemSize;
}

void NodesFree(int i, DataNode* mem){
    MILO_ASSERT(!AddrIsInLinearMem(mem), 0x13D);
    _MemOrPoolFree(i, FastPool, mem);
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
    int min = Min<int>(mSize, i);
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
            if(arr->UncheckedInt(0) == tag){
                return (DataArray*)arr;
            }
        }
    }
    if(fail) MILO_FAIL("Couldn't find %d in array (file %s, line %d)", tag, mFile.mStr, mLine);
    return 0;
}

DataArray* DataArray::FindArray(Symbol tag, bool fail) const {
    DataArray* found = FindArray((int)tag.mStr, false);
    if(found == 0 && fail) MILO_FAIL("Couldn't find '%s' in array (file %s, line %d)", tag.mStr, mFile.mStr, mLine);
    return found;
}

DECOMP_FORCEACTIVE(DataArray,
    "a->Size()==3",
    "AddrIsInLinearMem!\n"
)

#pragma push
#pragma force_active on
static DataArray* FindArrayTwoSyms(DataArray* a, Symbol s1, Symbol s2){
    return a->FindArray(s1, s2);
}

inline DataArray *DataArray::FindArray(Symbol s1, Symbol s2) const {
    return FindArray(s1, true)->FindArray(s2, true);
}
#pragma pop

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
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, Symbol &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = (arr->Sym(1));
        return true;
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, String &ret, bool b) const {
    const char *c;
    bool found = FindData(s, c, b);
    if (found) {
        ret = c;
        return true;
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, int &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = arr->Int(1);
        return true;
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, float &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = arr->Float(1);
        return true;
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, bool &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret = arr->Int(1);
        return true;
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, Plane &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret.a = arr->Float(1);
        ret.b = arr->Float(2);
        ret.c = arr->Float(3);
        ret.d = arr->Float(4);
        return true;
    } else {
        return false;
    }
}

bool DataArray::FindData(Symbol s, Hmx::Color &ret, bool b) const {
    DataArray *arr = FindArray(s, b);
    if (arr != nullptr) {
        ret.red = arr->Float(1);
        ret.green = arr->Float(2);
        ret.blue = arr->Float(3);
        if (arr->Size() > 4) {
            ret.alpha = arr->Float(4);
        } else {
            ret.alpha = 1;
        }
        return true;
    } else {
        return false;
    }
}

DataArray* DataArray::Clone(bool deep, bool eval, int extra){
    DataArray* da = new DataArray(mSize + extra);
    for(int i = 0; i < mSize; i++){
        da->mNodes[i] = (eval) ? mNodes[i].Evaluate() : mNodes[i];
        if(deep){
            if(da->mNodes[i].Type() == kDataArray){
                DataArray* cloned = da->mNodes[i].LiteralArray()->Clone(true, eval, 0);
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
        case kDataInt: {
            float a = anode->LiteralFloat();
            float b = bnode->LiteralFloat();
            if(a < b) return -1;
            return a != b;
        }
        case kDataString:
        case kDataSymbol:
            return stricmp(anode->Str(), bnode->Str());
        case kDataArray:
            return NodeCmp(&anode->Array()->Node(0), &bnode->Array()->Node(0));
        case kDataObject: {
            const char* a = anode->GetObj() ? anode->GetObj()->Name() : "";
            const char* b = bnode->GetObj() ? bnode->GetObj()->Name() : "";
            return stricmp(a, b);
        }
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
    DataArray* arr = (DataArray*)v;
    arr->Node(0).Print(TheDebug, true);
    TheDebug << MakeString(" took %.2f ms (File: %s Line: %d)\n", f, arr->File(), arr->Line());
}

DataNode DataArray::Execute() {
#ifdef MILO_DEBUG
    DataCallStackFrame frame(this);
#endif
    START_AUTO_TIMER_CALLBACK("array_exec", DataArrayGlitchCB, this);

    DataNode& node = Evaluate(0);
    switch (node.Type()) {
        case kDataFunc:
            return node.mValue.func(this);
        case kDataSymbol: {
            Hmx::Object* object = gDataDir->FindObject(node.mValue.symbol, true);
            if (object) {
                return object->Handle(this, true);
            }

            std::map<Symbol, DataFunc*>::iterator func = gDataFuncs.find(STR_TO_SYM(node.mValue.symbol));
            if (func != gDataFuncs.end()) {
                // Cache the function into the array to optimize repeat calls
                node = func->second;
                return func->second(this);
            }
            break;
        }
        case kDataObject: {
            if (!node.mValue.object) {
                MILO_WARN("###BAD THING HAPPENING###\n%s line %d: Trying to make a NULL object handle a message!\n###\n", File(), Line());
                break;
            }

            return node.mValue.object->Handle(this, true);
        }
        case kDataString: {
            Hmx::Object* object = gDataDir->FindObject(node.mValue.symbol, true);
            if (object) {
                return object->Handle(this, true);
            }
            break;
        }
        default:
            break;
    }

    if (sDefaultHandler) {
        DataNode n = sDefaultHandler(this);
        if (n.Type() != kDataUnhandled) {
            return n;
        }
    }

    String s;
    Node(0).Print(s, true);

    String sn;
    node.Print(sn,  true);

    if (s == sn) {
        MILO_WARN("%s not function or object (file %s, line %d)", s.c_str(), mFile, mLine);
    } else {
        MILO_WARN("%s = %s not function or object (file %s, line %d)", s.c_str(), sn.c_str(), mFile, mLine);
    }

    return 0;
}

void DataArray::Save(BinStream &bs) const {
    bs << mSize << mLine << mDeprecated;
    for (int i = 0; i < mSize; i++) {
        bs << mNodes[i];
    }
}

bool DataArrayDefined() {
    for (std::list<bool>::iterator it = gDataArrayConditional.begin(); it != gDataArrayConditional.end(); it++) {
        if (*it == false) return false;
    }
    return true;
}

void DataArray::Load(BinStream& bs) {
    mFile = gFile;

    short size;
    bs >> size;
    MemDoTempAllocations(true, false), Resize(size);

    bs >> mLine;
    bs >> mDeprecated;

    for (int i = 0; i < size;) {
        DataNode& node = mNodes[i];
        node.Load(bs);
        if (!DataArrayDefined() && (node.Type() < kDataIfdef || node.Type() > kDataEndif || node.Type() > kDataIfndef)) {
            if (node.Type() != kDataIfndef) {
                size--;
                continue;
            }
        }

        DataArray* array = nullptr;
        if (node.Type() == kDataSymbol && (array = DataGetMacro(STR_TO_SYM(node.mValue.symbol))) != 0) {
            size += array->Size() - 1;
            MemDoTempAllocations(true, false), Resize(size);

            for (int j = 0; j < array->Size(); j++) {
                mNodes[i++] = array->Node(j);
            }

            continue;
        }

        switch (node.Type()) {
            case kDataAutorun: {
                DataNode command;
                command.Load(bs);
                command.Command(this)->Execute();
                size -= 2;
                break;
            }
            case kDataDefine: {
                DataNode macro;
                macro.Load(bs);
                DataSetMacro(STR_TO_SYM(node.mValue.symbol), macro.Array(this));
                size -= 2;
                break;
            }
            case kDataUndef: {
                DataSetMacro(STR_TO_SYM(node.mValue.symbol), nullptr);
                size -= 1;
                break;
            }

            case kDataIfdef: {
                gDataArrayConditional.push_back(DataGetMacro(STR_TO_SYM(node.mValue.symbol)) != nullptr);
                size -= 1;
                break;
            }
            case kDataIfndef: {
                gDataArrayConditional.push_back(DataGetMacro(STR_TO_SYM(node.mValue.symbol)) == nullptr);
                size -= 1;
                break;
            }
            case kDataElse: {
                gDataArrayConditional.back() = !gDataArrayConditional.back();
                size -= 1;
                break;
            }
            case kDataEndif: {
                gDataArrayConditional.pop_back();
                size -= 1;
                break;
            }

            case kDataInclude:
            case kDataMerge: {
                const char* path = node.mValue.symbol;
                bool readFile = false;
                DataArray* macro = DataGetMacro(path);
                if (!macro) {
                    path = FileMakePath(FileGetPath(mFile.Str(), nullptr), path, nullptr);
                    macro = DataReadFile(path, true);
                    readFile = true;
                    if (!macro) {
                        MILO_FAIL("Couldn't open embedded file: %s (file %s, line %d)", path, mFile.Str(), mLine);
                    }
                }

                if (node.Type() == kDataInclude) {
                    size += macro->Size() - 1;
                    MemDoTempAllocations(true, false), Resize(size);
                    for (int j = 0; j < array->Size(); j++) {
                        mNodes[i++] = array->Node(j);
                    }
                } else {
                    if (macro->Size() == 0) {
                        MILO_FAIL("Empty merge file (possibly a re-included file): %s", path);
                    }

                    int remaining = size - i - 1;
                    MemDoTempAllocations(true, false), Resize(i);
                    DataMergeTags(this, macro);

                    i = mSize;
                    size = mSize + remaining;
                    MemDoTempAllocations(true, false), Resize(size);
                }

                if (readFile) {
                    macro->Release();
                }

                gFile = mFile;
                break;
            }

            default:
                i++;
                break;
        }
    }

    Resize(size);
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

// fn_80317B9C
void DataArray::LoadGlob(BinStream &bs, bool b) {
    MILO_ASSERT(mSize <= 0, 0x52A);
    int v;
    NodesFree(-mSize, mNodes);
    if (b) {
        bs >> v;
        mSize = -(v + 1);
        mNodes = (DataNode*)NodesAlloc(-mSize);
        bs.Read(mNodes, v);
        ((unsigned char*)mNodes)[v] = 0;
    } else {
        bs >> mSize;
        mNodes = (DataNode*)NodesAlloc(-mSize);
        bs.Read(mNodes, -mSize);
    }
}

void DataArray::SetFile(Symbol s){
    gFile = s;
}

DataNode DataArray::ExecuteBlock(int len){
    for(; len < mSize - 1; len++){
        Command(len)->Execute();
    }
    return Evaluate(len);
}

DataNode DataArray::ExecuteScript(int index, Hmx::Object *obj, const DataArray *_args, int _argStart) {
#ifdef MILO_DEBUG
    DataCallStackFrame frame(this);
#endif

    int numVars = 0;
    int size = mSize;

    if (index < (size - 1) && mNodes[index].Type() == kDataArray) {
        DataArray* arr = mNodes[index].mValue.array;
        numVars = arr->Size();
        MILO_ASSERT(_args != NULL || numVars == 0, 0x565);

        for (int i = 0; i < numVars; i++) {
            DataNode *var = arr->Var(i);
            DataPushVar(var);
            *var = _args->Evaluate(i + _argStart);
        }

        index++;
    }

    DataNode ret;
    if (index >= size) {
        ret = DataNode(0);
    } else {
        Hmx::Object *setThis = DataSetThis(obj);
        ret = ExecuteBlock(index);
        DataSetThis(setThis);
    }

    while (numVars-- != 0) {
        DataPopVar();
    }

    return ret;
}

TextStream& operator<<(TextStream& ts, const DataArray* da){
    if(da) da->Print(ts, kDataArray, false);
    else ts << "<null>";
    return ts;
}

BinStream &operator>>(BinStream &bs, DataArray *&da) {
    bool b;
    bs >> b;
    if (b) {
        da = new DataArray(0);
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

DECOMP_FORCEBLOCK(DataArray, (std::vector<Vector3>& v),
    v.insert(v.end(), Vector3());
)
