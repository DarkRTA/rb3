#pragma once
#include "beatmatch/TrackType.h"
#include "game/Player.h"
#include "obj/Data.h"
#include <map>

class TrackerMultiplierMap {
public:
    class MultiplierEntry {
    public:
        float unk0;
        int unk4;
    };

    TrackerMultiplierMap();
    ~TrackerMultiplierMap();

    void InitFromDataArray(const DataArray*);
    float GetMultiplier(float) const;
    int GetMultiplierIndex(float) const;
    const MultiplierEntry& FindEntry(float) const;
    float GetPercentOfMaxMultiplier(float) const;

    float unk0; // 0x0
    std::map<float, MultiplierEntry> unk4; // 0x4
};

class TrackerSource;

class TrackerSectionManager {
public:
    class Section {
    public:
        int unk0;
        int unk4;
        int unk8;
    };

    TrackerSectionManager();
    ~TrackerSectionManager();
    int TickAfterSection(int, int) const;
    int GetSectionEndTick(int) const;
    void GetGemStatsInRange(const Player*, int, int, int&, int&) const;
    int FindSectionContainingTick(int) const;
    int CountGemsInSection(const Player*, int) const;
    int CountNonEmptySections(const TrackerSource*, bool) const;
    int GetSectionCount() const;
    void Init();

    std::vector<Section> unk0; // 0x0
};

class TrackerUtils {
public:

    static int CountGemsInSong(int, TrackType);
    static float GetNextNoteMs(int, TrackType, float);
    static int CountVocalPhrasesInSong(int);
};