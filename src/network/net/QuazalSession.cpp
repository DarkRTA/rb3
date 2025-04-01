#include "network/net/QuazalSession.h"
#include "Core/CallContext.h"
#include "net/NetSession.h"
#include "os/Debug.h"

Quazal::CallContext *QuazalSession::mTerminatingContext;

QuazalSession::QuazalSession(bool b) {}

MakeQuazalSessionJob::MakeQuazalSessionJob(QuazalSession **addr, bool host)
    : mSessionAddress(addr), mHosting(host) {
    MILO_ASSERT(!(*addr), 0xF3);
}

bool MakeQuazalSessionJob::IsFinished() {
    if (QuazalSession::mTerminatingContext)
        return false;
    else {
        *mSessionAddress = new QuazalSession(mHosting);
        return true;
    }
}

void MakeQuazalSessionJob::Cancel(Hmx::Object *) {
    TheNetSession->OnCreateSessionJobComplete(false);
}

void MakeQuazalSessionJob::OnCompletion(Hmx::Object *) {
    TheNetSession->OnCreateSessionJobComplete(true);
}