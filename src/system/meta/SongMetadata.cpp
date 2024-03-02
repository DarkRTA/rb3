#include "meta/SongMetadata.h"
#include "utl/Symbols.h"
#include "os/Debug.h"

void SongMetadata::InitSongMetadata(){
    mID = 0;
    mIsOnDisc = false;
    mGameOrigin = rb3;
    mPreviewStartTime = 0.0f;
    mPreviewEndTime = 0.0f;
    mVersion = -1;
    mSongInfo = 0;
    mShortName = gNullStr;
    mSongVocalsBlock = 0;
}

SongMetadata::SongMetadata(){
    InitSongMetadata();
}

#define GET_MEMBER_ARRAY(sym) \
    member_exists = true; \
    existing_member_array = arr1->FindArray(sym, false); \
    if(!existing_member_array){ \
        bool exists_in_missing = false; \
        if(arr2){ \
            existing_member_array = arr2->FindArray(sym, false); \
            if(existing_member_array) exists_in_missing = true; \
        } \
        if(!exists_in_missing) member_exists = false; \
    }


SongMetadata::SongMetadata(DataArray* arr1, DataArray* arr2, bool onDisc) : mShortName(), mGameOrigin() {
    InitSongMetadata();
    mIsOnDisc = onDisc;
    bool member_exists;
    DataArray* existing_member_array;

    GET_MEMBER_ARRAY(song_id);
    if(member_exists) mID = existing_member_array->Int(1);
    else MILO_FAIL("song data for song '%s' has no song_id", arr1->Sym(0).Str());

    GET_MEMBER_ARRAY(game_origin);
    if(member_exists) mGameOrigin = existing_member_array->Sym(1);
    if(mGameOrigin == rb2){
        GET_MEMBER_ARRAY(ugc);
        if(member_exists){
            if(existing_member_array->Int(1) != 0){
                mGameOrigin = ugc;
            }
        }
    }

    GET_MEMBER_ARRAY(preview);
    if(member_exists){
        mPreviewStartTime = existing_member_array->Float(1);
        mPreviewEndTime = existing_member_array->Float(2);
    }

    GET_MEMBER_ARRAY(version);
    if(member_exists){
        mVersion = existing_member_array->Int(1);
    }

    mShortName = arr1->Sym(0);
    existing_member_array = arr1->FindArray(song, false);
    DataArray* song_array = (!arr2) ? 0 : arr2->FindArray(song, false);

    if(existing_member_array)
        mSongInfo = new DataArraySongInfo(existing_member_array, song_array, mShortName);
    else if(song_array)
        mSongInfo = new DataArraySongInfo(song_array, 0, mShortName);
    else MILO_FAIL("song data for song '%s' has no 'song' block", arr1->Sym(0).Str());

}

SongMetadata::~SongMetadata(){
    delete mSongInfo;
}

int SongMetadata::ID() const {
    return mID;
}

bool SongMetadata::IsOnDisc() const {
    return mIsOnDisc;
}

Symbol SongMetadata::GameOrigin() const {
    return mGameOrigin;
}

void SongMetadata::PreviewTimes(float& start, float& end) const {
    start = mPreviewStartTime;
    end = mPreviewEndTime;
}

DataArraySongInfo* SongMetadata::SongBlock() const {
    return mSongInfo;
}

int SongMetadata::NumVocalParts() const {
    MILO_ASSERT(mSongInfo, 0x79);
    return mSongInfo->GetNumVocalParts();
}
