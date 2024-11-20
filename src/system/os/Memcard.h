#ifndef OS_MEMCARD_H
#define OS_MEMCARD_H

#include "system/obj/Dir.h"
#include "system/obj/Object.h"
#include "system/os/Debug.h"

enum AccessType {};
enum CreateType {};

class MCFile {
public:
    virtual ~MCFile();
    virtual int Open(const char*, AccessType, CreateType);
    virtual void Read(void*, int);
    virtual void Write(const void*, int);
    virtual void Seek(int, BinStream::SeekType);
    virtual void Close();
    virtual bool IsOpen();

    class MCContainer *mpContainer;
};

class ContainerId {
public:
    int dummy;
};

class MCContainer {
public:
    virtual ~MCContainer();
    virtual void Mount(CreateType);
    virtual void Unmount();
    virtual int GetPathFreeSpace(const char*, unsigned long long*);
    virtual void GetDeviceFreeSpace(unsigned long long*);
    virtual void Delete(const char*);
    void DestroyMCFile(MCFile *);
    String BuildPath(const char *);

    ContainerId mCid;
    bool mIsMounted;
    inline bool IsMounted() { return mIsMounted; }
};

class Memcard : public Hmx::Object {
public:
    virtual void Init();
    virtual void Poll();
    void ShowDeviceSelector(const ContainerId &, bool, Hmx::Object *, int);
    bool IsDeviceValid(const ContainerId&);
    void DestroyContainer(MCContainer *);
    DONT_INLINE_CLASS const wchar_t *GetDisplayName() { return L""; }
    DONT_INLINE_CLASS const char *GetContainerName() { return ""; }
    DONT_INLINE_CLASS void SetContainerDisplayName(const wchar_t *) { return; }
    DONT_INLINE_CLASS void SetContainerName(const char *) { return; }
};

#endif // OS_MEMCARD_H
