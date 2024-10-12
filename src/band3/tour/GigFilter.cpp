#include "GigFilter.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

GigFilter::GigFilter() : mName(""), mIsInternal(0), mFilteredPartSym(gNullStr), mWeight(1.0f) {

}

GigFilter::~GigFilter() {

}

void GigFilter::Init(const DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1E);
    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(is_internal, mIsInternal, false);
    i_pConfig->FindData(weight, mWeight, false);
    mFilteredPartSym = gNullStr;
    i_pConfig->FindData(part_difficulty_filter, mFilteredPartSym, false);
    DataArray* filterarr = i_pConfig->FindArray(filter, false);
    if(filterarr){
        for(int i = 1; i < filterarr->Size(); i++){
            DataArray* pEntry = filterarr->Array(i);
            MILO_ASSERT(pEntry, 0x34);
            MILO_ASSERT(pEntry->Size() == 2, 0x35);
            FilterType ty = (FilterType)pEntry->Int(0);
            Symbol s = pEntry->Sym(1);
            mFilter.AddFilter(ty, s);
        }
    }
}

Symbol GigFilter::GetName() const { return mName; }
bool GigFilter::IsInternal() const { return mIsInternal; }

const SongSortMgr::SongFilter& GigFilter::GetFilter() const {
    return mFilter;
}

Symbol GigFilter::GetFilteredPartSym() const {
    return mFilteredPartSym;
}

// void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, int, Symbol) const {}

float GigFilter::GetWeight() const { return mWeight; }