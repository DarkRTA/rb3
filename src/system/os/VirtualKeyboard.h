#ifndef OS_VIRTUALKEYBOARD_H
#define OS_VIRTUALKEYBOARD_H
#include "obj/Object.h"
#include "utl/Str.h"
#include <list>

class VirtualKeyboard : public Hmx::Object {
public:
    VirtualKeyboard();
    virtual ~VirtualKeyboard();
    virtual DataNode Handle(DataArray*, bool);
    std::list<void*> mListIdk;
    Hmx::Object* mPobjKeyboardCallback;
    bool mCallbackReady;
    bool mMsgOk;
    String mCallbackMsg;

    void Init();
    void ClearKeyboardCallback();
    void Terminate();
    void PlatformTerminate();
    DataNode OnShowKeyboardUI(const DataArray*);
};

#endif
