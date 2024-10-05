#include "Mesh.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "revolution/GX.h"
#include "revolution/gx/GXAttr.h"
#include "revolution/gx/GXTransform.h"
#include "revolution/gx/GXTypes.h"
#include "revolution/mtx/mtx.h"
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, (GXCompType)4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, (GXCompType)1, 6);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, (GXCompType)5, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, (GXCompType)3, 9);
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, (GXCompType)4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_NBT, GX_NRM_NBT, (GXCompType)4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, (GXCompType)5, 0);
    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, (GXCompType)3, 9);
    GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_POS, GX_POS_XYZ, (GXCompType)3, 5);
    GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_NRM, GX_NRM_XYZ, (GXCompType)1, 6);
    GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_CLR0, GX_CLR_RGBA, (GXCompType)5, 0);
    GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_TEX0, GX_TEX_ST, (GXCompType)3, 9);

    DisplayList::Init();
    DataRegisterFunc("toggle_ao", OnToggleAO);
}

void WiiMesh::ReleaseBuffers() {
    WiiRnd::SyncFree(unk_0x148);
    WiiRnd::SyncFree(unk_0x14C);
    WiiRnd::SyncFree(unk_0x138);
    WiiRnd::SyncFree(unk_0x13C);
    WiiRnd::SyncFree(unk_0x140);
    WiiRnd::SyncFree(unk_0x144);
    WiiRnd::SyncFree(unk_0x150);
    unk_0x138 = NULL;
    unk_0x13C = NULL;
    unk_0x140 = NULL;
    unk_0x144 = NULL;
    unk_0x148 = NULL;
    unk_0x14C = NULL;
    unk_0x150 = NULL;
}

void* SkinAlloc(int i1, char*, int i2) {

}

void WiiMesh::CreateBuffers() {

}

WiiMesh::~WiiMesh() { }

void WiiMesh::SetVertexDesc() {
    GXClearVtxDesc();
    GXAttrType x = GX_INDEX16;
    if (mDisplays.unk_0x8 < 0x100) x = GX_INDEX8;
    GXSetVtxDesc(GX_VA_POS, x);
    GXSetVtxDesc(GX_VA_NRM, x);
    GXSetVtxDesc(GX_VA_CLR0, x);
    GXSetVtxDesc(GX_VA_TEX0, x);
    GXInvalidateVtxCache();
}

void WiiMesh::SetVertexBuffers(const void*) {
    const void* v = unk_0x138;
    GXSetArray(GX_VA_CLR0, v, 8);
    GXSetArray(GX_VA_TEX0, (const void*)((u32)v + 4), 8);
}

void WiiMesh::DrawFaces() {
    mDisplays.Draw((u32)this, bitmask_1 ? GX_VTXFMT4 : GX_VTXFMT0);
}

void WiiMesh::DrawReflection(bool b) {
    if (mVerts.empty()) {
        MILO_WARN("WiiMesh::DrawReflection: no vertices to render!\n");
        return;
    }
    if (mFaces.empty()) {
        MILO_WARN("WiiMesh::DrawReflection: no faces to render!\n");
        return;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    Mtx mtx;
    PSMTXIdentity(mtx);
    GXLoadNrmMtxImm(mtx, 0);
}

void WiiMesh::RemoveVertData() {
    mVerts.resize(0, true);

    ReleaseBuffers();
}
