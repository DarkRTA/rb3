#include "revolution/os/OSError.h"
#include "revolution/os/OSTime.h"
#include "revolution/rvl/so.h"
#include "sdk/RevoEX/so/SOBasic.h"
#include "types.h"

uint htonl(uint x) { return SOHtoNl(x); }
uint htons(u16 x) { return SOHtoNs(x); }
uint ntohl(uint x) { return SONtoHl(x); }
uint ntohs(u16 x) { return SONtoHs(x); }

so_ret_t poll(struct SOPollFD* fd, unsigned int pollct, int timeout) {
    return SOPoll((so_poll_t*)fd, pollct, 1000);
}

void bind(so_fd_t socket, const struct sockaddr* sa, unsigned int) {
    SOBind(socket, (so_addr_t*)sa);
}

void connect(so_fd_t socket, const sockaddr* sa, unsigned int) {
    SOConnect(socket, (so_addr_t*)sa);
}

void recv(so_fd_t sock, void* buf, unsigned long bufsiz, int flags) {
    SORecv(sock, buf, bufsiz, flags);
}

void recvfrom(so_fd_t sock, void* buf, size_t bufsiz, int flags, sockaddr* addr, unsigned int*) {
    SORecvFrom(sock, buf, bufsiz, flags, (so_addr_t*)addr);
}

void send(so_fd_t sock, const void* buf, size_t bufsiz, int flags) {
    SOSend(sock, buf, bufsiz, flags);
}

void sendto(so_fd_t sock, const void* buf, unsigned long bufsiz, int flags, const sockaddr* addr, unsigned int) {
    SOSendTo(sock, buf, bufsiz, flags, (so_addr_t*)addr);
}

void setsockopt(so_fd_t sock, int lvl, int name, const void* buf, unsigned int bufsiz) {
    SOSetSockOpt(sock, (so_lvl_t)lvl, (so_opt_t)name, buf, bufsiz);
}

so_fd_t socket(int a, int b, int c) {
    return SOSocket((so_pf_t)a, (so_type_t)b, (so_prot_t)c);
}

int closesocket(so_fd_t sock) {
    int err;
    if ((err = SOClose(sock))) {
        OSReport("SOClose returns %d\n", err);
    }
    return err;
}
