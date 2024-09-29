#ifndef OS_MEMCARD_H
#define OS_MEMCARD_H

#include "system/obj/Dir.h"
#include "system/obj/Object.h"
#include "system/os/Debug.h"

class MCFile {
public:
    class MCContainer *mpContainer;
};

class ContainerId {
public:
    int dummy;
};

class MCContainer {
public:
    virtual ~MCContainer();
    void DestroyMCFile(MCFile *);
    void BuildPath(const char *);

    ContainerId mCid;
    bool mIsMounted;
};

class Memcard : public Hmx::Object {
public:
    void Init();
    void Poll();
    void ShowDeviceSelector(const ContainerId &, bool, Hmx::Object *, int);
    void DestroyContainer(MCContainer *);
    const wchar_t *GetContainerDisplayName();
    const char *GetContainerName();
    void SetContainerDisplayName(const wchar_t *);
    void SetContainerName(const char *);
};

#endif // OS_MEMCARD_H