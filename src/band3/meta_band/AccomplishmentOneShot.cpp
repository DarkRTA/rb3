#include "AccomplishmentOneShot.h"

#include "system/utl/Symbols4.h"

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

// void AccomplishmentOneShot::AreOneShotConditionsMet() {
// }

void AccomplishmentOneShot::InitializeTrackerDesc(TrackerDesc&) const {

}

bool AccomplishmentOneShot::HasSpecificSongsToLaunch() const {
    return !(mOneShotSong == gNullStr);
}

void AccomplishmentOneShot::UpdateIncrementalEntryName(UILabel*, Symbol) {
}
