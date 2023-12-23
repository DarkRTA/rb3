#include "wiinetworksocket.hpp"
#include "revolution/rvl/so.h"

extern int fn_80308acc(const char*);

WiiNetworkSocket::~WiiNetworkSocket() { // 80308cc0
	Disconnect();
}

bool WiiNetworkSocket::Connect(u32 a, u16 b) {
	so_addr_t address;
	address.sa_len = 8;
	address.sa_family = 2;
	address.sa_port = b;
	address.sa_addr = a;
	s32 ret = SOConnect(native_sock, &address);
	if (ret < 0) {
		if (ret == -0x1a) return true;
		Failed = true;
	}
	return !ret;
}

void WiiNetworkSocket::Listen() {
	SOListen(native_sock, 5);
}
