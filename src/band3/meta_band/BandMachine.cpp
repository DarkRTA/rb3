#include "meta_band/BandMachine.h"
#include "BandMachineMgr.h"
#include "SessionMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "utl/Symbols3.h"

bool IsWaitingNetUIState(NetUIState state){
    return state >= 3 && state <= 8;
}

BandMachine::BandMachine() : mNetUIState(kNetUI_None), mNetUIStateParam(0), mPrimaryBandName(""), mPrimaryProfileName(""), mPrimaryMetaScore(0) {

}

void BandMachine::Reset(){
    mNetUIState = kNetUI_None;
    mNetUIStateParam = 0;
    mPrimaryBandName = "";
    mPrimaryProfileName = "";
    mPrimaryMetaScore = 0;
}

void BandMachine::SyncSave(BinStream& bs, unsigned char mask) const {
    if(mask & 1){
        bs << (unsigned char)mNetUIState;
        bs << mNetUIStateParam;
        bs << mCurrentSongPreview;
    }
    if(mask & 2){
        bs << mAvailableSongs.size();
        for(std::set<int>::const_iterator it = mAvailableSongs.begin(); it != mAvailableSongs.end(); ++it){
            bs << *it;
        }
    }
    if(mask & 8){
        bs << mProGuitarOrBassSongs.size();
        for(std::set<int>::const_iterator it = mProGuitarOrBassSongs.begin(); it != mProGuitarOrBassSongs.end(); ++it){
            bs << *it;
        }
    }
    if(mask & 4){
        bs << mPrimaryBandName;
        bs << mPrimaryProfileName;
        bs << mPrimaryMetaScore;
    }
}

void BandMachine::SyncLoad(BinStream& bs, unsigned char mask){
    if(mask & 1){
        unsigned char state;
        bs >> state;
        mNetUIState = (NetUIState)state;
        bs >> mNetUIStateParam;
        bs >> mCurrentSongPreview;
    }
    if(mask & 2){
        int size;
        bs >> size;
        mAvailableSongs.clear();
        for(int i = 0; i < size; i++){
            int key;
            bs >> key;
            mAvailableSongs.insert(key);
        }
    }
    if(mask & 8){
        int size;
        bs >> size;
        mProGuitarOrBassSongs.clear();
        for(int i = 0; i < size; i++){
            int key;
            bs >> key;
            mProGuitarOrBassSongs.insert(key);
        }
    }
    if(mask & 4){
        bs >> mPrimaryBandName;
        bs >> mPrimaryProfileName;
        bs >> mPrimaryMetaScore;
    }
}

NetUIState BandMachine::GetNetUIState() const { return mNetUIState; }
int BandMachine::GetNetUIStateParam() const { return mNetUIStateParam; }

bool BandMachine::HasSong(int i) const {
    return mAvailableSongs.find(i) != mAvailableSongs.end();
}

bool BandMachine::HasProGuitarOrBass(int i) const {
    return mProGuitarOrBassSongs.find(i) != mProGuitarOrBassSongs.end();
}

BEGIN_HANDLERS(BandMachine)
    HANDLE_EXPR(get_primary_profile_name, GetPrimaryProfileName())
    HANDLE_EXPR(get_primary_band_name, GetPrimaryBandName())
    HANDLE_EXPR(get_primary_metascore, mPrimaryMetaScore)
    HANDLE_EXPR(get_net_ui_state, mNetUIState)
    HANDLE_EXPR(get_net_ui_state_param, mNetUIStateParam)
    HANDLE_EXPR(get_current_song_preview, mCurrentSongPreview.c_str())
    HANDLE_CHECK(0xAB)
END_HANDLERS

String BandMachine::GetPrimaryProfileName(){ return mPrimaryProfileName; }
String BandMachine::GetPrimaryBandName(){ return mPrimaryBandName; }

LocalBandMachine::LocalBandMachine(BandMachineMgr* mgr) : mMachineMgr(mgr) {

}

String LocalBandMachine::GetPrimaryBandName(){
    BandMachineMgr* pMachineMgr = TheSessionMgr->mMachineMgr;
    MILO_ASSERT(pMachineMgr, 0xB7);
    if(pMachineMgr->IsLeaderMachineLocal()){
        BandProfile* pProfile = TheProfileMgr.GetPrimaryProfile();
        MILO_ASSERT(pProfile, 0xBD);
        return pProfile->GetBandName();
    }
    else return BandMachine::GetPrimaryBandName();
}

void LocalBandMachine::SetNetUIState(NetUIState state){
    NetUIState old = mNetUIState;
    mNetUIState = state;
    if(old != state){
        mMachineMgr->SyncLocalMachine(1);
    }
}

void LocalBandMachine::SetNetUIStateParam(int param){
    int old = mNetUIStateParam;
    mNetUIStateParam = param;
    if(old != param){
        mMachineMgr->SyncLocalMachine(1);
    }
}

void LocalBandMachine::SetPrimaryBandName(String name){
    if(name != mPrimaryBandName){
        mPrimaryBandName = name;
        mMachineMgr->SyncLocalMachine(4);
    }
}

void LocalBandMachine::SetPrimaryProfileName(String name){
    if(name != mPrimaryProfileName){
        mPrimaryProfileName = name;
        mMachineMgr->SyncLocalMachine(4);
    }
}

void LocalBandMachine::SetPrimaryMetaScore(int score){
    if(score != mPrimaryMetaScore){
        mPrimaryMetaScore = score;
        mMachineMgr->SyncLocalMachine(4);
    }
}

void LocalBandMachine::SetAvailableSongs(const std::set<int>& songs){
    if(mAvailableSongs != songs){
        mAvailableSongs = songs;
        mMachineMgr->SyncLocalMachine(2);
    }
}

void LocalBandMachine::SetProGuitarOrBassSongs(const std::set<int>& songs){
    if(mProGuitarOrBassSongs != songs){
        mProGuitarOrBassSongs = songs;
        mMachineMgr->SyncLocalMachine(8);
    }
}

void LocalBandMachine::SetCurrentSongPreview(const char* preview){
    if(mCurrentSongPreview != preview){
        mCurrentSongPreview = preview;
        mMachineMgr->SyncLocalMachine(1);
    }
}

RemoteBandMachine::RemoteBandMachine() : mActive(0) {

}

void RemoteBandMachine::Activate(unsigned int id){
    MILO_ASSERT(!mActive, 0x116);
    mID = id;
    mActive = true;
    Reset();
}

void RemoteBandMachine::Deactivate(){
    MILO_ASSERT(mActive, 0x120);
    mActive = false;
}

bool RemoteBandMachine::IsActive() const { return mActive; }

unsigned int RemoteBandMachine::GetMachineID() const {
    MILO_ASSERT(mActive, 299);
    return mID;
}