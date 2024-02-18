#ifndef RB3_MERGEFILTER_HPP
#define RB3_MERGEFILTER_HPP
#include "obj/Object.h"

enum Action {
    kMerge = 0,
    kReplace = 1,
    kKeep = 2,
};

class MergeFilter {
public:
    MergeFilter(int, int);
    virtual ~MergeFilter();
    virtual Action Filter(Hmx::Object*, Hmx::Object*);
    virtual void fn_803222E4();
    virtual void Unknown() = 0; // maybe not a method after all?

    int filter;
    int i;
};

#endif

// enum Action {
//     kMerge = 0,
//     kReplace = 1,
//     kKeep = 2,
// };
// class MergeFilter {
//     // total size: 0x8
// public:
//     void * __vptr$; // offset 0x0, size 0x4
// private:
//     enum Action mAction; // offset 0x4, size 0x4
// };
