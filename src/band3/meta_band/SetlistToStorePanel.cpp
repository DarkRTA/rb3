#include "meta_band/SetlistToStorePanel.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UIPanel.h"
#include "utl/Std.h"
#include "utl/Symbols3.h"

void SetlistToStorePanel::Enter() {
    UIPanel::Enter();
    unk58.Restart();
}

void SetlistToStorePanel::Load() {
    UIPanel::Load();
    MILO_ASSERT(!mAllMetadata, 0x1F);
    MILO_ASSERT(mLoaders.empty(), 0x20);
}

void SetlistToStorePanel::Poll() { UIPanel::Poll(); }

void SetlistToStorePanel::Unload() {
    mSongs.clear();
    mSongNames.clear();
    DeleteAll(mLoaders);
    if (mAllMetadata) {
        mAllMetadata->Release();
        mAllMetadata = nullptr;
    }
    UIPanel::Unload();
}

BEGIN_HANDLERS(SetlistToStorePanel)
    HANDLE_ACTION(get_songs_from_music_library, GetSongsFromMusicLibrary())
    HANDLE_ACTION(load_song_metadata, 0)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xE3)
END_HANDLERS