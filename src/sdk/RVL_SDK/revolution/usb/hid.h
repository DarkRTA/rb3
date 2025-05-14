#ifndef RVL_SDK_HID_H
#define RVL_SDK_HID_H
#include "revolution/IPC.h"
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _HIDClient {
    _HIDClient *next;
    void *attachHandler;
    unsigned long user;
} _HIDClient;

typedef struct HIDDevice {
    long fd;
    u16 vid;
    u16 pid;
    u8 iInterface;
    u8 endpoint_address_in;
    u8 endpoint_address_out;
    u8 inst;
    void *p_hdd;
    void *p_hcd;
    void *p_hid;
    void *p_hed0;
    void *p_hed1;
} HIDDevice;

typedef int (*AttachHandler_t)(_HIDClient *client, HIDDevice *device, unsigned long user);
typedef int (*DetachHandler_t)(long result, unsigned long user);

int HIDOpenAsync(void *memory, void *callback, void *user);
void HIDRegisterClient(_HIDClient *client, AttachHandler_t handler);
void HIDUnregisterClientAsync(_HIDClient *client, DetachHandler_t handler, void *user);

#ifdef __cplusplus
}
#endif
#endif
