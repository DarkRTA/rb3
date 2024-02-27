#include "os/NetworkSocket_Wii.h"
#include "os/Debug.h"

int UnimplementedFunction(const char* str){
    MILO_FAIL("NetworkSocket_Wii.cpp, need to implement %s!", str);
    return 0;
}

NetworkSocket* NetworkSocket::Create(bool streaming){
    return new WiiNetworkSocket(streaming);
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

WiiNetworkSocket::WiiNetworkSocket(int socket, bool streaming) : mSocket(socket), mStreaming(streaming), mFail(0) {
    int ret = SOFcntl(mSocket, 3, 0);
    SOFcntl(mSocket, 4, ret | 4);
}

WiiNetworkSocket::~WiiNetworkSocket(){
    Disconnect();
}

int WiiNetworkSocket::Listen(){
    return SOListen(mSocket, 5);
}

bool WiiNetworkSocket::SetNoDelay(bool b){
    return SOSetSockOpt(mSocket, SOL_SOCKET, SO_IP_NUM, 0, 4) == 0;
}
