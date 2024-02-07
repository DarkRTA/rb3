/*
    Compile unit: C:\rockband2\band2\src\meta\ContextChecker.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800E1048 -> 0x800E1DC0
*/
static int gContextWeight; // size: 0x4, address: 0x80A465A0
// Range: 0x800E1048 -> 0x800E10BC
static unsigned char CheckContextAnd(const class DataArray * arr /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800E10BC -> 0x800E1130
static unsigned char CheckContextOr(const class DataArray * arr /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800E1130 -> 0x800E11B0
static unsigned char CheckContextNot(const class DataArray * arr /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E11B0 -> 0x800E1258
static unsigned char CheckContextModeProperty(const class DataArray * arr /* r31 */) {
    // References
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E1258 -> 0x800E12EC
static unsigned char CheckContextDiff(const class DataArray * arr /* r29 */) {
    // Local variables
    int diff; // r0
    int i; // r30

    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x800E12EC -> 0x800E1370
static unsigned char CheckContextInstrument(const class DataArray * arr /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x800E1370 -> 0x800E140C
static unsigned char CheckContextSong(const class DataArray * arr /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x800E140C -> 0x800E14B8
static unsigned char CheckContextArtist(const class DataArray * arr /* r29 */) {
    // Local variables
    const char * artist; // r31
    int i; // r30

    // References
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x800E14B8 -> 0x800E156C
static unsigned char CheckContextCity(const class DataArray * arr /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Tour * TheTour;
}

// Range: 0x800E156C -> 0x800E15FC
static unsigned char CheckContextVenue(const class DataArray * arr /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class GameConfig * TheGameConfig;
}

class TourWorldEvent : public TourEvent {
    // total size: 0xC0
protected:
    class Symbol mTown; // offset 0x90, size 0x4
    class Symbol mVenue; // offset 0x94, size 0x4
    unsigned char mDisplaySong; // offset 0x98, size 0x1
    int mTownFameRequired; // offset 0x9C, size 0x4
    int mWorldFameRequired; // offset 0xA0, size 0x4
    int mBuzzRequired; // offset 0xA4, size 0x4
    class Symbol mItemRequired; // offset 0xA8, size 0x4
    class Symbol mAwardItem; // offset 0xAC, size 0x4
    class Symbol mWarningScreen; // offset 0xB0, size 0x4
    class Symbol mVenueVariant; // offset 0xB4, size 0x4
    class Symbol mBuzzVenue; // offset 0xB8, size 0x4
    unsigned char mAllowMoments; // offset 0xBC, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class vector * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class vector * _M_start; // offset 0x0, size 0x4
    class vector * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourTier {
    // total size: 0x10
public:
    class Symbol mName; // offset 0x0, size 0x4
    class vector mVenueTiers; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourTier * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourTier * * _M_start; // offset 0x0, size 0x4
    class TourTier * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourVenue {
    // total size: 0x14
public:
    class Symbol mName; // offset 0x0, size 0x4
    class Symbol mVariant; // offset 0x4, size 0x4
    class vector mEvents; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourVenue * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourVenue * * _M_start; // offset 0x0, size 0x4
    class TourVenue * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct TownUnlock {
    // total size: 0x8
    class Symbol mMaleTorso; // offset 0x0, size 0x4
    class Symbol mFemaleTorso; // offset 0x4, size 0x4
};
class TourTown {
    // total size: 0x28
public:
    class Symbol mName; // offset 0x0, size 0x4
    int mOrder; // offset 0x4, size 0x4
    class Symbol mContinent; // offset 0x8, size 0x4
    class vector mVenues; // offset 0xC, size 0xC
    struct TownUnlock mPlayedUnlock; // offset 0x18, size 0x8
    struct TownUnlock mCompletedUnlock; // offset 0x20, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourTown * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourTown * * _M_start; // offset 0x0, size 0x4
    class TourTown * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourStaff : public Object {
    // total size: 0x58
    class Symbol mStaffName; // offset 0x28, size 0x4
    int mStarsRequired; // offset 0x2C, size 0x4
    int mBuzzRequired; // offset 0x30, size 0x4
    class Symbol mItemRequired; // offset 0x34, size 0x4
    class DataArray * mBuzzModifier; // offset 0x38, size 0x4
    float mBuzzLostModifier; // offset 0x3C, size 0x4
    class DataArray * mMoneyPerStarModifier; // offset 0x40, size 0x4
    float mBuzzRequiredModifier; // offset 0x44, size 0x4
    class list mBuzzRequiredTowns; // offset 0x48, size 0x8
    int mMinMomentFreq; // offset 0x50, size 0x4
    int mMaxMomentFreq; // offset 0x54, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourStaff * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourStaff * * _M_start; // offset 0x0, size 0x4
    class TourStaff * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourMoment : public Object {
    // total size: 0x5C
    class Symbol mMomentName; // offset 0x28, size 0x4
    class DataArray * mCfg; // offset 0x2C, size 0x4
    int mMinVehicle; // offset 0x30, size 0x4
    int mMaxVehicle; // offset 0x34, size 0x4
    class String mLoadingScreen; // offset 0x38, size 0xC
    unsigned char mDisableStaff; // offset 0x44, size 0x1
    unsigned char mDisableOverdrive; // offset 0x45, size 0x1
    class EventSong * mAdditionalSong; // offset 0x48, size 0x4
    class EventSong * mReplaceSong; // offset 0x4C, size 0x4
    class TourWorldEvent * mOpportunity; // offset 0x50, size 0x4
    int mStarsRequired; // offset 0x54, size 0x4
    int mBuzzRequired; // offset 0x58, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourMoment * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourMoment * * _M_start; // offset 0x0, size 0x4
    class TourMoment * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct VehicleTown {
    // total size: 0xC
    int mVehicleLevel; // offset 0x0, size 0x4
    const class TourTown * mTown; // offset 0x4, size 0x4
    const class TourTier * mTier; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct VehicleTown * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct VehicleTown * _M_start; // offset 0x0, size 0x4
    struct VehicleTown * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct MappedTowns {
    // total size: 0x10
    class Symbol mHometown; // offset 0x0, size 0x4
    class vector mTowns; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct MappedTowns * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct MappedTowns * _M_start; // offset 0x0, size 0x4
    struct MappedTowns * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourWorld {
    // total size: 0x4C
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class vector mTiers; // offset 0x4, size 0xC
    class vector mTowns; // offset 0x10, size 0xC
    class vector mStaff; // offset 0x1C, size 0xC
    class vector mMoments; // offset 0x28, size 0xC
    class vector mDisabledBattles; // offset 0x34, size 0xC
    class vector mTownsByHometown; // offset 0x40, size 0xC
};
// Range: 0x800E15FC -> 0x800E16A4
static unsigned char CheckContextUnlocked(const class DataArray * arr /* r29 */) {
    // Local variables
    class TourBand * band; // r31
    int i; // r30

    // References
    // -> class Tour * TheTour;
}

static class Symbol sym_and; // size: 0x4, address: 0x80A4ADC4
static class Symbol sym_or; // size: 0x4, address: 0x80A4ADCC
static class Symbol sym_not; // size: 0x4, address: 0x80A4ADD4
static class Symbol mode_property; // size: 0x4, address: 0x80A4ADDC
static class Symbol diff; // size: 0x4, address: 0x80A4ADE4
static class Symbol instrument; // size: 0x4, address: 0x80A4ADEC
static class Symbol song; // size: 0x4, address: 0x80A4ADF4
static class Symbol artist; // size: 0x4, address: 0x80A4ADFC
static class Symbol city; // size: 0x4, address: 0x80A4AE04
static class Symbol venue; // size: 0x4, address: 0x80A4AE0C
static class Symbol unlocked; // size: 0x4, address: 0x80A4AE14
static class Symbol weight; // size: 0x4, address: 0x80A4AE1C
// Range: 0x800E16A4 -> 0x800E19D0
static unsigned char InternalCheckContext(const class DataArray * arr /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gContextWeight;
    // -> static class Symbol weight;
    // -> static class Symbol unlocked;
    // -> static class Symbol venue;
    // -> static class Symbol city;
    // -> static class Symbol artist;
    // -> static class Symbol song;
    // -> static class Symbol instrument;
    // -> static class Symbol diff;
    // -> static class Symbol mode_property;
    // -> static class Symbol sym_not;
    // -> static class Symbol sym_or;
    // -> static class Symbol sym_and;
}

static class Rand gContextRand; // size: 0x410, address: 0x809786C8
// Range: 0x800E19D0 -> 0x800E1A0C
int CheckContext() {
    // References
    // -> static int gContextWeight;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800E1A0C -> 0x800E1C80
class Symbol RandomContextSensitiveItem(const class DataArray * arr /* r28 */) {
    // Local variables
    class vector tips; // r1+0x58
    int total_weight; // r30
    int i; // r29
    int weight; // r0
    int val; // r0
    int i; // r5

    // References
    // -> class Debug TheDebug;
    // -> static class Rand gContextRand;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct WeightedTip {
    // total size: 0x8
    int mWeightAccum; // offset 0x0, size 0x4
    class Symbol mTip; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct WeightedTip * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct WeightedTip * _M_start; // offset 0x0, size 0x4
    struct WeightedTip * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x800E1C80 -> 0x800E1CDC
class DataNode OnRandomContext(class DataArray * args /* r31 */) {}

// Range: 0x800E1CDC -> 0x800E1CEC
void SeedRandomContext() {
    // References
    // -> static class Rand gContextRand;
}

// Range: 0x800E1CEC -> 0x800E1D48
class DataNode OnSeedRandomContext(class DataArray * args /* r31 */) {}

// Range: 0x800E1D48 -> 0x800E1DB0
void ContextCheckerInit() {
    // References
    // -> static class Rand gContextRand;
}

struct {
    // total size: 0x8
} __RTTI__P11WeightedTip; // size: 0x8, address: 0x80884940
// Range: 0x800E1DB0 -> 0x800E1DC0
static void __sinit_\ContextChecker_cpp() {
    // References
    // -> static class Rand gContextRand;
}


