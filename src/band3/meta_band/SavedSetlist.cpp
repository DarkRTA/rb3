#include "meta_band/SavedSetlist.h"
#include "utl/Symbol.h"

LocalSavedSetlist::LocalSavedSetlist()
    : SavedSetlist(gNullStr, gNullStr), mOwnerProfile(0) {
    mSaveSizeMethod = &SaveSize;
}