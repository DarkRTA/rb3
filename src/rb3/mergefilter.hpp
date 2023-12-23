#ifndef RB3_MERGEFILTER_HPP
#define RB3_MERGEFILTER_HPP
#include "data.hpp"

class MergeFilter {
public:
    MergeFilter(DataNode *, int);
    virtual ~MergeFilter();
    virtual DataNode *GetDataNode();
    virtual void fn_803222E4();
    virtual void Unknown() = 0;

    DataNode *node;
    int i;
};

#endif
