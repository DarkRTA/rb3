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

bool gToggleAO = true;

static DataNode OnToggleAO(DataArray*) {
    gToggleAO = !gToggleAO;
    TheDebug << MakeString("Ambient Occlusion is now %s!\n", gToggleAO ? "ON" : "OFF");
    return DataNode();
}

DisplayList::DisplayList() : mData(NULL), mSize(0), unk_0x8(0) {}

DisplayList::~DisplayList() { Clear(); }

void DisplayList::Init() {

}

void DisplayList::Clear() {
    WiiRnd::SyncFree(mData);
    mData = NULL;
    mSize = 0;
    unk_0x8 = 0;
}

void DisplayList::Copy(const DisplayList& d) {
    Clear();
}

void DisplayList::Draw(u32 u, _GXVtxFmt f) const {
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

/*
void WiiMesh::Init() {
    REGISTER_OBJ_FACTORY(WiiMesh)
    GXSetVtxAttrFmt(0, GX_VA_POS, 1, 4, 0);
    GXSetVtxAttrFmt(0, GX_VA_NRM, 0, 1, 6);
    GXSetVtxAttrFmt(0, GX_VA_CLR0, 1, 5, 0);
    GXSetVtxAttrFmt(0, GX_VA_TEX0, 1, 3, 9);
    GXSetVtxAttrFmt(1, GX_VA_POS, 1, 4, 0);
    GXSetVtxAttrFmt(1, GX_VA_NBT, 1, 4, 0);
    GXSetVtxAttrFmt(1, GX_VA_CLR0, 1, 5, 0);
    GXSetVtxAttrFmt(1, GX_VA_TEX0, 1, 3, 9);
    GXSetVtxAttrFmt(4, GX_VA_POS, 1, 3, 5);
    GXSetVtxAttrFmt(4, GX_VA_NRM, 0, 1, 6);
    GXSetVtxAttrFmt(4, GX_VA_CLR0, 1, 5, 0);
    GXSetVtxAttrFmt(4, GX_VA_TEX0, 1, 3, 9);

    DisplayList::Init();
    DataRegisterFunc("toggle_ao", OnToggleAO);
}
*/
