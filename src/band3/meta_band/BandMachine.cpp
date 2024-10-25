#include "meta_band/BandMachine.h"
#include "game/NetGameMsgs.h"
#include "obj/ObjMacros.h"
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
        bs << mSongs.size();
        for(std::set<int>::const_iterator it = mSongs.begin(); it != mSongs.end(); ++it){
            bs << *it;
        }
    }
    if(mask & 8){
        bs << mSongsWithProStrings.size();
        for(std::set<int>::const_iterator it = mSongsWithProStrings.begin(); it != mSongsWithProStrings.end(); ++it){
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
        mSongs.clear();
        for(int i = 0; i < size; i++){
            int key;
            bs >> key;
            mSongs.insert(key);
        }
    }
    if(mask & 8){
        int size;
        bs >> size;
        mSongsWithProStrings.clear();
        for(int i = 0; i < size; i++){
            int key;
            bs >> key;
            mSongsWithProStrings.insert(key);
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
    return mSongs.find(i) != mSongs.end();
}

bool BandMachine::HasProGuitarOrBass(int i) const {
    return mSongsWithProStrings.find(i) != mSongsWithProStrings.end();
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