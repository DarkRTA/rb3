#pragma once

#include "game/BandUser.h"
#include "types.h"

class TrackConfig {
public:
    TrackConfig(BandUser *);
    BandUser *mUser;
    const BandUser *GetBandUser() const;
    Symbol Type() const; // 0x0
    u8 kDualPerspective; // 0x4
    int mTrackNum;
    int TrackNum() const;
    void SetTrackNum(int); // 0x8
    int mMaxSlots;
    int GetMaxSlots() const;
    void SetMaxSlots(int); // 0xC
    int mNumSlots; // 0x10
    Symbol mName; // 0x14
    bool mLefty;
    bool IsLefty() const;
    bool UseLeftyGems() const;
    void SetLefty(bool); // 0x18
    uint mCymbalLanes;
    uint GetGameCymbalLanes() const;
    void SetGameCymbalLanes(uint); // 0x1c
    bool mDisableHopos;
    bool GetDisableHopos() const;
    void SetDisableHopos(bool); // 0x20
    std::vector<int> mSlotSpacing;

    bool IsDrumTrack() const;
    bool IsKeyboardTrack() const;
    bool IsRealGuitarTrack() const;
    bool AllowsOverlappingGems() const;
    bool AllowsPartialHits() const;
    const char *GetSlotColor(int) const;
};
