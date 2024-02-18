#ifndef OS_DEBUG_H
#define OS_DEBUG_H
#include "utl/TextFileStream.h"
#include "utl/TextStream.h"

class Debug : public TextStream {
public:
    bool mFailing;
    bool mExiting;
    bool mNoTry;
    bool mNoModal;
    bool mTry;
    TextFileStream* mLog; 
    bool mAlwaysFlush;
    TextStream* mReflect;
    void (* mModalCallback)(bool &, char *, bool);
    char mFailCallbacks[8]; // actually a list
    char mExitCallbacks[8]; // also actually a list
    unsigned int mFailThreadStack[50];
    const char* mFailThreadMsg;
    const char* mNotifyThreadMsg;

    virtual ~Debug();
    virtual void Print(const char*);

    TextStream* SetReflect(TextStream* ts){
        TextStream* ret = mReflect;
        mReflect = ts;
        return ret;
    }
};

#endif
