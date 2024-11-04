#pragma once
#include "beatmatch/TrackType.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "synth/FxSend.h"

class GuitarFx : public Hmx::Object {
public:
    GuitarFx(TrackType);
    virtual ~GuitarFx();
    virtual DataNode Handle(DataArray*, bool);

    void Load();
    void PostLoad();
    void Poll(int, bool, bool, float, float, float, bool, bool);
    FxSend* GetFxSend();

    DataNode OnMidiParser(DataArray*);

    int unk1c;
    bool unk20;
    bool unk21;
    TrackType mTrackType; // 0x24
    int unk28;
    DataArray* mFxCfg; // 0x2c
    ObjDirPtr<ObjectDir> mFxDir; // 0x30
    float unk3c;
    float unk40;
    float unk44;
    int unk48;
    int unk4c;
    int unk50;
    bool unk54;
    float unk58;
};