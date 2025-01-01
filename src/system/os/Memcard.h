#pragma once
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "obj/Msg.h"

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

class MCContainer {
public:
    MCContainer(const ContainerId& id) : mCid(id), mIsMounted(0) {}
    virtual ~MCContainer(){}
    virtual void Mount(CreateType) = 0;
    virtual void Unmount() = 0;
    virtual int GetPathFreeSpace(const char*, unsigned long long*) = 0;
    virtual int GetDeviceFreeSpace(unsigned long long*) = 0;
    virtual int Delete(const char*) = 0;
    virtual int RemoveDir(const char*) = 0;
    virtual int MakeDir(const char*) = 0;
    virtual int GetSize(const char*, int*) = 0;
    virtual int Format() = 0;
    virtual int Unformat() = 0;
    virtual MCFile* CreateMCFile() = 0;
    virtual void DestroyMCFile(MCFile *);
    virtual String BuildPath(const char *);
    virtual int PrintDir(const char*, bool) = 0;

    bool IsMounted() { return mIsMounted; }

    ContainerId mCid;
    bool mIsMounted;
};

DECLARE_MESSAGE(DeviceChosenMsg, "device_chosen")
    DeviceChosenMsg(int i) : Message(Type(), i){}
END_MESSAGE