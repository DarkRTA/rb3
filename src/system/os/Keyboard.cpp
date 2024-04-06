#include "os/Keyboard.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/MsgSource.h"

class MsgSource* gSource;
ObjPtr<Hmx::Object, ObjectDir> gObjOverride(0, 0);

void KeyboardInitCommon(){
    MILO_ASSERT(!gSource, 0x12);
    gSource = Hmx::Object::New<MsgSource>();
}

void KeyboardTerminateCommon(){
    delete gSource;
    gSource = 0;
}

void KeyboardSubscribe(Hmx::Object* o){
    if(gSource){
        gSource->AddSink(o, Symbol(), Symbol(), MsgSource::kHandle);
    }
}

void KeyboardUnsubscribe(Hmx::Object* o){
    if(gSource){
        gSource->RemoveSink(o, Symbol());
    }
}

Hmx::Object* KeyboardOverride(Hmx::Object* o){
    Hmx::Object* d = gObjOverride.mPtr;
    gObjOverride = o;
    return d;
}

void KeyboardSendMsg(int i, bool b1, bool b2, bool b3){
    KeyboardKeyMsg msg(i, b1, b2, b3);
    if(gObjOverride.mPtr){
        gObjOverride.mPtr->Handle(msg, false);
    }
    else {
        gSource->Handle(msg, false);
    }
}
