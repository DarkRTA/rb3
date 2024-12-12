#include "Mesh.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "revolution/GX.h"
#include "revolution/mtx/mtx.h"
#include "revolution/os/OSCache.h"
#include "rndwii/Rnd.h"
#include "utl/MemMgr.h"
#include <cstddef>
#include <cstring>

#define kTempSize 0x40000

int NUM_BUFFERS = 4;
bool gToggleAO = true;
void *DisplayList::sTemp;
void *DisplayList::sCurr;

static DataNode OnToggleAO(DataArray *) {
    gToggleAO = !gToggleAO;
    TheDebug << MakeString("Ambient Occlusion is now %s!\n", gToggleAO ? "ON" : "OFF");
    return 0;
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

void DisplayList::Copy(const DisplayList &d) {
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

void DisplayList::Begin(
    _GXPrimitive prim, _GXVtxFmt f, unsigned short us1, unsigned short us2
) {
    Begin(us2);
    Start(prim, f, us1);
}

void DisplayList::Start(_GXPrimitive pr, _GXVtxFmt f, unsigned short us) {
    u8 *b = (u8 *)sCurr;
    u32 *w = (u32 *)sCurr;
    u16 *h = (u16 *)sCurr;
    *b = (pr | f);
    sCurr = (void *)((u8 *)sCurr + 1);
    *h = us;
    sCurr = (void *)((u8 *)sCurr + 2);
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
    memset((void *)((u32)mData + tmp_a), 0, mSize - tmp_a);
    DCStoreRange(mData, mSize);
    sCurr = NULL; // memleak? mem is alloc'd but not freed
    MemPopHeap();
}

DisplayList &DisplayList::operator<<(unsigned short us) {
    MILO_ASSERT(sCurr, 202);
    if (unk_0x8 < 0x100) {
        u8 *test = (u8 *)((u32)sCurr + 4);
        us &= 0xFF;
        sCurr = test;
        (((u32)sCurr < (u32)sTemp + kTempSize)
         || (TheDebugFailer
                 << (MakeString(kAssertStr, "Mesh.cpp", 210, "sCurr < sTemp + kTempSize")
                    ),
             0));
        test[3] = us;
        test[2] = us;
        test[1] = us;
        test[0] = us;
    } else {
        u16 *test = (u16 *)((u32)sCurr + 8);
        sCurr = test;
        (((u32)sCurr < (u32)sTemp + kTempSize)
         || (TheDebugFailer
                 << (MakeString(kAssertStr, "Mesh.cpp", 219, "sCurr < sTemp + kTempSize")
                    ),
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

WiiMesh::WiiMesh()
    : mCTVtxs(nullptr), mPosNrmVtxs(nullptr), mPosQ(nullptr), mNrmQ(nullptr),
      mBoneWeights(nullptr), mBoneIndices(nullptr), mNumVerts(0), mNumFaces(0),
      unk_0x164(0), bitmask_0(0), bitmask_1(1), bitmask_2(0), unk_0x168(-1) {
    unk_0x150 = nullptr;
}

BEGIN_COPYS(WiiMesh)
    COPY_SUPERCLASS(RndMesh)
    CREATE_COPY(WiiMesh)
    BEGIN_COPYING_MEMBERS
        if (mNumFaces > 0)
            mDisplays.Copy(c->mDisplays);
    END_COPYING_MEMBERS
END_COPYS

int WiiMesh::GetSomeSizeFactor() {
    int ret;
    WiiMesh *own = (WiiMesh *)GeometryOwner();
    if (own->bitmask_2 && own->bitmask_1) {
        ret = 9;
    } else {
        ret = 16;
        if (own->bitmask_1)
            ret = 10;
    }
    return ret;
}

void WiiMesh::Init() {
    Register();
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
    WiiRnd::SyncFree(mBoneWeights);
    WiiRnd::SyncFree(mBoneIndices);
    WiiRnd::SyncFree(mCTVtxs);
    WiiRnd::SyncFree(mPosNrmVtxs);
    WiiRnd::SyncFree(mPosQ);
    WiiRnd::SyncFree(mNrmQ);
    WiiRnd::SyncFree(unk_0x150);
    mCTVtxs = NULL;
    mPosNrmVtxs = NULL;
    mPosQ = NULL;
    mNrmQ = NULL;
    mBoneWeights = NULL;
    mBoneIndices = NULL;
    unk_0x150 = NULL;
}

void *SkinAlloc(int i1, char *, int i2) {
    static int fastHeapNum = MemFindHeap("");
    int a, b, c, d;
    MemFreeBlockStats(fastHeapNum, a, b, c, d);
}

void WiiMesh::CreateBuffers() {
    u32 pos_nrm_vtx_scale = GetSomeSizeFactor();

    MILO_ASSERT(!mCTVtxs, 678);
    MILO_ASSERT(!mPosNrmVtxs, 679);
    MILO_ASSERT(!mPosQ, 680);
    MILO_ASSERT(!mNrmQ, 681);
    mCTVtxs = _MemAlloc(mNumVerts << 3, 0x20);
    if (bitmask_2 && bitmask_1) {
        mPosNrmVtxs = nullptr;
        mPosQ = SkinAlloc(mNumVerts * 6, "mesh VPosNrmQ", 0x20);
        mNrmQ = SkinAlloc(mNumVerts * 3, "mesh VPosNrmQ", 0x20);
    } else {
        mPosNrmVtxs = _MemAlloc(mNumVerts * pos_nrm_vtx_scale, 0x20);
        mPosQ = nullptr;
        mNrmQ = nullptr;
    }
    if (unk_0x164 > 1) {
        MILO_ASSERT(!mBoneWeights && !mBoneIndices, 711);
        mBoneWeights =
            SkinAlloc((Min((int)unk_0x164, 4) * mNumVerts) << 1, "Vertex Weights", 0x20);
    }
    if (unk_0x164 > 4) {
        MILO_ASSERT(!mBoneIndices, 723);
        mBoneIndices = SkinAlloc(mNumVerts << 2, "Vertex Indices", 0x20);
    } else {
        if (unk_0x164 > 1) {
            mBoneIndices = SkinAlloc(unk_0x164, "Vertex Indices", 0x20);
        }
    }
}

WiiMesh::~WiiMesh() { ReleaseBuffers(); }

void WiiMesh::SetVertexDesc() {
    GXClearVtxDesc();
    GXAttrType x = mDisplays.GetIdxType();
    GXSetVtxDesc(GX_VA_POS, x);
    GXSetVtxDesc(GX_VA_NRM, x);
    GXSetVtxDesc(GX_VA_CLR0, x);
    GXSetVtxDesc(GX_VA_TEX0, x);
    GXInvalidateVtxCache();
}

void WiiMesh::SetVertexBuffers(const void *) {
    const void *v = mCTVtxs;
    GXSetArray(GX_VA_CLR0, v, 8);
    GXSetArray(GX_VA_TEX0, (const void *)((u32)v + 4), 8);
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
