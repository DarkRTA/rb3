#ifndef OS_CONTENTMGR_WII_H
#define OS_CONTENTMGR_WII_H
#include "os/ContentMgr.h"

bool CntSdRsoInit(struct RSOObjectHeader*);
void CntSdRsoTerminate();

class WiiContentMgr : public ContentMgr {
public:
    void UnmountContents(Symbol);
};

extern WiiContentMgr TheWiiContentMgr;

#endif // OS_CONTENTMGR_WII_H