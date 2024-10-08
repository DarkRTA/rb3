#include "meta_band/BandSongMetadata.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"

int BandSongMetadata::sBandSaveVer = 0x11;

void BandSongMetadata::InitBandSongMetadata(){
    mTitle = 0;
    mArtist = 0;
    mAlbum = 0;
    mAlbumTrackNum = -1;
    mGenre = rock;
    mAnimTempo = 0;
    mLengthMs = 0;
    mHasAlternatePath = 0;
    mBasePoints = 0;
    mIsBonus = 0;
    mIsFake = 0;
    mIsTutorial = 0;
    mMuteWinCues = 0;
    mRating = 1;
    mGuidePitchVolume = 0;
    mVocalTonicNote = -1;
    mSongKey = -1;
    mSongTonality = -1;
    mSongScrollSpeed = 0;
    mTuningOffsetCents = 0;
    mBandFailCue = 0;
    mVocalPercussionBank = 0;
    mDrumKitBank = 0;
    mHasAlbumArt = 0;
    mIsMasterRecording = 0;
    mIsTriFrame = 0;
    for(int i = 0; i < 6; i++) mRealGuitarTuning[i] = 0;
    for(int i = 0; i < 4; i++) mRealBassTuning[i] = 0;
    mHasDiscUpdate = 0;
}

BandSongMetadata::BandSongMetadata(BandSongMgr* mgr) : mSongMgr(mgr) {
    InitBandSongMetadata();
}

BandSongMetadata::BandSongMetadata(DataArray* main_arr, DataArray* backup_arr, bool onDisc, BandSongMgr* mgr) : SongMetadata(main_arr, backup_arr, onDisc), mSongMgr(mgr) {
    InitBandSongMetadata();
    DataArray* member_arr;
    if(FIND_WITH_BACKUP(name)){
        mTitle = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(artist)){
        mArtist = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(album_name)){
        mAlbum = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(album_track_number)){
        mAlbumTrackNum = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(year_released)){
        mDateReleased = DateTime(member_arr->Int(1), 1, 1, 0, 0, 0);
    }
    if(FIND_WITH_BACKUP(year_recorded)){
        mDateRecorded = DateTime(member_arr->Int(1), 1, 1, 0, 0, 0);
    }
    else mDateRecorded = mDateReleased;
    if(FIND_WITH_BACKUP(genre)){
        mGenre = member_arr->Sym(1);
    }
    if(FIND_WITH_BACKUP(anim_tempo)){
        mAnimTempo = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(vocal_gender)){
        mVocalGender = member_arr->Sym(1);
    }
    if(FIND_WITH_BACKUP(song_length)){
        mLengthMs = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(alternate_path)){
        mHasAlternatePath = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(base_points)){
        mBasePoints = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(bonus)){
        mIsBonus = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(fake)){
        bool ret = false;
        DataNode& node = CONST_ARRAY(member_arr)->Node(1);
        if(node.Type() == kDataInt){
            if(CONST_ARRAY(member_arr)->Node(1).LiteralInt(0)) ret = true;
        }
        mIsFake = ret;
    }
    if(FIND_WITH_BACKUP(tutorial)){
        mIsTutorial = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(mute_win_cues)){
        mMuteWinCues = true;
    }
    if(FIND_WITH_BACKUP(rank)){
        for(int i = 1; i < member_arr->Size(); i++){
            DataArray* arr = member_arr->Array(i);
            mRanks[arr->Sym(0)] = arr->Float(1);
        }
    }
    if(FIND_WITH_BACKUP(rating)){
        mRating = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(guide_pitch_volume)){
        mGuidePitchVolume = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(vocal_tonic_note)){
        mVocalTonicNote = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(song_key)){
        mSongKey = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(song_tonality)){
        mSongTonality = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(song_scroll_speed)){
        mSongScrollSpeed = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(tuning_offset_cents)){
        mTuningOffsetCents = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(bank)){
        mVocalPercussionBank = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(drum_bank)){
        mDrumKitBank = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(band_fail_cue)){
        mBandFailCue = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(album_art)){
        mHasAlbumArt = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(master)){
        mIsMasterRecording = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(tri_frame)){
        mIsTriFrame = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(real_guitar_tuning)){
        for(int i = 0; i < 6; i++){
            DataArray* arr = member_arr->Array(1);
            mRealGuitarTuning[i] = arr->Int(i);
        }
    }
    if(FIND_WITH_BACKUP(real_bass_tuning)){
        for(int i = 0; i < 4; i++){
            DataArray* arr = member_arr->Array(1);
            mRealBassTuning[i] = arr->Int(i);
        }
    }
    if(FIND_WITH_BACKUP(extra_authoring)){
        mHasDiscUpdate = member_arr->Contains(disc_update);
    }
    if(FIND_WITH_BACKUP(solo)){
        DataArray* arr = member_arr->Array(1);
        for(int i = 0; i < arr->Size(); i++){
            Symbol solosym = arr->Sym(i);
            if(solosym != vocals){
                if(solosym == vocal_percussion) solosym = vocals;
                mSolos.push_back(solosym);
            }
        }
    }
    bool islatin1 = false;
    if(FIND_WITH_BACKUP(encoding)){
        islatin1 = member_arr->Sym(1) == latin1;
    }
    if(islatin1){
        char buf[0x100];
        ASCIItoUTF8(buf, 0x100, mTitle.c_str());
        mTitle = buf;
        ASCIItoUTF8(buf, 0x100, mArtist.c_str());
        mArtist = buf;
        ASCIItoUTF8(buf, 0x100, mAlbum.c_str());
        mAlbum = buf;
    }
}

const char* BandSongMetadata::Title() const { return mTitle.c_str(); }
const char* BandSongMetadata::Artist() const { return mArtist.c_str(); }
const char* BandSongMetadata::Album() const { return mAlbum.c_str(); }
int BandSongMetadata::AlbumTrackNum() const { return mAlbumTrackNum; }
Symbol BandSongMetadata::Genre() const { return mGenre; }
int BandSongMetadata::LengthMs() const { return mLengthMs; }
bool BandSongMetadata::HasAlternatePath() const { return mHasAlternatePath; }
bool BandSongMetadata::MuteWinCues() const { return mMuteWinCues; }
const std::map<Symbol, float>& BandSongMetadata::Ranks() const { return mRanks; }
int BandSongMetadata::Rating() const { return mRating; }
float BandSongMetadata::GuidePitchVolume() const { return mGuidePitchVolume; }
int BandSongMetadata::VocalTonicNote() const { return mVocalTonicNote; }

int BandSongMetadata::SongKey() const {
    return mSongKey >= 0 ? mSongKey : mVocalTonicNote;
}

int BandSongMetadata::SongTonality() const { return mSongTonality; }
float BandSongMetadata::ScrollSpeed() const { return mSongScrollSpeed; }
float BandSongMetadata::TuningOffset() const { return mTuningOffsetCents; }
Symbol BandSongMetadata::VocalPercussionBank() const { return mVocalPercussionBank; }
Symbol BandSongMetadata::DrumKitBank() const { return mDrumKitBank; }
bool BandSongMetadata::HasAlbumArt() const { return mHasAlbumArt; }
bool BandSongMetadata::IsMasterRecording() const { return mIsMasterRecording; }
Symbol BandSongMetadata::BandFailCue() const { return mBandFailCue; }

Symbol BandSongMetadata::Decade() const {
    int year = (mDateReleased.Year() / 10) - 1900;
    return MakeString("the%is", year);
}

bool BandSongMetadata::HasVocalHarmony() const {
    return HasPart(vocals, false) && SongMetadata::NumVocalParts() > 1;
}

bool BandSongMetadata::IsPrivate() const {
    return mIsTutorial || (mIsFake && !BandSongMgr::GetFakeSongsAllowed());
}

bool BandSongMetadata::IsRanked() const { return !mRanks.empty(); }

bool BandSongMetadata::IsVersionOK() const {
    bool ret = false;
    if(mVersion <= 0x1E) ret = true;
    return ret;
}

Symbol BandSongMetadata::LengthSym() const {
    DataArray* cfg = SystemConfig(song_select, song_lengths);
    for(int i = 1; i < cfg->Size(); i++){
        DataArray* arr = cfg->Array(i);
        if(arr->Size() == 1 || mLengthMs <= arr->Int(1)){
            return arr->Sym(0);
        }
    }
    MILO_FAIL("No song_length definitions!");
    return gNullStr;
}

Symbol BandSongMetadata::RatingSym() const {
    return MakeString("rating_%i", (int)mRating);
}

Symbol BandSongMetadata::SourceSym() const {
    bool official_dlc = GameOrigin() == rb3_dlc || GameOrigin() == rb1_dlc;
    Symbol ret = dlc;
    if(!official_dlc){
        Symbol orig = GameOrigin();
        ret = ugc;
        if(orig != ugc_plus) ret = GameOrigin();
    }
    return ret;
}

Symbol BandSongMetadata::VocalPartsSym() const {
    return MakeString("vocal_parts_%i", NumVocalParts());
}

Symbol BandSongMetadata::HasProGuitarSym() const {
    bool haspropart = HasPart(real_guitar, false) || HasPart(real_bass, false);
    return haspropart ? has_part_yes : has_part_no;
}

bool BandSongMetadata::HasKeys() const {
    return HasPart(keys, false) || HasPart(real_keys, false);
}

bool BandSongMetadata::HasGuitar() const {
    return HasPart(guitar, false) || HasPart(real_guitar, false);
}

bool BandSongMetadata::HasBass() const {
    return HasPart(bass, false) || HasPart(real_bass, false);
}

Symbol BandSongMetadata::HasKeysSym() const {
    bool haskeypart = HasPart(keys, false) || HasPart(real_keys, false);
    return haskeypart ? has_part_yes : has_part_no;
}

bool BandSongMetadata::HasSolo(Symbol s) const {
    if(s == real_guitar) s = guitar;
    else if(s == real_bass) s = bass;
    else if(s == real_keys) s = keys;
    else if(s == real_drum) s = drum;
    return std::find(mSolos.begin(), mSolos.end(), s) != mSolos.end();
}

Symbol BandSongMetadata::HasSoloSym(Symbol s) const {
    return HasSolo(s) ? has_part_yes : has_part_no;
}

bool BandSongMetadata::IsUGC() const {
    return GameOrigin() == ugc || GameOrigin() == ugc_plus;
}

const char* BandSongMetadata::MidiUpdate() const {
    if(mHasDiscUpdate) return MakeString("./songs/updates/%s/%s_update.mid", mShortName, mShortName);
    else return 0;
}

bool BandSongMetadata::IsDownload() const {
    return GameOrigin() != rb3;
}

void BandSongMetadata::Save(BinStream& bs){
    bs << sBandSaveVer;
    SongMetadata::Save(bs);
    bs << mTitle;
    bs << mArtist;
    bs << mAlbum;
    bs << mAlbumTrackNum;
    bs << mDateRecorded;
    bs << mDateReleased;
    bs << mGenre;
    bs << mBasePoints;
    bs << mIsBonus;
    bs << mIsFake;
    bs << mIsTutorial;
    bs << mMuteWinCues;
    bs << mRanks;
    bs << mRating;
    bs << mGuidePitchVolume;
    bs << mSongScrollSpeed;
    bs << mTuningOffsetCents;
    bs << mVocalPercussionBank;
    bs << mDrumKitBank;
    bs << mVocalTonicNote;
    bs << mSongKey;
    bs << mSongTonality;
    bs << mLengthMs;
    bs << mHasAlbumArt;
    bs << mIsMasterRecording;
    bs << mHasAlternatePath;
    bs << mIsTriFrame;
    bs << mAnimTempo;
    bs << mVocalGender;
    for(int i = 0; i < 6; i++) bs << mRealGuitarTuning[i];
    for(int i = 0; i < 4; i++) bs << mRealBassTuning[i];
    bs << mHasDiscUpdate;
    bs << mSolos;
}

void BandSongMetadata::Load(BinStream& bs){
    int rev;
    bs >> rev;
    SongMetadata::Load(bs);
    bs >> mTitle;
    bs >> mArtist;
    bs >> mAlbum;
    bs >> mAlbumTrackNum;
    bs >> mDateRecorded;
    bs >> mDateReleased;
    bs >> mGenre;
    if(rev < 0xD){ String s; bs >> s; }
    bs >> mBasePoints;
    bs >> mIsBonus;
    bs >> mIsFake;
    bs >> mIsTutorial;
    bs >> mMuteWinCues;
    bs >> mRanks;
    bs >> mRating;
    if(rev < 0xC){ short s; bs >> s; }
    bs >> mGuidePitchVolume;
    if(rev < 0xF){ String s; bs >> s; }
    bs >> mSongScrollSpeed;
    bs >> mTuningOffsetCents;
    bs >> mVocalPercussionBank;
    if(rev >= 9) bs >> mDrumKitBank;
    if(rev >= 1) bs >> mVocalTonicNote;
    if(rev >= 11){
        bs >> mSongKey;
        bs >> mSongTonality;
    }
    if(rev - 2U <= 11){
        std::vector<std::map<Symbol, String> > gross;
        bs >> gross;
    }
    if(rev >= 3) bs >> mLengthMs;
    if(rev >= 4){
        bs >> mHasAlbumArt;
        bs >> mIsMasterRecording;
    }
    if(rev >= 5){
        bs >> mHasAlternatePath;
        if(rev < 8){
            bool b, c; bs >> b; bs >> c;
        }
        bs >> mIsTriFrame;
    }
    if(rev >= 6) bs >> mAnimTempo;
    if(rev >= 16) bs >> mVocalGender;
    if(rev >= 7){
        for(int i = 0; i < 6; i++) bs >> mRealGuitarTuning[i];
        for(int i = 0; i < 4; i++) bs >> mRealBassTuning[i];
    }
    if(rev >= 10) bs >> mHasDiscUpdate;
    if(rev >= 0x11) bs >> mSolos;
}