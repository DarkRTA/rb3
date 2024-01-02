#ifndef RB3_BEATMATCHCONTROLLER_HPP
#define RB3_BEATMATCHCONTROLLER_HPP
#include "hmx/object.hpp"
#include "data.hpp"
#include "user.hpp"

class BeatMatchController : public Hmx::Object {
public:
    BeatMatchController(User*, const DataArray*, bool);
    virtual ~BeatMatchController();
    virtual int ButtonToSlot(int btn) const; // btn should be a JoypadButton
    virtual int SlotToButton(int slot) const; // should return a JoypadButton

    User* user;
    int forceMercury;
    bool unk24;
    bool unk25;
    int unk28;
    int unk2c;
    DataArray* slotsArray;
    DataArray* leftySlotsArray;
    DataArray* rightySlotsArray;
};

#endif

        // 808834ac 80 45 93 78     addr       fn_80459378
        // 808834b0 80 45 93 e8     addr       fn_804593E8
        // 808834b4 80 76 f5 40     addr       fn_8076F540_stub
        // 808834b8 00 00 00 00     addr       00000000
        // 808834bc 00 00 00 00     addr       00000000
        // 808834c0 00 00 00 00     addr       00000000
        // 808834c4 80 05 c7 ac     addr       fn_8005C7AC
        // 808834c8 00 00 00 00     addr       00000000
        // 808834cc 80 76 f5 40     addr       fn_8076F540_stub
        // 808834d0 80 77 ba a0     addr       fn_8077BAA0
        // 808834d4 80 45 94 74     addr       fn_80459474
        // 808834d8 80 45 94 7c     addr       fn_8045947C
        // 808834dc 80 76 f5 40     addr       fn_8076F540_stub
        // 808834e0 80 77 ba a0     addr       fn_8077BAA0
        // 808834e4 80 76 f5 40     addr       fn_8076F540_stub
        // 808834e8 80 76 f5 40     addr       fn_8076F540_stub
        // 808834ec 80 76 f5 40     addr       fn_8076F540_stub
        // 808834f0 80 12 66 f4     addr       fn_801266F4
        // 808834f4 80 77 ba b0     addr       fn_8077BAB0
