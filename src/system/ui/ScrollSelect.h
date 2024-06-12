#ifndef UI_SCROLLSELECT_H
#define UI_SCROLLSELECT_H
#include "obj/Data.h"
#include "obj/Object.h"
#include "ui/UIComponent.h"
#include "os/Joypad.h"

class LocalUser;

class ScrollSelect {
public:
    ScrollSelect();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~ScrollSelect(){}
    virtual int SelectedAux() const = 0;
    virtual void SetSelectedAux(int) = 0;

    void Store();
    void Reset();
    bool SelectScrollSelect(UIComponent*, LocalUser*);
    DataNode SendScrollSelected(UIComponent*, LocalUser*);
    bool CanScroll() const;
    UIComponent::State DrawState(UIComponent*) const;
    bool CatchNavAction(JoypadAction) const;
    bool RevertScrollSelect(UIComponent*, LocalUser*, Hmx::Object*);

    bool unk_0x4;
    int unk_0x8;

    DELETE_POOL_OVERLOAD(ScrollSelect);
};

#endif // UI_SCROLLSELECT_H
