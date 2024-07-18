#ifndef RNDOBJ_OVERLAY_H
#define RNDOBJ_OVERLAY_H
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

    void SetTimeout(float);
    void SetLines(int);
    void Clear();
    String& CurrentLine();
    void Draw(float);

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

#endif
