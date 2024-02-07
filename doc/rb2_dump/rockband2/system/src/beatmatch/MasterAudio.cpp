/*
    Compile unit: C:\rockband2\system\src\beatmatch\MasterAudio.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802E4DDC -> 0x802EA838
*/
static int kMaxSlots; // size: 0x4, address: 0x80A46C60
static class Symbol slip; // size: 0x4, address: 0x80A505DC
static class Symbol unmute; // size: 0x4, address: 0x80A505E4
// Range: 0x802E4DDC -> 0x802E4EA8
enum AudioStyle ParseStyle(class Symbol & style /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Symbol unmute;
    // -> static class Symbol slip;
}

class Submix {
    // total size: 0x8
    class Symbol mName; // offset 0x0, size 0x4
    class SlotChannelMapping * mMapping; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Submix * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Submix * * _M_start; // offset 0x0, size 0x4
    class Submix * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SubmixCollection {
    // total size: 0xC
    class vector mSubmixes; // offset 0x0, size 0xC
};
class PitchMucker {
    // total size: 0x14
    unsigned char mToggle; // offset 0x0, size 0x1
    float mMaxPitch; // offset 0x4, size 0x4
    float mMinPitch; // offset 0x8, size 0x4
    unsigned int mFrames; // offset 0xC, size 0x4
    unsigned int mPeriod; // offset 0x10, size 0x4
};
// Range: 0x802E4EA8 -> 0x802E5B14
void * MasterAudio::MasterAudio(class MasterAudio * const this /* r27 */, class DataArray * cfg /* r28 */, int num_players /* r29 */, class BeatMaster * beat_master /* r30 */, class SongData * song_data /* r26 */) {
    // Local variables
    float atten_db; // f0
    float common_atten_db; // f0
    float background_atten_db; // f0
    float practice_atten_db; // r1+0x90
    float unplayed_atten_db; // r1+0x8C
    float cue_atten_db; // r1+0x88
    float remote_atten_db; // r1+0x84
    class Symbol style; // r1+0x80

    // References
    // -> const char * gNullStr;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__11MasterAudio;
    // -> struct [anonymous] __vt__13BeatMatchSink;
    // -> struct [anonymous] __vt__14BeatMasterSink;
}

// Range: 0x802E5B14 -> 0x802E5F54
void * MasterAudio::~MasterAudio(class MasterAudio * const this /* r30 */) {
    // Local variables
    class ChannelData * * cit; // r29
    class TrackData * * tit; // r29
    int i; // r29

    // References
    // -> struct [anonymous] __vt__11MasterAudio;
}

// Range: 0x802E5F54 -> 0x802E6158
void MasterAudio::Load(class MasterAudio * const this /* r30 */, class DataArray * data /* r27 */, class PlayerTrackConfigList * player_track_config_list /* r31 */) {
    // Local variables
    int t; // r29
    int p; // r27

    // References
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E6158 -> 0x802E65F8
void MasterAudio::CopyTrack(class MasterAudio * const this /* r21 */, int track /* r24 */, int player /* r22 */, int slot /* r23 */) {
    // Local variables
    class TrackData * track_data; // r28
    int num_channels; // r30
    class list channels_to_dup; // r1+0x70
    int num_new_channels; // r27
    struct _List_iterator it; // r1+0x40
    int i; // r26
    int old_channel; // r25
    int new_channel; // r24
    class ChannelData * channel_data; // r1+0x3C
    struct ExtraTrackInfo extra_track_info; // r1+0x78
}

// Range: 0x802E65F8 -> 0x802E6734
void MasterAudio::CreateSecondaryTrack(class MasterAudio * const this /* r29 */, int player /* r30 */, int slot /* r31 */) {
    // Local variables
    class list channels; // r1+0x30
    struct _List_iterator it; // r1+0x18
    struct ExtraTrackInfo extra_track_info; // r1+0x38
}

// Range: 0x802E6734 -> 0x802E683C
void MasterAudio::UpdateFocusVolumes(class MasterAudio * const this /* r30 */) {
    // Local variables
    float bg_volume; // f31
    int num_captured_tracks; // r0
    int i; // r31
    float atten; // f30
}

// Range: 0x802E683C -> 0x802E6898
int MasterAudio::NumCapturedTracks() {
    // Local variables
    int num_captured_tracks; // r5
    int i; // r6
}

// Range: 0x802E6898 -> 0x802E68D0
float MasterAudio::NumTracksToVolume() {}

// Range: 0x802E68D0 -> 0x802E6C84
void MasterAudio::SetupChannels(class MasterAudio * const this /* r22 */, class DataArray * data /* r20 */, class DataArray * tracks /* r23 */) {
    // Local variables
    class DataArray * pans; // r30
    class DataArray * vols; // r29
    class DataArray * cores; // r28
    class DataArray * crowd_channels; // r27
    class DataArray * synth; // r20
    int maxStreams; // r26
    int nMuted; // r25
    int ch; // r24
    unsigned char is_play_track; // r0
    class FaderGroup & faders; // r20
    unsigned char is_crowd_channel; // r0
    float secureVol; // f31
    class ChannelData * channel_data; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E6C84 -> 0x802E7130
void MasterAudio::SetupTracks(class MasterAudio * const this /* r23 */, class DataArray * data /* r20 */, class DataArray * tracks /* r24 */, class PlayerTrackConfigList * player_track_config_list /* r25 */) {
    // Local variables
    class DataArray * methods; // r29
    class DataArray * method_array; // r26
    int t; // r28
    class Symbol instrument; // r1+0x34
    struct ExtraTrackInfo extra_track_info; // r1+0x44
    enum AudioStyle method; // r26
    int player; // r27
    int slot; // r26
    void (MasterAudio::* setup_func)(void *, void *, int, int, int, struct ExtraTrackInfo &); // r1+0x38
    class DataNode & node; // r0
    class DataArray * channels; // r30
    int c; // r22
    class DataArray * channels2; // r21
    int c2; // r20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E7130 -> 0x802E7140
void MasterAudio::FillChannelList() {}

// Range: 0x802E7140 -> 0x802E7290
void MasterAudio::GetExtraTrackInfo(class MasterAudio * const this /* r30 */, class PlayerTrackConfigList * player_track_config_list /* r27 */, class Symbol & instrument /* r28 */, struct ExtraTrackInfo & extra_track_info /* r31 */) {
    // Local variables
    int instrument_player; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x802E7290 -> 0x802E74B8
void MasterAudio::SetupTrackChannel(class MasterAudio * const this /* r29 */, int channel /* r30 */, struct ExtraTrackInfo & extra_track_info /* r31 */) {
    // Local variables
    float stereo_scale; // f31
    float stereo_center; // f30
    float max_center; // f0
    float min_center; // f3
    float spread; // f1
    class ChannelData * channel_data; // r27
    class FaderGroup & faders; // r27
}

// Range: 0x802E74B8 -> 0x802E75DC
void MasterAudio::SetupBackgroundChannel(class MasterAudio * const this /* r27 */, int channel /* r28 */, struct ExtraTrackInfo & extra_track_info /* r29 */) {
    // Local variables
    class FaderGroup & faders; // r31
    class ChannelData * channel_data; // r30
}

// Range: 0x802E75DC -> 0x802E762C
void MasterAudio::CheckDuckableChannel(class MasterAudio * const this /* r31 */) {
    // Local variables
    class FaderGroup & faders; // r0
}

// Range: 0x802E762C -> 0x802E7680
unsigned char MasterAudio::Fail() {}

// Range: 0x802E7680 -> 0x802E76E4
unsigned char MasterAudio::IsReady(class MasterAudio * const this /* r30 */) {}

// Range: 0x802E76E4 -> 0x802E7738
unsigned char MasterAudio::IsFinished() {}

// Range: 0x802E7738 -> 0x802E778C
unsigned char MasterAudio::IsPlaying() {}

// Range: 0x802E778C -> 0x802E783C
void MasterAudio::Play(class MasterAudio * const this /* r30 */) {
    // Local variables
    int c; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E783C -> 0x802E7A50
void MasterAudio::Poll(class MasterAudio * const this /* r30 */) {
    // Local variables
    class ChannelData * * it; // r29
    float now; // f0
    int i; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E7A50 -> 0x802E7B10
void MasterAudio::Jump(class MasterAudio * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    int track; // r31
}

// Range: 0x802E7B10 -> 0x802E7B20
void MasterAudio::ToggleMuteMaster() {}

// Range: 0x802E7B20 -> 0x802E7B28
void MasterAudio::SetMuteMaster() {}

// Range: 0x802E7B28 -> 0x802E7B30
void MasterAudio::SetMasterVolume() {}

// Range: 0x802E7B30 -> 0x802E7B54
void MasterAudio::UpdateMasterFader(class MasterAudio * const this /* r4 */) {}

// Range: 0x802E7B54 -> 0x802E7B5C
void MasterAudio::SetForegroundVolume() {}

// Range: 0x802E7B5C -> 0x802E7B64
void MasterAudio::SetBackgroundVolume() {}

// Range: 0x802E7B64 -> 0x802E7BD8
void MasterAudio::SetStereo(class MasterAudio * const this /* r29 */, unsigned char on /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802E7BD8 -> 0x802E7CAC
void MasterAudio::SetSpeed(class MasterAudio * const this /* r31 */, float speed /* f31 */) {
    // Local variables
    class list channels; // r1+0x28
    struct _List_iterator it; // r1+0x10
}

// Range: 0x802E7CAC -> 0x802E7CB8
void MasterAudio::SetVocalDuckFader() {}

// Range: 0x802E7CB8 -> 0x802E7CC4
void MasterAudio::SetVocalCueFader() {}

// Range: 0x802E7CC4 -> 0x802E7CD0
void MasterAudio::SetVocalFailFader() {}

// Range: 0x802E7CD0 -> 0x802E7CDC
void MasterAudio::SetCrowdFader() {}

// Range: 0x802E7CDC -> 0x802E7CE8
void MasterAudio::SetBaseCrowdFader() {}

// Range: 0x802E7CE8 -> 0x802E7DB4
void MasterAudio::ResetSlipTrack(class MasterAudio * const this /* r29 */, int track /* r30 */, unsigned char bForce /* r31 */) {
    // Local variables
    class list channels; // r1+0x28
    struct _List_iterator it; // r1+0x10
}

// Range: 0x802E7DB4 -> 0x802E7ED8
void MasterAudio::SetFX(class MasterAudio * const this /* r29 */, int track /* r28 */, enum FXCore core /* r30 */, unsigned char onoff /* r31 */) {
    // Local variables
    class list channels; // r1+0x28
    struct _List_iterator it; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E7ED8 -> 0x802E7EFC
float MasterAudio::GetTime() {}

// Range: 0x802E7EFC -> 0x802E7F78
void MasterAudio::SetPaused(class MasterAudio * const this /* r31 */) {}

// Range: 0x802E7F78 -> 0x802E7F80
void MasterAudio::SetMuckWithPitch() {}

// Range: 0x802E7F80 -> 0x802E7FF8
void MasterAudio::SetRemoteTrack(class MasterAudio * const this /* r30 */, int track /* r31 */) {}

static class Symbol mute; // size: 0x4, address: 0x80A505EC
// Range: 0x802E7FF8 -> 0x802E8224
void MasterAudio::SetTrackFader(class MasterAudio * const this /* r27 */, int track /* r28 */, int slot /* r29 */, class Symbol & fader /* r30 */, float val /* f30 */, float duration /* f31 */) {
    // Local variables
    class list channels; // r1+0x40
    struct _List_iterator it; // r1+0x2C
    int ch; // r0
    class Fader * f; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol mute;
}

// Range: 0x802E8224 -> 0x802E8300
void MasterAudio::Hit(class MasterAudio * const this /* r27 */, int track /* r28 */, float ms /* f31 */, int gem_id /* r29 */) {
    // Local variables
    int slot; // r31
    class TrackData * track_data; // r30
    const class GameGemList & gem_list; // r30
    float nearest_chunk_ms; // f31
    float chunk_end_ms; // f2
}

// Range: 0x802E8300 -> 0x802E8498
void MasterAudio::ReleaseGem(class MasterAudio * const this /* r30 */, int track /* r31 */, float ms /* f30 */, int gem_id /* r27 */, float delta /* f31 */) {
    // Local variables
    class GameGem & gem; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E8498 -> 0x802E8518
void MasterAudio::Miss(class MasterAudio * const this /* r29 */, int track /* r30 */, float ms /* f31 */) {
    // Local variables
    int gem_slot; // r31
}

// Range: 0x802E8518 -> 0x802E85C4
void MasterAudio::Pass(class MasterAudio * const this /* r28 */, int track /* r29 */, float ms /* f31 */) {
    // Local variables
    int slot; // r30
}

// Range: 0x802E85C4 -> 0x802E85F4
void MasterAudio::Ignore() {}

// Range: 0x802E85F4 -> 0x802E860C
void MasterAudio::PlayGem() {}

// Range: 0x802E860C -> 0x802E86C8
void MasterAudio::SeeGem(class MasterAudio * const this /* r29 */, int track /* r30 */) {
    // Local variables
    class TrackData * track_data; // r6
    int slot; // r31
}

// Range: 0x802E86C8 -> 0x802E86EC
void MasterAudio::SetHeadToHead(class MasterAudio * const this /* r5 */) {}

// Range: 0x802E86EC -> 0x802E86F8
void MasterAudio::MuteAllTracks() {}

// Range: 0x802E86F8 -> 0x802E8700
void MasterAudio::AddFaders() {}

// Range: 0x802E8700 -> 0x802E8730
void MasterAudio::DontPlay() {}

// Range: 0x802E8730 -> 0x802E8804
void MasterAudio::PlayChunk(class MasterAudio * const this /* r30 */, int track /* r31 */, float start_ms /* f30 */, float end_ms /* f31 */) {
    // Local variables
    class list channels; // r1+0x28
    struct _List_iterator it; // r1+0x10
}

// Range: 0x802E8804 -> 0x802E881C
unsigned char MasterAudio::IsSucceeding(int track /* r0 */) {}

// Range: 0x802E881C -> 0x802E8874
void MasterAudio::SetNonmutable(class MasterAudio * const this /* r30 */, int track /* r31 */) {}

// Range: 0x802E8874 -> 0x802E8884
void MasterAudio::MuteTrack() {}

// Range: 0x802E8884 -> 0x802E8950
void MasterAudio::MuteTrack(class MasterAudio * const this /* r29 */, int track /* r30 */, int slot /* r31 */, float fadeMs /* f30 */) {
    // Local variables
    float vol; // f31
}

static class Symbol mute; // size: 0x4, address: 0x80A505F4
// Range: 0x802E8950 -> 0x802E89D8
void MasterAudio::UnmuteTrack(class MasterAudio * const this /* r29 */, int track /* r30 */, int slot /* r31 */) {
    // References
    // -> static class Symbol mute;
}

// Range: 0x802E89D8 -> 0x802E8A40
void MasterAudio::UnmuteAllTracks(class MasterAudio * const this /* r30 */) {
    // Local variables
    int track; // r31
}

// Range: 0x802E8A40 -> 0x802E8AE0
void MasterAudio::MuteAllTracks(class MasterAudio * const this /* r27 */, enum DontPlayReason reason /* r28 */, float fadeMs /* f31 */) {
    // Local variables
    int track; // r29
}

// Range: 0x802E8AE0 -> 0x802E8B54
void MasterAudio::FadeOutDrums(class MasterAudio * const this /* r30 */, int track /* r31 */) {}

// Range: 0x802E8B54 -> 0x802E8BC8
void MasterAudio::RestoreDrums(class MasterAudio * const this /* r30 */, int track /* r31 */) {}

// Range: 0x802E8BC8 -> 0x802E8C80
void MasterAudio::Capturing(class MasterAudio * const this /* r29 */, int track /* r31 */, unsigned char captured /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E8C80 -> 0x802E8D00
void MasterAudio::ChangeTrack(class MasterAudio * const this /* r29 */, int player /* r30 */, int new_track /* r31 */) {}

// Range: 0x802E8D00 -> 0x802E8E14
void MasterAudio::SetLevels(class MasterAudio * const this /* r29 */, class DataArray * cfg /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802E8E14 -> 0x802E8E60
void MasterAudio::ActivePlayersChanged(class MasterAudio * const this /* r5 */) {}

// Range: 0x802E8E60 -> 0x802E8ED4
void MasterAudio::HandleSubmix(class MasterAudio * const this /* r29 */, const char * description /* r30 */) {}

// Range: 0x802E8ED4 -> 0x802E8F24
void MasterAudio::SetButtonMashingMode(unsigned char onoff /* r29 */) {}

// Range: 0x802E8F24 -> 0x802E8FF0
void MasterAudio::FillSwing(class MasterAudio * const this /* r28 */, int track /* r29 */) {}

// Range: 0x802E8FF0 -> 0x802E90F8
int MasterAudio::GemSlot(int gem_id /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E90F8 -> 0x802E9314
void MasterAudio::PrintFaders(class MasterAudio * const this /* r30 */) {
    // Local variables
    int ch; // r28

    // References
    // -> class Debug TheDebug;
}

class SlipTrack {
    // total size: 0x1C
    class Stream * mStream; // offset 0x0, size 0x4
    class vector mChannels; // offset 0x4, size 0xC
    float mOffMs; // offset 0x10, size 0x4
    float mMaxSlip; // offset 0x14, size 0x4
    unsigned char mOn; // offset 0x18, size 0x1
};
class ChannelData {
    // total size: 0x2C
    class Stream * mStream; // offset 0x0, size 0x4
    int mChannel; // offset 0x4, size 0x4
    class SlipTrack * mSlipTrack; // offset 0x8, size 0x4
    class Fader * mBaseFader; // offset 0xC, size 0x4
    unsigned char mIsTrackChannel; // offset 0x10, size 0x1
    float mPan; // offset 0x14, size 0x4
    float mOriginalPan; // offset 0x18, size 0x4
    enum FXCore mCore; // offset 0x1C, size 0x4
    float mOverallSpeed; // offset 0x20, size 0x4
    float mSpeed; // offset 0x24, size 0x4
    unsigned char mDirty; // offset 0x28, size 0x1
};
// Range: 0x802E9314 -> 0x802E941C
void * ChannelData::ChannelData(class ChannelData * const this /* r28 */, class Stream * song_stream /* r29 */, int channel /* r30 */, float vol /* f31 */) {}

// Range: 0x802E941C -> 0x802E947C
class ChannelData * ChannelData::Copy(class ChannelData * const this /* r30 */, int new_channel /* r31 */) {}

// Range: 0x802E947C -> 0x802E9528
void * ChannelData::~ChannelData(class ChannelData * const this /* r29 */) {}

// Range: 0x802E9528 -> 0x802E95E8
void ChannelData::SetPlayable(class ChannelData * const this /* r30 */) {}

// Range: 0x802E95E8 -> 0x802E95FC
void ChannelData::ForceOn() {}

// Range: 0x802E95FC -> 0x802E9668
void ChannelData::Reset(class ChannelData * const this /* r31 */) {}

// Range: 0x802E9668 -> 0x802E967C
void ChannelData::Poll() {}

// Range: 0x802E967C -> 0x802E9720
void ChannelData::SetSlipTrackSpeed(class ChannelData * const this /* r31 */, float speed /* f31 */) {
    // Local variables
    float real_speed; // f0
}

// Range: 0x802E9720 -> 0x802E974C
void ChannelData::SetFX(class ChannelData * const this /* r6 */) {}

// Range: 0x802E974C -> 0x802E977C
void ChannelData::SetStereo(class ChannelData * const this /* r5 */, unsigned char stereo /* r0 */) {}

// Range: 0x802E977C -> 0x802E9804
void ChannelData::PlayChunk(class ChannelData * const this /* r31 */, float start_ms /* f30 */, float end_ms /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E9804 -> 0x802E9810
float ChannelData::GetFaderVal() {}

// Range: 0x802E9810 -> 0x802E9818
void ChannelData::SetFaderVal() {}

// Range: 0x802E9818 -> 0x802E983C
void ChannelData::SetPan(class ChannelData * const this /* r4 */) {}

// Range: 0x802E983C -> 0x802E9844
float ChannelData::GetPan() {}

class TrackData {
    // total size: 0x58
    unsigned char mSucceeding; // offset 0x0, size 0x1
    class vector mSucceedingVec; // offset 0x4, size 0x14
    class vector mLastGemTimes; // offset 0x18, size 0xC
    unsigned char mMultiSlot; // offset 0x24, size 0x1
    int mLastPlayedGem; // offset 0x28, size 0x4
    unsigned char mCaptured; // offset 0x2C, size 0x1
    class SlotChannelMapping * mChannelMapping; // offset 0x30, size 0x4
    class SubmixCollection * mSubmixes; // offset 0x34, size 0x4
    enum AudioStyle mAudioStyle; // offset 0x38, size 0x4
    int mPlayer; // offset 0x3C, size 0x4
    unsigned char mIndieSlots; // offset 0x40, size 0x1
    unsigned char mNonmutable; // offset 0x41, size 0x1
    unsigned char mButtonMashingMode; // offset 0x42, size 0x1
    float mLastMashTime; // offset 0x44, size 0x4
    unsigned char mInFill; // offset 0x48, size 0x1
    class DataArray * mOriginalChannelsArray; // offset 0x4C, size 0x4
    int mChannelsIndex; // offset 0x50, size 0x4
    int mCopiedTo; // offset 0x54, size 0x4
};
// Range: 0x802E9844 -> 0x802E98A0
void * TrackData::TrackData(class TrackData * const this /* r31 */) {}

// Range: 0x802E98A0 -> 0x802E9914
void * TrackData::TrackData(class TrackData * const this /* r30 */, class DataArray * channels /* r31 */) {}

// Range: 0x802E9914 -> 0x802E9968
void * TrackData::TrackData(class TrackData * const this /* r31 */) {}

// Range: 0x802E9968 -> 0x802E9A44
void TrackData::Init(class TrackData * const this /* r28 */, enum AudioStyle audio_style /* r29 */, unsigned char indie_slots /* r30 */) {
    // References
    // -> static int kMaxSlots;
}

class SlotChannelMapping {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
// Range: 0x802E9A44 -> 0x802E9A74
unsigned char TrackData::HasMoreChannelsAvailable() {}

// Range: 0x802E9A74 -> 0x802E9B28
unsigned char TrackData::Playable(const class TrackData * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x802E9B28 -> 0x802E9C08
void * TrackData::~TrackData(class TrackData * const this /* r30 */) {}

// Range: 0x802E9C08 -> 0x802E9C7C
class TrackData * TrackData::CreateSecondaryTrack(class TrackData * const this /* r30 */) {}

// Range: 0x802E9C7C -> 0x802E9C9C
void TrackData::FillChannelList() {}

// Range: 0x802E9C9C -> 0x802E9CBC
void TrackData::FillChannelList() {}

// Range: 0x802E9CBC -> 0x802E9CFC
void TrackData::Hit(class TrackData * const this /* r30 */, int gem_id /* r31 */) {}

// Range: 0x802E9CFC -> 0x802E9D08
void TrackData::Miss() {}

// Range: 0x802E9D08 -> 0x802E9D10
void TrackData::SetCaptured() {}

// Range: 0x802E9D10 -> 0x802E9D18
void TrackData::SetPlayer() {}

// Range: 0x802E9D18 -> 0x802E9D20
void TrackData::SetNonmutable() {}

// Range: 0x802E9D20 -> 0x802E9D2C
void TrackData::SetButtonMashingMode() {}

// Range: 0x802E9D2C -> 0x802E9D34
void TrackData::SetLastMashTime() {}

// Range: 0x802E9D34 -> 0x802E9D74
void TrackData::Reset(class TrackData * const this /* r31 */) {}

// Range: 0x802E9D74 -> 0x802E9F5C
void TrackData::SetSucceeding() {
    // Local variables
    int i; // r5
}

// Range: 0x802E9F5C -> 0x802E9F94
unsigned char TrackData::IsSlotActive() {}

// Range: 0x802E9F94 -> 0x802EA110
void TrackData::FillChannelListWithInactiveSlots(const class TrackData * const this /* r25 */, class list & channels /* r26 */, float ms /* f31 */, unsigned char succeeding /* r27 */) {
    // Local variables
    int active_channels; // r31
    int inactive_channels; // r30
    unsigned char all_active_slots_succeeding; // r29
    int s; // r28
    int c; // r28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

static class Symbol _s; // size: 0x4, address: 0x80A505FC
static class Symbol _s; // size: 0x4, address: 0x80A50604
static class Symbol _s; // size: 0x4, address: 0x80A5060C
static class Symbol _s; // size: 0x4, address: 0x80A50614
static class Symbol _s; // size: 0x4, address: 0x80A5061C
static class Symbol _s; // size: 0x4, address: 0x80A50624
// Range: 0x802EA110 -> 0x802EA838
class DataNode MasterAudio::Handle(class MasterAudio * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x138
} __vt__11MasterAudio; // size: 0x138, address: 0x808CC178
struct {
    // total size: 0x8
} __RTTI__11MasterAudio; // size: 0x8, address: 0x808CC2E0
struct {
    // total size: 0x8
} __RTTI__PP9TrackData; // size: 0x8, address: 0x808CC3E8
struct {
    // total size: 0x8
} __RTTI__PP11ChannelData; // size: 0x8, address: 0x808CC400

