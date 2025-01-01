#pragma once
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
    Memcard(){}
    virtual ~Memcard(){}
    virtual void Init();
    virtual void Terminate();
    virtual void Poll();
    virtual void SetContainerName(const char *){}
    virtual void SetContainerDisplayName(const wchar_t *){}
    virtual const char *GetContainerName(){ return ""; }
    virtual const wchar_t *GetDisplayName() { return L""; }
    virtual void ShowDeviceSelector(const ContainerId &, bool, Hmx::Object *, int);
    virtual bool IsDeviceValid(const ContainerId&);
    virtual int DeleteContainer(const ContainerId&) = 0;
    virtual void CreateContainer(const ContainerId&) = 0;
    virtual void DestroyContainer(MCContainer *);
};
