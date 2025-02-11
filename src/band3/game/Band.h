#pragma once
#include "game/CommonPhraseCapturer.h"
#include "game/Performer.h"
#include "game/Player.h"
#include "obj/Object.h"

class BandPerformer;
class BandUser;
class BeatMaster;

class Band : public Hmx::Object {
public:
    Band(bool, int, BandUser *, BeatMaster *);
    virtual ~Band();
    virtual DataNode Handle(DataArray *, bool);

    int EnergyMultiplier() const;
    int EnergyCrowdBoost() const;
    void ForceStars(int);
    void UpdateBonusLevel(float);
    int DeployBandEnergy(BandUser *);
    int GetMultiplier(bool, int &, int &, int &) const;
    Performer *MainPerformer() const;
    Performer *GetBand() const;
    Player *AddPlayer(BeatMaster *, BandUser *);

    BandPerformer *mBandPerformer; // 0x1c
    std::vector<int> unk20;
    std::vector<int> unk28;
    float unk30;
    int unk34;
    float unk38;
    int unk3c;
    bool unk40;
    int unk44;
    int unk48;
    int unk4c;
    int unk50;
    float unk54;
    float unk58;
    bool unk5c;
    int unk60;
    int unk64;
    std::vector<int> unk68;
    std::vector<int> unk70;
    CommonPhraseCapturer *mCommonPhraseCapturer; // 0x78
};