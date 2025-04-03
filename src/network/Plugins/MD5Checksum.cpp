#include "network/Plugins/MD5Checksum.h"
#include "Plugins/Buffer.h"
#include "Plugins/MD5.h"

namespace Quazal {
    MD5Checksum::MD5Checksum() {}
    MD5Checksum::~MD5Checksum() {}

    bool MD5Checksum::ComputeChecksum(const Buffer &bref, Buffer *bptr) {
        int buf;
        MD5 md5;
        md5.update(bref.GetContentPtr(), bref.GetContentSize());
        md5.finalize();
        bptr->AppendData(&buf, 16, -1);
        return true;
    }

    unsigned int MD5Checksum::GetChecksumLength() { return 16; }
}