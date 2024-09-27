#ifndef CHAR_CHARCLIPDRIVER_H
#define CHAR_CHARCLIPDRIVER_H
#include "obj/Object.h"
#include "char/CharClip.h"

class CharClipDriver {
public:
    CharClipDriver(Hmx::Object*, const CharClipDriver&);
    CharClipDriver(Hmx::Object*, CharClip*, int, float, CharClipDriver*, float, float, bool);
    ~CharClipDriver();

    void DeleteStack();
    CharClipDriver* Exit(bool);
    void ExecuteEvent(Symbol);
    void SetBeatOffset(float, TaskUnits, Symbol);
    CharClipDriver* DeleteClip(Hmx::Object*);
    CharClipDriver* Next() const { return mNext; }
    CharClip* GetClip() const { return mClip; }

    NEW_POOL_OVERLOAD(CharClipDriver)
    DELETE_POOL_OVERLOAD(CharClipDriver)

    int mPlayFlags; // 0x0
    float mBlendWidth; // 0x4
    float mTimeScale; // 0x8
    float mRampIn; // 0xc
    float mBeat; // 0x10
    float mDBeat; // 0x14
    float mBlendFrac; // 0x18
    float mAdvanceBeat; // 0x1c
    float mWeight; // 0x20
    ObjOwnerPtr<CharClip, ObjectDir> mClip; // 0x24
    CharClipDriver* mNext; // 0x30
    int mNextEvent; // 0x34
    DataArray* mEventData; // 0x38
    bool mPlayMultipleClips; // 0x3c
};

#endif