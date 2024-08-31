#ifndef TOUR_QUESTJOURNAL_H
#define TOUR_QUESTJOURNAL_H

#include "meta/FixedSizeSaveable.h"
#include <set>
class TourProgress;

class QuestJournal : public FixedSizeSaveable {
    public:
    QuestJournal(TourProgress&);
    virtual ~QuestJournal();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void CompleteQuest(Symbol);
    void HandleDataChange();
    void Clear();
    void FakeFill();

    static int SaveSize(int);
    
    TourProgress& unk_0x8;
    std::set<Symbol> unk_0xC;
};

#endif // TOUR_QUESTJOURNAL_H
