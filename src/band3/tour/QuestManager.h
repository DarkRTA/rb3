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
    bool HasQuest(Symbol s) const { return GetQuest(s); }
    bool HasQuestFilter(Symbol s) const { return GetQuestFilter(s); }
    bool HasFixedSetlist(Symbol s) const { return GetFixedSetlist(s); }
    Quest* GetQuest(Symbol) const;
    GigFilter* GetQuestFilter(Symbol) const;
    FixedSetlist* GetFixedSetlist(Symbol) const;
    void CompleteQuest(TourProgress*, Symbol);
    
    bool IsQuestAvailable(const TourProgress&, Symbol, Symbol, int);

    std::map<Symbol, Quest*> mMapQuests; // 0x4
    std::map<Symbol, GigFilter*> mMapQuestFilters; // 0x1c
    std::map<Symbol, FixedSetlist*> mMapFixedSetlists; // 0x34
};

extern QuestManager TheQuestMgr;
