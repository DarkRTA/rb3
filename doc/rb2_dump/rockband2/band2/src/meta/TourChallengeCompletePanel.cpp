/*
    Compile unit: C:\rockband2\band2\src\meta\TourChallengeCompletePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801BE7A0 -> 0x801C0504
*/
class DataArray * types; // size: 0x4, address: 0x80A4D8C0
class Symbol botb_pref_award_multiple_singular; // size: 0x4, address: 0x80A4D8C8
class Symbol botb_pref_award_multiple; // size: 0x4, address: 0x80A4D8D0
class Symbol botb_perf_award_single; // size: 0x4, address: 0x80A4D8D8
class Symbol botb_perf_award_none; // size: 0x4, address: 0x80A4D8E0
class Symbol botb_perf_award_top; // size: 0x4, address: 0x80A4D8E8
class Symbol botb_perf_award_suck_score; // size: 0x4, address: 0x80A4D8F0
class Symbol botb_perf_award_suck_streak; // size: 0x4, address: 0x80A4D8F8
class Symbol botb_perf_award_suck_mult; // size: 0x4, address: 0x80A4D900
class Symbol botb_perf_default; // size: 0x4, address: 0x80A4D908
class Symbol botb_rank_no_friends; // size: 0x4, address: 0x80A4D910
class Symbol botb_rank_vs_friend; // size: 0x4, address: 0x80A4D918
class Symbol botb_rank_overall_score; // size: 0x4, address: 0x80A4D920
class Symbol botb_rank_overall_streak; // size: 0x4, address: 0x80A4D928
class Symbol botb_rank_overall_mult; // size: 0x4, address: 0x80A4D930
class Symbol botb_rank_top100_score; // size: 0x4, address: 0x80A4D938
class Symbol botb_rank_top100_streak; // size: 0x4, address: 0x80A4D940
class Symbol botb_rank_top100_mult; // size: 0x4, address: 0x80A4D948
class Symbol botb_rank_champ; // size: 0x4, address: 0x80A4D950
class Symbol botb_rank_failed; // size: 0x4, address: 0x80A4D958
class Symbol botb_rank_default; // size: 0x4, address: 0x80A4D960
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class BandLabel * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Sequence * mPtr; // offset 0x8, size 0x4
};
enum EventMomentState {
    kMomentNone = 0,
    kMomentSuccess = 1,
    kMomentFail = 2,
};
struct Item {
    // total size: 0xC0
    class ObjPtr mAnim; // offset 0x0, size 0xC
    class ObjPtr mIconLabel; // offset 0xC, size 0xC
    class String mIconLabelStr; // offset 0x18, size 0xC
    class ObjPtr mTextLabel; // offset 0x24, size 0xC
    class String mTextLabelStr; // offset 0x30, size 0xC
    int mTextLabelStart; // offset 0x3C, size 0x4
    int mTextLabelEnd; // offset 0x40, size 0x4
    class ObjPtr mSfx; // offset 0x44, size 0xC
    unsigned char mActive; // offset 0x50, size 0x1
    class ObjPtr mMomentSuccessGrp; // offset 0x54, size 0xC
    class ObjPtr mMomentFailGrp; // offset 0x60, size 0xC
    class Symbol mMomentName; // offset 0x6C, size 0x4
    class ObjPtr mMomentSuccessLabel; // offset 0x70, size 0xC
    class ObjPtr mMomentFailLabel; // offset 0x7C, size 0xC
    class String mMomentStr; // offset 0x88, size 0xC
    int mMomentEnd; // offset 0x94, size 0x4
    class ObjPtr mMomentSfx; // offset 0x98, size 0xC
    enum EventMomentState mMomentState; // offset 0xA4, size 0x4
    float mStartTime; // offset 0xA8, size 0x4
    float mAnimEndTime; // offset 0xAC, size 0x4
    float mCountEndTime; // offset 0xB0, size 0x4
    float mMomentEndTime; // offset 0xB4, size 0x4
    float mMomentCountEndTime; // offset 0xB8, size 0x4
    unsigned char mNeedCount; // offset 0xBC, size 0x1
    unsigned char mNeedMomentCount; // offset 0xBD, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class BandList : public UIList {
    // total size: 0x2B0
    float mDelayFrac; // offset 0x25C, size 0x4
    float mEnterTime; // offset 0x260, size 0x4
    float mExitTime; // offset 0x264, size 0x4
    float mElementTime; // offset 0x268, size 0x4
    class vector mAnimating; // offset 0x26C, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class BandList * mPtr; // offset 0x8, size 0x4
};
class EventCompleteDir : public PanelDir {
    // total size: 0x2C0
    class ObjList mItems; // offset 0x24C, size 0xC
    unsigned char mEnabled; // offset 0x258, size 0x1
    float mInitialDelay; // offset 0x25C, size 0x4
    float mAnimTime; // offset 0x260, size 0x4
    float mCountTime; // offset 0x264, size 0x4
    float mMomentTime; // offset 0x268, size 0x4
    class ObjPtr mChallengeList; // offset 0x26C, size 0xC
    unsigned char mNeedListAnim; // offset 0x278, size 0x1
    unsigned char mNeedListScroll; // offset 0x279, size 0x1
};
// Range: 0x801BE7A0 -> 0x801BE9F4
void TourChallengeCompletePanel::Enter(class TourChallengeCompletePanel * const this /* r29 */) {
    // Local variables
    class Timer t; // r1+0x8
    class EventCompleteDir * dir; // r30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
}

// Range: 0x801BE9F4 -> 0x801BEA04
void TourChallengeCompletePanel::Exit() {}

// Range: 0x801BEA04 -> 0x801BEA1C
unsigned char TourChallengeCompletePanel::IsLoaded() {}

// Range: 0x801BEA1C -> 0x801BF04C
void TourChallengeCompletePanel::UpdateBasics() {
    // Local variables
    class EventCompleteDir * dir; // r31
    class TourBand * b; // r30
    class TourEvent * e; // r26
    enum WinMetric m; // r25

    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Tour * TheTour;
}

static class Symbol botb_rank_award; // size: 0x4, address: 0x80A4D968
static class Symbol botb_unranked; // size: 0x4, address: 0x80A4D970
class BotbCompRank {
    // total size: 0x110
    char mType; // offset 0x0, size 0x1
    int mNum1; // offset 0x4, size 0x4
    int mNum2; // offset 0x8, size 0x4
    int mFriend; // offset 0xC, size 0x4
    char mText[255]; // offset 0x10, size 0xFF
};
class BotbCompPerf {
    // total size: 0x110
    char mType; // offset 0x0, size 0x1
    int mNum1; // offset 0x4, size 0x4
    int mNum2; // offset 0x8, size 0x4
    int mFriend; // offset 0xC, size 0x4
    char mText[255]; // offset 0x10, size 0xFF
};
// Range: 0x801BF04C -> 0x801BFE58
void TourChallengeCompletePanel::UnpackResponse(class TourChallengeCompletePanel * const this /* r27 */) {
    // Local variables
    class EventCompleteDir * dir; // r28
    class TourBand * b; // r0
    class TourEvent * e; // r0
    enum WinMetric m; // r0
    class BotbCompRank rank; // r1+0x1A0
    class BotbCompPerf perf; // r1+0x90
    class vector users; // r1+0x84
    class BandUser * * u; // r26
    class Profile * profile; // r28
    class String cookies; // r1+0x78

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Symbol botb_perf_default;
    // -> class Symbol botb_perf_award_suck_mult;
    // -> class Symbol botb_perf_award_suck_streak;
    // -> class Symbol botb_perf_award_suck_score;
    // -> class Symbol botb_perf_award_top;
    // -> class Symbol botb_perf_award_none;
    // -> class Symbol botb_perf_award_single;
    // -> class Symbol botb_pref_award_multiple;
    // -> class Symbol botb_pref_award_multiple_singular;
    // -> static class Symbol botb_unranked;
    // -> static class Symbol botb_rank_award;
    // -> class Debug TheDebug;
    // -> class Symbol botb_rank_default;
    // -> class Symbol botb_rank_failed;
    // -> class Symbol botb_rank_champ;
    // -> class Symbol botb_rank_top100_mult;
    // -> class Symbol botb_rank_top100_streak;
    // -> class Symbol botb_rank_top100_score;
    // -> class Symbol botb_rank_overall_mult;
    // -> class Symbol botb_rank_overall_streak;
    // -> class Symbol botb_rank_overall_score;
    // -> class Symbol botb_rank_vs_friend;
    // -> class Symbol botb_rank_no_friends;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Tour * TheTour;
}

static class Symbol botb_net_results_failed; // size: 0x4, address: 0x80A4D978
// Range: 0x801BFE58 -> 0x801BFFE0
void TourChallengeCompletePanel::StartFailed(class TourChallengeCompletePanel * const this /* r31 */) {
    // Local variables
    class EventCompleteDir * dir; // r30
    class TourBand * b; // r0
    class vector users; // r1+0xC
    int n; // r29
    class Profile * pProfile; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol botb_net_results_failed;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Tour * TheTour;
}

// Range: 0x801BFFE0 -> 0x801C0064
class DataNode TourChallengeCompletePanel::OnMsg(class TourChallengeCompletePanel * const this /* r30 */) {}

// Range: 0x801C0064 -> 0x801C0094
void TourChallengeCompletePanel::SetSubmittedData() {}

// Range: 0x801C0094 -> 0x801C0504
class DataNode TourChallengeCompletePanel::Handle(class TourChallengeCompletePanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__24RockCentralOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__26TourChallengeCompletePanel; // size: 0xAC, address: 0x808A17E8

