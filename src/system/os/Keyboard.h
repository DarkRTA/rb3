#ifndef OS_KEYBOARD_H
#define OS_KEYBOARD_H
#include "obj/Msg.h"
#include "obj/Object.h"

void KeyboardInitCommon();
void KeyboardTerminateCommon();

void KeyboardInit();
void KeyboardTerminate();
void KeyboardPoll();

void KeyboardSubscribe(Hmx::Object*);
void KeyboardUnsubscribe(Hmx::Object*);
Hmx::Object* KeyboardOverride(Hmx::Object*);
void KeyboardSendMsg(int, bool, bool, bool);

BEGIN_MESSAGE(KeyboardKeyMsg, key, int, bool, bool, bool);
    MESSAGE_ARRAY_CTOR(KeyboardKeyMsg)
END_MESSAGE;

inline KeyboardKeyMsg::KeyboardKeyMsg(int i, bool b1, bool b2, bool b3)
    : Message(Type(), DataNode(i), DataNode(b1), DataNode(b2), DataNode(b3)) {
}

#endif
