#pragma once
#include "obj/Msg.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

void KeyboardInitCommon();
void KeyboardTerminateCommon();

void KeyboardInit();
void KeyboardTerminate();
void KeyboardPoll();

void KeyboardSubscribe(Hmx::Object *);
void KeyboardUnsubscribe(Hmx::Object *);
Hmx::Object *KeyboardOverride(Hmx::Object *);
void KeyboardSendMsg(int, bool, bool, bool);

extern ObjPtr<Hmx::Object, ObjectDir> gObjOverride;

DECLARE_MESSAGE(KeyboardKeyMsg, "key")
KeyboardKeyMsg(int i, bool b1, bool b2, bool b3) : Message(Type(), i, b1, b2, b3) {}
int GetKey() const { return mData->Int(2); }
bool GetShift() const { return mData->Int(3); }
bool GetCtrl() const { return mData->Int(4); }
bool GetAlt() const { return mData->Int(5); }
END_MESSAGE
;
