#ifndef RB3_DATAMERGEFILTER_HPP
#define RB3_DATAMERGEFILTER_HPP
#include "data.hpp"
#include "mergefilter.hpp"
#include "hmx/object.hpp"

class DataMergeFilter : public MergeFilter {
public:
    DataMergeFilter(DataNode *, int); // fn_80320314
    virtual ~DataMergeFilter(); // fn_803201F4
    virtual int Filter(Hmx::Object*, Hmx::Object*); // fn_8032215C

    DataType nodeType;
    DataFunc* filterFunc;
    Hmx::Object* filterObj;
    int filterInt;

};

#endif
