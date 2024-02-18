#ifndef RB3_WIINETWORKSOCKET_HPP
#define RB3_WIINETWORKSOCKET_HPP
#include "types.h"
#include "networksocket.hpp"

class WiiNetworkSocket : public NetworkSocket {
public:
    so_fd_t native_sock;
    bool unk1;
    bool Failed;
    bool unk2;
    bool unk3;

    WiiNetworkSocket(bool);
    virtual ~WiiNetworkSocket(); // 0x80308cc0

    /** Connects to `addr` on port `port`.
     * @param addr The IPv4 address to attempt to connect to.
     * @param port The port to connect to the address with.
     * @return Whether it succeeded or not, 1 == success
     */
    bool Connect(u32 addr, u16 port); // 0x80308d34
    bool Fail(); // 0x80308e84
    bool Disconnect(); // 0x80308e34
    bool Bind(u16); // 0x80308e8c
    bool InqBoundPort(); // 0x80308f10, weird func, calls a stub with the name then
                         // returns 0
    void Listen(); // 0x80308da8
    WiiNetworkSocket *Accept(); // 0x80308db4
    bool GetRemoteIP(); // 0x80308e28, see inqboundport
    int CanSend(); // 0x80309210
    int BytesAvailable(); // 0x80309080
    void *Send(int, uint); // 0x80308f40
    void *Recv(void *, size_t); // 0x80309110
    bool SendTo(); // 0x80309020
    bool BroadcastTo(); // 0x80309050
    bool RecvFrom(); // 0x803091e0
    bool SetNoDelay(int); // 0x80309280
    int V_Unk19(); // links to fn_8077BAA0, which returns 0
};
#endif
