#include "meta/ConnectionStatusPanel.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "os/PlatformMgr.h"

ConnectionStatusPanel::ConnectionStatusPanel() {}

ConnectionStatusPanel::~ConnectionStatusPanel() {}

void ConnectionStatusPanel::Enter() {
    UIPanel::Enter();
    ThePlatformMgr.AddSink(this, connection_status_changed);
    CheckForLostConnection();
}

void ConnectionStatusPanel::Exit() {
    ThePlatformMgr.RemoveSink(this, connection_status_changed);
    UIPanel::Exit();
}

DataNode ConnectionStatusPanel::OnMsg(const ConnectionStatusChangedMsg &msg) {
    CheckForLostConnection();
    return 0;
}

void ConnectionStatusPanel::CheckForLostConnection() {
    if (!ThePlatformMgr.IsConnected()) {
        Handle(on_connection_lost_msg, true);
    }
}

BEGIN_HANDLERS(ConnectionStatusPanel)
    HANDLE_MESSAGE(ConnectionStatusChangedMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x42)
END_HANDLERS
