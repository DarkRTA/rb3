#pragma once
#include "synth/MicManagerInterface.h"
#include <vector>

#define kNumberOfMicClients 4

class MicClientMapper {
public:
    class MicMappingData {
    public:
        int unk0;
        int unk4;
        int mMicID; // 0x8
        bool bLocked; // 0xc
    };

    class PlayerMappingData {
    public:
        int mMicID; // mic ID
        int unk4;
    };

    MicClientMapper();
    ~MicClientMapper();
    void SetMicManager(MicManagerInterface*);
    void HandleMicsChanged();
    void RefreshMics();
    int GetMicIDForClientID(const MicClientID&) const;
    int GetMicIDForPlayerID(int) const;
    int GetPlayerIDForMicID(int) const;
    bool HasMicID(int) const;
    void GetAllConnectedMics(std::vector<int>&) const;
    void SetNumberOfPlayers(int);
    void UnlockAllMicIDs();
    void RefreshPlayerMapping();
    void LockMicID(int);
    void UnlockMicID(int);
    bool IsMicIDLocked(int) const;
    bool GetFirstUnlockedMicID(int&) const;

    MicManagerInterface* mMicManager; // 0x0
    std::vector<MicMappingData> mMappingData; // 0x4
    std::vector<PlayerMappingData> mPlayers; // 0xc
    int mNumPlayers; // 0x14
};