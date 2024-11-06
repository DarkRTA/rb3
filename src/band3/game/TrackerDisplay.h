#pragma once
#include "obj/Data.h"
#include "obj/Msg.h"

enum TrackerChallengeType {

};

class TrackerDisplay {
public:
    TrackerDisplay();
    virtual ~TrackerDisplay();
    virtual void Show() const;
    virtual void Hide() const;
    virtual void SendMsg(const Message&) const = 0;

    void Initialize(Symbol);
    void SetChallengeType(TrackerChallengeType) const;
    void SetIntegerProgress(int) const;
    void SetPercentageProgress(float) const;
    void SetTimeProgress(float) const;
    void HandleIncrement();
    void ShowTarget(DataArrayPtr&) const;
    void HandleTargetPass(int, DataArrayPtr&) const;
    void LastTargetPass() const;

    static void MsToMinutesSeconds(float, int&, int&);
    static DataArrayPtr MakeIntegerTargetDescription(int);
    static DataArrayPtr MakePercentTargetDescription(float);
    static DataArrayPtr MakeTimeTargetDescription(float);
};