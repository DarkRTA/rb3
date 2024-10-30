#pragma once
#include "system/utl/BinStream.h"
#include "system/utl/Str.h"
#include "system/utl/HxGuid.h"

class Synchronizable {
public:
    Synchronizable(const char*);
    virtual ~Synchronizable();
    virtual void SyncSave(BinStream&, unsigned int) const = 0;
    virtual void SyncLoad(BinStream&, unsigned int) = 0;
    virtual bool HasSyncPermission() const = 0;
    virtual void OnSynchronizing(unsigned int){}
    virtual void OnSynchronized(unsigned int){}

    void Publish(const char*);
    void Unpublish();
    void SetSyncDirty(unsigned int, bool);
    void SynchronizeIfDirty();
    void AddDirtyUser(const UserGuid&);
    const char* GetUniqueTag() const;

    unsigned int mDirtyMask; // 0x4 - flags/mask?
    std::vector<UserGuid> mDirtyUsers; // 0x8
    String mTag; // 0x10
};