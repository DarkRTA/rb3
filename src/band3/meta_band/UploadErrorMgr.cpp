#include "meta_band/UploadErrorMgr.h"
#include "decomp.h"
#include "meta_band/SessionMgr.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "utl/Symbols4.h"

UploadErrorMgr *TheUploadErrorMgr;

void UploadErrorMgr::Init() {
    MILO_ASSERT(TheUploadErrorMgr == NULL, 0x1C);
    TheUploadErrorMgr = new UploadErrorMgr();
    TheNetSession->AddSink(TheUploadErrorMgr, session_ready);
}

DECOMP_FORCEACTIVE(UploadErrorMgr, "%d_%s")

UploadErrorMgr::UploadErrorMgr() {}
UploadErrorMgr::~UploadErrorMgr() {}

DataNode UploadErrorMgr::OnMsg(const SessionReadyMsg &) {
    mDisplayedErrors.clear();
    return DataNode(kDataUnhandled, 0);
}

BEGIN_HANDLERS(UploadErrorMgr)
    HANDLE_MESSAGE(SessionReadyMsg)
    HANDLE_CHECK(0x76)
END_HANDLERS