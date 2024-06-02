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

    void SetLines(int);
    void Clear();
    static void Init();
    static void Terminate();

    static RndOverlay* Find(Symbol, bool);
    static std::list<RndOverlay*> sOverlays;

    const char* mName;
    bool mShowing;
    std::list<String> mLines;
    std::list<String>::iterator mLine;
    Hmx::Color mBackColor;
    Hmx::Color mTextColor;
    int mCursorChar;
    Callback* mCallback;
    Timer mTimer;
    float mTimeout;
    bool mModal;
    int mDumpCount;
};

#endif
