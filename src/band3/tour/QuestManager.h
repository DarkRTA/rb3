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

    std::map<Symbol, Quest*> unk_0x4;
    std::map<Symbol, GigFilter> unk_0x1C;
    std::map<Symbol, FixedSetlist> unk_0x34;
};

extern QuestManager TheQuestMgr;
