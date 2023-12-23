#ifndef RB3_DATAMERGEFILTER_HPP
#define RB3_DATAMERGEFILTER_HPP
#include "data.hpp"
#include "mergefilter.hpp"

class DataMergeFilter : public MergeFilter {
public:
    DataMergeFilter(DataNode *, int); // fn_80320314
    virtual ~DataMergeFilter(); // fn_803201F4
    virtual DataNode *GetDataNode(); // fn_8032215C

    int filler;
};

#endif
