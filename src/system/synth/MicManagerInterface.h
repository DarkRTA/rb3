#pragma once

class MicClientID {
public:
    MicClientID() : unk0(-1), mPlayerID(-1) {}
    MicClientID(int i, int j) : unk0(i), mPlayerID(j) {}
    MicClientID(const MicClientID &id) : unk0(id.unk0), mPlayerID(id.mPlayerID) {}

    MicClientID &operator=(const MicClientID &id) {
        if (this != &id) {
            unk0 = id.unk0;
            mPlayerID = id.mPlayerID;
        }
        return *this;
    }
    int unk0; // mic id
    int mPlayerID; // 0x4
};

class MicManagerInterface {
public:
    MicManagerInterface() {}
    virtual ~MicManagerInterface() {}
    virtual void HandleMicsChanged() = 0;
    virtual void SetPlayback(bool) = 0;
    virtual float GetEnergyForMic(const MicClientID &) = 0;
};