#include "Mesh.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "revolution/GX.h"
#include "revolution/gx/GXAttr.h"
#include "revolution/gx/GXTypes.h"
#include "revolution/os/OSCache.h"
#include "rndwii/Rnd.h"
#include "utl/MemMgr.h"
#include <cstddef>
#include <cstring>

#define kTempSize 0x40000

int NUM_BUFFERS = 4;
bool gToggleAO = true;
void* DisplayList::sTemp;
void* DisplayList::sCurr;

static DataNode OnToggleAO(DataArray*) {
    gToggleAO = !gToggleAO;
    TheDebug << MakeString("Ambient Occlusion is now %s!\n", gToggleAO ? "ON" : "OFF");
    return DataNode();
}

DisplayList::DisplayList() : mData(NULL), mSize(0), unk_0x8(0) {}

DisplayList::~DisplayList() { Clear(); }

void DisplayList::Init() {
    if (sTemp == NULL) {
        static int _x = MemFindHeap("main");
        MemPushHeap(_x);
        sTemp = _MemAlloc(0x40000, 0x20);
        MemPopHeap();
    }
}

void DisplayList::Clear() {
    WiiRnd::SyncFree(mData);
    mData = NULL;
    mSize = 0;
    unk_0x8 = 0;
}

void DisplayList::Copy(const DisplayList& d) {
    Clear();
    mSize = d.mSize;
    unk_0x8 = d.unk_0x8;

    static int _x = MemFindHeap("main");
    MemPushHeap(_x);
    mData = _MemAlloc(mSize, 0x20);
    MemPopHeap();
    DCZeroRange(mData, mSize);
    memcpy(mData, d.mData, mSize);
    DCStoreRange(mData, mSize);
}

void DisplayList::Begin(unsigned short us) {
    MILO_ASSERT(!sCurr, 147);
    sCurr = sTemp;
    Clear();
    unk_0x8 = us;
}

void DisplayList::Begin(_GXPrimitive prim, _GXVtxFmt f, unsigned short us1, unsigned short us2) {
    Begin(us2);
    Start(prim, f, us1);
}

void DisplayList::Start(_GXPrimitive pr, _GXVtxFmt f, unsigned short us) {
    // ????
}

void DisplayList::End() {
    MILO_ASSERT(sCurr, 174);
    MILO_ASSERT(!mSize && !mData, 175);
    static int _x = MemFindHeap("main");
    MemPushHeap(_x);
    u32 tmp_a = ((u32)sTemp - (u32)sCurr);
    u32 tmp_b = (tmp_a + 31) & 0xFFFFFFE0;
    mSize = tmp_b;
    mData = _MemAlloc(tmp_b, 0x20);
    DCZeroRange(mData, mSize);
    memcpy(mData, sTemp, tmp_a);
    memset((void*)((u32)mData + tmp_a), 0, mSize - tmp_a);
    DCStoreRange(mData, mSize);
    sCurr = NULL; // memleak? mem is alloc'd but not freed
    MemPopHeap();
}

DisplayList& DisplayList::operator<<(unsigned short us) {
    MILO_ASSERT(sCurr, 202);
    if (unk_0x8 < 0x100) {
        u8* test = (u8*)((u32)sCurr + 4);
        us &= 0xFF;
        sCurr = test;
        (((u32)sCurr < (u32)sTemp + kTempSize)
         || (TheDebugFailer << (MakeString(
                 kAssertStr,
                 "Mesh.cpp",
                 210,
                 "sCurr < sTemp + kTempSize"
             )),
             0));
        test[3] = us;
        test[2] = us;
        test[1] = us;
        test[0] = us;
    } else {
        u16* test = (u16*)((u32)sCurr + 8);
        sCurr = test;
        (((u32)sCurr < (u32)sTemp + kTempSize)
         || (TheDebugFailer << (MakeString(
                 kAssertStr,
                 "Mesh.cpp",
                 219,
                 "sCurr < sTemp + kTempSize"
             )),
             0));
        test[3] = us;
        test[2] = us;
        test[1] = us;
        test[0] = us;
    }
    return *this;
}

void DisplayList::Draw(u32, _GXVtxFmt) const {
    MILO_ASSERT(mData, 237);
    MILO_ASSERT(mSize > 0, 238);
    DCStoreRange(mData, mSize);
    GXCallDisplayList(mData, mSize);
}

WiiMesh::WiiMesh() {}

BEGIN_COPYS(WiiMesh)
    COPY_SUPERCLASS(RndMesh)
    CREATE_COPY(WiiMesh)
    BEGIN_COPYING_MEMBERS
        if (mNumFaces > 0) mDisplays.Copy(c->mDisplays);
    END_COPYING_MEMBERS
END_COPYS


void WiiMesh::Init() {
    REGISTER_OBJ_FACTORY(WiiMesh)
    GXSetVtxAttrFmt((_GXVtxFmt)0, GX_VA_POS, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((_GXVtxFmt)0, GX_VA_NRM, (GXCompCnt)0, (GXCompType)1, 6);
    GXSetVtxAttrFmt((_GXVtxFmt)0, GX_VA_CLR0, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((_GXVtxFmt)0, GX_VA_TEX0, (GXCompCnt)1, (GXCompType)3, 9);
    GXSetVtxAttrFmt((_GXVtxFmt)1, GX_VA_POS, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((_GXVtxFmt)1, GX_VA_NBT, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((_GXVtxFmt)1, GX_VA_CLR0, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((_GXVtxFmt)1, GX_VA_TEX0, (GXCompCnt)1, (GXCompType)3, 9);
    GXSetVtxAttrFmt((_GXVtxFmt)4, GX_VA_POS, (GXCompCnt)1, (GXCompType)3, 5);
    GXSetVtxAttrFmt((_GXVtxFmt)4, GX_VA_NRM, (GXCompCnt)0, (GXCompType)1, 6);
    GXSetVtxAttrFmt((_GXVtxFmt)4, GX_VA_CLR0, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((_GXVtxFmt)4, GX_VA_TEX0, (GXCompCnt)1, (GXCompType)3, 9);

    DisplayList::Init();
    DataRegisterFunc("toggle_ao", OnToggleAO);
}

void WiiMesh::ReleaseBuffers() {

}

WiiMesh::~WiiMesh() { }
