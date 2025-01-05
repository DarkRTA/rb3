#include "synth/MicClientMapper.h"
#include "os/Debug.h"
#include "synth/Synth.h"

MicClientMapper::MicClientMapper() : mMicManager(0), mNumPlayers(2) {
    for(int i = 0; i < 4; i++){
        // push back MicMappingData
    }
    for(int i = 0; i < mNumPlayers; i++){
        PlayerMappingData data;
        data.mMicID = -1;
        data.unk4 = -1;
        mPlayers.push_back(data);
    }
}

MicClientMapper::~MicClientMapper(){

}

void MicClientMapper::SetMicManager(MicManagerInterface* micInt){
    mMicManager = micInt;
    HandleMicsChanged();
}

void MicClientMapper::HandleMicsChanged(){
    RefreshMics();
    if(mMicManager) mMicManager->HandleMicsChanged();
}

int MicClientMapper::GetMicIDForClientID(const MicClientID& clientID) const {
    if(clientID.mPlayerID == -1){
        for(std::vector<MicMappingData>::const_iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
            if(it->unk0 == clientID.unk0) return it->mMicID;
        }
        return -1;
    }
    else return GetMicIDForPlayerID(clientID.mPlayerID);
}

int MicClientMapper::GetPlayerIDForMicID(int micID) const {
    int idx = 0;
    for(std::vector<PlayerMappingData>::const_iterator it = mPlayers.begin(); it != mPlayers.end(); ++it, ++idx){
        if(it->mMicID == micID) return idx;
    }
    return -1;
}

int MicClientMapper::GetMicIDForPlayerID(int playerID) const {
    if(playerID >= mNumPlayers) return -1;
    else return mPlayers[playerID].mMicID;
}

bool MicClientMapper::HasMicID(int micID) const {
    for(std::vector<MicMappingData>::const_iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->mMicID == micID) return true;
    }
    return false;
}

void MicClientMapper::GetAllConnectedMics(std::vector<int>& mics) const {
    for(std::vector<MicMappingData>::const_iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->mMicID != -1){
            mics.push_back(it->mMicID);
        }
    }
}

void MicClientMapper::SetNumberOfPlayers(int i_iCount){
    if(i_iCount != mNumPlayers){
        MILO_ASSERT(( 0) <= ( i_iCount) && ( i_iCount) < ( kNumberOfMicClients), 0xB7);
        mNumPlayers = i_iCount;
        mPlayers.clear();
        for(int i = 0; i < mNumPlayers; i++){
            PlayerMappingData data;
            data.mMicID = -1;
            data.unk4 = -1;
            mPlayers.push_back(data);
        }
        UnlockAllMicIDs();
        RefreshPlayerMapping();
    }
}

void MicClientMapper::LockMicID(int micID){
    for(std::vector<MicMappingData>::iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->mMicID == micID){
            if(it->bLocked){
                MILO_WARN("MicClientMapper::UnlockMicID - Trying to lock an already locked mic!");
            }
            it->bLocked = true;
        }
    }
}

void MicClientMapper::UnlockMicID(int micID){
    for(std::vector<MicMappingData>::iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->mMicID == micID){
            if(!it->bLocked){
                MILO_WARN("MicClientMapper::UnlockMicID - Trying to unlock an already unlocked mic!");
            }
            it->bLocked = false;
        }
    }
}

void MicClientMapper::UnlockAllMicIDs(){
    for(std::vector<MicMappingData>::iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        it->bLocked = false;
    }
}

bool MicClientMapper::IsMicIDLocked(int micID) const {
    for(std::vector<MicMappingData>::const_iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->mMicID == micID){
            return it->bLocked;
        }
    }
    return false;
}

bool MicClientMapper::GetFirstUnlockedMicID(int& micID) const {
    for(std::vector<MicMappingData>::const_iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->mMicID != -1 && !it->bLocked){
            micID = it->mMicID;
            return true;
        }
    }
    return false;
}

void MicClientMapper::RefreshMics(){
    for(std::vector<MicMappingData>::iterator it = mMappingData.begin(); it != mMappingData.end(); ++it){
        if(it->unk0 != -1 && it->mMicID != -1 && !TheSynth->IsMicConnected(it->mMicID)){
            TheSynth->ReleaseMic(it->mMicID);
            int playerID = GetPlayerIDForMicID(it->mMicID);
            if(playerID != -1){
                mPlayers[playerID].mMicID = -1;
            }
            it->mMicID = -1;
            it->bLocked = false;
        }
    }
    for(std::vector<MicMappingData>::iterator iter = mMappingData.begin(); iter != mMappingData.end(); ++iter){
        if(iter->unk0 != -1 && iter->mMicID == -1){
            iter->mMicID = TheSynth->GetNextAvailableMicID();
            MILO_ASSERT(iter->bLocked == false, 0x186);
            if(iter->mMicID != -1){
                TheSynth->CaptureMic(iter->mMicID);
            }
        }
    }
    RefreshPlayerMapping();
}

void MicClientMapper::RefreshPlayerMapping(){
    
}