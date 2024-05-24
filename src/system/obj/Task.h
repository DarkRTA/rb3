#ifndef OBJ_TASK_H
#define OBJ_TASK_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include <list>

class Task : public Hmx::Object {
public:
    Task(){}
    virtual ~Task(){}
    virtual void Poll(float) = 0;
};

class MessageTask : public Task {
public:
    MessageTask(Hmx::Object*, DataArray*);
    virtual ~MessageTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Poll(float);

    ObjOwnerPtr<Hmx::Object, ObjectDir> mObj;
    DataArray* mMsg;
};

class ScriptTask : public Task {
public:

    struct Var {
        Var(DataNode* np, const DataNode& n) : var(np), value(n) {}
        DataNode* var;
        DataNode value;
    };

    ScriptTask(DataArray*, bool, DataArray*);
    virtual ~ScriptTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Poll(float);

    void UpdateVarsObjects(DataArray*);

    std::list<Var> mVars;
    std::list<Hmx::Object*> mObjects;
    ObjOwnerPtr<Hmx::Object, ObjectDir> mThis;
    DataArray* mScript;
    bool mOnce;
};

#endif
