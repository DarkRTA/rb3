#include "network/Core/Job.h"

namespace Quazal {

    Job::Job(const DebugString &) : unk8(0), unkc(0), unk14(0) {
        unk1c = Initial;
        unk20 = 0;
        unk24 = 0;
        unk10 = 0;
        unk30 = 0;
        unk31 = 0;
    }

    Job::~Job() {}

    void Job::PerformExecution(const Time &time) {
        unk28 = time;
        DecoratedExecute();
        if (unk1c == 4) {
            SetDefaultPostExecutionState();
        }
        unk24++;
    }

    void Job::SetDefaultPostExecutionState() {
        ValidateTransition(unk1c, Complete);
        unk1c = Complete;
        if (unk10) {
            (*unk10)(this, unk14);
        }
    }

    String Job::GetTraceInfo() const { return ""; }

    void Job::Resume() {
        ValidateTransition(unk1c, Ready);
        unk1c = Ready;
    }

    void Job::SetToWaiting(int i) {
        ValidateTransition(unk1c, Waiting);
        unk1c = Waiting;
        unk20 = i;
    }

    void Job::SetToSuspended() {
        ValidateTransition(unk1c, Suspended);
        unk1c = Suspended;
    }

    void Job::SetToReady() {
        ValidateTransition(unk1c, Ready);
        unk1c = Ready;
    }

    void Job::SetToRunning() {
        ValidateTransition(unk1c, Running);
        unk1c = Running;
    }

    void Job::SetToComplete() {
        ValidateTransition(unk1c, Complete);
        unk1c = Complete;
    }

    void Job::SetToCancel() {
        ValidateTransition(unk1c, Complete);
        unk1c = Complete;
    }

    void Job::SetToInitial() {
        ValidateTransition(unk1c, Initial);
        unk1c = Initial;
    }

    // what even is the point of this function lmao
    void Job::ValidateTransition(State s1, State s2) {
        if (s1 == Initial && s2 == Waiting)
            return;
        if (s1 == Initial && s2 == Suspended)
            return;
        if (s1 == Initial && s2 == Ready)
            return;
        if (s1 == Complete && s2 == Initial)
            return;
        if (s1 == Ready && s2 == Running)
            return;
        if (s1 == Running && s2 == Suspended)
            return;
        if (s1 == Running && s2 == Waiting)
            return;
        if (s1 == Running && s2 == Complete)
            return;
        if (s1 == Suspended && s2 == Ready)
            return;
        if (s1 == Waiting && s2 == Ready)
            return;
        if (s1 == Ready && s2 == Ready)
            return;
        if (s1 == Running && s2 == Ready)
            return;
        if (s1 == Waiting && s2 == Complete)
            return;
        if (s1 == Ready && s2 == Complete)
            return;
        if (s1 == Suspended && s2 == Complete)
            return;
        if (s1 == Waiting && s2 == Waiting)
            return;
    }

}