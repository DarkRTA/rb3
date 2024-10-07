#pragma once
#include "obj/Object.h"
#include "os/Timer.h"
#include <list>

class PassiveMessage {
public:

};

class PassiveMessageQueue {
public:
    PassiveMessageQueue(Hmx::Object* o) : mMessageDuration(2000.0f), mCallback(o) {}
    virtual ~PassiveMessageQueue(){}
    virtual PassiveMessage* GetAndPreProcessFirstMessage();
    virtual void AddMessage(PassiveMessage*);

    void SetMessageDuration(float);
    void Poll();

    float mMessageDuration; // 0x4
    std::list<PassiveMessage*> mQueue; // 0x8
    Hmx::Object* mCallback; // 0x10
    Timer mTimer; // 0x14
};