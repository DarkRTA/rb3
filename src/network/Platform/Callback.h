#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class CallbackRoot : public RootObject {
    public:
        CallbackRoot() {}
        virtual ~CallbackRoot() {}
        virtual void Call() { CallObjectMethod(); }
        virtual void CallObjectMethod() = 0;
    };

    template <class T1, class T2>
    class Callback : public CallbackRoot {
    public:
        typedef void (T1::*TemplateFunc)(T2);

        Callback(T1 *target, TemplateFunc func, T2 arg)
            : mTargetObject(target), mMethod(func), mArg(arg) {}
        virtual ~Callback() {}
        virtual void CallObjectMethod() {
            TemplateFunc func = mMethod;
            (mTargetObject->*func)(mArg);
        }

        T1 *mTargetObject; // 0x4
        TemplateFunc mMethod; // 0x8
        T2 mArg; // 0x14
    };
}