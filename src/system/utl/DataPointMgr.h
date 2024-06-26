#ifndef UTL_DATAPOINTMGR_H
#define UTL_DATAPOINTMGR_H

#include "obj/Data.h"
#include <map>

class DataPoint {
public:
    DataPoint();
    DataPoint(const char *);

    void AddPair(const char *, DataNode);
    void AddPair(Symbol, DataNode);

    Symbol mType;
    std::map<Symbol, DataNode> mNameValPairs;
};

typedef void DataPointRecordFunc(DataPoint &, int);

class DataPointMgr {
public:
    DataPointMgr();

    DataPointRecordFunc *SetDataPointRecorder(DataPointRecordFunc *);
    void RecordDataPoint(DataPoint &, int);

    DataPointRecordFunc *mDataPointRecorder;
};

extern DataPointMgr &TheDataPointMgr;

template <class N1, class V1> void SendDataPoint(const char *type, N1 name1, V1 value1) {
    DataPoint point(type);
    point.AddPair(name1, value1);
    TheDataPointMgr.RecordDataPoint(point, 1);
}

template <class N1, class V1, class N2, class V2>
void SendDataPoint(const char *type, N1 name1, V1 value1, N2 name2, V2 value2) {
    DataPoint point(type);
    point.AddPair(name1, value1);
    point.AddPair(name2, value2);
    TheDataPointMgr.RecordDataPoint(point, 1);
}

template <class N1, class V1, class N2, class V2, class N3, class V3>
void SendDataPoint(
    const char *type,
    // clang-format off: looks nicer this way
    N1 name1, V1 value1,
    N2 name2, V2 value2,
    N3 name3, V3 value3
    // clang-format on
) {
    DataPoint point(type);
    point.AddPair(name1, value1);
    point.AddPair(name2, value2);
    point.AddPair(name3, value3);
    TheDataPointMgr.RecordDataPoint(point, 1);
}

template <class N1, class V1, class N2, class V2, class N3, class V3, class N4, class V4>
void SendDataPoint(
    const char *type,
    // clang-format off
    N1 name1, V1 value1,
    N2 name2, V2 value2,
    N3 name3, V3 value3,
    N4 name4, V4 value4
    // clang-format on
) {
    DataPoint point(type);
    point.AddPair(name1, value1);
    point.AddPair(name2, value2);
    point.AddPair(name3, value3);
    point.AddPair(name4, value4);
    TheDataPointMgr.RecordDataPoint(point, 1);
}

#endif
