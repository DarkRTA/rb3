#pragma once
#include "utl/Symbol.h"
#include "tour/FixedSetlist.h"
#include "tour/GigFilter.h"
#include "tour/Quest.h"
#include <map>

class QuestManager {
    public:
    QuestManager();
    virtual ~QuestManager();
    void Cleanup();
    void Init(DataArray*);
    void ConfigureQuestData(DataArray*);
    void ConfigureQuestFilterData(DataArray*);
    void ConfigureFixedSetlistData(DataArray*);
    bool HasQuest(Symbol) const;
    bool HasQuestFilter(Symbol) const;
    bool HasFixedSetlist(Symbol) const;
    Quest* GetQuest(Symbol) const;
    GigFilter* GetQuestFilter(Symbol) const;
    FixedSetlist* GetFixedSetlist(Symbol) const;
    void CompleteQuest(TourProgress*, Symbol);
    
    
    bool IsQuestAvailable(const TourProgress&, Symbol, Symbol, int);

    std::map<Symbol, Quest*> unk_0x4;
    std::map<Symbol, GigFilter*> unk_0x1C;
    std::map<Symbol, FixedSetlist*> unk_0x34;
};

extern QuestManager TheQuestMgr;
