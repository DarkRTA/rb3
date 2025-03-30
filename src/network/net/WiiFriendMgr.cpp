#include "network/net/WiiFriendMgr.h"
#include "Platform/StringStream.h"
#include "net/Server.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include "utl/Std.h"
#include "utl/UTF8.h"

WiiFriendMgr TheWiiFriendMgr;

WiiFriendProfile::WiiFriendProfile() : mPrincipalID(0), mName(""), mStatus("") {}
WiiFriendProfile::~WiiFriendProfile() {}

WiiFriendProfile &WiiFriendProfile::operator=(const WiiFriendProfile &wp) {
    mPrincipalID = wp.mPrincipalID;
    mName = wp.mName;
    mStatus = wp.mStatus;
    return *this;
}

WiiFriend::WiiFriend() : unk0(""), mConsoleCode(0), mMasterProfile(0), unk24(0) {}

WiiFriend::~WiiFriend() {
    DeleteAll(unk18);
    if (mMasterProfile) {
        RELEASE(mMasterProfile);
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
        if (strcmp(p->mName.c_str(), cc) == 0)
            return p;
    }
    return nullptr;
}

WiiFriend &WiiFriend::operator=(const WiiFriend &wf) {
    unk0 = wf.unk0;
    mConsoleCode = wf.mConsoleCode;
    DeleteAll(unk18);
    int num = wf.NumProfiles();
    for (int i = 0; i < num; i++) {
        WiiFriendProfile *p = new WiiFriendProfile();
        *p = *wf.GetProfileByIdx(i);
        unk18.push_back(p);
    }
    if (wf.mMasterProfile) {
        mMasterProfile = new WiiFriendProfile();
        *mMasterProfile = *wf.mMasterProfile;
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
    p->mName = str;
    p->unk1c = this;
    unk18.push_back(p);
    return p;
}

void WiiFriend::SetMasterProfileStatus(const char *cc) {
    if (mMasterProfile)
        mMasterProfile->SetStatus(cc);
}

bool WiiFriend::PromoteMasterProfile() {
    String name = WiiFriendMgr::GetMasterProfileName(ConsoleCode());
    for (std::vector<WiiFriendProfile *>::iterator it = unk18.begin(); it < unk18.end();
         ++it) {
        if (strcmp((*it)->Name(), name.c_str()) == 0) {
            mMasterProfile = *it;
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
    for (std::vector<WiiFriend *>::const_iterator it = mFriends.begin();
         it < mFriends.end();
         ++it) {
        WiiFriend *cur = *it;
        WiiFriendProfile *p = cur->MasterProfile();
        if (p && id == p->mPrincipalID) {
            return cur;
        }
    }
    return nullptr;
}

WiiFriend *WiiFriendList::GetFriendByConsoleCode(unsigned long long code) const {
    for (std::vector<WiiFriend *>::const_iterator it = mFriends.begin();
         it < mFriends.end();
         ++it) {
        WiiFriend *cur = *it;
        if (cur->ConsoleCode() == code) {
            return cur;
        }
    }
    return nullptr;
}

WiiFriendProfile *WiiFriendList::GetProfile(int i1) const {
    int numFriends = mFriends.size();
    for (int i = 0; i < numFriends; i++) {
        WiiFriendProfile *p = GetFriendByIdx(i)->GetProfileByPrincipalID(i1);
        if (p)
            return p;
    }
    return nullptr;
}

void WiiFriendList::Sort(WiiFriendSortFunc func) {
    std::sort(mFriends.begin(), mFriends.end(), func);
}

WiiFriend *WiiFriendList::AddFriend(unsigned long long code, String str) {
    WiiFriend *wf = new WiiFriend();
    MemDoTempAllocations m(true, false);
    int len = str.length() * 3 + 1;
    char *cstr = new char[len];
    UTF8FilterKeyboardString(cstr, len, str.c_str());
    wf->unk0 = cstr;
    wf->mConsoleCode = code;
    mFriends.push_back(wf);
    delete[] cstr;
    return wf;
}

bool WiiFriendList::RemoveFriend(unsigned long long code) {
    for (std::vector<WiiFriend *>::iterator it = mFriends.begin(); it < mFriends.end();
         ++it) {
        if ((*it)->ConsoleCode() == code) {
            delete *it;
            mFriends.erase(it);
            return true;
        }
    }
    return false;
}

String WiiFriendMgr::GetMasterProfileName(unsigned long long code) {
    Quazal::StringStream stream;
    stream << "Master User (" << code << ")";
    return stream.m_szBuffer;
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

void WiiFriendMgr::Init() {
    SetName("wii_friend_mgr", ObjectDir::Main());
    TheServer->AddSink(this, ServerStatusChangedMsg::Type());
}

void WiiFriendMgr::Terminate() {
    TheServer->RemoveSink(this, ServerStatusChangedMsg::Type());
    if (unk1c)
        unk1c->ReleaseRef();
    if (unk20)
        unk20->ReleaseRef();
    if (unk64) {
        RELEASE(unk64);
    }
    if (unkb4) {
    }
    if (unk2c) {
        unk2c = false;
    }
}

void WiiFriendMgr::GetCachedFriends(WiiFriendList *list) { *list = unk24; }

void WiiFriendMgr::UseConsoleFriends(bool b1) {
    if (!b1) {
        DeleteAll(unk24.mFriends);
    }
    unk68 = b1;
}

void WiiFriendMgr::SetStatusDelimiter(char iDelimiter) {
    MILO_ASSERT(iDelimiter, 0x2C7);
    if (iDelimiter) {
        unkb8 = iDelimiter;
        unkb9 = false;
    }
}