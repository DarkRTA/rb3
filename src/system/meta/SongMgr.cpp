#include "SongMgr.h"

SongMgr::~SongMgr() {}
void SongMgr::Init() {}
bool SongMgr::HasSong(int) const { return false; }
bool SongMgr::HasSong(Symbol, bool) const { return false; }
int SongMgr::Data(int) const { return 0; }
void SongMgr::ContentStarted() {}
bool SongMgr::ContentDiscovered(Symbol) {}
void SongMgr::ContentDone() {}
void SongMgr::ContentMounted(const char*, const char*) {}
void SongMgr::ContentUnmounted(const char*) {}
const char* SongMgr::ContentName(int) const {}
void SongMgr::SongAudioData(Symbol) const {}
const char* SongMgr::ContentName(Symbol, bool) const {}
void SongMgr::GetContentNames(Symbol, std::vector<Symbol>&) const {}
bool SongMgr::SongCacheNeedsWrite() const {}
void SongMgr::IsSongCacheWriteDone() const {}
void SongMgr::IsSongMounted(Symbol) const {}