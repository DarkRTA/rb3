#include <ec/md5.h>
#include <ec/internal/md5.h>

namespace ec {

    int ec::md5_sum(const void* data, size_t length, ECString& dest) {
        MD5_CTX md5;
        unsigned char hash[16];
        MD5_Init(&md5);
        MD5_Update(&md5, data, length);
        MD5_Final(hash, &md5);

        dest.clear();
        if (ec::hex_encode(hash, sizeof(hash), dest) < 0) {
            return -1;
        }

        return 0;
    }

}
