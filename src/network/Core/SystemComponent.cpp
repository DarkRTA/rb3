#include "SystemComponent.h"
#include "Core/PseudoSingleton.h"
#include "Core/Scheduler.h"
#include "decomp.h"
#include "network/Platform/TraceLog.h"

DECOMP_FORCEACTIVE(SystemComponent, 
"Uninitialized",
"Initializing",
"Ready",
"ReadyInUse",
"TerminatingInUse",
"Terminating",
"Terminated",
"Faulty",
"Unknown",
"Invalid"
)

namespace Quazal {
SystemComponent::SystemComponent(const String& s) : mName(s), mState((_State)1), mRefs(0), mParent(NULL) {}

SystemComponent::~SystemComponent() {
    if (mParent != 0) mParent = 0;
}

void SystemComponent::SetName(const String& name) {
    mName = name;
}

bool SystemComponent::SetState(_State state, bool b) {
    if (!b && !ValidTransition(state)) {
        return false;
    } else {
        StateTransition(state);
        mState = state;
        return true;
    }
}

void SystemComponent::SetParent(SystemComponent* parent) {
    if (mParent != NULL) mParent = NULL;
    if (parent == NULL) return;
    mParent = parent;
}

bool SystemComponent::ValidTransition(_State state) {
    if (state == Faulty) return true;
    if (state == Unknown) return true;
    switch(mState) {
        case Uninitialized   : return (state == Initializing || state == TerminatingInUse || state == Terminated);
        case Initializing    : return state == Ready;
        case Ready           : return (state == ReadyInUse || state == TerminatingInUse);
        case ReadyInUse      : return (state == Ready || state == Terminating);
        case Terminating     : return (mRefs == 0 && state == TerminatingInUse);
        case TerminatingInUse: return state == Terminated;
        case Terminated      : return (state == Uninitialized || state == Initializing);
        case Faulty          : return true;
        case Unknown         : return true;

        default: return false;
    }
}

bool SystemComponent::UseIsAllowed() {
    return mState == Ready || mState == ReadyInUse;
}

void SystemComponent::Trace(uint ui, bool b) const {
    if (b) {
        TraceLog::ScopedIndent indent(2);
        TraceImpl(ui);
    }
}

SystemComponent::_State Quazal::SystemComponent::Initialize() {
    OnInitialize();
    _State s = mState;
    switch(s) {
        case Uninitialized:
        case Terminated:
            if (ValidTransition(Initializing)) {
                StateTransition(Initializing);
                mState = Initializing;
            }
            if (BeginInitialization() && ValidTransition(Ready)) {
                StateTransition(Ready);
                mState = Ready;
            }
            return mState;
            break;
        case Initializing:
            if (EndInitialization() && ValidTransition(Ready)) {
                StateTransition(Ready);
                mState = Ready;
            }
            return mState;
            break;
        case Ready:
        case ReadyInUse:
            return mState;
        default:
            {
                TraceLog::ScopedIndent indent(2);
                TraceImpl(1);
            }
            return mState;
    }
    return s;
}

bool SystemComponent::BeginInitialization() { return true; }

SystemComponent::_State SystemComponent::Terminate() {
    OnTerminate();
    _State s = mState;
    switch(s) {
        case Terminated : return s;

        case ReadyInUse      :
            if (ValidTransition(Terminating)) {
                StateTransition(Terminating);
                mState = Terminating;
            }
            return mState;
            break;
        case Uninitialized   :
        case Initializing    :
        case Ready           :
        case Unknown         :
        case Faulty          :
            StateTransition(TerminatingInUse);
            mState = TerminatingInUse;
            if (BeginTermination() && ValidTransition(Terminated)) {
                StateTransition(Terminated);
                mState = Terminated;
            }
            return mState;
            break;
        case Terminating     :
            if (mRefs == 0) {
                if (ValidTransition(TerminatingInUse)) {
                    StateTransition(TerminatingInUse);
                    mState = TerminatingInUse;
                }
                if (BeginTermination() && ValidTransition(Terminated)) {
                    StateTransition(Terminated);
                    mState = Terminated;
                }
            }
            return mState;
            break;
        case TerminatingInUse:
            if (EndTermination() && ValidTransition(Terminated)) {
                StateTransition(Terminated);
                mState = Terminated;
            }
            return mState;
            break;
        default:
            { // necessary because the compiler interleaves the loading/returning elsewise
                TraceLog::ScopedIndent indent(2);
                TraceImpl(1);
            }
            return mState;
    }
    return s;
}

bool SystemComponent::BeginTermination() { return true; }

SystemComponent::Use::Use(Quazal::SystemComponent* sc, const char* cc) : mComponent(sc), mName(cc) {
    bool b;
    if (sc->UseIsAllowed()) {
        if (sc->mState == Ready && sc->ValidTransition(ReadyInUse)) {
            sc->StateTransition(ReadyInUse);
            sc->mState = ReadyInUse;
        }
        sc->mRefs++;
        b = true;
    } else b = false;
    mComponentExists = b;
}

SystemComponent::Use::~Use() {
    if (mComponentExists) {
        SystemComponent* sc = mComponent;
        if (!(--sc->mRefs)) {
            if (sc->mState == ReadyInUse) {
                if (sc->ValidTransition(Ready)) {
                    sc->StateTransition(Ready);
                    sc->mState = Ready;
                }
            } else {
                if (sc->ValidTransition(TerminatingInUse)) {
                    sc->StateTransition(TerminatingInUse);
                    sc->mState = TerminatingInUse;
                }
            }
        }
    }
}

void SystemComponent::WaitForTerminatedState(unsigned int ui) { // returns struct
    Terminate();
    if (ui != 0 && Scheduler::CurrentThreadCanWaitForJob()) {
        if (PseudoSingleton::GetCurrentContext() == 0) {

        } else {
            
        }
    }
}
}
