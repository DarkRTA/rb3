#ifndef UTL_MULTITEMPOTEMPOMAP_H
#define UTL_MULTITEMPOTEMPOMAP_H
#include "utl/Str.h"
#include "utl/TempoMap.h"

class MultiTempoTempoMap : public TempoMap {
public:
    MultiTempoTempoMap();
    virtual ~MultiTempoTempoMap(); // fn_80358FA8
    virtual double TickToTime(float) const; // fn_803583A8
    virtual double TimeToTick(float) const; // fn_80358528
    virtual float GetTempo(int) const; // fn_8035825C
    virtual int GetTempoUSecs(int i); // fn_803582F8
    virtual double GetTempoBPM(int) const; // fn_80358370
    virtual int GetNumTempoChangePoints() const; // fn_80358AB4
    virtual int GetTempoChangePoint(int) const; // fn_80358ABC
    virtual void V_Unk9(); // fn_80358B08
    virtual void V_Unk10(); // fn_80358864
    virtual void V_Unk11(int, int); // fn_80358880
    virtual int V_Unk12(int, int *); // fn_80358914
    virtual int V_Unk13(int, int *); // fn_803589B8
    virtual void V_Unk14(); // fn_803589E8

    // symbols from RB2:
    // AddTempoInfoPoint__18MultiTempoTempoMapFii
    // PointForTick__18MultiTempoTempoMapCFf
    // PointForTime__18MultiTempoTempoMapCFf
    // WipeTempoInfoPoints__18MultiTempoTempoMapFi
    // Finalize__18MultiTempoTempoMapFv
    // CompareTick__18MultiTempoTempoMapFfRCQ218MultiTempoTempoMap14TempoInfoPoint
    // CompareTime__18MultiTempoTempoMapFfRCQ218MultiTempoTempoMap14TempoInfoPoint

    int *unk4; // some unknown class/pointer to some unknown class
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
};

#endif
