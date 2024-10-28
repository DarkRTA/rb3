#include "NetworkSocket.h"
#include "RevoEX/so/SOBasic.h"
#include "decomp.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "revolution/os/OSError.h"
#include "revolution/os/OSInterrupt.h"
#include "revolution/rvl/so.h"
#include <cstddef>

bool WiiNetworkSocket::sInit = false;

int UnimplementedFunction(const char* str){
    MILO_FAIL(__FILE__ ", need to implement %s!", str);
    return 0;
}

NetworkSocket* NetworkSocket::Create(bool streaming){
    return new WiiNetworkSocket(streaming);
}

bool NetworkSocket::ResolveHostName(String str) {
    if (WiiNetworkSocket::Init() == false) {
        return 0;
    } else {
        so_ret_t ret = SOGetHostByName(str.c_str());
        if (ret != 0) {

            MILO_FAIL("WiiNetworkSockets only support IPv4");
            return 0;
        } else return 0;
    }
}

bool WiiNetworkSocket::Init() {
    ThePlatformMgr.InitSOLibrary(true);
    sInit = ThePlatformMgr.mEthernetCableConnected;
    return sInit;
}

WiiNetworkSocket::WiiNetworkSocket(bool streaming) : mStreaming(streaming), mFail(0) {
    Init();
    if(!mStreaming) mSocket = SOSocket(PF_INET, SOCK_DGRAM, PROTO_DGRAM_TCP);
    else mSocket = SOSocket(PF_INET, SOCK_STREAM, PROTO_DGRAM_TCP);
    mFail = mSocket < SO_OK;
    if(!mFail){
        int ret = SOFcntl(mSocket, 3, 0);
        SOFcntl(mSocket, 4, ret | 4);
    }
}

DECOMP_FORCEACTIVE(NetworkSocket_Wii, "NetworkSocket_Wii.cpp", "buf[buflen-1] == '\\0'")


WiiNetworkSocket::WiiNetworkSocket(int socket, bool streaming) : mSocket(socket), mStreaming(streaming), mFail(0) {
    int ret = SOFcntl(mSocket, 3, 0);
    SOFcntl(mSocket, 4, ret | 4);
}

WiiNetworkSocket::~WiiNetworkSocket(){
    Disconnect();
}

int NetworkSocket::IPStringToInt(const String& str) {
    WiiNetworkSocket::Init();
    u32 addr;
    if (SOInetAtoN(str.c_str(), &addr) != 0) return addr;
    return -1;
}

String NetworkSocket::GetHostName() {
    return String("");
}

bool WiiNetworkSocket::Connect(uint ip, unsigned short port) {
    so_addr_t add;
    add.sa_len = 8; add.sa_family = 2; add.sa_port = port; add.sa_addr = ip;
    so_ret_t ret = SOConnect(mSocket, &add);

    if (ret < 0) {
        if (ret == -0x1a) return true;
        mFail = true;
        OSReport("SOConnect failed (%d)\n", ret);
    }
    return ret == 0;
}

int WiiNetworkSocket::Listen(){
    return SOListen(mSocket, 5);
}

NetworkSocket* WiiNetworkSocket::Accept() {
    so_addr_t accept_addr;
    accept_addr.sa_len = 8;
    so_ret_t sock2 = SOAccept(mSocket, &accept_addr);
    if (sock2 < 0) {
        return NULL;
    }
    return new WiiNetworkSocket(sock2, mStreaming);
}

int WiiNetworkSocket::GetRemoteIP(unsigned int&, unsigned short&) {
    return UnimplementedFunction("WiiNetworkSocket::GetRemoteIP");
}

void WiiNetworkSocket::Disconnect() {
    if (mSocket >= 0) {
        SOShutdown(mSocket, (so_shut_t)2);
        SOClose(mSocket);
        mSocket = -1;
    }
}

bool WiiNetworkSocket::Fail() const { return mFail; }

void WiiNetworkSocket::Bind(u16 port) {
    u32 b = true;
    SOSetSockOpt(mSocket, (so_lvl_t)0xFFFF, (so_opt_t)4, &b, 4);
    so_addr_t bind_addr;
    bind_addr.sa_addr = SOHtoNl(0);
    bind_addr.sa_len = 8;
    bind_addr.sa_family = 2;
    bind_addr.sa_port = port;
    so_ret_t ret = SOBind(mSocket, &bind_addr);
    if (ret < 0) {
        OSReport("SOBind failed. (%d)\n", ret);
    }
}

int WiiNetworkSocket::InqBoundPort(unsigned short&) const {
    UnimplementedFunction("WiiNetworkSocket::InqBoundPort");
    return 0;
}

int WiiNetworkSocket::Send(const void*, u32) {
    if (mFail) return 0;
}

int WiiNetworkSocket::SendTo(const void*, u32, uint, u16) {
    UnimplementedFunction("WiiNetworkSocket::SendTo");
    return 0;
}

int WiiNetworkSocket::BroadcastTo(const void*, u32, u16) {
    UnimplementedFunction("WiiNetworkSocket::BroadcastTo");
    return 0;
}

bool WiiNetworkSocket::CanRead() const {
    bool ret = false;
    bool tru = true;
    so_poll_t poll;
    poll.socket = mSocket;
    poll.mask = (so_event_t)tru;
    poll.result = (so_event_t)0;
    bool status = OSDisableInterrupts();
    so_ret_t ret2 = SOPoll(&poll, 1, 0);
    OSRestoreInterrupts(status);
    if (ret2 >= 0 && poll.result == poll.mask) {
        ret = tru;
    }
    return ret;
}

int WiiNetworkSocket::Recv(void* buf, u32 siz) {
    if (mFail) return 0;
    if (CanRead()) {
        so_ret_t ret = SORecv(mSocket, buf, siz, 0);
        switch (ret) {
            case SO_E15:
            case SO_E56:
                mFail = true;
            case SO_EAGAIN:
                return 0;
            default:
                MILO_FAIL("error in Recv: %i", (int)ret);
                if (ret < 0) return 0;
                return 0;
            case SO_OK:
                return ret;
        }
    }
    return 0;
}

int WiiNetworkSocket::RecvFrom(void*, u32, uint&, u16&) {
    UnimplementedFunction("WiiNetworkSocket::RecvFrom");
    return 0;
}

bool WiiNetworkSocket::CanSend() const {
    so_poll_t polls;
    bool ret = false;
    polls.socket = mSocket;
    polls.mask = (so_event_t)8;
    polls.result = (so_event_t)0;
    if (SOPoll(&polls, 1, 0) >= 0 && polls.result == polls.mask) ret = true;
    return ret;
}

bool WiiNetworkSocket::SetNoDelay(bool b){
    BOOL b2 = b;
    return SOSetSockOpt(mSocket, (so_lvl_t)6, (so_opt_t)0x2001, &b2, 4) == 0;
}
