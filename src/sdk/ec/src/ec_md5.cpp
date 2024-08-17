#include <ec/md5.h>
#include <ec/internal/md5.h>

namespace ec {

    ECResult ec::md5_sum(const void* data, size_t length, ECString& dest) {
        MD5_CTX md5;
        unsigned char hash[16];
        MD5_Init(&md5);
        MD5_Update(&md5, data, length);
        MD5_Final(hash, &md5);

        dest.clear();
        if (EC_FAIL(ec::hex_encode(hash, sizeof(hash), dest))) {
            return ECResult_Failure;
        }

        return ECResult_Success;
    }

}
