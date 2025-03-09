#include "MultiMesh.h"
#include "os/Timer.h"
#include "rndobj/Rnd.h"
#include "rndwii/Mat.h"
#include "rndwii/Mesh.h"

void WiiMultiMesh::DrawShowing() {
    START_AUTO_TIMER("multimesh");
    if (mInstances.empty() || mMesh == nullptr) {
        return;
    }
    WiiMesh *mesh = (WiiMesh *)(RndMesh *)mMesh;
    WiiMat *mat = (WiiMat *)mesh->Mat();
    RndMesh *m2 = mesh->mGeomOwner;
    MILO_ASSERT(mesh->NumBones() == 0, 5);
    if (m2->NumFaces() == 0) {
        return;
    }
    {
        TIMER_ACTION("faces", mesh->SetVertexDesc(); mesh->SetVertexBuffers(nullptr););
    }
    {
        START_AUTO_TIMER("selmat");
    }
    if (mat == nullptr)
        mat = (WiiMat *)TheRnd->unk84;
    mat->Select(false);
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("xfms");
    }
    {
        START_AUTO_TIMER("faces");
    }
}
