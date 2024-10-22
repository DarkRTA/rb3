#pragma once
#include "meta_band/BandProfile.h"
#include "obj/Msg.h"
#include "os/User.h"

class PrimaryProfileChangedMsg : public Message {
public:
    PrimaryProfileChangedMsg() : Message(Type()) {}
    PrimaryProfileChangedMsg(DataArray *da) : Message(da) {}
    virtual ~PrimaryProfileChangedMsg() {}
    static Symbol Type() {
        static Symbol t("primary_profile_changed_msg");
        return t;
    }
};

class ProfileChangedMsg : public Message {
public:
    ProfileChangedMsg(BandProfile* p) : Message(Type(), p) {}
    ProfileChangedMsg(DataArray *da) : Message(da) {}
    virtual ~ProfileChangedMsg() {}
    static Symbol Type() {
        static Symbol t("profile_changed_msg");
        return t;
    }
    BandProfile* GetProfile() const { return mData->Obj<BandProfile>(2); }
};

// turns out this was already implemented in os/ProfileSwappedMsg.h
// class ProfileSwappedMsg : public Message {
// public:
//     ProfileSwappedMsg(LocalUser* u1, LocalUser* u2) : Message(Type(), u1, u2) {}
//     ProfileSwappedMsg(DataArray *da) : Message(da) {}
//     virtual ~ProfileSwappedMsg() {}
//     static Symbol Type() {
//         static Symbol t("profile_swapped");
//         return t;
//     }
//     LocalUser* GetUser1() const { return mData->Obj<LocalUser>(2); }
//     LocalUser* GetUser2() const { return mData->Obj<LocalUser>(3); }
// };