/*
    Compile unit: C:\rockband2\system\src\os\BlockMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A354C -> 0x805A43E0
*/
class BlockMgr TheBlockMgr; // size: 0x60, address: 0x80983ED0
int kArkBlockSize; // size: 0x4, address: 0x80A57D40
static char * gBuffers; // size: 0x4, address: 0x80A54888
int gCurrBuffNum; // size: 0x4, address: 0x80A5488C
// Range: 0x805A354C -> 0x805A35AC
int GetFreeBuffer() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> int gCurrBuffNum;
}

int sCurrTimestamp; // size: 0x4, address: 0x80A54890
// Range: 0x805A35AC -> 0x805A3600
void * Block::Block(class Block * const this /* r31 */) {
    // References
    // -> static char * gBuffers;
}

// Range: 0x805A3600 -> 0x805A3608
int Block::GetCurrTimestamp() {
    // References
    // -> int sCurrTimestamp;
}

// Range: 0x805A3608 -> 0x805A361C
void Block::UpdateTimestamp() {
    // References
    // -> int sCurrTimestamp;
}

// Range: 0x805A361C -> 0x805A3644
unsigned char Block::Matches() {}

// Range: 0x805A3644 -> 0x805A3674
unsigned char Block::Matches() {}

// Range: 0x805A3674 -> 0x805A36A8
void * BlockRequest::BlockRequest() {}

class _List_node : public _List_node_base {
    // total size: 0x20
public:
    class AsyncTask _M_data; // offset 0x8, size 0x18
};
// Range: 0x805A36A8 -> 0x805A3788
void * BlockRequest::BlockRequest(class BlockRequest * const this /* r30 */, const class AsyncTask & task /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9AsyncTask>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<9AsyncTask>; // size: 0x8, address: 0x80921E88
// Range: 0x805A3788 -> 0x805A37B0
unsigned char BlockRequest::Matches() {}

// Range: 0x805A37B0 -> 0x805A37EC
unsigned char BlockRequest::Exceeds() {}

// Range: 0x805A37EC -> 0x805A3854
void BlockMgr::GetAssociatedBlocks() {
    // Local variables
    int extraAmt; // r5
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805A3854 -> 0x805A39F0
void BlockMgr::KillBlockRequests(class BlockMgr * const this /* r30 */, class ArkFile * iArk /* r31 */) {
    // Local variables
    struct _List_iterator blockItr; // r1+0x48
    struct _List_iterator taskItr; // r1+0x44
}

// Range: 0x805A39F0 -> 0x805A3A78
char * BlockMgr::GetBlockData(class BlockMgr * const this /* r29 */, int arkfileNum /* r30 */, int iBlockNum /* r31 */) {
    // Local variables
    class Block * block; // r31
}

// Range: 0x805A3A78 -> 0x805A3F1C
void BlockMgr::AddTask(class BlockMgr * const this /* r27 */, const class AsyncTask & iTask /* r28 */) {
    // Local variables
    struct _List_iterator blockItr; // r1+0x84
    int blocknum; // r30
    int arkfileNum; // r29

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<12BlockRequest>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9AsyncTask>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<12BlockRequest>; // size: 0x8, address: 0x80921EC8
// Range: 0x805A3F1C -> 0x805A4240
void BlockMgr::ReadAheadBlocks(class BlockMgr * const this /* r26 */, int arkfileNum /* r27 */, int startBlock /* r28 */, int numBlocks /* r29 */) {
    // Local variables
    struct _List_iterator reqItr; // r1+0x58
    struct _List_iterator raReqItr; // r1+0x54
    int block; // r30
    class Block * b; // r0

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9AsyncTask>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<12BlockRequest>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Archive * TheArchive;
}

// Range: 0x805A4240 -> 0x805A42CC
class Block * BlockMgr::FindBlock(class BlockMgr * const this /* r27 */, int arkfileNum /* r28 */, int iBlockNum /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x805A42CC -> 0x805A4348
class Block * BlockMgr::FindLRUBlock(class BlockMgr * const this /* r31 */) {
    // Local variables
    int minTime; // r3
    class Block * lruBlock; // r5
    int j; // r6
}

struct {
    // total size: 0x8
} __RTTI__PP5Block; // size: 0x8, address: 0x80921F58
struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x805A4348 -> 0x805A43E0
static void __sinit_\BlockMgr_cpp() {
    // References
    // -> class BlockMgr TheBlockMgr;
}

class _List_node : public _List_node_base {
    // total size: 0x18
public:
    class BlockRequest _M_data; // offset 0x8, size 0x10
};

