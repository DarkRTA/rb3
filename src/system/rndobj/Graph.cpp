#include "rndobj/Graph.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "rndobj/DOFProc.h"
#include "rndobj/Utl.h"
#include <list>

RndGraph* sOneFrame;
std::list<RndGraph>* sGraphs;
std::list<FakeGraph> sFakes;
ObjPtr<RndCam, ObjectDir> sCam(NULL, NULL);

static DataNode OnGraphReset(DataArray*) {
    RndGraph::ResetAll();
    return DataNode(0);
}

void RndGraph::Init() {
    sGraphs = new std::list<RndGraph>;
    TheDebug.mExitCallbacks.push_back(RndGraph::Terminate); 
    DataRegisterFunc("graph_reset", OnGraphReset);
}

void RndGraph::Terminate() {
    delete sGraphs;
    sGraphs = 0;
    delete sOneFrame;
    sOneFrame = 0;
}

void RndGraph::ResetAll() {
    delete sOneFrame;
    sOneFrame = NULL;
    sGraphs->empty();
}

void RndGraph::SetCamera(RndCam* c) { sCam = c; }

RndGraph* RndGraph::GetOneFrame() { 
    if (sOneFrame == NULL) sOneFrame = new RndGraph(NULL);
    return sOneFrame;    
}

void RndGraph::Free(const void* id, bool b) {
    if (sGraphs == NULL) return;
    for (std::list<RndGraph>::reverse_iterator it = sGraphs->rbegin(); it != sGraphs->rend(); it++) {
        if (it->mId == id) {
            delete &(*it); return;
        }
    }
    for (std::list<FakeGraph>::iterator it = sFakes.begin(); it != sFakes.end(); it++) {
        if (&(*it) == id) {
            delete &(*it); return;
        }
    }
    if (b) MILO_WARN("could not find line graph %x to free\n", (int)id);
}

RndGraph::RndGraph(const void* cv) : mEnable(1), mDrawFixedZ(0), mZ(0.0f), mId((void*)cv) {
    
}

RndGraph::~RndGraph(){
    mEnable = true;
    Reset();
}

void RndGraph::Draw(){
    for(int i = 0; i < mStuff.size(); i++){
        if(mDrawFixedZ){
            mStuff[i]->DrawFixedZ(mZ);
        }
        else mStuff[i]->Draw();
    }
}

void RndGraph::Reset(){
    if(mEnable){
        for(int i = 0; i < mStuff.size(); i++){
            delete mStuff[i];
        }
        mStuff.clear();
    }
}

void RndGraph::AddLine(const Vector3& a, const Vector3& b, const Hmx::Color& col, bool buf){
    if(mEnable) mStuff.push_back(new Line(a, b, col, buf));
}

void RndGraph::AddSphere(const Vector3& center, float radius, const Hmx::Color& col){
    if(mEnable) mStuff.push_back(new DrawSphere(center, radius, col));
}

void RndGraph::AddString(const char* cc, const Vector2& vec, const Hmx::Color& col){
    if(mEnable) mStuff.push_back(new DrawString(cc, vec, col));
}

void RndGraph::AddString3D(const char* text, const Vector3& worldPos, const Hmx::Color& col){
    if(mEnable) mStuff.push_back(new DrawString3D(text, worldPos, col));
}

void DrawString3D::DrawFixedZ(float) { Draw(); }

void DrawString3D::Draw() { UtilDrawString(mText.c_str(), mPos, mCol); }

void DrawString::DrawFixedZ(float) { Draw(); }

void DrawString::Draw() { TheRnd->DrawString(mText.c_str(), mPos, mCol, true); }

void DrawSphere::DrawFixedZ(float f) { UtilDrawSphere(Vector3(mCenter.X(), mCenter.Z(), f), mRadius, mCol); }

void DrawSphere::Draw() { UtilDrawSphere(mCenter, mRadius, mCol); }

void Line::DrawFixedZ(float f) { 
    TheRnd->DrawLine(Vector3(mA.X(), mA.Y(), f), Vector3(mB.X(), mB.Y(), f), mCol, mZBuf);
}

void Line::Draw() { TheRnd->DrawLine(mA, mB, mCol, mZBuf); }
