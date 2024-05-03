#ifndef SYNTH_SYNTH_H
#define SYNTH_SYNTH_H
#include "obj/Object.h"
#include "rndobj/Overlay.h"
#include "synth/FxSend.h"
#include "synth/FxSendPitchShift.h"
#include "synth/Mic.h"
#include "synth/ByteGrinder.h"

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

class Fader;
class Stream;
class StandardStream;

class Synth : public Hmx::Object, public RndOverlay::Callback {
public:
    Synth();
    virtual ~Synth();
    virtual DataNode Handle(DataArray*, bool);
    virtual void PreInit(){}
    virtual void Init();
    virtual void InitSecurity();
    virtual void SetDolby(bool, bool){}
    virtual void SetMono(bool){}
    virtual bool Fail(){ return false; }
    virtual void Terminate();
    virtual void Poll();
    virtual bool HasPendingVoices(){ return false; }
    virtual void SetFXMode(int, FXMode){}
    virtual FXMode GetFXMode(int) const { return kFXModeOff; }
    virtual void SetFXVolume(int, float){}
    virtual float GetFXVolume(int) const { return 0.0f; }
    virtual void SetFXDelay(int, float){}
    virtual float GetFXDelay(int) const { return 0.0f; }
    virtual void SetFXFeedback(int, float){}
    virtual float GetFXFeedback(int) const { return 0.0f; }
    virtual void SetFXChain(bool){}
    virtual int GetFXChain() const { return 0; }
    virtual void SetChatVoiceGain(int, float){}
    virtual float GetChatVoiceGain(int){ return 1.0f; }
    virtual Mic* GetMic(int){ return 0; } // fix this
    virtual Mic* GetPartyMic(){ return 0; } // ditto
    virtual void SetMicFX(bool){}
    virtual bool GetMixFC() const { return false; }
    virtual void SetMicVolume(float){}
    virtual float GetMicVolume() const { return 0.0f; }
    virtual void SuspendMics(){}
    virtual void ResumeMics(){}
    virtual int GetNumConnectedMics(){ return 0; }
    virtual int GetNextAvailableMiCID() const { return -1; }
    virtual bool IsMicConnected(int) const { return false; }
    virtual void CaptureMic(int){}
    virtual void ReleaseMic(int){}
    virtual void ReleaseAllMics(){}
    virtual int GetSecureOutput(){ return 0; } // fix this
    virtual bool DidMicsChange() const { return false; }
    virtual void ResetMicsChanged(){}
    virtual Stream* NewStream(const char*, float, float, bool);
    virtual Stream* NewBufStream(const void*, int, Symbol, float, bool);
    virtual int NewStreamDecoder(File*, StandardStream*, Symbol){ return 0; }
    virtual void NewStreamFile(const char*, File*&, Symbol&);
    virtual void EnableLevels(bool){}
    virtual void UpdateOverlay(RndOverlay*, float);
    virtual void RequirePushToTalk(bool, int){}
    virtual void SetIncomingVoiceChatVolume(float){}
    virtual FxSendPitchShift* CreatePitchShift(int, SendChannels);
    virtual void DestroyPitchShift(FxSendPitchShift*);

    std::vector<int> unk20; // mLevelData?
    ByteGrinder mGrinder; // unk28
    int mNumMics; // unk2c
    int unk30; // MidiSynth* mMidiSynth
    std::vector<int> unk34; // mNullMics
    bool unk3c; // mMuted
    ObjDirPtr<class ObjectDir> unk40;
    Fader* unk4c;
};

extern Synth* TheSynth;

#endif
