#include "AccomplishmentConditional.h"
#include "system/utl/Symbols.h"

AccomplishmentConditional::AccomplishmentConditional(DataArray* i_pConfig, int i) : Accomplishment(i_pConfig, i) {
    AccomplishmentConditional::Configure(i_pConfig);
}

AccomplishmentConditional::~AccomplishmentConditional() {

}

void AccomplishmentConditional::UpdateConditionOptionalData(AccomplishmentCondition& condition, DataArray* i_pConditionEntryArray) {
    MILO_ASSERT(i_pConditionEntryArray->Size() >= 2, 0x1f);

    for (int i = 2; i < i_pConditionEntryArray->Size(); i++) {
        DataArray* pEntry = i_pConditionEntryArray->Node(i).Array();
        MILO_ASSERT(pEntry, 0x29);
        Symbol name = Accomplishment::GetName();
        if (pEntry->Size() != 2) {
            TheDebug.Fail(MakeString("Invalid condition entry in %s.", name.Str()));
        }
        Symbol s = pEntry->Node(0).Sym();
        if(s == instrument) {
            condition.scoreType = (ScoreType)pEntry->Node(1).Int();
        } else if (s == difficulty) {
            condition.difficulty = (Difficulty)pEntry->Node(1).Int();
        } else {
            MILO_ASSERT(false, 0x3b);
        }
    }
}

void AccomplishmentConditional::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x43);
    DataArray* pConditionArray = i_pConfig->FindArray(conditions, true);
    if (pConditionArray != NULL) {
        MILO_ASSERT(pConditionArray->Size() > 1, 0x4b);
        for (int i = 1; i < pConditionArray->Size(); i++) {
            DataArray* pConditionEntryArray = pConditionArray->Node(i).Array();
            MILO_ASSERT(pConditionEntryArray, 0x50);

            AccomplishmentCondition condition;
            condition.test2 = 0;
            condition.difficulty = (Difficulty)0;
            condition.scoreType = (ScoreType)10;
            condition.s = pConditionEntryArray->Node(0).Sym();

            if (pConditionEntryArray->Size() >= 2) {
                condition.test2 = pConditionEntryArray->Node(1).Int();
                UpdateConditionOptionalData(condition, pConditionEntryArray);
            }

            m_lConditions.push_back(condition);
        }
    }
}

bool AccomplishmentConditional::CanBeLaunched() const {
    return true;
}

bool AccomplishmentConditional::InqRequiredScoreTypes(std::set<ScoreType>& o_rScoreTypes) const {
    MILO_ASSERT(!m_lConditions.empty(), 0x70);
    MILO_ASSERT(o_rScoreTypes.empty(), 0x71);

    for (std::vector<AccomplishmentCondition>::const_iterator i = m_lConditions.begin(); i != m_lConditions.end(); i++) {
        ScoreType scoreType = i->scoreType;
        if (scoreType != 10) {
            o_rScoreTypes.insert(scoreType);
        }
    }

    if (o_rScoreTypes.size() == 0) {
        return Accomplishment::InqRequiredScoreTypes(o_rScoreTypes);
    } else {
        return !o_rScoreTypes.empty();
    }
}

Difficulty AccomplishmentConditional::GetRequiredDifficulty() const {
    MILO_ASSERT(!m_lConditions.empty(), 0x8b);

    Difficulty requiredDifficulty = (Difficulty)3;

    for (std::vector<AccomplishmentCondition>::const_iterator i = m_lConditions.begin(); i != m_lConditions.end(); i++) {
        const AccomplishmentCondition& cond = *i;
        Difficulty conddiff = cond.difficulty;
        if (conddiff < requiredDifficulty) {
            requiredDifficulty = conddiff;
        }
    }

    if (requiredDifficulty != 0) {
        return requiredDifficulty;
    }
    return Accomplishment::GetRequiredDifficulty();

}
