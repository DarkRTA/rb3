/*
    Compile unit: C:\rockband2\system\src\os\NetworkSocket_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805C0498 -> 0x805C05F4
*/
// Range: 0x805C0498 -> 0x805C04D8
class NetworkSocket * NetworkSocket::Create(unsigned char streaming /* r31 */) {}

// Range: 0x805C04D8 -> 0x805C04E4
class String NetworkSocket::GetHostName() {}

class WiiNetworkSocket : public NetworkSocket {
    // total size: 0x4
};
// Range: 0x805C04E4 -> 0x805C04E8
void WiiNetworkSocket::Init() {}

// Range: 0x805C04E8 -> 0x805C0524
void * WiiNetworkSocket::WiiNetworkSocket(class WiiNetworkSocket * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16WiiNetworkSocket;
}

// Range: 0x805C0524 -> 0x805C058C
void * WiiNetworkSocket::~WiiNetworkSocket(class WiiNetworkSocket * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16WiiNetworkSocket;
}

// Range: 0x805C058C -> 0x805C0594
unsigned char WiiNetworkSocket::Connect() {}

// Range: 0x805C0594 -> 0x805C0598
void WiiNetworkSocket::Listen() {}

// Range: 0x805C0598 -> 0x805C05A0
class NetworkSocket * WiiNetworkSocket::Accept() {}

// Range: 0x805C05A0 -> 0x805C05A4
void WiiNetworkSocket::GetRemoteIP() {}

// Range: 0x805C05A4 -> 0x805C05A8
void WiiNetworkSocket::Disconnect() {}

// Range: 0x805C05A8 -> 0x805C05B0
unsigned char WiiNetworkSocket::Fail() {}

// Range: 0x805C05B0 -> 0x805C05B4
void WiiNetworkSocket::Bind() {}

// Range: 0x805C05B4 -> 0x805C05BC
unsigned char WiiNetworkSocket::InqBoundPort() {}

// Range: 0x805C05BC -> 0x805C05C4
int WiiNetworkSocket::Send() {}

// Range: 0x805C05C4 -> 0x805C05CC
int WiiNetworkSocket::SendTo() {}

// Range: 0x805C05CC -> 0x805C05D4
int WiiNetworkSocket::BroadcastTo() {}

// Range: 0x805C05D4 -> 0x805C05DC
int WiiNetworkSocket::Recv() {}

// Range: 0x805C05DC -> 0x805C05E4
int WiiNetworkSocket::RecvFrom() {}

// Range: 0x805C05E4 -> 0x805C05EC
unsigned char WiiNetworkSocket::CanSend() {}

// Range: 0x805C05EC -> 0x805C05F4
unsigned int WiiNetworkSocket::BytesAvailable() {}

struct {
    // total size: 0x48
} __vt__16WiiNetworkSocket; // size: 0x48, address: 0x80924A50
struct {
    // total size: 0x8
} __RTTI__16WiiNetworkSocket; // size: 0x8, address: 0x80924AB8
struct {
    // total size: 0x8
} __RTTI__13NetworkSocket; // size: 0x8, address: 0x80924AD0

