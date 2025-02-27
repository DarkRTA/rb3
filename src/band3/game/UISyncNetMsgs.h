#pragma once
#include "net/NetMessage.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "os/User.h"
#include "ui/UIComponent.h"

class ComponentFocusNetMsg : public NetMessage {
public:
    ComponentFocusNetMsg(User *, UIComponent *);
    virtual ~ComponentFocusNetMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(ComponentFocusNetMsg);
    NETMSG_NAME(ComponentFocusNetMsg);

    NETMSG_NEWNETMSG(ComponentFocusNetMsg);

    UserGuid mUserGuid; // 0x4
    String mComponentName; // 0x14
};

class ComponentSelectNetMsg : public NetMessage {
public:
    ComponentSelectNetMsg(User *, UIComponent *, bool);
    virtual ~ComponentSelectNetMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(ComponentSelectNetMsg);
    NETMSG_NAME(ComponentSelectNetMsg);

    NETMSG_NEWNETMSG(ComponentSelectNetMsg);

    UserGuid mUserGuid; // 0x4
    String mComponentName; // 0x14
    bool mShowSelect; // 0x20
};

DECLARE_MESSAGE(NetComponentSelectMsg, "net_component_select");
NetComponentSelectMsg(User *o, const char *c) : Message(Type(), o, c) {}
END_MESSAGE

class ComponentScrollNetMsg : public NetMessage {
public:
    ComponentScrollNetMsg(User *, UIComponent *);
    virtual ~ComponentScrollNetMsg() {}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    NETMSG_BYTECODE(ComponentScrollNetMsg);
    NETMSG_NAME(ComponentScrollNetMsg);

    NETMSG_NEWNETMSG(ComponentScrollNetMsg);

    UserGuid mUserGuid; // 0x4
    String mComponentName; // 0x14
    int mPosition; // 0x20
    int mFirstShowing; // 0x24
};

DECLARE_MESSAGE(NetComponentScrollMsg, "net_component_scroll");
NetComponentScrollMsg(User *u, const char *c, int i1, int i2)
    : Message(Type(), u, c, i1, i2) {}
END_MESSAGE

DECLARE_MESSAGE(NetComponentPostScrollMsg, "net_component_post_scroll");
NetComponentPostScrollMsg(User *u, const char *c, int i1, int i2)
    : Message(Type(), u, c, i1, i2) {}
END_MESSAGE