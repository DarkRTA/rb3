#include "net/SessionMessages.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include "utl/HxGuid.h"
#include "utl/MemStream.h"

JoinRequestMsg::JoinRequestMsg(const std::vector<User*>& users, int gamemode) : mAuthData(false) {
    for(std::vector<User*>::const_iterator it = users.begin(); it != users.end(); ++it){
        mUserGuids.push_back((*it)->mUserGuid);
        MemStream stream(false);
        (*it)->SyncSave(stream, -1);
        mUserDatas.push_back(stream);
    }
    mAuthData.Seek(0, BinStream::kSeekBegin);
    mGameMode = gamemode;
}

void JoinRequestMsg::GetUserData(int index, BinStream& bs) const {
    MILO_ASSERT(index < NumUsers(), 0x33);
    bs.Write(mUserDatas[index].Buffer(), mUserDatas[index].BufferSize());
}

const UserGuid& JoinRequestMsg::GetUserGuid(int index) const {
    MILO_ASSERT(index < NumUsers(), 0x39);
    return mUserGuids[index];
}

void JoinRequestMsg::GetAuthenticationData(BinStream& bs) const {
    bs.Write(mAuthData.Buffer(), mAuthData.BufferSize());
}

void JoinRequestMsg::Save(BinStream& bs) const {
    unsigned char numusers = NumUsers();
    bs << numusers;
    for(int i = 0; i < numusers; i++){
        bs << mUserGuids[i];
        bs << mUserDatas[i].BufferSize();
        GetUserData(i, bs);
    }
    bs << mAuthData.BufferSize();
    GetAuthenticationData(bs);
    bs << mGameMode;
}

void JoinRequestMsg::Load(BinStream& bs){
    unsigned char numusers;
    bs >> numusers;
    for(int i = 0; i < numusers; i++){
        UserGuid uguid;
        bs >> uguid;
        mUserGuids.push_back(uguid);
        int bufsize;
        bs >> bufsize;
        MemStream stream(false);
        mUserDatas.push_back(stream);
        mUserDatas[mUserDatas.size() - 1].Resize(bufsize);
        bs.Read((void*)mUserDatas[mUserDatas.size() - 1].Buffer(), bufsize);
    }
    int bufsize;
    bs >> bufsize;
    mAuthData.Resize(bufsize);
    bs.Read((void*)mAuthData.Buffer(), bufsize);
    bs >> mGameMode;
}

JoinResponseMsg::JoinResponseMsg(JoinResponseError err, int custom) : mError(err), mCustomError(custom) {}
bool JoinResponseMsg::Joined() const { return mError == kSuccess; }

void JoinResponseMsg::Save(BinStream& bs) const {
    bs << mError;
    bs << mCustomError;
}

void JoinResponseMsg::Load(BinStream& bs){
    int error;
    bs >> error;
    mError = (JoinResponseError)error;
    bs >> mCustomError;
}

void JoinResponseMsg::Print(TextStream& ts) const {
    if(mError == kSuccess){
        ts << "Join Request Accepted\n";
    }
    else {
        ts << MakeString("Join Request Rejected, Error=%i, CustomError=%i\n", mError, mCustomError);
    }
}

NewUserMsg::NewUserMsg(const User* user) : mUserData(false) {
    mUserGuid = user->mUserGuid;
    user->SyncSave(mUserData, -1);
}

void NewUserMsg::GetUserData(BinStream& bs) const {
    bs.Write(mUserData.Buffer(), mUserData.BufferSize());
}

void NewUserMsg::Save(BinStream& bs) const {
    bs << mUserGuid;
    bs << mUserData.BufferSize();
    GetUserData(bs);
}

void NewUserMsg::Load(BinStream& bs){
    bs >> mUserGuid;
    int size;
    bs >> size;
    mUserData.Resize(size);
    bs.Read((void*)mUserData.Buffer(), size);
}

UserLeftMsg::UserLeftMsg(User* user) : mUserGuid(user->mUserGuid) {
    
}

void UserLeftMsg::Save(BinStream& bs) const {
    bs << mUserGuid;
}

void UserLeftMsg::Load(BinStream& bs){
    bs >> mUserGuid;
}

AddUserRequestMsg::AddUserRequestMsg(const User* user) : mUserData(false), mAuthData(false) {
    mUserGuid = user->mUserGuid;
}

void AddUserRequestMsg::GetUserData(BinStream& bs) const {
    bs.Write(mUserData.Buffer(), mUserData.BufferSize());
}

void AddUserRequestMsg::GetAuthenticationData(BinStream& bs) const {
    bs.Write(mAuthData.Buffer(), mAuthData.BufferSize());
}

void AddUserRequestMsg::Save(BinStream& bs) const {
    bs << mUserGuid;
    bs << mUserData.BufferSize();
    GetUserData(bs);
    bs << mAuthData.BufferSize();
    GetAuthenticationData(bs);
}

void AddUserRequestMsg::Load(BinStream& bs){
    bs >> mUserGuid;
    int size;
    bs >> size;
    mUserData.Resize(size);
    bs.Read((void*)mUserData.Buffer(), size);
    bs >> size;
    mAuthData.Resize(size);
    bs.Read((void*)mAuthData.Buffer(), size);
}

AddUserResponseMsg::AddUserResponseMsg(User* user) : mSuccess(user) {
    if(user){
        mUserGuid = user->mUserGuid;
    }
}

void AddUserResponseMsg::Save(BinStream& bs) const {
    bs << mSuccess;
    if(mSuccess) bs << mUserGuid;
}

void AddUserResponseMsg::Load(BinStream& bs){
    bs >> mSuccess;
    if(mSuccess) bs >> mUserGuid;
}

UpdateUserDataMsg::UpdateUserDataMsg(const User* user, unsigned int mask) : mDirtyMask(mask), mUserData(false) {
    mUserGuid = user->mUserGuid;
    user->SyncSave(mUserData, mDirtyMask);
}

void UpdateUserDataMsg::GetUserData(BinStream& bs) const {
    bs.Write(mUserData.Buffer(), mUserData.BufferSize());
}

void UpdateUserDataMsg::Save(BinStream& bs) const {
    bs << mUserGuid;
    bs << mDirtyMask;
    bs << mUserData.BufferSize();
    GetUserData(bs);
}

void UpdateUserDataMsg::Load(BinStream& bs){
    bs >> mUserGuid;
    bs >> mDirtyMask;
    int size;
    bs >> size;
    mUserData.Resize(size);
    bs.Read((void*)mUserData.Buffer(), size);
}

void FinishedArbitrationMsg::Save(BinStream& bs) const {
    bs << mMachineID;
}

void FinishedArbitrationMsg::Load(BinStream& bs){
    bs >> mMachineID;
}

StartGameOnTimeMsg::StartGameOnTimeMsg(unsigned long long ul) : mStartTime(ul) {

}

void StartGameOnTimeMsg::Save(BinStream& bs) const {
    bs << mStartTime;
}

void StartGameOnTimeMsg::Load(BinStream& bs){
    bs >> mStartTime;
}

EndGameMsg::EndGameMsg(int i, bool b, float f) : mResultCode(i), mReportStats(b), unkc(f) {

}

void EndGameMsg::Save(BinStream& bs) const {
    bs << mResultCode;
    bs << mReportStats;
    bs << unkc;
}

void EndGameMsg::Load(BinStream& bs){
    bs >> mResultCode;
    bs >> mReportStats;
    bs >> unkc;
}

void VoiceDataMsg::GetVoiceData(BinStream& bs) const {
    bs.Write(mVoiceData.Buffer(), mVoiceData.BufferSize());
}

void VoiceDataMsg::Save(BinStream& bs) const {
    bs << mUserGuid;
    bs << mVoiceData.BufferSize();
    GetVoiceData(bs);
}

void VoiceDataMsg::Load(BinStream& bs){
    bs >> mUserGuid;
    int size;
    bs >> size;
    mVoiceData.Resize(size);
    bs.Read((void*)mVoiceData.Buffer(), size);
}

DataArrayMsg::DataArrayMsg(DataArray* arr) : mBuffer(false) {
    mBuffer << arr;
    mBuffer.Seek(0, BinStream::kSeekBegin);
}

void DataArrayMsg::Save(BinStream& bs) const {
    bs << mBuffer.BufferSize();
    bs.Write(mBuffer.Buffer(), mBuffer.BufferSize());
}

void DataArrayMsg::Load(BinStream& bs){
    int size;
    bs >> size;
    mBuffer.Resize(size);
    bs.Read((void*)mBuffer.Buffer(), size);
}

void DataArrayMsg::Dispatch(){
    DataArray* arr;
    mBuffer >> arr;
    arr->Execute();
    arr->Release();
}

void DataArrayMsg::Print(TextStream& ts) const {
    MemStream stream(false);
    stream.Write(mBuffer.Buffer(), mBuffer.BufferSize());
    stream.Seek(0, BinStream::kSeekBegin);
    DataArray* arr;
    stream >> arr;
    ts << arr;
    arr->Release();
    ts << '\n';
}