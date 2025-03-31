#include "net/NetSession.h"
#include "Platform/Time.h"
#include "decomp.h"
#include "game/Game.h"
#include "meta_band/SessionMgr.h"
#include "MatchmakingSettings.h"
#include "Net.h"
#include "NetMessage.h"
#include "NetSession.h"
#include "SessionMessages.h"
#include "game/BandUser.h"
#include "net/Net.h"
#include "net/NetMessenger.h"
#include "net/NetSearchResult.h"
#include "net/QuazalSession.h"
#include "net/SessionMessages.h"
#include "net/SyncStore.h"
#include "net/VoiceChatMgr.h"
#include "network/ObjDup/Session.h"
#include "network/ObjDup/Station.h"
#include "network/Extensions/SessionClock.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include "utl/BinStream.h"
#include "utl/HxGuid.h"
#include "utl/MemStream.h"
#include "utl/Symbols.h"
#include <vector>
#include <algorithm>

NetSession *TheNetSession;
std::vector<LocalUser *> gLocalUsersRemovedThisFrame;

NetMessage *JoinRequestMsg::NewNetMessage() { return new JoinRequestMsg(); }
NetMessage *JoinResponseMsg::NewNetMessage() { return new JoinResponseMsg(kSuccess, 0); }
NetMessage *NewUserMsg::NewNetMessage() { return new NewUserMsg(); }
NetMessage *UserLeftMsg::NewNetMessage() { return new UserLeftMsg(); }
NetMessage *AddUserRequestMsg::NewNetMessage() { return new AddUserRequestMsg(); }
NetMessage *AddUserResponseMsg::NewNetMessage() { return new AddUserResponseMsg(); }
NetMessage *UpdateUserDataMsg::NewNetMessage() { return new UpdateUserDataMsg(); }
NetMessage *BeginArbitrationMsg::NewNetMessage() { return new BeginArbitrationMsg(); }
NetMessage *FinishedArbitrationMsg::NewNetMessage() {
    return new FinishedArbitrationMsg();
}
NetMessage *StartGameOnTimeMsg::NewNetMessage() { return new StartGameOnTimeMsg(); }
NetMessage *EndGameMsg::NewNetMessage() { return new EndGameMsg(); }
NetMessage *VoiceDataMsg::NewNetMessage() { return new VoiceDataMsg(); }
NetMessage *DataArrayMsg::NewNetMessage() { return new DataArrayMsg(); }

namespace {
    void RegisterSessionMessages() {
        JoinRequestMsg::Register();
        JoinResponseMsg::Register();
        NewUserMsg::Register();
        AddUserRequestMsg::Register();
        AddUserResponseMsg::Register();
        UserLeftMsg::Register();
        UpdateUserDataMsg::Register();
        BeginArbitrationMsg::Register();
        FinishedArbitrationMsg::Register();
        StartGameOnTimeMsg::Register();
        EndGameMsg::Register();
        VoiceDataMsg::Register();
        DataArrayMsg::Register();
    }

    void DisconnectOnFail() {}
}

NetSession::NetSession()
    : mData(0), mLocalHost(0), mJoinData(0), mSettings(new SessionSettings()),
      mJobMgr(this), mCurrentStateJobID(-1), mGameState(kInLobby),
      mRevertingJoinResult(0), mGameStartTime(0), mState(kIdle), mOnlineEnabled(0),
      mQNet(0) {
    SetName("session", ObjectDir::Main());
    DataArray *cfg = SystemConfig("net", "session");
    cfg->FindData("game_start_delay", mGameStartDelay, true);

    cfg->FindInt("connection_timeout");
    cfg->FindInt("max_connection_silence");

    RegisterSessionMessages();
    TheDebug.AddExitCallback(DisconnectOnFail);
    MILO_ASSERT(!TheNetSession, 0x5B);
    TheNetSession = this;
}

NetSession::~NetSession() {
    RELEASE(mData);
    RELEASE(mJoinData);
    RELEASE(mGameStartTime);
    RELEASE(mQNet);
    RELEASE(mSettings);
    QuazalSession::KillSession();
    while (QuazalSession::StillDeleting()) {
        QuazalSession::Poll();
    }
    gLocalUsersRemovedThisFrame.clear();
    TheNetSession = nullptr;
}

void NetSession::RegisterOnline() {
    MILO_ASSERT(!IsOnlineEnabled(), 0x78);
    if (IsBusy()) {
        MILO_FAIL("NetSession::!IsBusy %d\n", mState);
    }
    AssignLocalOwner();
    MILO_ASSERT(!mData, 0x7C);
    mData = SessionData::New();
    SetState(kCreatingHostSession);
    Job *job = new MakeQuazalSessionJob(&mQNet, true);
    mCurrentStateJobID = job->ID();
    mJobMgr.QueueJob(job);
}

void NetSession::AssignLocalOwner() {
    MILO_ASSERT(!mLocalHost, 0x89);
    std::vector<LocalUser *> users;
    GetLocalUserList(users);
    mLocalHost = TheUserMgr->GetLocalUserFromPadNum(ThePlatformMgr.GetOwnerOfGuest(0));
    MILO_ASSERT(mLocalHost, 0xA5);
}

void NetSession::OnCreateSessionJobComplete(bool b) {
    MILO_ASSERT(mState == kCreatingHostSession || mState == kCreatingJoinSession || mState == kRevertingToHost, 0xAC);
    if (mState == kCreatingHostSession) {
        if (b) {
            SetState(kRegisteringHostSession);
            Job *job = PrepareRegisterHostSessionJob();
            mCurrentStateJobID = job->ID();
            mJobMgr.QueueJob(job);
        } else {
            SetState(kIdle);
            static SessionReadyMsg msg(0);
            MsgSource::Handle(msg, false);
        }
    } else if (mState == kCreatingJoinSession) {
        if (b) {
            SetState(kConnectingToSession);
            Job *job = PrepareConnectSessionJob();
            mCurrentStateJobID = job->ID();
            mJobMgr.QueueJob(job);
        } else {
            JoinResponseMsg msg(kCannotConnect, 0);
            OnMsg(msg);
        }
    } else {
        SetState(kIdle);
        MILO_ASSERT(mRevertingJoinResult, 0xD2);
        JoinResultMsg msg = mRevertingJoinResult->Data();
        RELEASE(mRevertingJoinResult);
        Handle(msg, false);
        if (!b)
            Disconnect();
    }
}

void NetSession::OnRegisterSessionJobComplete(bool b) {
    MILO_ASSERT(mState == kRegisteringHostSession, 0xE0);
    SetState(kIdle);
    if (b) {
        std::vector<LocalUser *> users;
        GetLocalUserList(users);
        for (int i = 0; i < users.size(); i++) {
            RemoveLocalFromSession(users[i]);
        }
        mOnlineEnabled = true;
        MILO_ASSERT(mLocalHost, 0xEF);
        AddLocalToSession(mLocalHost);
        for (int i = 0; i < users.size(); i++) {
            if (users[i] != mLocalHost) {
                AddLocalToSession(users[i]);
            }
        }
    } else
        Disconnect();

    SessionReadyMsg msg(b);
    MsgSource::Handle(msg, false);
}

void NetSession::OnConnectSessionJobComplete(bool b) {
    MILO_ASSERT(mState == kConnectingToSession, 0x103);
    if (b) {
        if (!IsOnlineEnabled()) {
            std::vector<LocalUser *> users;
            GetLocalUserList(users);
            for (int i = 0; i < users.size(); i++) {
                users[i]->UpdateOnlineID();
            }
        }
        SetState(kRequestingJoin);
        JoinRequestMsg msg(mUsers, mSettings->ModeFilter());
        TheNetMessenger.DeliverMsg(
            Quazal::Session::GetInstance()->GetMasterID(), msg, kReliable
        );
    } else {
        static JoinResponseMsg response(kCannotConnect, 0);
        OnMsg(response);
    }
}

void NetSession::Clear() {
    Disconnect();
    std::vector<LocalUser *> users;
    GetLocalUserList(users);
    for (int i = 0; i < users.size(); i++) {
        RemoveLocalUser(users[i]);
    }
    SetState(kIdle);
    mGameState = kInLobby;
    mSettings->Clear();
}

UNPOOL_DATA
void NetSession::Disconnect() {
    if (mState == kRequestingNewUser) {
        SetState(kIdle);
        static AddUserResultMsg failureMsg(0);
        Handle(failureMsg, false);
    }
    if (mState == kRequestingJoin) {
        static JoinResponseMsg response(kCannotConnect, 0);
        OnMsg(response);
    }

    for (int jobID = mCurrentStateJobID; jobID != -1;) {
        mCurrentStateJobID = -1;
        MILO_ASSERT(mJobMgr.HasJob(jobID), 0x14C);
        mJobMgr.CancelJob(jobID);
    }

    RELEASE(mGameStartTime);

    if (mGameState == kInOnlineGame) {
        EndSession(false);
        mGameState = kInLocalGame;
    }

    std::vector<LocalUser *> localusers;
    GetLocalUserList(localusers);
    for (int i = 0; i < localusers.size(); i++) {
        RemoveLocalFromSession(localusers[i]);
    }
    mOnlineEnabled = false;
    RELEASE(mQNet);
    RELEASE(mRevertingJoinResult);
    mLocalHost = nullptr;
    mStillArbitrating.clear();
    DeleteSession();
    RELEASE(mJoinData);
    RELEASE(mData);
    for (int i = 0; i < localusers.size(); i++) {
        AddLocalToSession(localusers[i]);
    }
    for (int i = 0; i < mUsers.size();) {
        if (!mUsers[i]->IsLocal()) {
            ProcessUserLeftMsg(UserLeftMsg(mUsers[i]));
            i = 0;
        } else
            i++;
    }
    static SessionDisconnectedMsg msg;
    Handle(msg, false);
}
END_UNPOOL_DATA

void NetSession::Poll() {
    mJobMgr.Poll();
    bool b2 = false;
    if (mGameState == (GameState)1) {
        bool b1 = true;
        if (mGameStartTime) {
            b1 = false;
        }
        if (b1)
            b2 = true;
    }
    if (b2)
        EnterInGameState();
    if (mQNet) {
        if (mQNet->HasHostLeft()) {
            if (!(mState >= 3 && mState <= 6)) {
                Disconnect();
            } else if (mState == 5) {
                static JoinResponseMsg response(kCannotConnect, 0);
                OnMsg(response);
            }
        } else {
            std::vector<int> clients;
            if (mQNet->HaveClientsLeft(clients)) {
                FOREACH (it, clients) {
                    RemoveClient(*it);
                }
            }
        }
    }
    QuazalSession::Poll();
    gLocalUsersRemovedThisFrame.clear();
}

bool NetSession::IsLocal() const {
    if (mState - 3U <= 3) {
        return false;
    } else if (!mOnlineEnabled)
        return true;
    else if (!IsHost())
        return false;
    else {
        for (int i = 0; i < mUsers.size(); i++) {
            if (!mUsers[i]->IsLocal())
                return false;
        }
        return true;
    }
}

FORCE_LOCAL_INLINE
bool NetSession::IsOnlineEnabled() const { return mOnlineEnabled; }
END_FORCE_LOCAL_INLINE

UNPOOL_DATA
void NetSession::Join(NetSearchResult *res) {
    MILO_ASSERT(mState == kIdle, 0x1CC);
    if (mOnlineEnabled && mData->Equals(res->mSessionData)) {
        static JoinResultMsg msg(kNoSelfJoin, 0);
        Handle(msg, false);
    } else if (!IsLocal()) {
        static JoinResultMsg msg(kAlreadyHosting, 0);
        Handle(msg, false);
    } else {
        if (!mOnlineEnabled)
            AssignLocalOwner();
        SetState(kCreatingJoinSession);
        RELEASE(mJoinData);
        mJoinData = SessionData::New();
        res->mSessionData->CopyInto(mJoinData);
        RELEASE(mQNet);
        Job *job = new MakeQuazalSessionJob(&mQNet, false);
        mCurrentStateJobID = job->ID();
        mJobMgr.QueueJob(job);
    }
}
END_UNPOOL_DATA

namespace {
    void DenyRequest(unsigned int ui, JoinResponseError err, int custom) {
        MILO_ASSERT(custom == -1 || err == kCustom, 0x1F2);
        JoinResponseMsg respMsg(err, custom);
        TheNetMessenger.DeliverMsg(ui, respMsg, kReliable);
        ProcessedJoinRequestMsg pjReqMsg(false);
        TheNet.GetNetSession()->Handle(pjReqMsg, false);
    }
}

bool NetSession::CheckJoinable(
    JoinResponseError &err, int &iref, std::vector<UserGuid> users, BinStream &bs
) {
    if (!IsHost()) {
        err = kNotHosting;
        return false;
    } else if (IsBusy()) {
        err = kBusy;
        return false;
    } else {
        int numUsers = mUsers.size();
        int numAllowedPlayers = TheNet.GetGameData()->GetNumPlayersAllowed();
        if (numAllowedPlayers - numUsers < users.size()) {
            err = kNoRoom;
            return false;
        } else {
            for (int i = 0; i < users.size(); i++) {
                User *curUser = TheUserMgr->GetUser(users[i], false);
                if (curUser && HasUser(curUser)) {
                    err = kSameGuid;
                    return false;
                }
            }
            int num;
            if (!TheNet.GetGameData()->AuthenticateJoin(bs, num)) {
                err = kCustom;
                iref = num;
                return false;
            } else
                return true;
        }
    }
}

void NetSession::UpdateSyncStore(const User *user) {
    unsigned int machineID = user->mMachineID;
    TheSyncStore->SyncUser(user);
    SyncUserMsg msg(user);
    SendToAllClientsExcept(msg, kReliable, machineID);
    SyncAllMsg allmsg;
    unsigned int ui = machineID;
    TheNetMessenger.DeliverMsg(ui, allmsg, kReliable);
}

bool NetSession::OnMsg(const JoinRequestMsg &msg) {
    unsigned int sender = TheNetMessenger.LastSender();
    if (IsJoining()) {
        TheNetMessenger.FlushClientMessages(sender);
        return false;
    } else {
        int curNumUsers = msg.NumUsers();
        JoinResponseError err;
        int unk11c = -1;
        MemStream ms;
        msg.GetAuthenticationData(ms);
        ms.Seek(0, BinStream::kSeekBegin);
        std::vector<UserGuid> users;
        for (int i = 0; i < curNumUsers; i++) {
            users.push_back(msg.GetUserGuid(i));
        }
        if (!CheckJoinable(err, unk11c, users, ms)) {
            DenyRequest(sender, err, unk11c);
            TheNetMessenger.FlushClientMessages(sender);
            return false;
        } else if (mSettings->ModeFilter() != msg.GameMode()) {
            DenyRequest(sender, kWrongMode, -1);
            TheNetMessenger.FlushClientMessages(sender);
            return false;
        } else {
            JoinResponseMsg respMsg(kSuccess, 0);
            std::vector<User *> joiners;
            for (int i = 0; i < curNumUsers; i++) {
                RemoteUser *remoteUser = GetNewRemoteUser();
                remoteUser->SetUserGuid(msg.GetUserGuid(i));
                MemStream rms;
                msg.GetUserData(i, rms);
                rms.Seek(0, BinStream::kSeekBegin);
                remoteUser->SyncLoad(rms, -1);
                remoteUser->mMachineID = sender;
                AddRemoteToSession(remoteUser);
                joiners.push_back(remoteUser);
                NewUserMsg userMsg(remoteUser);
                SendToAllClientsExcept(userMsg, kReliable, sender);
                NewRemoteUserMsg remoteUserMsg(remoteUser);
                Handle(remoteUserMsg, false);
            }
            TheNetMessenger.DeliverMsg(sender, respMsg, kReliable);
            std::vector<User *> usersInList;
            GetUserList(usersInList);
            FOREACH (it, usersInList) {
                if (sender != (*it)->mMachineID) {
                    NewUserMsg userMsg(*it);
                    TheNetMessenger.DeliverMsg(sender, userMsg, kReliable);
                }
            }
            MILO_ASSERT(!joiners.empty(), 0x28D);
            UpdateSyncStore(joiners.front());
            static ProcessedJoinRequestMsg acceptedMsg(true);
            MsgSource::Handle(acceptedMsg, false);
        }
    }
    return true;
}

bool NetSession::OnMsg(const JoinResponseMsg &msg) {
    MILO_ASSERT(mState == kRequestingJoin || mState == kConnectingToSession || mState == kCreatingJoinSession, 0x29B);
    if (msg.Joined()) {
        std::vector<LocalUser *> users;
        GetLocalUserList(users);
        FOREACH (it, users) {
            if (!(*it)->HasOnlinePrivilege()) {
                JoinResponseMsg respMsg(kCannotConnect, 0);
                return OnMsg(respMsg);
            }
        }
        FOREACH (it, users) {
            RemoveLocalFromSession(*it);
        }
        mOnlineEnabled = true;
        FinishJoin(msg);
        delete mData;
        mData = mJoinData;
        mJoinData = nullptr;
        FOREACH (it, users) {
            AddLocalToSession(*it);
        }
        TheVoiceChatMgr->JoinVoiceChannel();
        SetState(kIdle);
        JoinResultMsg jMsg(msg.Error(), msg.CustomError());
        Handle(jMsg, false);
    } else {
        FinishJoin(msg);
        RELEASE(mJoinData);
        RELEASE(mQNet);
        if (mOnlineEnabled) {
            MILO_ASSERT(!mRevertingJoinResult, 0x2E0);
            mRevertingJoinResult = new JoinResultMsg(msg.Error(), msg.CustomError());
            SetState(kRevertingToHost);
            Job *job = new MakeQuazalSessionJob(&mQNet, true);
            mCurrentStateJobID = job->ID();
            mJobMgr.QueueJob(job);
        } else {
            MILO_ASSERT(mLocalHost, 0x2EC);
            mLocalHost = nullptr;
            SetState(kIdle);
            JoinResultMsg jMsg(msg.Error(), msg.CustomError());
            Handle(jMsg, false);
        }
    }
    return true;
}

void NetSession::AddLocalUser(LocalUser *newUser) {
    MILO_ASSERT(mState == kIdle, 0x2F9);
    MILO_ASSERT(newUser, 0x2FA);
    MILO_ASSERT(!HasUser(newUser), 0x2FC);
    if (IsHost()) {
        AddLocalToSession(newUser);
        NewUserMsg msg(newUser);
        SendToAllClientsExcept(msg, kReliable, -1);
        static AddUserResultMsg successMsg(1);
        Handle(successMsg, false);
    } else {
        SetState(kRequestingNewUser);
        newUser->UpdateOnlineID();
        AddUserRequestMsg msg(newUser);
        TheNetMessenger.DeliverMsg(
            Quazal::Session::GetInstance()->GetMasterID(), msg, kReliable
        );
    }
}

bool NetSession::OnMsg(const AddUserRequestMsg &msg) {
    unsigned int lastsender = TheNetMessenger.LastSender();
    int ie4 = -1;
    JoinResponseError err;
    MemStream stream(false);
    msg.GetAuthenticationData(stream);
    stream.Seek(0, BinStream::kSeekBegin);
    std::vector<UserGuid> guids;
    guids.push_back(msg.GetUserGuid());
    if (!CheckJoinable(err, ie4, guids, stream)) {
        AddUserResponseMsg msg(0);
        TheNetMessenger.DeliverMsg(lastsender, msg, kReliable);
        return false;
    } else {
        RemoteUser *newremote = GetNewRemoteUser();
        newremote->SetUserGuid(msg.GetUserGuid());
        MemStream ustream(false);
        msg.GetUserData(ustream);
        ustream.Seek(0, BinStream::kSeekBegin);
        newremote->SyncLoad(ustream, -1);
        newremote->mMachineID = lastsender;
        AddRemoteToSession(newremote);
        NewUserMsg umsg(newremote);
        SendToAllClientsExcept(umsg, kReliable, lastsender);
        NewRemoteUserMsg rumsg(newremote);
        Handle(rumsg, false);
        AddUserResponseMsg respmsg(newremote);
        TheNetMessenger.DeliverMsg(lastsender, respmsg, kReliable);
        return true;
    }
}

bool NetSession::OnMsg(const AddUserResponseMsg &msg) {
    MILO_ASSERT(mState == kRequestingNewUser, 0x346);
    if (msg.mSuccess) {
        AddLocalToSession(TheUserMgr->GetLocalUser(msg.mUserGuid, true));
    }
    SetState(kIdle);
    static AddUserResultMsg result(1);
    result[0] = msg.mSuccess;
    Handle(result, false);
    return true;
}

bool NetSession::OnMsg(const NewUserMsg &msg) {
    MILO_ASSERT(!IsHost(), 0x35A);
    MILO_ASSERT(mQNet, 0x35B);
    RemoteUser *newUser = GetNewRemoteUser();
    newUser->SetUserGuid(msg.mUserGuid);
    MILO_ASSERT(!HasUser(newUser), 0x35F);
    MemStream stream(false);
    msg.GetUserData(stream);
    stream.Seek(0, BinStream::kSeekBegin);
    newUser->SyncLoad(stream, -1);
    AddRemoteToSession(newUser);
    NewRemoteUserMsg rmsg(newUser);
    Handle(rmsg, false);
    return true;
}

void NetSession::RemoveLocalUser(LocalUser *user) {
    MILO_ASSERT(user, 0x36E);
    if (HasUser(user)) {
        RemoveLocalFromSession(user);
        if ((IsOnlineEnabled() && !IsJoining()) || mState == kRequestingJoin) {
            UserLeftMsg msg(user);
            if (IsHost()) {
                SendToAllClientsExcept(msg, kReliable, -1);
            } else {
                TheNetMessenger.DeliverMsg(
                    Quazal::Session::GetInstance()->GetMasterID(), msg, kReliable
                );
            }
        }
        user->Reset();
        LocalUserLeftMsg msg(user);
        Export(msg, true);
        if (user == mLocalHost)
            Disconnect();
    }
}

bool NetSession::OnMsg(const UserLeftMsg &msg) {
    ProcessUserLeftMsg(msg);
    return true;
}

void NetSession::ProcessUserLeftMsg(const UserLeftMsg &msg) {
    RemoteUser *ruser = TheUserMgr->GetRemoteUser(msg.mUserGuid, true);
    if (HasUser(ruser)) {
        unsigned int machineID = ruser->GetMachineID();
        RemovingRemoteUserMsg rmsg(ruser);
        Handle(rmsg, false);
        RemoveRemoteFromSession(ruser);
        if (IsHost()) {
            SendToAllClientsExcept(msg, kReliable, machineID);
        }
        RemoteUserLeftMsg rleftmsg(ruser);
        Handle(rleftmsg, false);
    }
}

void NetSession::StartGame() {
    MILO_ASSERT(IsHost(), 0x3C3);
    MILO_ASSERT(mState == kIdle, 0x3C4);
    if (mSettings->Ranked())
        StartArbitration();
    else
        BeginGameStartCountdown();
}

void NetSession::StartArbitration() {
    MILO_ASSERT(IsHost(), 0x3D3);
    SetState(kClientsArbitrating);
    for (int i = 0; i < mUsers.size(); i++) {
        if (!mUsers[i]->IsLocal()) {
            unsigned int target = mUsers[i]->mMachineID;
            std::vector<int>::iterator it =
                std::find(mStillArbitrating.begin(), mStillArbitrating.end(), target);
            if (it == mStillArbitrating.end())
                mStillArbitrating.push_back(target);
        }
    }
    BeginArbitrationMsg amsg;
    SendToAllClientsExcept(amsg, kReliable, -1);
}

bool NetSession::OnMsg(const BeginArbitrationMsg &) {
    MILO_ASSERT(mState == kIdle, 0x3E9);
    SetState(kClientsArbitrating);
    Job *job = PrepareRegisterArbitrationJob();
    job->ID();
    mJobMgr.QueueJob(job);
    return true;
}

bool NetSession::OnMsg(const FinishedArbitrationMsg &msg) {
    SetDoneArbitrating(msg.MachineID());
    return true;
}

void NetSession::SetDoneArbitrating(int id) {
    MILO_ASSERT(IsHost(), 0x3F9);
    MILO_ASSERT(mState == kClientsArbitrating, 0x3FA);
    std::vector<int>::iterator it =
        std::find(mStillArbitrating.begin(), mStillArbitrating.end(), id);
    MILO_ASSERT(it != mStillArbitrating.end(), 0x400);
    mStillArbitrating.erase(it);
    if (mStillArbitrating.empty()) {
        SetState(kHostArbitrating);
        Job *job = PrepareRegisterArbitrationJob();
        mCurrentStateJobID = job->ID();
        mJobMgr.QueueJob(job);
    }
}

DECOMP_FORCEACTIVE(NetSession, "mState == kHostArbitrating")

void NetSession::BeginGameStartCountdown() {
    MILO_ASSERT(IsHost(), 0x421);
    MILO_ASSERT(mState == kIdle || mState == kHostArbitrating, 0x422);
    MILO_ASSERT(mGameState == kInLobby, 0x423);
    SetState(kIdle);
    mGameState = kStartingGame;
    int i2 = IsLocal() ? 0 : mGameStartDelay;
    MILO_ASSERT(!mGameStartTime, 0x427);
    if (i2) {
        mGameStartTime = new Quazal::Time(Quazal::SessionClock::GetTime() + i2);
        StartGameOnTimeMsg msg(*mGameStartTime);
        SendToAllClientsExcept(msg, kReliable, -1);
    }
}

bool NetSession::OnMsg(const StartGameOnTimeMsg &msg) {
    MILO_ASSERT(!IsHost(), 0x432);
    MILO_ASSERT(mState == kIdle || mState == kHostArbitrating, 0x433);
    MILO_ASSERT(!mGameStartTime, 0x434);
    MILO_ASSERT(mGameState == kInLobby, 0x435);
    SetState(kIdle);
    mGameState = kStartingGame;
    mGameStartTime = new Quazal::Time(msg.mStartTime);
    return true;
}

void NetSession::EndGame(int i, bool reportResult, float f) {
    MILO_ASSERT(IsInGame(), 0x43E);
    if (IsHost()) {
        bool ranked = mSettings->Ranked();
        if (ranked)
            MILO_ASSERT(reportResult, 0x444);
        EndGameMsg msg(i, ranked, f);
        SendToAllClientsExcept(msg, kReliable, -1);
        LeaveInGameState(i, reportResult, f);
    } else {
        EndGameMsg msg(i, reportResult, f);
        TheNetMessenger.DeliverMsg(
            Quazal::Session::GetInstance()->GetMasterID(), msg, kReliable
        );
    }
}

bool NetSession::OnMsg(const EndGameMsg &msg) {
    if (IsInGame()) {
        if (IsHost()) {
            EndGame(msg.mResultCode, msg.mReportStats, msg.unkc);
        } else {
            LeaveInGameState(msg.mResultCode, msg.mReportStats, msg.unkc);
        }
    }
    return true;
}

LocalUser *NetSession::GetLocalHost() const { return mLocalHost; }

bool NetSession::HasUser(const User *user) const {
    MILO_ASSERT(user, 0x470);
    return std::find(mUsers.begin(), mUsers.end(), user) != mUsers.end();
}

void NetSession::GetLocalUserList(std::vector<LocalUser *> &users) const {
    for (int i = 0; i < mUsers.size(); i++) {
        if (mUsers[i]->IsLocal()) {
            LocalUser *u = mUsers[i]->GetLocalUser();
            users.push_back(u);
        }
    }
}

void NetSession::GetRemoteUserList(std::vector<RemoteUser *> &users) const {
    for (int i = 0; i < mUsers.size(); i++) {
        if (!mUsers[i]->IsLocal()) {
            RemoteUser *u = mUsers[i]->GetRemoteUser();
            users.push_back(u);
        }
    }
}

void NetSession::GetUserList(std::vector<User *> &users) const {
    for (int i = 0; i < mUsers.size(); i++) {
        users.push_back(mUsers[i]);
    }
}

int NetSession::NumOpenSlots() const {
    return TheNet.GetGameData()->GetNumPlayersAllowed() - mUsers.size();
}

RemoteUser *NetSession::GetNewRemoteUser() {
    std::vector<RemoteUser *> rusers;
    TheUserMgr->GetRemoteUsers(rusers);
    for (int i = 0; i < rusers.size(); i++) {
        if (!HasUser(rusers[i]))
            return rusers[i];
    }
    MILO_FAIL("No more free Remote Users to be assigned!");
    return nullptr;
}

void NetSession::UpdateUserData(User *user, unsigned int ui) {
    MILO_ASSERT(user, 0x4A6);
    MILO_ASSERT(user->IsLocal(), 0x4A7);
    if (HasUser(user) && !IsBusy()) {
        UpdateUserDataMsg msg(user, ui);
        if (IsHost()) {
            SendToAllClientsExcept(msg, kReliable, -1);
        } else {
            TheNetMessenger.DeliverMsg(
                Quazal::Session::GetInstance()->GetMasterID(), msg, kReliable
            );
        }
    }
}

bool NetSession::OnMsg(const UpdateUserDataMsg &msg) {
    RemoteUser *ruser = TheUserMgr->GetRemoteUser(msg.mUserGuid, false);
    if (ruser) {
        MemStream stream(false);
        msg.GetUserData(stream);
        stream.Seek(0, BinStream::kSeekBegin);
        ruser->SyncLoad(stream, msg.mDirtyMask);
        if (IsHost()) {
            SendToAllClientsExcept(msg, kReliable, ruser->mMachineID);
        }
        RemoteUserUpdatedMsg msg(ruser);
        Handle(msg, false);
    }
    return true;
}

void NetSession::SendMsg(User *destUser, NetMessage &msg, PacketType ptype) {
    MILO_ASSERT(destUser, 0x4D1);
    std::vector<RemoteUser *> remoteusers;
    remoteusers.push_back(destUser->GetRemoteUser());
    SendMsg(remoteusers, msg, ptype);
}

using namespace Quazal;

void NetSession::SendMsg(
    const std::vector<RemoteUser *> &users, NetMessage &msg, PacketType ptype
) {
    if (!mOnlineEnabled || !mQNet)
        return;
    else {
        std::vector<unsigned int> machineIDs;
        for (int i = 0; i < users.size(); i++) {
            unsigned int machineID = users[i]->GetMachineID();
            std::vector<unsigned int>::iterator it =
                std::find(machineIDs.begin(), machineIDs.end(), machineID);
            if (it == machineIDs.end()) {
                MILO_ASSERT(machineID != Station::GetLocalInstance()->GetStationID(), 0x4EA);
                TheNetMessenger.DeliverMsg(machineID, msg, ptype);
                machineIDs.push_back(machineID);
            }
        }
    }
}

void NetSession::SendMsgToAll(NetMessage &msg, PacketType ptype) {
    if (!mOnlineEnabled || !mQNet)
        return;
    SendToAllClientsExcept(msg, ptype, -1);
}

DataNode NetSession::OnSendMsg(DataArray *a) {
    User *destUser = a->Obj<User>(2);
    DataArray *arr = a->Array(3);
    int i = a->Int(4);
    DataArrayMsg msg(arr);
    SendMsg(destUser, msg, (PacketType)i);
    return 1;
}

DataNode NetSession::OnSendMsgToAll(DataArray *a) {
    DataArray *arr = a->Array(2);
    int i = a->Int(3);
    DataArrayMsg msg(arr);
    SendMsgToAll(msg, (PacketType)i);
    return 1;
}

void NetSession::SendToAllClientsExcept(
    const NetMessage &msg, PacketType ptype, unsigned int ui
) {
    if (mQNet) {
        MILO_ASSERT(Station::GetLocalInstance(), 0x516);
        std::vector<unsigned int> machineIDs;
        machineIDs.push_back(Station::GetLocalInstance()->GetStationID());
        machineIDs.push_back(ui);
        for (int i = 0; i < mUsers.size(); i++) {
            unsigned int machineID = mUsers[i]->GetMachineID();
            std::vector<unsigned int>::iterator it =
                std::find(machineIDs.begin(), machineIDs.end(), machineID);
            if (it == machineIDs.end()) {
                TheNetMessenger.DeliverMsg(machineID, msg, ptype);
                machineIDs.push_back(machineID);
            }
        }
    }
}

void NetSession::AddLocalToSession(LocalUser *user) {
    user->UpdateOnlineID();
    if (mOnlineEnabled) {
        user->mMachineID = Quazal::Station::GetLocalInstance()->GetStationID();
    }
    mUsers.push_back(user);
}

void NetSession::AddRemoteToSession(RemoteUser *user) { mUsers.push_back(user); }

void NetSession::RemoveLocalFromSession(LocalUser *user) {
    mUsers.erase(std::find(mUsers.begin(), mUsers.end(), user));
}

void NetSession::RemoveRemoteFromSession(RemoteUser *user) {
    mUsers.erase(std::find(mUsers.begin(), mUsers.end(), user));
}

void NetSession::EnterInGameState() {
    MILO_ASSERT(mGameState == kStartingGame, 0x552);
    if (mOnlineEnabled) {
        mGameState = kInOnlineGame;
        StartSession();
    } else {
        mGameState = kInLocalGame;
    }
    static SyncStartGameMsg start;
    Handle(start, false);
}

void NetSession::LeaveInGameState(int i1, bool b2, float f3) {
    switch (mGameState) {
    case kInOnlineGame:
        EndSession(b2);
        break;
    case kInLocalGame:
        break;
    default:
        MILO_FAIL("NetSession::LeaveInGameState while in state %i", mGameState);
    }
    mGameState = kInLobby;
    RELEASE(mGameStartTime);
    GameEndedMsg msg(i1, f3);
    Handle(msg, false);
}

void NetSession::RemoveClient(unsigned int ui) {
    TheNetMessenger.FlushClientMessages(ui);
    if (IsHost()) {
        for (int i = 0; i < mUsers.size(); i) {
            User *cur = mUsers[i];
            if (ui == cur->mMachineID) {
                UserLeftMsg msg(cur);
                ProcessUserLeftMsg(msg);
                i = 0;
            } else
                i++;
        }
        if (mState == kClientsArbitrating) {
            SetDoneArbitrating(ui);
        }
    }
}

bool NetSession::IsHost() const {
    if (mState == kRequestingNewUser || IsJoining())
        return false;
    if (mState == kCreatingHostSession || mState == kRegisteringHostSession) {
        return true;
    } else if (mQNet) {
        return Quazal::Session::GetInstance()->IsADuplicationMaster();
    } else
        return true;
}

bool NetSession::IsBusy() const {
    switch (mState) {
    case kCreatingHostSession:
    case kRegisteringHostSession:
    case kCreatingJoinSession:
    case kConnectingToSession:
    case kRequestingJoin:
    case kRevertingToHost:
    case kRequestingNewUser:
        return true;
    case kIdle:
    case kClientsArbitrating:
    case kHostArbitrating:
        return false;
    default:
        MILO_FAIL("Invalid state %i in NetSession::IsBusy()", mState);
        return false;
    }
}

FORCE_LOCAL_INLINE
bool NetSession::IsJoining() const { return mState - 3 <= 3U; }
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
bool NetSession::IsInGame() const {
    return mGameState == kInLocalGame || mGameState == kInOnlineGame;
}
END_FORCE_LOCAL_INLINE

bool NetSession::IsStartingGame() const { return mGameState == kStartingGame; }

void NetSession::SetState(SessionState state) {
    bool oldbusy = IsBusy();
    mState = state;
    mCurrentStateJobID = -1;
    if (oldbusy != IsBusy()) {
        static SessionBusyMsg msg;
        MsgSource::Handle(msg, false);
    }
}

void NetSession::HandleSessionMsg(SessionMsg *smsg) {
    int targetByteCode = smsg->ByteCode();
    if (targetByteCode == JoinRequestMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<JoinRequestMsg *>(smsg));
    } else if (targetByteCode == JoinResponseMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<JoinResponseMsg *>(smsg));
    } else if (targetByteCode == NewUserMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<NewUserMsg *>(smsg));
    } else if (targetByteCode == AddUserRequestMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<AddUserRequestMsg *>(smsg));
    } else if (targetByteCode == AddUserResponseMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<AddUserResponseMsg *>(smsg));
    } else if (targetByteCode == UserLeftMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<UserLeftMsg *>(smsg));
    } else if (targetByteCode == UpdateUserDataMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<UpdateUserDataMsg *>(smsg));
    } else if (targetByteCode == BeginArbitrationMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<BeginArbitrationMsg *>(smsg));
    } else if (targetByteCode == FinishedArbitrationMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<FinishedArbitrationMsg *>(smsg));
    } else if (targetByteCode == StartGameOnTimeMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<StartGameOnTimeMsg *>(smsg));
    } else if (targetByteCode == EndGameMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<EndGameMsg *>(smsg));
    } else if (targetByteCode == VoiceDataMsg::StaticByteCode()) {
        OnMsg(*dynamic_cast<VoiceDataMsg *>(smsg));
    }
}

BEGIN_HANDLERS(NetSession)
    HANDLE_ACTION(disconnect, Disconnect())
    HANDLE_ACTION(clear, Clear())
    HANDLE(send_msg, OnSendMsg)
    HANDLE(send_msg_to_all, OnSendMsgToAll)
    HANDLE_EXPR(num_users, (int)mUsers.size())
END_HANDLERS