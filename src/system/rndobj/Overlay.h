#pragma once
#include "utl/TextStream.h"
#include "obj/Data.h"
#include "utl/Str.h"
#include <list>
#include "math/Color.h"
#include "os/Timer.h"

class RndOverlay : public TextStream {
public:

    class Callback {
    public:
        Callback(){}
        virtual ~Callback(){}
        virtual float UpdateOverlay(RndOverlay*, float){}
    };

    RndOverlay(const DataArray*);
    virtual ~RndOverlay();
    virtual void Print(const char *);

    void SetCallback(Callback* cb){ mCallback = cb; }
    bool Showing() const { return mShowing; }
    void SetCursorChar(int cursChar){ mCursorChar = cursChar; }
    void SetDumpCount(int dump_count) { mDumpCount = dump_count; }

    void SetOverlay(bool b){
        mShowing = b;
        mTimer.Restart();
    }

    int NumLines() const { return mLines.size(); }

    void SetTimeout(float);
    void SetLines(int);
    void Clear();
    String& CurrentLine();
    float Draw(float);

    static void Init();
    static void Terminate();
    static void TogglePosition();
    static void DrawAll(bool);

    static RndOverlay* Find(Symbol, bool);
    static bool sTopAligned;
    static std::list<RndOverlay*> sOverlays;

    const char* mName; // 0x4
    bool mShowing; // 0x8
    std::list<String> mLines; // 0xc
    std::list<String>::iterator mLine; // 0x14
    Hmx::Color mBackColor; // 0x18
    Hmx::Color mTextColor; // 0x28
    int mCursorChar; // 0x38
    Callback* mCallback; // 0x3c
    Timer mTimer; // 0x40
    float mTimeout; // 0x70
    bool mModal; // 0x74
    int mDumpCount; // 0x78
};