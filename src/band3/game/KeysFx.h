#pragma once
#include "beatmatch/TrackType.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "synth/FxSend.h"

class KeysFx : public Hmx::Object {
public:
    KeysFx(TrackType);
    virtual ~KeysFx();
    virtual DataNode Handle(DataArray *, bool);

    void Load();
    void PostLoad();
    void Poll(bool, bool, float, float, float);
    FxSend *GetFxSend();

    TrackType mTrackType; // 0x1c
    int unk20; // 0x20
    ObjDirPtr<ObjectDir> mFxDir; // 0x24
    bool unk30; // 0x30
    bool unk31; // 0x31
    float unk34; // 0x34
};