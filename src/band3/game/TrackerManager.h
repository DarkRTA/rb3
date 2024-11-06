#pragma once
#include "Tracker.h"
#include "TrackerDisplay.h"
#include "game/Band.h"

class TrackerSource;

class TrackerManager {
public:
    TrackerManager(Band*);
    ~TrackerManager();

    void ForceStars(int);
    void Restart();
    TrackerSource* CreateSource(TrackerDesc&) const;

    int unk0;
    float unk4;
    TrackerBandDisplay unk8;
    TrackerBroadcastDisplay unkc;
    int unk10;
    int unk14;
    Band* unk18;
    int unk1c;
    int unk20;
    int unk24;
    Symbol unk28;
    int unk2c;
    bool unk30;
    bool unk31;
    bool unk32;
    float unk34;
    std::vector<int> unk38;
    bool unk40;
    int unk44;
    bool unk48;
    bool unk49;
    float unk4c;
};