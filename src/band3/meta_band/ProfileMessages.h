#pragma once
#include "meta_band/BandProfile.h"
#include "obj/Msg.h"

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