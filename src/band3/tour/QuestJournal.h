#ifndef TOUR_QUESTJOURNAL_H
#define TOUR_QUESTJOURNAL_H

#include "meta/FixedSizeSaveable.h"
class TourProgress;

class QuestJournal : public FixedSizeSaveable {
    public:
    QuestJournal(TourProgress&);
    virtual ~QuestJournal();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
    void CompleteQuest(Symbol);
};

#endif // TOUR_QUESTJOURNAL_H
