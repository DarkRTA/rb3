#include "QuestJournal.h"
#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"
#include "tour/QuestManager.h"
#include "tour/TourProgress.h"

QuestJournal::QuestJournal(TourProgress& tp) : m_rOwningProgress(tp) {
    mSaveSizeMethod = SaveSize;
}

QuestJournal::~QuestJournal() { }

void QuestJournal::CompleteQuest(Symbol) { HandleDataChange(); }

void QuestJournal::SaveFixed(FixedSizeSaveableStream& fsss) const {
    SaveStd(fsss, m_setCompletedQuests, 20);
}

int QuestJournal::SaveSize(int) {
    if (FixedSizeSaveable::sPrintoutsEnabled) {
        MILO_LOG("* %s = %i\n", "QuestJournal", 84);
    }
    return 84;
}

void QuestJournal::LoadFixed(FixedSizeSaveableStream& fsss, int) {
    LoadStd(fsss, m_setCompletedQuests, 20);
}

void QuestJournal::HandleDataChange() {
    m_rOwningProgress.SetDirty(true, 1);
}

void QuestJournal::Clear() {
    m_setCompletedQuests.clear();
}

void QuestJournal::FakeFill() {
    std::map<Symbol, Quest*>::iterator end_it = TheQuestMgr.mMapQuests.end(), it = TheQuestMgr.mMapQuests.begin();
    while (it != end_it) {
        if (m_setCompletedQuests.size() >= 20) break;
        m_setCompletedQuests.insert(Symbol(it->first));
        it++;
        
    }
}
