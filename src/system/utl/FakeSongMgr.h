#ifndef UTL_FAKESONGMGR_H
#define UTL_FAKESONGMGR_H
#include "obj/Data.h"

class SongInfo; // forward dec

class FakeSongMgr {
public:
    DataArray* GetSongConfig(Symbol);
    static const char* GetPath(const SongInfo*, const char*);
    static const char* MidiFullPath(const SongInfo*);
    static const char* MidiFile(const SongInfo*);
};

extern FakeSongMgr* TheFakeSongMgr;

#endif
