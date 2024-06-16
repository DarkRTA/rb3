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

    DataArray* result;
    std::vector<Symbol> songs;

    InqSongs(songs);

    return songs[i_iIndex];
}

int FixedSetlist::GetNumSongs() const {
    MILO_ASSERT(m_pSongEntries, 0x4F);

    return m_pSongEntries->Size() - 1;
}

bool FixedSetlist::InqSongs(std::vector<Symbol>& o_rSongs) const {
    MILO_ASSERT(o_rSongs.empty(), 0x56);

    for (int i = 1; i < m_pSongEntries->Size(); i++) {
        Symbol s = gNullStr;
        DataNode& songEntryNode = m_pSongEntries->Node(i);
        if (songEntryNode.Type() == kDataSymbol) {
            s = songEntryNode.Sym(0);
        } else if (songEntryNode.Type() == kDataArray) {
            DataArray* pArray = songEntryNode.Array(0);
            MILO_ASSERT(pArray->Size() == 1, 0x63);
            int difficultyIndex = pArray->Node(0).Int(pArray);
            s = TheAccomplishmentMgr.GetTourSafeDiscSongAtDifficultyIndex(difficultyIndex);
        } else {
            MILO_ASSERT(false, 0x6b);
        }
        o_rSongs.push_back(s);
    }

    return !o_rSongs.empty();
}