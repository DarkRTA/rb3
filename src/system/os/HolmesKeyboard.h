#ifndef OS_HOLMESKEYBOARD_H
#define OS_HOLMESKEYBOARD_H
#include "obj/Object.h"
#include "utl/MemStream.h"

struct CWnd {
    int hell_if_i_know_lmao;
};

class HolmesInput : public Hmx::Object {
public:
    HolmesInput(CWnd*);
    virtual ~HolmesInput();
    virtual DataNode Handle(DataArray*, bool);

    void LoadKeyboard(BinStream&);
    void LoadJoypad(BinStream&);
    void SendKeyboardMessages();
    int SendJoypadMessages();

    bool mSubscribe;
    MemStream* mJoypadBuffer;
    MemStream* mKeyboardBuffer;
    CWnd* mOwner;
};

#endif
