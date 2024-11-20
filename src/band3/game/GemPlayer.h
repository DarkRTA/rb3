#pragma once
#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/BeatMatcher.h"
#include "game/Player.h"
#include "obj/ObjMacros.h"

class BandPerformer;

class GemPlayer : public Player, public BeatMatchSink {
public:
    GemPlayer(BandUser*, BeatMaster*, Band*, int, BandPerformer*);
    OBJ_CLASSNAME(GemPlayer)
    OBJ_SET_TYPE(GemPlayer)
    virtual ~GemPlayer();
    virtual DataNode Handle(DataArray*, bool);

    int GetRGFret(int) const;
    int GetMaxSlots() const;
    void PrintAddHead(int,int,int,int,int);

    bool IsAutoplay() const;
    void SetAutoplay(bool);

    void SetFillLogic(FillLogic);

    void PrintMsg(const char*);

    Performer* unk_0x2cc;
    u8 pad[0x70];

    TextStream* unk_0x340;

    u8 pad2[0x30];

    BeatMatcher* mBeatMatcher; // 0x374
};