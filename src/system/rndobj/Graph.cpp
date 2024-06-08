#include "rndobj/Graph.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include <list>

RndGraph* sOneFrame;
std::list<RndGraph>* sGraphs;

static DataNode OnGraphReset(DataArray*) {
    RndGraph::ResetAll();
    return DataNode();
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
