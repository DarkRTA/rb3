#ifndef META_HELDBUTTONPANEL_H
#define META_HELDBUTTONPANEL_H
#include "obj/ObjMacros.h"
#include "ui/UIPanel.h"
#include "meta/ButtonHolder.h"

class HeldButtonPanel : public UIPanel {
public:
    HeldButtonPanel();
    OBJ_CLASSNAME(HeldButtonPanel);
    OBJ_SET_TYPE(HeldButtonPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~HeldButtonPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();

    ButtonHolder* mHolder;
    bool mHandling;

    NEW_OBJ(HeldButtonPanel)
};

#endif