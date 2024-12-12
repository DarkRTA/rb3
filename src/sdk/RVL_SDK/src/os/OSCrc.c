#include <revolution/os/OSCrc.h>

u32 OSCalcCRC32(const void *buf, u32 length) {
    static u32 crc32_table[16] = { 0x00000000, 0x1DB71064, 0x3B6E20C8, 0x26D930AC,
                                   0x76DC4190, 0x6B6B51F4, 0x4DB26158, 0x5005713C,
                                   0xEDB88320, 0xF00F9344, 0xD6D6A3E8, 0xCB61B38C,
                                   0x9B64C2B0, 0x86D3D2D4, 0xA00AE278, 0xBDBDF21C };
    unsigned int crc = -1;
    u8 *buf2 = (void *)buf;
    while (length--) {
        crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *buf2) & 255];
        buf2++;
    }
    return ~crc;
}
