#include "types.h"
#include <revolution/rvl/so.h>

const char* __SOCKETVersion = "<< RVL_SDK - SOCKET \trelease build: Jun  9 2009 12:00:01 (0x4199_60831) >>";


so_fd_t SOSocket(so_pf_t protocol_family, so_type_t type, so_prot_t protocol) {

}

so_ret_t SOClose(so_fd_t socket) {
    s32 x;
    so_ret_t ret;
    ret = SOiPrepare(NULL, &x);
    if (!ret) {
        return SOiConclude(NULL, -49);
    }
    return ret;
}
