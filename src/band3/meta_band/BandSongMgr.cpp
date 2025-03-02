#include "meta_band/BandSongMgr.h"
#include "Utl.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "meta/SongMgr.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/SongUpgradeMgr.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/Dir.h"
#include "game/GameMode.h"
#include "obj/DirLoader.h"
#include "os/Archive.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/System.h"
#include "stl/_pair.h"
#include "utl/CacheMgr.h"
#include "utl/FakeSongMgr.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

BandSongMgr gSongMgr;
BandSongMgr &TheSongMgr = gSongMgr;

bool BandSongMgr::sFakeSongsAllowed;

const char *OLD_DLC_DIR = "songs/updates/";
const char *exclusionList[] = {
    "danicalifornia", "blackholesun", "hierkommtalex", "rockandrollstar"
};

BandSongMgr::BandSongMgr()
    : unkc0(0), unk124(1), mUpgradeMgr(0), mLicenseMgr(0), mMaxSongCount(-1), unk13c(0),
      unk140(0) {
    ClearAndShrink(mContentAltDirs);
    TheBaseSongManger = this;
}

void BandSongMgr::Init() {
    SongMgr::Init();
    SetName("song_mgr", ObjectDir::sMainDir);
    TheContentMgr->RegisterCallback(this, false);
    mSongNameLookup.clear();
    mSongIDLookup.clear();
    DataArray *cfg = SystemConfig(song_mgr);
    DataArray *altarr = cfg->FindArray(alt_dirs, false);
    if (altarr) {
        for (int i = 1; i < altarr->Size(); i++) {
            const char *str = altarr->Array(i)->Str(0);
            if (strlen(str) != 0) {
                mContentAltDirs.push_back(String(str));
            }
        }
    }
    mMaxSongCount = cfg->FindInt(max_song_count);
    mUpgradeMgr = new SongUpgradeMgr();
    mLicenseMgr = new LicenseMgr();
}

bool BandSongMgr::CreateSongCacheID(CacheID **id) {
    *id = nullptr;
    DataArray *cfg = SystemConfig("net", "cache");
    const char *filename = cfg->FindStr("file_name");
    const char *bannername = cfg->FindStr("banner_name");
    const char *bannerdesc = cfg->FindStr("banner_desc");
    bool ret = TheCacheMgr->CreateCacheID(
        filename, bannername, nullptr, bannerdesc, nullptr, 0x400, id
    );
    MILO_ASSERT(ret, 0x8C);
    return ret;
}

void BandSongMgr::Terminate() {
    RELEASE(unkc0);
    RELEASE(mLicenseMgr);
    RELEASE(mUpgradeMgr);
    ClearAndShrink(mContentAltDirs);
    TheContentMgr->UnregisterCallback(this, false);
    mSongNameLookup.clear();
    mSongIDLookup.clear();
}

struct SongRankCmp {
    SongRankCmp(BandSongMgr *mgr, Symbol s) : mSongMgr(mgr), mPart(s) {}
    bool operator()(int x, int y) const {
        float rankX = ((BandSongMetadata *)mSongMgr->Data(x))->Rank(mPart);
        float rankY = ((BandSongMetadata *)mSongMgr->Data(y))->Rank(mPart);
        if (rankX == rankY)
            return x < y;
        else
            return rankX < rankY;
    }

    BandSongMgr *mSongMgr;
    Symbol mPart;
};

void BandSongMgr::ContentDone() {
    SongMgr::ContentDone();
    mSongRankings.clear();
    std::vector<int> songs;
    GetRankedSongs(songs, false, true);
    Symbol instSyms[9] = { "band", "guitar",      "vocals",    "drum",     "bass",
                           "keys", "real_guitar", "real_bass", "real_keys" };
    for (int i = 0; i < 9U; i++) {
        SongRanking ranking;
        ranking.mInstrument = instSyms[i];
        std::vector<int> curSongs = songs;
        std::vector<int> i80;
        std::sort(
            curSongs.begin(), curSongs.end(), SongRankCmp(this, ranking.mInstrument)
        );
        FOREACH (it, curSongs) {
            BandSongMetadata *data = (BandSongMetadata *)Data(*it);
            if (!data->IsDownload() && data->HasPart(ranking.mInstrument, false)) {
                i80.push_back(*it);
            }
        }
        int i4 = i80.size();
        if (i4 != 0) {
            int numRanks = SystemConfig("song_groupings", "rank")->Size() - 1;
            int i11 = 0;
            for (int i = 0; i < numRanks; i++) {
                int i8 = i4 / numRanks;
                if (i >= numRanks - (i4 % numRanks)) {
                    i8++;
                }
                if (i8 != 0) {
                    int i2 = i80[i11];
                    int i5 = i80[i11 + i8 - 1];
                    BandSongMetadata *b2 = (BandSongMetadata *)Data(i2);
                    BandSongMetadata *b5 = (BandSongMetadata *)Data(i5);
                    float r5 = b5->Rank(ranking.mInstrument);
                    float r2 = b2->Rank(ranking.mInstrument);
                    ranking.mTierRanges.push_back(std::make_pair(r2, r5));
                    i11 += i8;
                } else {
                    MILO_WARN(
                        "Instrument %s only has %d songs but %d groups. Group                        %d will have no songs.\n",
                        ranking.mInstrument,
                        i80.size(),
                        numRanks,
                        i
                    );
                }
            }
        }
        mSongRankings.push_back(ranking);
    }
    unk124 = false;
    SyncSharedSongs();
    if (&TheRockCentral) {
        std::vector<BandProfile *> profiles = TheProfileMgr.GetSignedInProfiles();
        std::vector<int> songs2;
        GetRankedSongs(songs2, false, true);
        std::vector<int> ic8;
        FOREACH (it, ic8) {
            int cur = *it;
            if (mUpgradeMgr->HasUpgrade(cur)) {
                ic8.push_back(cur);
            }
        }
        TheRockCentral.SyncAvailableSongs(profiles, songs2, ic8, nullptr);
    }
    if (mSongCacheWriteAllowed && TheSaveLoadMgr) {
        TheSaveLoadMgr->AutoSave();
    }
}

void BandSongMgr::ContentMounted(const char *c1, const char *c2) {
    SongMgr::ContentMounted(c1, c2);
}

const char *BandSongMgr::ContentPattern() {
    return TheArchive ? "&songs*.dta" : "&songs*.dt?";
}

const char *BandSongMgr::ContentDir() { return "songs"; }

Symbol BandSongMgr::GetShortNameFromSongID(int songID, bool fail) const {
    MILO_ASSERT(songID != kSongID_Invalid && songID != kSongID_Any && songID != kSongID_Random, 0x156);
    std::map<int, Symbol>::const_iterator it = mSongNameLookup.find(songID);
    if (it != mSongNameLookup.end())
        return it->second;
    it = mExtraSongIDMap.find(songID);
    if (it != mExtraSongIDMap.end())
        return it->second;
    if (fail) {
        MILO_FAIL("Couldn't find song short name for SONG_ID %d", songID);
    }
    return gNullStr;
}

int BandSongMgr::GetSongIDFromShortName(Symbol shortName, bool fail) const {
    std::map<Symbol, int>::const_iterator it = mSongIDLookup.find(shortName);
    if (it != mSongIDLookup.end()) {
        MILO_ASSERT(it->second != kSongID_Invalid, 0x16D);
        return it->second;
    } else {
        for (std::map<int, Symbol>::const_iterator it = mExtraSongIDMap.begin();
             it != mExtraSongIDMap.end();
             ++it) {
            if (it->second == shortName) {
                MILO_ASSERT(it->first != kSongID_Invalid, 0x176);
                return it->first;
            }
        }
        if (fail) {
            MILO_FAIL(
                "Couldn't find song ID for short name \"%s\", does song have a SONG_ID?",
                shortName.Str()
            );
        }
        return 0;
    }
}

void BandSongMgr::GetContentNames(Symbol s, std::vector<Symbol> &vec) const {
    SongMgr::GetContentNames(s, vec);
    int songID = GetSongIDFromShortName(s, false);
    if (mUpgradeMgr->HasUpgrade(songID)) {
        const char *contentName = mUpgradeMgr->ContentName(songID);
        MILO_ASSERT(contentName, 0x18C);
        if (!streq(contentName, ".")) {
            vec.push_back(contentName);
        }
    }
}

SongMetadata *BandSongMgr::Data(int i) const { return SongMgr::Data(i); }

SongInfo *BandSongMgr::SongAudioData(int i) const {
    SongMetadata *data = Data(i);
    if (!data)
        return 0;
    else {
        SongInfo *songInfo = data->SongBlock();
        MILO_ASSERT(songInfo, 0x1a0);
        RELEASE(unkc0);
        unkc0 = new DataArraySongInfo(songInfo);
        const char *update = ((BandSongMetadata *)data)->MidiUpdate(); // lol can you
                                                                       // actually do this
        if (update)
            unkc0->AddExtraMidiFile(update, 0);
        if (mUpgradeMgr->HasUpgrade(i)) {
            SongUpgradeData *upgrade = mUpgradeMgr->UpgradeData(i);
            MILO_ASSERT(upgrade, 0x1C3);
            unkc0->AddExtraMidiFile(UpgradeMidiFile(i), 0);
        }
        return unkc0;
    }
}

const char *BandSongMgr::SongName(int i) const {
    BandSongMetadata *data = (BandSongMetadata *)Data(i);
    if (data)
        return data->Title();
    else
        return gNullStr;
}

const char *BandSongMgr::SongName(Symbol s) const {
    return SongName(GetSongIDFromShortName(s, true));
}

const char *BandSongMgr::UpgradeMidiFile(int i) const {
    const char *file = gNullStr;
    if (mUpgradeMgr->HasUpgrade(i)) {
        SongUpgradeData *upgrade = mUpgradeMgr->UpgradeData(i);
        MILO_ASSERT(upgrade, 0x20A);
        file = upgrade->MidiFile();
    }
    return file;
}

const char *BandSongMgr::MidiFile(Symbol s) const {
    SongInfo *info = SongMgr::SongAudioData(s);
    if (info)
        return FakeSongMgr::MidiFile(info);
    else
        return gNullStr;
}

const char *BandSongMgr::SongFilePath(Symbol s1, const char *cc, bool b3) const {
    const char *path = gNullStr;
    BandSongMetadata *data = (BandSongMetadata *)Data(GetSongIDFromShortName(s1, true));
    if (data) {
        if (b3 && data->IsDownload()) {
            String str =
                MakeString("%s%s", SongMgr::SongAudioData(s1)->GetBaseFileName(), cc);
            unsigned int idx = str.find("_song");
            if (idx != String::npos) {
                str.erase(idx, 5);
            }
            path = MakeString("%s", str);
        } else if (data->HasAlternatePath()) {
            const char *base =
                FileGetBase(SongMgr::SongAudioData(s1)->GetBaseFileName(), nullptr);
            path = MakeString("%s%s/%s%s", OLD_DLC_DIR, base, base, cc);
        } else {
            path = MakeString("%s%s", SongMgr::SongAudioData(s1)->GetBaseFileName(), cc);
        }
    }
    if (!UsingCD()) {
        if (data) {
            if (data->IsOnDisc() || data->HasAlternatePath())
                return path;
        } else if (streq(cc, ".milo")) {
            DirLoader::SetCacheMode(true);
            path = DirLoader::CachedPath(path, false);
            DirLoader::SetCacheMode(false);
        }
    }
    return path;
}

DECOMP_FORCEACTIVE(BandSongMgr, "")

const char *BandSongMgr::GetAlbumArtPath(Symbol s) const {
    if (HasSong(s, true))
        return SongFilePath(s, "_keep.png", true);
    else
        return gNullStr;
}

const char *BandSongMgr::SongPath(Symbol s) const {
    return SongMgr::SongAudioData(s)->GetBaseFileName();
}

int BandSongMgr::RankTier(float f, Symbol s) const {
    std::list<SongRanking>::const_iterator r =
        std::find(mSongRankings.begin(), mSongRankings.end(), s);
    MILO_ASSERT(r != mSongRankings.end(), 0x278);
    int i = 0;
    for (; i < r->mTierRanges.size(); i++) {
        if (f <= r->mTierRanges[i].second)
            return i;
    }
    return i - 1;
}

int BandSongMgr::NumRankTiers(Symbol s) const {
    std::list<SongRanking>::const_iterator r =
        std::find(mSongRankings.begin(), mSongRankings.end(), s);
    MILO_ASSERT(r != mSongRankings.end(), 0x289);
    return r->mTierRanges.size();
}

Symbol BandSongMgr::RankTierToken(int i) const {
    return SystemConfig(song_groupings, rank)->Array(i + 1)->FindSym(band);
}

void BandSongMgr::GetRankedSongs(std::vector<int> &vec, bool b1, bool b2) const {
    if (b1) {
        TheGameMode->Property("demos_allowed", true)->Int();
    }
    vec.clear();
    for (std::set<int>::const_iterator it = mAvailableSongs.begin();
         it != mAvailableSongs.end();
         ++it) {
        int cur = *it;
        BandSongMetadata *data = (BandSongMetadata *)Data(cur);
        if (data->IsRanked() && !data->IsPrivate() && (b2 || !IsRestricted(cur))) {
            vec.push_back(*it);
        }
    }
}

int BandSongMgr::GetValidSongCount(const std::map<int, SongMetadata *> &songs) const {
    int count = 0;
    for (std::map<int, SongMetadata *>::const_iterator it = songs.begin();
         it != songs.end();
         ++it) {
        BandSongMetadata *data = (BandSongMetadata *)it->second;
        if (data && data->IsRanked() && !data->IsPrivate())
            count++;
    }
    return count;
}

bool BandSongMgr::IsSongUnplayable(int songID, BandUserMgr &mgr, bool bvar3) const {
    BandSongMetadata *data = (BandSongMetadata *)Data(songID);
    Symbol shortname = GetShortNameFromSongID(songID, true);
    if (data->IsPrivate()) {
        MILO_WARN("%s is private!", shortname);
        return false;
    } else if (!data->IsRanked()) {
        MILO_WARN("%s is not ranked!", shortname);
        return false;
    } else {
        std::vector<BandUser *> users;
        mgr.GetParticipatingBandUsers(users);
        bool b5 = false;
        bool b4 = false;
        bool b3 = false;
        int i12 = 0;
        int i7 = 0;
        FOREACH (it, users) {
            Symbol controller = (*it)->GetControllerSym();
            MILO_ASSERT(controller != none, 0x2E3);
            if (controller == drum)
                b5 = true;
            else if (controller == vocals)
                b4 = true;
            else if (controller == keys)
                b3 = true;
            else if (controller == real_guitar)
                i7++;
            else
                i12++;
        }
        bool b1 = false;
        bool b11 = true;
        if (i12 == 1) {
            b1 = true;
            if (!data->HasPart(guitar, false) && !data->HasPart(bass, false)) {
                b1 = false;
            }
            if (!b1)
                b11 = false;
        }
        if (i12 > 1) {
            if (!data->HasPart(guitar, false) || !data->HasPart(bass, false)) {
                b11 = false;
            }
            if (data->HasPart(guitar, false) || data->HasPart(bass, false)) {
                b1 = true;
            }
        }
        if (i7 == 1) {
            if (data->HasPart(real_guitar, false) || data->HasPart(real_bass, false)) {
                b11 = false;
            } else
                b1 = true;
        }
        if (i7 > 1) {
            if (!data->HasPart(real_guitar, false) || !data->HasPart(real_bass, false)) {
                b11 = false;
            }
            if (data->HasPart(real_guitar, false) || data->HasPart(real_bass, false)) {
                b1 = true;
            }
        }
        if (b3) {
            if (data->HasPart(keys, false))
                b1 = true;
            else
                b11 = false;
        }
        if (b4) {
            if (data->HasPart(vocals, false))
                b1 = true;
            else
                b11 = false;
        }
        if (b5) {
            if (data->HasPart(drum, false))
                b1 = true;
            else
                b11 = false;
        }
        if (bvar3)
            return !b11;
        else
            return !b1;
    }
}

int BandSongMgr::GetCurSongCount() const { return unk140 + mCachedSongMetadata.size(); }
bool BandSongMgr::CanAddSong() const { return GetCurSongCount() + 1 < mMaxSongCount; }
int BandSongMgr::GetMaxSongCount() const { return mMaxSongCount; }

void BandSongMgr::AddSongData(DataArray *a, DataLoader *dl, ContentLocT lt) {
    const char *cc;
    for (int i = 0; i < 32; i++) {
    }
    if (dl) {
    }
    std::vector<int> vec;
    AddSongData(a, mUncachedSongMetadata, cc, lt, vec);
    unk140 = GetValidSongCount(mUncachedSongMetadata);
}

void BandSongMgr::AddSongData(
    DataArray *a,
    std::map<int, SongMetadata *> &map,
    const char *cc,
    ContentLocT loct,
    std::vector<int> &ivec
) {
    int arrSize = a->Size();
    int numSongs = CountSongsInArray(a);
    for (int i = arrSize - numSongs; i < arrSize; i++) {
        DataArray *curArray = a->Array(i);
        Symbol curSym = curArray->Sym(0);
        DataArray *cfgArr = SystemConfig(missing_song_data)->FindArray(curSym, false);
        int songID = GetSongID(curArray, cfgArr);
        if (IsInExclusionList(curSym.mStr, songID)) {
            MILO_LOG("Skipping song %s because not licensed for RB3.\n", curSym);
        } else if (songID == 0) {
            MILO_LOG("The song %s has an invalid songID. Skipping.\n", curSym);
        } else if (HasSong(songID)) {
            MILO_LOG("The song %s was found twice in the song manager data.\n", curSym);
        } else {
            bool isRoot = loct == kLocationRoot;
            AddSongIDMapping(songID, curSym);
            if (map.find(songID) != map.end()) {
                delete map.find(songID)->second;
            }
            if (cfgArr) {
                map[songID] = new BandSongMetadata(cfgArr, curArray, isRoot, this);
            } else {
                map[songID] = new BandSongMetadata(curArray, nullptr, isRoot, this);
            }
            mAvailableSongs.insert(songID);
            ivec.push_back(songID);
        }
    }
}

int BandSongMgr::GetPosInRecentList(int) { return -1; }
bool BandSongMgr::IsDemo(int) const { return false; }

bool BandSongMgr::IsRestricted(int songID) const {
    BandSongMetadata *data = (BandSongMetadata *)Data(songID);
    int rating = data->Rating();
    if (!AllowedToAccessContent(rating)) {
        MILO_WARN(
            "Song %d has rating %d, which should mean it is restricted", songID, rating
        );
    }
    return false;
}

SongUpgradeData *BandSongMgr::GetUpgradeData(int i) const {
    return mUpgradeMgr->UpgradeData(i);
}

bool BandSongMgr::HasLicense(Symbol s) const { return mLicenseMgr->HasLicense(s); }

void BandSongMgr::AddSongIDMapping(int i, Symbol s) {
    std::map<int, Symbol>::const_iterator nameIt = mSongNameLookup.find(i);
    if (nameIt != mSongNameLookup.end() && i != 0 && nameIt->second != s) {
        Symbol val = nameIt->second;
        MILO_WARN("Song %s and song %s have duplicate song_id %d!", s, val, i);
    }
    std::map<Symbol, int>::const_iterator idIt = mSongIDLookup.find(s);
    if (idIt != mSongIDLookup.end() && i != idIt->second) {
        MILO_WARN(
            "SongID %d and SongID %d have duplicate short name %s!", i, idIt->second, s
        );
    }
    mSongNameLookup[i] = s;
    mSongIDLookup[s] = i;
}

bool BandSongMgr::SongCacheNeedsWrite() const {
    return SongMgr::SongCacheNeedsWrite() || mUpgradeMgr->SongCacheNeedsWrite()
        || mLicenseMgr->LicenseCacheNeedsWrite();
}

void BandSongMgr::ClearSongCacheNeedsWrite() {
    SongMgr::ClearSongCacheNeedsWrite();
    mUpgradeMgr->ClearSongCacheNeedsWrite();
}

void BandSongMgr::ReadCachedMetadataFromStream(BinStream &bs, int rev) {
    int count;
    bs >> count;
    for (int i = 0; i < count; i++) {
        int i40;
        bs >> i40;
        bool remove;
        do {
            if (mMaxSongCount <= GetCurSongCount())
                break;
            remove = RemoveOldestCachedContent();
        } while (remove);
        if (mMaxSongCount <= GetCurSongCount()) {
            BandSongMetadata data(this);
            data.Load(bs);
        } else {
            BandSongMetadata *data = new BandSongMetadata(this);
            data->Load(bs);
            mCachedSongMetadata[i40] = data;
        }
    }
    if (rev >= 5) {
        bs >> unk114;
    }
    if (rev >= 11) {
        bs >> unk11c;
    }
    if (rev >= 6) {
        mUpgradeMgr->ReadCachedMetadataFromStream(bs, rev);
    }
    if (rev >= 8) {
        mLicenseMgr->ReadCachedMetadataFromStream(bs, rev);
    }
    unk124 = false;
}

void BandSongMgr::WriteCachedMetadataToStream(BinStream &bs) const {
    bs << mCachedSongMetadata.size();
    FOREACH (it, mCachedSongMetadata) {
        bs << it->first;
        it->second->Save(bs);
    }
    bs << unk114;
    bs << unk11c;
    mUpgradeMgr->WriteCachedMetadataToStream(bs);
    mLicenseMgr->WriteCachedMetadataToStream(bs);
}

bool BandSongMgr::RemoveOldestCachedContent() {
    if (mCachedSongMetadata.size() == 0)
        return false;
    else {
        MILO_WARN("Invalid SongID for song %s\n");
    }
}

void BandSongMgr::ClearCachedContent() {
    SongMgr::ClearCachedContent();
    mUpgradeMgr->ClearCachedContent();
    mLicenseMgr->ClearCachedContent();
    unk114.clear();
    unk11c.clear();
    unk124 = true;
}

void BandSongMgr::AddSongs(DataArray *a) {
    AddSongData(a, nullptr, kLocationRoot);
    ContentDone();
}

void BandSongMgr::AddRecentSong(int) {}

DECOMP_FORCEACTIVE(BandSongMgr, "mSongNameLookup.find(id) == mSongNameLookup.end()")

bool BandSongMgr::InqAvailableSongSources(std::set<Symbol> &sourceSet) {
    MILO_ASSERT(sourceSet.empty(), 0x5B8);
    std::vector<int> songs;
    GetRankedSongs(songs, false, false);
    FOREACH (it, songs) {
        BandSongMetadata *songData = (BandSongMetadata *)Data(*it);
        MILO_ASSERT(songData, 0x5C4);
        sourceSet.insert(songData->SourceSym());
    }
    return sourceSet.size();
}

int BandSongMgr::GetPartDifficulty(Symbol s1, Symbol s2) const {
    BandSongMetadata *songMetaData =
        (BandSongMetadata *)Data(GetSongIDFromShortName(s1, true));
    MILO_ASSERT(songMetaData, 0x5D6);
    float rank = songMetaData->Rank(s2);
    return RankTier(rank, s2);
}

int BandSongMgr::GetNumVocalParts(Symbol s) const {
    BandSongMetadata *songData =
        (BandSongMetadata *)Data(GetSongIDFromShortName(s, true));
    MILO_ASSERT(songData, 0x5E4);
    return songData->NumVocalParts();
}

int BandSongMgr::NumRankedSongs(TrackType ty, bool b2, Symbol s3) const {
    int num = 0;
    std::vector<int> songs;
    GetRankedSongs(songs, false, false);
    FOREACH (it, songs) {
        BandSongMetadata *data = (BandSongMetadata *)Data(*it);
        MILO_ASSERT(data, 0x5F3);
        if (b2) {
            if (data->HasVocalHarmony()) {
                goto checkSym;
            }
        } else {
            if (ty != kNumTrackTypes) {
                Symbol trackSym = TrackTypeToSym(ty);
                if (!data->HasPart(trackSym, false))
                    continue;
            }
        checkSym:
            if (s3 == gNullStr || data->SourceSym() == s3) {
                num++;
            }
        }
    }
    return num;
}

void BandSongMgr::SyncSharedSongs() { MILO_WARN("machine"); }

bool BandSongMgr::GetFakeSongsAllowed() { return sFakeSongsAllowed; }
void BandSongMgr::SetFakeSongsAllowed(bool b) { sFakeSongsAllowed = b; }

void BandSongMgr::AllowCacheWrite(bool b) {
    bool old = mSongCacheWriteAllowed;
    mSongCacheWriteAllowed = b;
    if (!old && b && SongCacheNeedsWrite() && TheSaveLoadMgr) {
        TheSaveLoadMgr->AutoSave();
    }
}

void BandSongMgr::CheatToggleMaxSongCount() {
    DataArray *cfg = SystemConfig(song_mgr);
    int max = cfg->FindInt(max_song_count);
    int max_debug = cfg->FindInt(max_song_count_debug);
    if (mMaxSongCount == max)
        max = max_debug;
    mMaxSongCount = max;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandSongMgr)
    HANDLE_EXPR(has_song, HasSong(_msg->Sym(2), true))
    HANDLE_EXPR(song_path, SongPath(_msg->Sym(2)))
    HANDLE_EXPR(song_file_path, SongFilePath(_msg->Sym(2), _msg->Str(3), false))
    HANDLE_EXPR(song_name, SongName(_msg->Sym(2)))
    HANDLE_EXPR(
        upgrade_midi_file, UpgradeMidiFile(GetSongIDFromShortName(_msg->Sym(2), true))
    )
    HANDLE_EXPR(get_meta_data, Data(GetSongIDFromShortName(_msg->Sym(2), true)))
    HANDLE_EXPR(rank_tier, RankTier(_msg->Float(2), _msg->Sym(3)))
    HANDLE_EXPR(
        rank_tier_for_song,
        RankTier(
            ((BandSongMetadata *)Data(GetSongIDFromShortName(_msg->Sym(2), true)))
                ->Rank(_msg->Sym(3)),
            _msg->Sym(3)
        )
    )
    HANDLE_EXPR(num_rank_tiers, NumRankTiers(_msg->Sym(2)))
    HANDLE_EXPR(rank_tier_token, RankTierToken(_msg->Int(2)))
    HANDLE_EXPR(num_vocal_parts, GetNumVocalParts(_msg->Sym(2)))
    HANDLE_ACTION(
        add_recent_song, AddRecentSong(GetSongIDFromShortName(_msg->Sym(2), true))
    )
    HANDLE_EXPR(
        part_plays_in_song,
        ((BandSongMetadata *)Data(GetSongIDFromShortName(_msg->Sym(2), true)))
            ->HasPart(_msg->Sym(3), false)
    )
    HANDLE_EXPR(
        mute_win_cues,
        ((BandSongMetadata *)Data(GetSongIDFromShortName(_msg->Sym(2), true)))
            ->MuteWinCues()
    )
    HANDLE_EXPR(midi_file, MidiFile(_msg->Sym(2)))
    HANDLE_EXPR(is_demo, IsDemo(_msg->Int(2)))
    HANDLE_EXPR(
        has_upgrade, GetUpgradeData(GetSongIDFromShortName(_msg->Sym(2), true)) != 0
    )
    HANDLE_EXPR(has_license, HasLicense(_msg->Sym(2)))
    HANDLE_EXPR(get_fake_songs_allowed, GetFakeSongsAllowed())
    HANDLE_ACTION(set_fake_songs_allowed, SetFakeSongsAllowed(_msg->Int(2)))
    HANDLE_ACTION(sync_shared_songs, SyncSharedSongs())
    HANDLE_EXPR(get_max_song_count, GetMaxSongCount())
    HANDLE_ACTION(cheat_toggle_max_song_count, CheatToggleMaxSongCount())
    HANDLE_SUPERCLASS(SongMgr)
    HANDLE_CHECK(0x6DF)
END_HANDLERS
#pragma pop
