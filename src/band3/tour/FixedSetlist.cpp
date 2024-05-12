#include "FixedSetlist.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h";
#include <vector>

FixedSetlist::FixedSetlist() : mWeight(0.0), mSongEntries(nullptr), mName("") {
}

FixedSetlist::~FixedSetlist() {

}

void FixedSetlist::Init(const DataArray *config) {
    if (config == nullptr) {
        TheDebug.Fail(MakeString(kAssertStr, __FILE__, 30, "i_pConfig"));
    }

    mName = config->Sym(0);

    config->FindData(group, mGroup, true);
    config->FindData(weight, mWeight, false);
    DataArray* pSongsArray = config->FindArray(songs, true);

    if (pSongsArray == nullptr) {
        TheDebug.Fail(MakeString(kAssertStr, __FILE__, 42, "pSongsArray"));
    }
    if (pSongsArray->Size() <= 1) {
        TheDebug.Fail(MakeString(kAssertStr, __FILE__, 43, "pSongsArray->Size() > 1"));
    }

    mSongEntries = pSongsArray;
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

Symbol FixedSetlist::GetSongName(int index) {
    if (index < GetNumSongs()){
        TheDebug.Fail(MakeString(kAssertStr, __FILE__, 68, "i_iIndex < GetNumSongs()"));
    }

    Symbol name = mSongs.at(index);

    return name;
}

int FixedSetlist::GetNumSongs() const {
    if (mSongEntries == nullptr) {
        TheDebug.Fail(MakeString(kAssertStr, __FILE__, 79, "m_pSongEntries"));
    }
    
    return mSongEntries->Size() - 1;
}

void FixedSetlist::InqSongs(std::vector<Symbol>& songs) const {
    if (songs.empty()) {
        TheDebug.Fail(MakeString(kAssertStr, __FILE__, 86, "o_rSongs.empty()"));
    }

    // Requires TheAccomplishMgr to continue. 
}