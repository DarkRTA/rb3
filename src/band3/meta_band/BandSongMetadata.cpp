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