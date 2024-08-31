#ifndef METABAND_PERFORMANCEDATA_H
#define METABAND_PERFORMANCEDATA_H

#include "system/obj/Object.h"
#include "system/meta/FixedSizeSaveable.h"
#include "band3/game/Defines.h"
#include "band3/game/Stats.h"

class PerformanceData : public Hmx::Object, public FixedSizeSaveable {
    PerformanceData();
    virtual ~PerformanceData();
    void Initialize(const Stats&, int, ScoreType, Difficulty, Symbol, int, int, bool);
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void SaveSize(int);
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    void Prune(Stats&);
    void InitializeStatsVectors();
    DataNode Handle(DataArray*, bool);
};

#endif // METABAND_PERFORMANCEDATA_H