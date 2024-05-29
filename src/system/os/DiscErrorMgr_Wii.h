#ifndef OS_DISCERRORMGR_WII_H
#define OS_DISCERRORMGR_WII_H
#include <list>

struct TPLPalette;

class DiscErrorMgrWii {
public:

    class Callback {
    public:
        virtual void DiscErrorStart(){}
        virtual void DiscErrorEnd(){}
        virtual void DiscErrorDraw(void*){}
    };

    DiscErrorMgrWii();

    bool mDiscError;
    bool mRetryError;
    bool mMovieReadError;
    bool mActive;
    TPLPalette* mEjectErrorTpl;
    TPLPalette* mRetryErrorTpl;
    std::list<Callback*> mCallbacks;
};

#endif
