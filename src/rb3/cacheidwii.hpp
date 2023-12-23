#ifndef RB3_CACHEIDWII_HPP
#define RB3_CACHEIDWII_HPP
#include "cacheid.hpp"
#include "string.hpp"

class CacheIDWii : CacheID {
public:
    CacheIDWii(); // fn_803442FC
    virtual ~CacheIDWii(); // fn_80344360
    virtual char *GetCachePath(const char *); // fn_803443E0
    virtual void GetCacheSearchPath(const char *); // fn_803444B4

    String s1;
    String s2;
    String s3;
};

#endif
