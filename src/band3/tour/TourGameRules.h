#pragma once
#include "types.h"
#include "obj/Data.h"
#include <vector>

enum TourGameType {
};

class TourGameRules {
public:
    TourGameRules();
    virtual ~TourGameRules();
    virtual void Init(const DataArray *);

    TourGameType mGameType;
    TourGameType GetGameType() const;
    std::vector<float> m_vTargets;
    int GetNumTargets() const;
    float GetTarget(int) const;
    DataArray *mChallengeData;
    const DataArray *GetChallengeSpecificData() const;
};
