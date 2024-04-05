#ifndef OS_NETWORKSOCKET_H
#define OS_NETWORKSOCKET_H
#include "utl/Str.h"
#include <revolution/rvl/so.h>

struct NetAddress {
    NetAddress(unsigned int ip, unsigned short port) : mIP(ip), mPort(port) {}
    unsigned int mIP;
    int a, b;
    unsigned short mPort;
};

class NetworkSocket {
public:
    NetworkSocket(){} // this isn't even used idk why i put it here
    virtual ~NetworkSocket(){} // ditto
    virtual bool Connect(unsigned int, unsigned short) = 0;
    virtual bool Fail() const = 0;
    virtual void Disconnect() = 0;
    virtual void Bind(unsigned short) = 0;
    virtual int InqBoundPort(unsigned short&) const = 0;
    virtual int Listen() = 0;
    virtual NetworkSocket* Accept() = 0;
    virtual int GetRemoteIP(unsigned int&, unsigned short&) = 0;
    virtual bool CanSend() const = 0;
    virtual bool CanRead() const = 0;
    virtual int Send(const void*, unsigned long) = 0;
    virtual int Recv(void*, unsigned long) = 0;
    virtual int SendTo(const void*, unsigned long, unsigned int, unsigned short) = 0;
    virtual int BroadCastTo(const void*, unsigned long, unsigned short) = 0;
    virtual int RecvFrom(void*, unsigned long, unsigned int&, unsigned short&) = 0;
    virtual bool SetNoDelay(bool) = 0;
    virtual NetworkSocket* GetSocket(){ return 0; }

    static NetworkSocket* Create(bool);
    String ResolveHostName(String);
};

class WiiNetworkSocket : public NetworkSocket {
public:
    WiiNetworkSocket(bool);
    WiiNetworkSocket(int, bool);
    virtual ~WiiNetworkSocket();
    virtual bool Connect(unsigned int, unsigned short);
    virtual bool Fail() const;
    virtual void Disconnect();
    virtual void Bind(unsigned short);
    virtual int InqBoundPort(unsigned short&) const;
    virtual int Listen();
    virtual NetworkSocket* Accept();
    virtual int GetRemoteIP(unsigned int&, unsigned short&);
    virtual bool CanSend() const;
    virtual bool CanRead() const;
    virtual int Send(const void*, unsigned long);
    virtual int Recv(void*, unsigned long);
    virtual int SendTo(const void*, unsigned long, unsigned int, unsigned short);
    virtual int BroadCastTo(const void*, unsigned long, unsigned short);
    virtual int RecvFrom(void*, unsigned long, unsigned int&, unsigned short&);
    virtual bool SetNoDelay(bool);

    static void Init();

    static bool sInit;
    so_fd_t mSocket;
    bool mStreaming;
    bool mFail;
};

#endif
