#pragma once
#include "os/ContentMgr.h"
#include "obj/DataFile.h"
#include <set>

class LicenseMgr : public ContentMgr::Callback {
public:
    LicenseMgr();
    virtual ~LicenseMgr(){}
    virtual void ContentStarted();
    virtual bool ContentDiscovered(Symbol);
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentLoaded(class Loader*, ContentLocT, Symbol);
    virtual const char* ContentPattern();
    virtual const char* ContentDir();

    bool HasLicense(Symbol) const;
    void AddLicenses(DataArray*, DataLoader*, ContentLocT, Symbol);
    bool LicenseCacheNeedsWrite() const;
    bool WriteCachedMetadataToStream(BinStream&) const;
    bool ReadCachedMetadataFromStream(BinStream&, int);
    void ClearCachedContent();
    void MarkAvailable(Symbol, Symbol);

    std::set<Symbol> mLicenses; // 0x4
};