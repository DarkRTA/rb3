#include "network/net/WiiFriendMgr.h"
#include "utl/Std.h"

WiiFriendProfile::WiiFriendProfile() : mPrincipalID(0), unk4(""), unk10("") {}
WiiFriendProfile::~WiiFriendProfile() {}

WiiFriendProfile &WiiFriendProfile::operator=(const WiiFriendProfile &wp) {
    mPrincipalID = wp.mPrincipalID;
    unk4 = wp.unk4;
    unk10 = wp.unk10;
    return *this;
}

WiiFriend::WiiFriend() : unk0(""), unk10(0), unk20(0), unk24(0) {}

WiiFriend::~WiiFriend() {
    DeleteAll(unk18);
    if (unk20) {
        RELEASE(unk20);
    }
}

WiiFriendProfile *WiiFriend::GetProfileByIdx(int idx) const {
    if (idx >= 0 && idx < (int)unk18.size())
        return unk18[idx];
    else
        return nullptr;
}

WiiFriendProfile *WiiFriend::GetProfileByPrincipalID(int id) const {
    int numProfiles = unk18.size();
    for (int i = 0; i < numProfiles; i++) {
        WiiFriendProfile *p = GetProfileByIdx(i);
        if (p->mPrincipalID == id)
            return p;
    }
    return nullptr;
}

WiiFriendProfile *WiiFriend::GetProfile(const char *cc) const {
    int numProfiles = unk18.size();
    for (int i = 0; i < numProfiles; i++) {
        WiiFriendProfile *p = GetProfileByIdx(i);
        if (strcmp(p->unk4.c_str(), cc) == 0)
            return p;
    }
    return nullptr;
}

WiiFriend &WiiFriend::operator=(const WiiFriend &wf) {
    unk0 = wf.unk0;
    unk10 = wf.unk10;
    DeleteAll(unk18);
    int num = wf.NumProfiles();
    for (int i = 0; i < num; i++) {
        WiiFriendProfile *p = new WiiFriendProfile();
        *p = *wf.GetProfileByIdx(i);
        unk18.push_back(p);
    }
    if (wf.unk20) {
        unk20 = new WiiFriendProfile();
        *unk20 = *wf.unk20;
    }
    unk24 = wf.unk24;
    return *this;
}

void WiiFriend::SortProfiles(WiiFriendProfileSortFunc func) {
    std::sort(unk18.begin(), unk18.end(), func);
}

WiiFriendProfile *WiiFriend::AddProfile(int id, String str) {
    WiiFriendProfile *p = new WiiFriendProfile();
    p->mPrincipalID = id;
    p->unk4 = str;
    p->unk1c = this;
    unk18.push_back(p);
    return p;
}

void WiiFriend::SetMasterProfileStatus(const char *cc) {
    if (unk20)
        unk20->unk10 = cc;
}

bool WiiFriend::PromoteMasterProfile() {
    String name = WiiFriendMgr::GetMasterProfileName(unk10);
    FOREACH (it, unk18) {
        if (strcmp((*it)->unk4.c_str(), name.c_str()) == 0) {
            unk20 = *it;
            unk18.erase(it);
            return true;
        }
    }
    return false;
}

WiiFriendList::WiiFriendList() {}

WiiFriendList::~WiiFriendList() { DeleteAll(mFriends); }

WiiFriendList &WiiFriendList::operator=(const WiiFriendList &wfl) {
    int numfriends = wfl.mFriends.size();
    DeleteAll(mFriends);
    for (int i = 0; i < numfriends; i++) {
        WiiFriend *wf = new WiiFriend();
        *wf = *wfl.GetFriendByIdx(i);
        mFriends.push_back(wf);
    }
    return *this;
}

WiiFriend *WiiFriendList::GetFriendByIdx(int idx) const {
    if (idx >= 0 && idx < mFriends.size()) {
        return mFriends[idx];
    } else
        return nullptr;
}

WiiFriend *WiiFriendList::GetFriendByMasterPrincipalID(int id) const {
    for (int i = 0; i < mFriends.size(); i++) {
        WiiFriend *wf = mFriends[i];
        if (wf->unk20->mPrincipalID == id) {
            return wf;
        }
    }
    return nullptr;
}

void WiiFriendList::Sort(WiiFriendSortFunc func) {
    std::sort(mFriends.begin(), mFriends.end(), func);
}

WiiFriendMgr::WiiFriendMgr()
    : unk1c(0), unk20(0), unk2c(0), unk2d(0), unk60(10), unk64(0), unk68(0), unk6c(0),
      unk70(0), unk74(1), unka8(""), unkb4(0) {
    SetStatusDelimiter(':');
    for (int i = 0; i < 4; i++) {
        unk78[i] = "";
    }
}

WiiFriendMgr::~WiiFriendMgr() {}