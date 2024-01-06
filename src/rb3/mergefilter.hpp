#ifndef RB3_MERGEFILTER_HPP
#define RB3_MERGEFILTER_HPP
#include "data.hpp"
#include "hmx/object.hpp"

class MergeFilter {
public:
    MergeFilter(int, int);
    virtual ~MergeFilter();
    virtual int Filter(Hmx::Object*, Hmx::Object*);
    virtual void fn_803222E4();
    virtual void Unknown() = 0; // maybe not a method after all?

    int filter;
    int i;
};

#endif
