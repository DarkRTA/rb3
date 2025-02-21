#pragma once
#include "obj/Object.h"
#include "rndobj/Overlay.h"
#include "synth/FxSend.h"
#include "synth/FxSendPitchShift.h"
#include "synth/Mic.h"
#include "synth/MicClientMapper.h"
#include "synth/MicNull.h"
#include "synth/MidiSynth.h"
#include "synth/ByteGrinder.h"
#include "synth/MidiInstrumentMgr.h"

enum FXMode {
    kFXModeOff,
    kFXModeRoom,
    kFXModeSmallStudio,
    kFXModeMedStudio,
    kFXModeLargeStudio,
    kFXModeHall,
    kFXModeSpace,
    kFXModeEcho,
    kFXModeDelay,
    kFXModePipe,
    kFXModeChorus,
    kFXModeWah,
    kFXModeFlanger
};

// courtesy of RB2
struct LevelData {
    float mRMS; // offset 0x0, size 0x4
    float mPeak; // offset 0x4, size 0x4
    float mPeakHold; // offset 0x8, size 0x4
    int mPeakAge; // offset 0xC, size 0x4
    class String mName; // offset 0x10, size 0xC
};

class Fader;
class Stream;
class StandardStream;
class StreamReader;

class Synth : public Hmx::Object, public RndOverlay::Callback {
public:
    Synth();
    virtual ~Synth() {}
    virtual DataNode Handle(DataArray *, bool);
    virtual void PreInit() {}
    virtual void Init();
    virtual void InitSecurity();
    virtual void SetDolby(bool, bool) {}
    virtual void SetMono(bool) {}
    virtual bool Fail() { return false; }
    virtual void Terminate();
    virtual void Poll();
    virtual bool HasPendingVoices() { return false; }
    virtual void SetFXMode(int, FXMode) {}
    virtual FXMode GetFXMode(int) const { return kFXModeOff; }
    virtual void SetFXVolume(int, float) {}
    virtual float GetFXVolume(int) const { return 0.0f; }
    virtual void SetFXDelay(int, float) {}
    virtual float GetFXDelay(int) const { return 0.0f; }
    virtual void SetFXFeedback(int, float) {}
    virtual float GetFXFeedback(int) const { return 0.0f; }
    virtual void SetFXChain(bool) {}
    virtual int GetFXChain() const { return 0; }
    virtual void SetChatVoiceGain(int, float) {}
    virtual float GetChatVoiceGain(int) { return 1.0f; }
    virtual Mic *GetMic(int idx) { return mNullMics[idx]; }
    virtual Mic *GetPartyMic() { return 0; } // ditto
    virtual void SetMicFX(bool) {}
    virtual bool GetMicFX() const { return false; }
    virtual void SetMicVolume(float) {}
    virtual float GetMicVolume() const { return 0.0f; }
    virtual void SuspendMics() {}
    virtual void ResumeMics() {}
    virtual int GetNumConnectedMics() { return 0; }
    virtual int GetNextAvailableMicID() const { return -1; }
    virtual bool IsMicConnected(int) const { return false; }
    virtual void CaptureMic(int) {}
    virtual void ReleaseMic(int) {}
    virtual void ReleaseAllMics() {}
    virtual int GetSecureOutput() { return 0; } // fix this
    virtual bool DidMicsChange() const { return false; }
    virtual void ResetMicsChanged() {}
    virtual Stream *NewStream(const char *, float, float, bool);
    virtual Stream *NewBufStream(const void *, int, Symbol, float, bool);
    virtual StreamReader *NewStreamDecoder(File *, StandardStream *, Symbol) { return 0; }
    virtual void NewStreamFile(const char *, File *&, Symbol &);
    virtual void EnableLevels(bool) {}
    virtual float UpdateOverlay(RndOverlay *, float);
    virtual void RequirePushToTalk(bool, int) {}
    virtual void SetIncomingVoiceChatVolume(float) {}
    virtual FxSendPitchShift *CreatePitchShift(int, SendChannels);
    virtual void DestroyPitchShift(FxSendPitchShift *);

    void StopAllSfx(bool);
    void PauseAllSfx(bool);
    float GetMasterVolume();
    void SetMasterVolume(float);
    void Play(const char *, float, float, float);
    void SetFX(const DataArray *);
    void StopPlaybackAllMics();
    void SetMic(const DataArray *);
    void ToggleHud();
    void DrawMeter(float &, float, float, const char *);
    void DrawMeterScale(float &);
    bool CheckCommonBank(bool);
    int GetSampleMem(ObjectDir *, Platform);
    int GetSPUOverhead();
    int GetFXOverhead();

    template <class T>
    T *Find(const char *name, bool fail) {
        if (!CheckCommonBank(false))
            return nullptr;
        else {
            T *obj = unk40->Find<T>(name, false);
            if (!obj && fail) {
                MILO_FAIL(
                    "Synth::Find() - %s %s not found in %s",
                    T::StaticClassName(),
                    name,
                    unk40->GetPathName()
                );
            }
            return obj;
        }
    }

    DataNode OnStartMic(const DataArray *);
    DataNode OnStopMic(const DataArray *);
    DataNode OnNumConnectedMics(const DataArray *);
    DataNode OnSetMicVolume(const DataArray *);
    DataNode OnSetFX(const DataArray *);
    DataNode OnSetFXVol(const DataArray *);
    DataNode OnPassthrough(DataArray *);

    int GetNumMics() const;
    MidiInstrumentMgr *GetMidiInstrumentMgr() const { return mMidiInstrumentMgr; }
    MicClientMapper *GetMicClientMapper() const { return mMicClientMapper; }
    static Synth *New();

    std::vector<LevelData> mLevelData; // 0x20
    ByteGrinder mGrinder; // 0x28
    int mNumMics; // 0x2c
    MidiSynth *mMidiSynth; // 0x30
    std::vector<MicNull *> mNullMics; // 0x34
    bool mMuted; // 0x3c
    ObjDirPtr<ObjectDir> unk40;
    Fader *mMasterFader; // 0x4c
    Fader *mSfxFader; // 0x50
    Fader *mMidiInstrumentFader; // 0x54
    MicClientMapper *mMicClientMapper; // 0x58
    MidiInstrumentMgr *mMidiInstrumentMgr; // 0x5c
    int unk60; // TranscodableMixer* mSecureMixer?
    int unk64; // Stream* mDebugStream?
    RndOverlay *mHud; // 0x68
};

void SynthInit();
void SynthTerminate();

extern Synth *TheSynth;
