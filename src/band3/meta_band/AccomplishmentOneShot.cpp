#include "AccomplishmentOneShot.h"

#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"
#include "Campaign.h"
#include "ProfileMgr.h"

AccomplishmentOneShot::AccomplishmentOneShot(DataArray* i_pConfig, int i) : AccomplishmentConditional(i_pConfig, i), mOneShotSong(gNullStr), mOneShotPlayerMin(0) {
    AccomplishmentOneShot::Configure(i_pConfig);
}

AccomplishmentOneShot::~AccomplishmentOneShot() {
}

void AccomplishmentOneShot::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x23);

    i_pConfig->FindData(oneshot_song, mOneShotSong, false);
    i_pConfig->FindData(oneshot_playermin, mOneShotPlayerMin, false);
}

int AccomplishmentOneShot::GetType() const {
    return 9;
}

bool AccomplishmentOneShot::AreOneShotConditionsMet(ScoreType, Difficulty, Performer* i_pPerformer, Symbol, int) {
    MILO_ASSERT(i_pPerformer, 0x3c);

    for (size_t i = 0; i < m_lConditions.size(); i++) {
        Symbol condition = m_lConditions.at(i).s;
        if (condition == stars) {
            // TODO: check the performer's stars
            return false;
        } else if (condition == unison_percent) {

        } else if (condition == unison_phrases) {

        } else if (condition == upstrum_percent) {

        } else if (condition == times_revived) {

        } else if (condition == saves) {

        } else if (condition == awesomes) {

        } else if (condition == double_awesomes) {

        } else if (condition == all_double_awesomes) {

        } else if (condition == triple_awesomes) {

        } else if (condition == all_triple_awesomes) {

        } else {
            if (condition != full_combo) {

            }
            
        }
    }
}

void AccomplishmentOneShot::InitializeTrackerDesc(TrackerDesc& param_1) const {
    Accomplishment::InitializeTrackerDesc(param_1);
    MILO_ASSERT(!m_lConditions.empty(), 0xe6);
    AccomplishmentCondition condition = m_lConditions[0];
    MILO_ASSERT(TheCampaign, 0xe9);
    LocalUser* pUser = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0xeb);
    Profile* pProfile = TheProfileMgr.GetProfileForUser(pUser);
    MILO_ASSERT(pProfile, 0xee);

    if (condition.s == upstrum_percent) {

    } else if (condition.s == stars) {

    } else if (condition.s == unison_phrases) {

    }
}

bool AccomplishmentOneShot::HasSpecificSongsToLaunch() const {
    return !(mOneShotSong == gNullStr);
}

