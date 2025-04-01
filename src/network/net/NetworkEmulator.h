#pragma once
#include "Plugins/EmulationDevice.h"
#include "obj/Object.h"

class NetworkEmulator : public Hmx::Object {
public:
    NetworkEmulator();
    virtual ~NetworkEmulator() {}
    virtual DataNode Handle(DataArray *, bool);

    void Enable();
    void Disable();
    void SetBandwidth(int, int);
    void SetJitter(int, int);
    void SetLatency(int, int);
    void SetPacketDropProbability(int, int);

    Quazal::EmulationDevice *mInDevice; // 0x1c
    Quazal::EmulationDevice *mOutDevice; // 0x20
    int mInBandwidth; // 0x24
    int mOutBandwidth; // 0x28
    int mInJitter; // 0x2c
    int mOutJitter; // 0x30
    int mInLatency; // 0x34
    int mOutLatency; // 0x38
    int mInDropProb; // 0x3c
    int mOutDropProb; // 0x40
    int mEnabled; // 0x44
};