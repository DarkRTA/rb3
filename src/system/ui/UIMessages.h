#ifndef UI_UIMESSAGES_H
#define UI_UIMESSAGES_H
#include "obj/Msg.h"
#include "ui/UIComponent.h"

BEGIN_MESSAGE(UIComponentScrollMsg, "component_scroll", UIComponent*, LocalUser*);
END_MESSAGE;

BEGIN_MESSAGE(UIComponentSelectMsg, "component_select", UIComponent*, LocalUser*);
END_MESSAGE;

BEGIN_MESSAGE(UIComponentSelectDoneMsg, "component_select_done", UIComponent*, LocalUser*);
END_MESSAGE;

inline UIComponentScrollMsg::UIComponentScrollMsg(UIComponent* comp, LocalUser* user) : 
    Message(Type(), DataNode(comp), DataNode(user)){}

inline UIComponentSelectMsg::UIComponentSelectMsg(UIComponent* comp, LocalUser* user) : 
    Message(Type(), DataNode(comp), DataNode(user)){}

inline UIComponentSelectDoneMsg::UIComponentSelectDoneMsg(UIComponent* comp, LocalUser* user) : 
    Message(Type(), DataNode(comp), DataNode(user)){}

#endif
