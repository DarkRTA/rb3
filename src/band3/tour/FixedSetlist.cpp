#include "FixedSetlist.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include <vector>
#include "band3/meta_band/AccomplishmentManager.h"

FixedSetlist::FixedSetlist() : mWeight(1), m_pSongEntries(NULL), mName("") {
}

FixedSetlist::~FixedSetlist() {
    
}

void FixedSetlist::Init(const DataArray *i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1e);

    mName = i_pConfig->Sym(0);

    i_pConfig->FindData(group, mGroup, true);
    i_pConfig->FindData(weight, mWeight, false);
    DataArray* pSongsArray = i_pConfig->FindArray(songs, true);

    MILO_ASSERT(pSongsArray, 0x2A);
    MILO_ASSERT(pSongsArray->Size() > 1, 0x2B);

    m_pSongEntries = pSongsArray;
}

Symbol FixedSetlist::GetName() const {
    return mName;
}

Symbol FixedSetlist::GetGroup() const {
    return mGroup;
}

float FixedSetlist::GetWeight() const {
    return mWeight;
}

Symbol FixedSetlist::GetSongName(int i_iIndex) {
    MILO_ASSERT(i_iIndex < GetNumSongs(), 0x44);

    Symbol name = mSongs.at(i_iIndex);

    DataArray* result;
    InqSongs(mSongs);
    if(result) {
        result->FindData(Symbol(""), name, true);
    }

    return name;
}

int FixedSetlist::GetNumSongs() const {
    MILO_ASSERT(m_pSongEntries, 0x4F);

    return m_pSongEntries->Size() - 1;
}

void FixedSetlist::InqSongs(std::vector<Symbol>& o_rSongs) const {
    MILO_ASSERT(o_rSongs.empty(), 0x56);

    for (int i = 0; i < o_rSongs.size(); i++) {
        DataArray* pArray;

        MILO_ASSERT(pArray->Size(), 0x0);
        pArray = TheAccomplishmentMgr.GetTourSafeDiscSongAtDifficultyIndex(0);
        Symbol s = pArray->Sym(0);
        pArray->Array(0);
    }
}