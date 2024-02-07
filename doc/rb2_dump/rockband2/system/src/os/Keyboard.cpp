/*
    Compile unit: C:\rockband2\system\src\os\Keyboard.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BE560 -> 0x805BEA4C
*/
static class MsgSource gSource; // size: 0x48, address: 0x80985908
static class ObjPtr gOverride; // size: 0xC, address: 0x8098595C
// Range: 0x805BE560 -> 0x805BE5AC
void KeyboardSubscribe() {
    // References
    // -> static class MsgSource gSource;
    // -> const char * gNullStr;
}

// Range: 0x805BE5AC -> 0x805BE5E8
void KeyboardUnsubscribe() {
    // References
    // -> static class MsgSource gSource;
    // -> const char * gNullStr;
}

// Range: 0x805BE5E8 -> 0x805BE660
class Object * KeyboardOverride(class Object * override /* r30 */) {
    // References
    // -> static class ObjPtr gOverride;
}

// Range: 0x805BE660 -> 0x805BE948
void KeyboardSendMsg() {
    // Local variables
    class KeyboardKeyMsg msg; // r1+0x48

    // References
    // -> static class MsgSource gSource;
    // -> static class ObjPtr gOverride;
    // -> struct [anonymous] __vt__14KeyboardKeyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

// Range: 0x805BE948 -> 0x805BEA4C
static void __sinit_\Keyboard_cpp() {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> static class ObjPtr gOverride;
    // -> struct [anonymous] __vt__9MsgSource;
    // -> static class MsgSource gSource;
}


