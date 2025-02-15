#pragma once
#include <vector>

class Player;
class GemPlayer;

class CommonPhraseCapturer {
public:
    class PhraseState {
    public:
        int unk0;
        int unk4;
        int unk8;
    };
    CommonPhraseCapturer();

    void Enabled(Player *, int, int, bool);
    void LocalHitLastGem(Player *, int, int);
    void LocalFail(Player *, int, int);
    void Reset();
    void ExtendPhraseStates(int);
    void HandlePhraseNote(GemPlayer *, int, int, bool);
    bool IsMultiplayerPhrase(int);
    bool HasPlayedWholePhrase(GemPlayer *, int, int, int);
    void HitLastGem(Player *, int, int);
    void Fail(Player *, int, int);
    void HandleVocalPhrase(Player *, int, int, bool);
    void OneTrackCompletedPhrase(int, int);
    void AllTracksCompletedPhrase(int);
    bool DidTrackFail(int, int) const;

    std::vector<PhraseState> mPhraseStates; // 0x0
    int mDisabledTracks; // 0x8
    int mFinishedTracks; // 0xc
    bool mInUnisonPhrase; // 0x10
    int mLastStartedPhraseID; // 0x14
};