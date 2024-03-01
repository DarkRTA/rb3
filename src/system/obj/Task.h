#ifndef OBJ_TASK_H
#define OBJ_TASK_H
#include "obj/Object.h"

class Task : public Hmx::Object {
public:
    Task(){}
    virtual ~Task(){}
    virtual void Poll(float) = 0;
};

#endif
