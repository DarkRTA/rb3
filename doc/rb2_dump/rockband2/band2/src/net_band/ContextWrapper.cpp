/*
    Compile unit: C:\rockband2\band2\src\net_band\ContextWrapper.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8021437C -> 0x80214C8C
*/
static float kContextTimeoutPeriodMs; // size: 0x4, address: 0x80A566C0
class ContextWrapper {
    // total size: 0x50
    class Object * mCallbackObject; // offset 0x0, size 0x4
    class Updatable * mUpdatable; // offset 0x4, size 0x4
    unsigned char mDeleteUpdatable; // offset 0x8, size 0x1
    int mId; // offset 0xC, size 0x4
    class ProtocolCallContext * mContext; // offset 0x10, size 0x4
    class Timer mTimeout; // offset 0x18, size 0x38
};
// Range: 0x8021437C -> 0x802143CC
void * ContextWrapper::ContextWrapper(class ContextWrapper * const this /* r31 */) {}

// Range: 0x802143CC -> 0x80214440
void * ContextWrapper::~ContextWrapper(class ContextWrapper * const this /* r30 */) {}

// Range: 0x80214440 -> 0x802144E8
void ContextWrapper::SetCallbackObject(class ContextWrapper * const this /* r27 */, class Object * object /* r28 */, class Updatable * updatable /* r29 */, unsigned char delete_updatable /* r30 */, int id /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802144E8 -> 0x802144F0
class Object * ContextWrapper::GetCallbackObject() {}

// Range: 0x802144F0 -> 0x80214584
void ContextWrapper::Reset(class ContextWrapper * const this /* r31 */) {}

// Range: 0x80214584 -> 0x802148DC
void ContextWrapper::Poll(class ContextWrapper * const this /* r31 */) {
    // Local variables
    class RockCentralOpCompleteMsg msg; // r1+0x30
    class RockCentralOpCompleteMsg msg; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__7Message;
    // -> class RockCentralGateway RockCentral;
    // -> static float kContextTimeoutPeriodMs;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

class ContextWrapperPool {
    // total size: 0x640
    class ContextWrapper mContextWrappers[20]; // offset 0x0, size 0x640
};
// Range: 0x802148DC -> 0x80214A58
class ContextWrapper * ContextWrapperPool::NewContextWrapper(class Object * object /* r29 */, int id /* r30 */) {
    // Local variables
    int i; // r4
    class RockCentralOpCompleteMsg msg; // r1+0x18

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
}

// Range: 0x80214A58 -> 0x80214ADC
void ContextWrapperPool::CancelOutstandingContexts(class ContextWrapperPool * const this /* r28 */, class Object * object /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80214ADC -> 0x80214C30
void ContextWrapperPool::FailAllContexts(class ContextWrapperPool * const this /* r30 */) {
    // Local variables
    int i; // r31
    class RockCentralOpCompleteMsg msg; // r1+0x18

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x80214C30 -> 0x80214C8C
void ContextWrapperPool::Poll(class ContextWrapperPool * const this /* r30 */) {
    // Local variables
    int i; // r31
}


