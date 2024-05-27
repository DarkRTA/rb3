#ifndef METABAND_SONGMGR_H
#define METABAND_SONGMGR_H

#include "system/utl/Symbol.h"

#include <vector>

class SongMgr {
    ~SongMgr();
    void Init();
    void HasSong(int) const;
    void HasSong(Symbol, bool) const;
    void Data(int) const;
    void ContentStarted();
    void ContentDiscovered(Symbol);
    void ContentDone();
    void ContentMounted(const char*, const char*);
    virtual void ContentUnmounted(const char*);
    void ContentName(int) const;
    void SongAudioData(Symbol) const;
    void ContentName(Symbol, bool) const;
    void GetContentNames(Symbol, std::vector<Symbol>);
    void SongCacheNeedsWrite() const;
    void IsSongCacheWriteDone() const;
    void IsSongMounted(Symbol) const;
};

#endif // METABAND_SONGMGR_H