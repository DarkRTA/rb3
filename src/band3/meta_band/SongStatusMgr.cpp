#include "SongStatusMgr.h"

void SongStatusData::Clear(ScoreType) {}
void SongStatusData::SaveSize(int) {}
void SongStatusData::SaveToStream(BinStream&, ScoreType) const {}
void SongStatusData::LoadFromStream(BinStream&, ScoreType) {}

SongStatus::SongStatus() {}
SongStatus::~SongStatus() {}
void SongStatus::Clear() {}
void SongStatus::SaveSize(int) {}
void SongStatus::SaveFixed(FixedSizeSaveableStream&) const {}
void SongStatus::LoadFixed(FixedSizeSaveableStream&, int) {}
void SongStatus::SetDirty(ScoreType, Difficulty, bool) {}
void SongStatus::SetLastPlayed(int) {}
void SongStatus::GetLastPlayed() const {}
void SongStatus::SetPlayCount(int) {}
void SongStatus::SetBitmapLessonComplete(unsigned int&, int, bool) {}
void SongStatus::SetProGuitarLessonSectionComplete(Difficulty, int, bool) {}

SongStatusLookup::SongStatusLookup() {}
SongStatusLookup::~SongStatusLookup() {}
void SongStatusLookup::Clear() {}
void SongStatusLookup::Save(FixedSizeSaveableStream&) const {}
void SongStatusLookup::Load(FixedSizeSaveableStream&, int) {}


SongStatusMgr::~SongStatusMgr() {}
void SongStatusMgr::Clear() {}
// void SongStatusMgr::GetScore(int, ScoreType) const {}
// void SongStatusMgr::GetStars(int, ScoreType, Difficulty) const {}
// void SongStatusMgr::GetBestStars(int, ScoreType, Difficulty) const {
// }
