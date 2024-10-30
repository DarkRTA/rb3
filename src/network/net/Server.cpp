#include "net/Server.h"
#include "Server.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

Server::Server() : mLoginState(0) {

}

void Server::Init(){
    SetName("server", ObjectDir::Main());
    DataArray* cfg = SystemConfig("net", "server");
    mKey = cfg->FindStr("access_key");
    mPort = cfg->FindInt("port");
    mAddress = cfg->FindStr("address");
    for(int i = 0; i < 4; i++) mPlayerIDs[i] = 0;
}

BEGIN_HANDLERS(Server)
    HANDLE_ACTION(login, Login())
    HANDLE_ACTION(logout, Logout())
    HANDLE_EXPR(is_connected, IsConnected())
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x32)
END_HANDLERS

Server::~Server(){

}