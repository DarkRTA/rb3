#ifndef RNDOBJ_MODALKEYLISTENER_H
#define RNDOBJ_MODALKEYLISTENER_H
#include "obj/Object.h"
#include "os/Keyboard.h"

class ModalKeyListener : public Hmx::Object {
public:
    ModalKeyListener(){}
    virtual ~ModalKeyListener(){}
    virtual DataNode Handle(DataArray*, bool);

    DataNode OnMsg(const KeyboardKeyMsg&);
};

#endif
