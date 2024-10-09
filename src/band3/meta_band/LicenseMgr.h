#pragma once
#include "os/ContentMgr.h"
#include <set>

class LicenseMgr : public ContentMgr::Callback {
public:
    LicenseMgr();
    virtual ~LicenseMgr(){}
    virtual void ContentStarted();
    virtual bool ContentDiscovered(Symbol);
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentLoaded(class Loader*, ContentLocT, Symbol);
    virtual const char* ContentDir();

    std::set<Symbol> unk4; // 0x4
};