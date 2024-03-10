#ifndef META_CONNECTIONSTATUSPANEL_H
#define META_CONNECTIONSTATUSPANEL_H
#include "obj/Object.h"
#include "ui/UIPanel.h"

class ConnectionStatusPanel : public UIPanel, virtual Hmx::Object {
public:
    ConnectionStatusPanel();
    OBJ_CLASSNAME(ConnectionStatusPanel);
    OBJ_SET_TYPE(ConnectionStatusPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ConnectionStatusPanel();
    virtual void Enter();
    virtual void Exit();
};

#endif
