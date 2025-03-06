#include "meta_band/MusicLibrary.h"
#include "meta/SongPreview.h"
#include "meta_band/SongSortMgr.h"
#include "net/Synchronize.h"
#include "utl/Symbol.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MusicLibrary::MusicLibrary(SongPreview &) : Synchronizable("music_library"), unk40(0) {}

MusicLibrary::MusicLibraryTask::MusicLibraryTask() { Reset(); }

void MusicLibrary::MusicLibraryTask::Reset() {
    setlistMode = 0;
    filter.Reset();
    filterLocked = false;
    allowDuplicates = true;
    requiresStandardParts = true;
    backScreen = main_hub_screen;
    nextScreen = part_difficulty_screen;
    maxSetlistSize = 0;
    partSym = gNullStr;
    unk2c = 11;
    titleToken = music_library;
    makingSetlistToken = making_setlist;
}

void MusicLibrary::MusicLibraryTask::ResetWithBackScreen(Symbol s) {
    Reset();
    backScreen = s;
}

void MusicLibrary::MusicLibraryTask::GetSongFilterAsString(String &str) {
    for (int i = 0; i < kNumFilterTypes; i++) {
        const std::set<Symbol> &filterSet = filter.GetFilterSet((FilterType)i);
        if (!filterSet.empty()) {
            str += MakeString("%i:", i);
            FOREACH (it, filterSet) {
                Symbol cur = *it;
                if (it != filterSet.begin())
                    str += ",";
                str += cur.mStr;
            }
            str += ";";
        }
    }
}

void MusicLibrary::MusicLibraryTask::SetSongFilter(const SongSortMgr::SongFilter &filt) {
    filter = filt;
}