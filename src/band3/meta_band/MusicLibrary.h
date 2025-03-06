#pragma once
#include "meta/SongPreview.h"
#include "meta_band/SongSortMgr.h"
#include "net/Synchronize.h"
#include "os/ContentMgr.h"
#include "ui/UIListProvider.h"
#include <vector>

class MusicLibrary : public UIListProvider,
                     public ContentMgr::Callback,
                     public Synchronizable {
public:
    class MusicLibraryTask {
    public:
        enum SetlistMode {
            kSetlistOptional = 0,
            kSetlistForced = 1,
            kSetlistForbidden = 2
        };

        MusicLibraryTask();
        void Reset();
        void ResetWithBackScreen(Symbol);
        void GetSongFilterAsString(String &);
        void SetSongFilter(const SongSortMgr::SongFilter &);

        int setlistMode; // 0x0
        SongSortMgr::SongFilter filter; // 0x4
        bool filterLocked; // 0x18
        bool allowDuplicates; // 0x19
        bool requiresStandardParts; // 0x1a
        Symbol backScreen; // 0x1c
        Symbol nextScreen; // 0x20
        int maxSetlistSize; // 0x24
        Symbol partSym; // 0x28
        int unk2c; // 0x2c
        Symbol titleToken; // 0x30
        Symbol makingSetlistToken; // 0x34
    };

    MusicLibrary(SongPreview &);

    const std::vector<int> &GetSetlist();
    void AppendToSetlist(int);
    void RemoveLastSongFromSetlist();

    bool unk40; // 0x40
    MusicLibraryTask unk44; // 0x44
};

extern MusicLibrary *TheMusicLibrary;