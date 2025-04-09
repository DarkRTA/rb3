#pragma once
#include <vector>

/** Info about a beat marker. */
struct BeatInfo {
    BeatInfo(int t, int l) : mTick(t), mLevel(l) {}
    /** This beat marker's tick. */
    int mTick; // 0x0
    /** This beat marker's level (up or down beat?)
     * midi note of 12 = down beat, level = 1
     * midi note of 13 = up beat, level = 0
     */
    int mLevel; // 0x4
};

/** The map of beats for the current song. */
class BeatMap {
private:
    /** The collection of beat markers. */
    std::vector<BeatInfo> mInfos; // 0x0

    float Interpolate(int tick, int idx) const {
        const BeatInfo &r30 = mInfos[idx];
        const BeatInfo &r31 = mInfos[idx + 1];

        int k1 = mInfos[idx].mTick;

        return idx
            + static_cast<float>(tick - k1) / static_cast<float>(r31.mTick - r30.mTick);
    }

    float Interpolate(float tick, int idx) const {
        const BeatInfo &r30 = mInfos[idx];
        const BeatInfo &r31 = mInfos[idx + 1];
        int k1 = mInfos[idx].mTick;
        return idx
            + static_cast<float>(tick - k1) / static_cast<float>(r31.mTick - r30.mTick);
    }

public:
    BeatMap();
    ~BeatMap() {}

    /** Attempt to add a new beat marker with the supplied tick and level.
     * @param [in] tick The tick.
     * @param [in] level The level (up or down beat).
     * @returns True, if a new beat marker was successfully added, false if not.
     */
    bool AddBeat(int tick, int level);
    float Beat(int tick) const;
    float Beat(float tick) const;
    float BeatToTick(float) const;

    /** Is the beat at the supplied index a downbeat?
     * @param [in] idx The index in mInfos to check.
     * @returns True if downbeat, false if not.
     */
    bool IsDownbeat(int idx) const;
};

extern BeatMap *TheBeatMap;
void SetTheBeatMap(BeatMap *);
void ResetTheBeatMap();
