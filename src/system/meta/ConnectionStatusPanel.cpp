#include "meta/ConnectionStatusPanel.h"
#include "utl/Symbols.h"
#include "os/PlatformMgr.h"

extern PlatformMgr ThePlatformMgr;

ConnectionStatusPanel::ConnectionStatusPanel(){

}

ConnectionStatusPanel::~ConnectionStatusPanel(){
    
}

void ConnectionStatusPanel::Enter(){
    UIPanel::Enter();
    ThePlatformMgr.AddSink(this, connection_status_changed, Symbol(), MsgSource::kHandle);
    CheckForLostConnection();
}

void ConnectionStatusPanel::Exit(){
    ThePlatformMgr.RemoveSink(this, connection_status_changed);
    UIPanel::Exit();
}

DataNode ConnectionStatusPanel::OnMsg(const ConnectionStatusChangedMsg& msg){
    CheckForLostConnection();
    return DataNode(0);
}
