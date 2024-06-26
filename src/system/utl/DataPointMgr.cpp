#include "utl/DataPointMgr.h"
#include <utility>

DataPointMgr gDataPointMgr;
DataPointMgr &TheDataPointMgr = gDataPointMgr;

DataPoint::DataPoint() {
}
DataPoint::DataPoint(const char *type) {
    // someone forgot their initializer lists at home
    mType = type;
}

void DataPoint::AddPair(const char *name, DataNode value) {
    mNameValPairs.insert(std::make_pair(name, value));
}

void DataPoint::AddPair(Symbol name, DataNode value) {
    mNameValPairs.insert(std::make_pair(name, value));
}

DataPointMgr::DataPointMgr() : mDataPointRecorder(nullptr) {
}

DataPointRecordFunc *DataPointMgr::SetDataPointRecorder(DataPointRecordFunc *recorder) {
    DataPointRecordFunc *old = mDataPointRecorder;
    mDataPointRecorder = recorder;
    return old;
}

void DataPointMgr::RecordDataPoint(DataPoint &point, int i) {
    if (mDataPointRecorder) {
        mDataPointRecorder(point, i);
    }
}
