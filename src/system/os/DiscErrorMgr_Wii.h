#pragma once
#include <revolution/TPL.h>
#include <revolution/DVD.h>
#include <list>

class DiscErrorMgrWii {
public:
    class Callback {
    public:
        virtual void DiscErrorStart() {}
        virtual void DiscErrorEnd() {}
        virtual void DiscErrorDraw(void *) {}
    };

    DiscErrorMgrWii();
    void Init();
    void InitDiscError();
    void *LoadFile(const char *, unsigned long &);
    void SetDiscError(bool);
    void LoopUntilNoDiscError(DVDFileInfo *, bool);
    void RegisterCallback(Callback *);
    void UnregisterCallback(Callback *);
    void NotifyCallbacksStart();
    void NotifyCallbacksEnd();
    void NotifyCallbacksDiscDraw();

    bool mDiscError; // 0x0
    bool mRetryError; // 0x1
    bool mMovieReadError; // 0x2
    bool mActive; // 0x3
    TPLPalette *mEjectErrorTpl; // 0x4
    TPLPalette *mRetryErrorTpl; // 0x8
    std::list<Callback *> mCallbacks; // 0xc
};

class WiiDiscErrorSessionTerminatior : public DiscErrorMgrWii::Callback {
public:
    WiiDiscErrorSessionTerminatior() {}
    virtual void DiscErrorStart();
};

extern WiiDiscErrorSessionTerminatior TheWiiDiscErrorSessionTerminator;