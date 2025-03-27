#pragma once
#include "meta_band/SessionMgr.h"
#include "obj/Object.h"
#include <set>

class UploadErrorMgr : public Hmx::Object {
public:
    UploadErrorMgr();
    virtual ~UploadErrorMgr();
    virtual DataNode Handle(DataArray *, bool);

    DataNode OnMsg(const SessionReadyMsg &);

    static void Init();

    std::set<String> mDisplayedErrors; // 0x1c
};

extern UploadErrorMgr *TheUploadErrorMgr;