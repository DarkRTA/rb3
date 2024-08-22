#include "QuestJournal.h"
#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"
#include "tour/QuestManager.h"
#include "tour/TourProgress.h"

QuestJournal::QuestJournal(TourProgress& tp) : unk_0x8(tp) {
    mSaveSizeMethod = SaveSize;
}

QuestJournal::~QuestJournal() { }

void QuestJournal::CompleteQuest(Symbol) { HandleDataChange(); }

void QuestJournal::SaveFixed(FixedSizeSaveableStream& fsss) const {
    SaveStd(fsss, unk_0xC, 20);
}

int QuestJournal::SaveSize(int) {
    if (FixedSizeSaveable::sPrintoutsEnabled) {
        MILO_LOG("* %s = %i\n", "QuestJournal", 84);
    }
    return 84;
}

void QuestJournal::LoadFixed(FixedSizeSaveableStream& fsss, int) {
    LoadStd(fsss, unk_0xC, 20);
}

void QuestJournal::HandleDataChange() {
    unk_0x8.SetDirty(true, 1);
}

void QuestJournal::Clear() {
    unk_0xC.clear();
}

void QuestJournal::FakeFill() {
    std::map<Symbol, Quest*>::iterator end_it = TheQuestMgr.unk_0x4.end(), it = TheQuestMgr.unk_0x4.begin();
    while (it != end_it) {
        if (unk_0xC.size() >= 20) break;
        unk_0xC.insert(Symbol(it->first));
        it++;
        
    }
}
