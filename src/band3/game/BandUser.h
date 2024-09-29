#ifndef GAME_BANDUSER_H
#define GAME_BANDUSER_H

#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "os/User.h"
#include "types.h"
#include "system/bandobj/BandCharacter.h"

class BandCharDesc;

class BandUser : public virtual User {
    BandUser();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~BandUser();
    virtual bool IsNullUser();
    virtual bool IsParticipating();

public:
    bool IsFullyInGame() const;
    ControllerType GetControllerType() const;
    Difficulty GetDifficulty() const;
    Symbol GetDifficultySym() const;
    TrackType GetTrackType() const;
    Symbol GetTrackSym() const;
    BandCharacter *GetCharLocal();
    bool HasChar();

private:
    Difficulty mDifficulty; // 0x8
    u8 unk_0xC; // 0xC
    TrackType mTrackType; // 0x10
    ControllerType mControllerType; // 0x14
    u8 unk_0x18, unk_0x19; // 0x18, 0x19
    int unk_0x1C, unk_0x20; // 0x1C, 0x20
    String mOvershellFocus; // 0x24
    int mChar; // 0x30
    GameplayOptions mGameplayOptions; // 0x34
    u8 mAutoplay;
    Symbol mPreviousAward;
    float mLastHitFraction;
    void *mTrack;
    void *mPlayer;
    bool mParticipating;
    bool mIsWiiRemoteController;
    bool mJustDisconnected;
};

class LocalBandUser : public BandUser {};

class NullLocalBandUser : public LocalBandUser {
    virtual ~NullLocalBandUser();
    virtual bool IsNullUser() const;
};

#endif // GAME_BANDUSER_H
