#include "os/Keyboard.h"
#include "obj/Object.h"
#include "obj/Msg.h"

#include "decomp.h"

class MsgSource *gSource;
ObjPtr<Hmx::Object, ObjectDir> gObjOverride(nullptr);

void KeyboardInitCommon() {
    MILO_ASSERT(!gSource, 0x12);
    gSource = Hmx::Object::New<MsgSource>();
}

void KeyboardTerminateCommon() { RELEASE(gSource); }

void KeyboardSubscribe(Hmx::Object *o) {
    if (gSource) {
        gSource->AddSink(o);
    }
}

void KeyboardUnsubscribe(Hmx::Object *o) {
    if (gSource) {
        gSource->RemoveSink(o);
    }
}

Hmx::Object *KeyboardOverride(Hmx::Object *o) {
    Hmx::Object *d = gObjOverride;
    gObjOverride = o;
    return d;
}

void KeyboardSendMsg(int key, bool shift, bool ctrl, bool alt) {
    KeyboardKeyMsg msg(key, shift, ctrl, alt);
    if (gObjOverride) {
        gObjOverride->Handle(msg, false);
    } else {
        gSource->Handle(msg, false);
    }
}

DECOMP_FORCEBLOCK(Keyboard, (ObjPtr<Hmx::Object, ObjectDir>* objPtr),
    objPtr->~ObjPtr();
    objPtr->RefOwner();
    objPtr->Replace(nullptr, nullptr);
)
