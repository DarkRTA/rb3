#ifndef TOUR_TOURGAMERULES_H
#define TOUR_TOURGAMERULES_H

#include "obj/Data.h"
#include <vector>

enum TourGameType {

};

class TourGameRules {
public:
    TourGameRules();
    virtual ~TourGameRules();
    virtual void Init(const DataArray*);

    TourGameType mGameType; TourGameType GetGameType() const;
    std::vector<int> mTargets; short GetNumTargets() const; int GetTarget(int) const;
    DataArray* mChallengeData; const DataArray* GetChallengeSpecificData() const;
};

#endif // TOUR_TOURGAMERULES_H
