#ifndef BEATMATCH_GEMINFO_H
#define BEATMATCH_GEMINFO_H

enum NoStrumState {
    kStrumForceOn,
    kStrumForceOff,
    kStrumDefault
};

struct MultiGemInfo {
    int track;
    int slots;
    float ms;
    float duration_ms;
    int tick;
    int duration_ticks;
    bool ignore_duration;
    bool is_cymbal;
    int players;
    NoStrumState no_strum;
};

// 4 bits max
enum RGNoteType {
    kRGNormal,
    kRGGhost,
    kRGBend,
    kRGMuted,
    kRGTap,
    kRGPalmMute,
    kRGNaturalHarmonic,
    kRGPinchHarmonic,
    kRGSlide,
    kRGPickSlide,
    kRGWhammyUp,
    kRGWhammyDown,
    kRGBassPop,
    kRGBassSlap
};

enum RGStrumType {
    kRGNoStrum,
    kRGStrum,
    kRGStrumHigh,
    kRGStrumLow
};

struct RGGemInfo {
    int track;
    int slots;
    float ms;
    float duration_ms;
    int tick;
    int duration_ticks;
    NoStrumState no_strum;
    bool show_chord_names;
    bool show_slashes;
    char mFret[6];
    RGNoteType mRGNoteType[6];
    RGStrumType mStrumType;
    unsigned char mHandPosition;
    unsigned char mRootNote;
    
};

#endif