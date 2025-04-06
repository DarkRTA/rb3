#include "network/Core/StateMachine.h"

namespace Quazal {

    StateMachine::StateMachine(StateFunc func)
        : mCurrentState(&StateMachine::TopState), mSourceState(func) {}

    StateMachine::~StateMachine() {}

    StateMachine::StateFunc StateMachine::TopState(const QEvent &) { return 0; }

    void StateMachine::InitialTransition() {
        QSimpleEvent event(0);
        (this->*mSourceState)(event);
        StateFuncFactory state = mCurrentState;

        Trigger(state, 2);
        while (!Trigger(state, 1)) {
            state = mCurrentState;
            Trigger(state, 2);
        }
    }

    void
    StateMachine::StaticStateTransition(TransitionPath *path, StateFuncFactory func) {
        StateFuncFactory state = mCurrentState;
        while (state) {
            StateFunc triggered = Trigger(state, 3);
            if (!triggered) {
                Trigger(state, 0);
            }
        }

        // clang-format off
        // local_24 = *(param_1 + 4);
        // local_20 = *(param_1 + 8);
        // local_1c = *(param_1 + 0xc);
        // while (iVar1 = __ptmf_cmpr(&local_24,param_1 + 0x10), iVar1 != 0) {
        //   local_3c = local_24;
        //   local_38 = local_20;
        //   local_34 = local_1c;
        //   QSimpleEvent::QSimpleEvent(auStack_a0,3);
        //   fn_806F5E50(&local_6c,param_1,auStack_a0); ptmf call
        //   local_78 = local_6c;
        //   local_74 = local_68;
        //   local_70 = local_64;
        //   local_30 = local_6c;
        //   local_2c = local_68;
        //   local_28 = local_64;
        //   iVar1 = fn_806F5DBC(&local_30); ptmf test
        //   if (iVar1 == 0) {
        //     local_48 = local_24;
        //     local_44 = local_20;
        //     local_40 = local_1c;
        //     QSimpleEvent::QSimpleEvent(auStack_a8,0);
        //     fn_806F5E50(&local_84,param_1,auStack_a8); ptmf call
        //     local_90 = local_84;
        //     local_8c = local_80;
        //     local_88 = local_7c;
        //     local_24 = local_84;
        //     local_20 = local_80;
        //     local_1c = local_7c;
        //   }
        //   else {
        //     local_24 = local_30;
        //     local_20 = local_2c;
        //     local_1c = local_28;
        //   }
        // }


        // if (*(param_2 + 0x18) == 0) {
        //   local_54 = *param_3;
        //   local_50 = param_3[1];
        //   local_4c = param_3[2];
        //   TransitionPathSetup(param_1,param_2,&local_54);
        // }
        // else {
        //   for (uVar3 = *(param_2 + 0x18) >> 1; uVar3 != 0; uVar3 = uVar3 >> 2) {
        //     QSimpleEvent::QSimpleEvent(auStack_98,uVar3 & 3);
        //     fn_806F5E50(auStack_60,param_1,auStack_98);
        //     param_2 = param_2 + 3;
        //   }
        //   uVar2 = *param_2;
        //   *(param_1 + 8) = param_2[1];
        //   *(param_1 + 4) = uVar2;
        //   *(param_1 + 0xc) = param_2[2];
        // }
        // return;
        // clang-format on
    }

    void StateMachine::TransitionPathSetup(TransitionPath *, StateFuncFactory) {}

}