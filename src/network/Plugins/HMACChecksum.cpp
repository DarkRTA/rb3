#include "network/Plugins/HMACChecksum.h"
#include "KeyedChecksumAlgorithm.h"
#include "Plugins/Buffer.h"
#include "Plugins/MD5.h"

namespace Quazal {
    HMACChecksum::HMACChecksum() : KeyedChecksumAlgorithm(8, 0x40) {}
    HMACChecksum::~HMACChecksum() {}

    bool HMACChecksum::ComputeChecksum(const Buffer &bref, Buffer *bptr) {
        MD5 md5;
        md5.update(mKIPad, 0x40);
        md5.update(bref.GetContentPtr(), bref.GetContentSize());
        md5.finalize();
        MD5 md5_2;
        md5_2.update(mKOPad, 0x40);
        unsigned char chars[0x10];
        md5_2.update(chars, 0x10);
        md5_2.finalize();
        char data[16];
        bptr->AppendData(&data, 0x10, -1);
        return true;
    }

    unsigned int HMACChecksum::GetChecksumLength() { return 0x10; }
}