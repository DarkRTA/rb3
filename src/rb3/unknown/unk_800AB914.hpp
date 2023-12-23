#ifndef UNKNOWN_UNK_800AB914_HPP
#define UNKNOWN_UNK_800AB914_HPP

// static fxn linked to these: fn_800AB960
namespace DiscErrorMgrWii {
    class Callback {
    public:
        Callback();
        virtual void fn_8076F540();
        // virtual fn_8076F540(); // duplicated in the vtable
        // virtual fn_8076F540(); // duplicated in the vtable yet again
    };

    // yes, the vtable actually spells the class name out like that
    class WiiDiscErrorSessionTerminatior : Callback {
    public:
        WiiDiscErrorSessionTerminatior();
        virtual void fn_800AAFBC();
        virtual void fn_8076F540();
        // virtual fn_8076F540(); // duplicated in the vtable
    };
} // namespace DiscErrorMgrWii

#endif
