#pragma once
#include "meta/FixedSizeSaveable.h"
#include <set>
class TourProgress;

class QuestJournal : public FixedSizeSaveable {
public:
    QuestJournal(TourProgress &);
    virtual ~QuestJournal();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    void CompleteQuest(Symbol);
    void HandleDataChange();
    void Clear();
    void FakeFill();

    static int SaveSize(int);

    TourProgress &m_rOwningProgress; // 0x8
    std::set<Symbol> m_setCompletedQuests; // 0xc
};