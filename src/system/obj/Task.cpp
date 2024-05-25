#include "obj/Task.h"
#include "obj/DataUtl.h"

MessageTask::MessageTask(Hmx::Object* o, DataArray* msg) : mObj(this, o), mMsg(msg) {
    MILO_ASSERT(msg, 0x1D);
    msg->AddRef();
}

MessageTask::~MessageTask(){
    if(mMsg){
        mMsg->Release();
        mMsg = 0;
    }
}

void MessageTask::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(from == mObj){
        if(!to) delete this;
        else mObj = to;
    }
}

void MessageTask::Poll(float f){
    if(mObj && mMsg){
        DataNode r = mObj->Handle(mMsg, false);
        if(r.Type() != kDataUnhandled) delete this;
    }
}

ScriptTask::ScriptTask(DataArray* arr1, bool b, DataArray* arr2) : mThis(this, DataThis()), mScript(arr1), mOnce(b) {
    arr1->AddRef();
    static DataNode* task = DataVariable("task");
    *task = DataNode(this);
    mVars.push_back(Var(task, *task));
    if(!arr2) arr2 = arr1;
    UpdateVarsObjects(arr2);
    *task = DataNode(*task);
}

ScriptTask::~ScriptTask(){
    for(std::list<Hmx::Object*>::iterator it = mObjects.begin(); it != mObjects.end(); it++){
        (*it)->Release(this);
    }
    mScript->Release();
}