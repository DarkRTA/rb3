#pragma once
#include "net/NetMessage.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "os/User.h"
#include "ui/UIComponent.h"

class ComponentFocusNetMsg : public NetMessage {
public:
    ComponentFocusNetMsg() {}
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
    ComponentSelectNetMsg() {}
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
User *GetUser() const { return mData->Obj<User>(2); }
const char *GetStr() const { return mData->Str(3); } // this arg is apparently component?
END_MESSAGE

class ComponentScrollNetMsg : public NetMessage {
public:
    ComponentScrollNetMsg() {}
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

// NET_SCROLL_MSG (net_component_scroll ($user $component $selected_pos $first_showing)
DECLARE_MESSAGE(NetComponentScrollMsg, "net_component_scroll");
NetComponentScrollMsg(User *u, const char *c, int i1, int i2)
    : Message(Type(), u, c, i1, i2) {}
User *GetUser() const { return mData->Obj<User>(2); }
const char *GetStr() const { return mData->Str(3); }
int GetSelectedPos() const { return mData->Int(4); }
int GetFirstShowing() const { return mData->Int(5); }
END_MESSAGE

DECLARE_MESSAGE(NetComponentPostScrollMsg, "net_component_post_scroll");
NetComponentPostScrollMsg(User *u, const char *c, int i1, int i2)
    : Message(Type(), u, c, i1, i2) {}
END_MESSAGE