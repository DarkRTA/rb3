#ifndef UI_UI_H
#define UI_UI_H
#include "obj/Object.h"

class UIScreen; // forward dec

class UIManager : public virtual Hmx::Object {
public:
    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIManager();
    virtual void Init();
    virtual void Terminate();
    virtual void Poll();
    virtual void Draw();
    virtual void GotoScreen(const char*, bool, bool);
    virtual void GotoScreen(UIScreen*, bool, bool);
    virtual void PushScreen(UIScreen*);
    virtual void PopScreen(UIScreen*);
    virtual void ResetScreen(UIScreen*);
    virtual int InComponentSelect();
    virtual bool IsBlockingTransition(){ return false; }
    virtual bool IsTimelineResetAllowed() const { return true; }
    virtual void SendTransitionComplete(UIScreen*, UIScreen*);

    int unkc;
    // more members here
};

#endif
