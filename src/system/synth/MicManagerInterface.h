#pragma once

class MicClientID {
public:
    MicClientID(int i, int j) : unk0(i), mPlayerID(j) {}
    int unk0; // mic id
    int mPlayerID; // 0x4
};

class MicManagerInterface {
public:
    MicManagerInterface(){}
    virtual ~MicManagerInterface(){}
    virtual void HandleMicsChanged() = 0;
    virtual void SetPlayback(bool) = 0;
    virtual float GetEnergyForMic(const MicClientID&) = 0;
};