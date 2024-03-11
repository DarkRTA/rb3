#ifndef META_CONNECTIONSTATUSPANEL_H
#define META_CONNECTIONSTATUSPANEL_H
#include "obj/Object.h"
#include "ui/UIPanel.h"
#include "obj/Msg.h"

BEGIN_MESSAGE(ConnectionStatusChangedMsg, connection_status_changed, int);
END_MESSAGE;

class ConnectionStatusPanel : public UIPanel {
public:
    ConnectionStatusPanel();
    OBJ_CLASSNAME(ConnectionStatusPanel);
    OBJ_SET_TYPE(ConnectionStatusPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ConnectionStatusPanel();
    virtual void Enter();
    virtual void Exit();
    
    void CheckForLostConnection();
    DataNode OnMsg(const ConnectionStatusChangedMsg&);
};

#endif
