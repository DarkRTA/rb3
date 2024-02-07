/*
    Compile unit: C:\rockband2\band2\src\game\CommonPhraseCapturer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8004A084 -> 0x8004ACC0
*/
// Range: 0x8004A084 -> 0x8004A0D0
void * CommonPhraseCapturer::CommonPhraseCapturer(class CommonPhraseCapturer * const this /* r31 */) {}

// Range: 0x8004A0D0 -> 0x8004A1CC
void CommonPhraseCapturer::Reset(class CommonPhraseCapturer * const this /* r31 */) {
    // Local variables
    class vector & activePlayers; // r0
    int i; // r6
    int i; // r7

    // References
    // -> class Game * TheGame;
}

// Range: 0x8004A1CC -> 0x8004A390
void CommonPhraseCapturer::HandlePhraseNote(class CommonPhraseCapturer * const this /* r26 */, class GemPlayer * player /* r27 */, int track /* r28 */, int gem /* r29 */, unsigned char hit /* r30 */) {
    // Local variables
    int phrase; // r31
    int tracks_needed; // r0
    unsigned char unison; // r0

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8004A390 -> 0x8004A468
void CommonPhraseCapturer::LocalHitLastGem(class CommonPhraseCapturer * const this /* r28 */, class Player * player /* r29 */, int phrase /* r30 */, int track /* r31 */) {
    // Local variables
    int tracks_needed; // r5

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8004A468 -> 0x8004A550
void CommonPhraseCapturer::LocalFail(class CommonPhraseCapturer * const this /* r24 */, class Player * guilty_player /* r25 */, int phrase /* r26 */, int track /* r27 */) {
    // Local variables
    int tracks; // r0
    int t; // r29
    class Player * player; // r28

    // References
    // -> class SongDB * TheSongDB;
    // -> class Game * TheGame;
}

// Range: 0x8004A550 -> 0x8004A5E8
void CommonPhraseCapturer::Miss(class CommonPhraseCapturer * const this /* r28 */, class Player * player /* r29 */, int track /* r30 */) {
    // Local variables
    int phrase; // r31

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8004A5E8 -> 0x8004A64C
unsigned char CommonPhraseCapturer::DidTrackFail() {}

// Range: 0x8004A64C -> 0x8004A6F8
void CommonPhraseCapturer::Enabled(class CommonPhraseCapturer * const this /* r28 */, class Player * player /* r29 */, int track /* r30 */, unsigned char enabled /* r31 */) {
    // Local variables
    int phrase; // r5

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8004A6F8 -> 0x8004A82C
unsigned char CommonPhraseCapturer::HasPlayedWholePhrase(class GemPlayer * player /* r27 */, int phrase /* r28 */, int track /* r26 */, int gem /* r29 */) {
    // Local variables
    const class vector & gems; // r0
    const class vector & phrase_ids; // r0

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8004A82C -> 0x8004A8BC
void CommonPhraseCapturer::HitLastGem(class CommonPhraseCapturer * const this /* r28 */, class Player * player /* r29 */, int phrase /* r30 */, int track /* r31 */) {}

// Range: 0x8004A8BC -> 0x8004A94C
void CommonPhraseCapturer::Fail(class CommonPhraseCapturer * const this /* r28 */, class Player * guilty_player /* r29 */, int phrase /* r30 */, int track /* r31 */) {}

// Range: 0x8004A94C -> 0x8004A99C
void CommonPhraseCapturer::OneTrackCompletedPhrase() {
    // Local variables
    class Player * player; // r31

    // References
    // -> class Game * TheGame;
}

// Range: 0x8004A99C -> 0x8004AA64
void CommonPhraseCapturer::AllTracksCompletedPhrase(class CommonPhraseCapturer * const this /* r28 */, int phrase /* r29 */) {
    // Local variables
    int tracks; // r0
    int t; // r30
    class Player * player; // r0

    // References
    // -> class SongDB * TheSongDB;
    // -> class Game * TheGame;
}

// Range: 0x8004AA64 -> 0x8004AAD0
int CommonPhraseCapturer::ComputeTracks(class CommonPhraseCapturer * const this /* r30 */, int phrase /* r31 */) {
    // References
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8004AAD0 -> 0x8004ABA0
unsigned char CommonPhraseCapturer::IsUnisonPhrase(class CommonPhraseCapturer * const this /* r30 */, int phrase /* r29 */) {
    // Local variables
    int tracks; // r31
    int countParticipants; // r30
    int t; // r29

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8004ABA0 -> 0x8004ACC0
void CommonPhraseCapturer::ExtendPhraseStates() {}

struct {
    // total size: 0x8
} __RTTI__PQ220CommonPhraseCapturer11PhraseState; // size: 0x8, address: 0x80872FF0

