#ifndef OS_CONTENTMGR_WII_H
#define OS_CONTENTMGR_WII_H
#include "os/ContentMgr.h"

bool CntSdRsoInit(struct RSOObjectHeader*);
void CntSdRsoTerminate();

class WiiContent : public Content {
public:
    WiiContent();
    virtual ~WiiContent();
    virtual const char* Root();
    virtual int OnMemcard();

    void Enumerate(const char*, void(*)(const char*, const char*), bool, const char*);
};

class WiiContentMgr : public ContentMgr {
public:
    void UnmountContents(Symbol);
};

extern WiiContentMgr TheWiiContentMgr;
extern const char* gCurContentName;

#endif // OS_CONTENTMGR_WII_H