#include "net/Server_Wii.h"
#include "net/Server.h"
#include "os/Timer.h"

WiiServer gWiiServer;
Server &TheServer = gWiiServer;
Timer g_LoginTimer;

WiiServer::WiiServer()
    : unk68(0), unk69(0), unk6a(0), unk6b(0), unk6c(0), unk70(0), unk74(0), unk78(0),
      unk7c(0), unk84(0), unk88(0), unk8c(0), unk90(0), unk94(0), unk98(0), unk9c(0),
      unka0(0), unka4(0), unka8(0), unkac(0), unkad(0), unke0(0) {}