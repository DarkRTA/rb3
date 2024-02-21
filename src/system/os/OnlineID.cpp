#include "os/OnlineID.h"
#include "os/Debug.h"

OnlineID::OnlineID(): mValid(0) {}

void OnlineID::SetPrincipalID(int id){
    mPrincipalID = id;
    mValid = true;
}

int OnlineID::GetPrincipalID() const {
    ASSERT(mValid, 0x61);
    return mPrincipalID;
}

const char* OnlineID::ToString() const {
    if(mValid) return MakeString("%010x", mPrincipalID);
    else return "";
}

bool OnlineID::operator==(const OnlineID& oid) const {
    if(!mValid || !oid.mValid) return mValid == oid.mValid;
    else return mPrincipalID == oid.mPrincipalID;
}

BinStream& operator<<(BinStream& bs, const OnlineID& ssm){
    ASSERT(ssm.mValid, 0xBE);
    bs << ssm.mPrincipalID;
    return bs;
}

BinStream& operator>>(BinStream& bs, OnlineID& oid){
    bs >> oid.mPrincipalID;
    oid.mValid = true;
    return bs;
}
