#ifndef RB3_BLOCKMGR_HPP
#define RB3_BLOCKMGR_HPP
#include "arkfile.hpp"

class BlockMgr {
public:
    long long list1; // std::list
    long long list2; // ditto
    int unk10, unk14, unk18;

    void KillBlockRequests(ArkFile *);
    void Poll();
};

#endif