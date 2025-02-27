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
    virtual DataNode Handle(DataArray *, bool);

    void Load();
    void PostLoad();
    void Poll(int, bool, bool, float, float, float, bool, bool);
    FxSend *GetFxSend();

    DataNode OnMidiParser(DataArray *);

    int mLastSetting; // 0x1c
    bool mLastGains; // 0x20
    bool mLastReverb; // 0x21
    TrackType mTrackType; // 0x24
    int mFramesWhammyIdle; // 0x28
    DataArray *mFxCfg; // 0x2c
    ObjDirPtr<ObjectDir> mFxDir; // 0x30
    float unk3c;
    float mFbNote; // 0x40
    float mFbEnd; // 0x44
    int unk48;
    int unk4c;
    int unk50;
    bool mLastWhammying; // 0x54
    float mLastWhammyPos; // 0x58
};