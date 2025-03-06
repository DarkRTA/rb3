#include "meta_band/MusicLibrary.h"
#include "MusicLibraryNetSetlists.h"
#include "SongSetlistProvider.h"
#include "ViewSetting.h"
#include "decomp.h"
#include "meta/SongPreview.h"
#include "meta_band/HeaderPerformanceProvider.h"
#include "meta_band/SongSortMgr.h"
#include "net/Synchronize.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

MusicLibrary *TheMusicLibrary;

void MusicLibrary::Init(SongPreview &prev) {
    MILO_ASSERT(!TheMusicLibrary, 0x53);
    TheMusicLibrary = new MusicLibrary(prev);
}

DECOMP_FORCEACTIVE(MusicLibrary, "TheMusicLibrary")

MusicLibrary::MusicLibrary(SongPreview &prev)
    : Synchronizable("music_library"), unk40(0),
      mViewSettingsProvider(new ViewSettingsProvider()), mSongPreview(prev), unkc8(0),
      unkcc(gNullStr), unkd0(0), unkd4(gNullStr), unkd8(0), unkdc(0), unke0(0), unke4(8),
      unke8(9), unkec(0), unkf0(0), unkf4(0), unkf8(0), unkfc(0), unk100(0), unk104(0),
      unk108(0), unk10c(0), unk110(0), unk114(0), unk118(0), unk11c(0), unk120(0),
      unk124(0), unk128(0), unk12c(0), unk12d(0), mSetlistProvider(new SetlistProvider()),
      unk13c(0), mNetSetlists(new MusicLibraryNetSetlists()), unk15c(0),
      mSetlistScoresProvider(new SetlistScoresProvider()), unk164(0), unk168(0),
      unk16c(0), unk170(0), unk174(0) {
    SetName("music_library", ObjectDir::Main());
}

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