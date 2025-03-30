#pragma once
#include "obj/Msg.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "network/Platform/String.h"
#include "net_band/Updatable.h"
#include "utl/TextStream.h"
#include <list>
#include <map>

class ContextWrapper;

class DataResult {
public:
    DataResult() {}
    virtual ~DataResult() {}

    bool GetDataResultValue(String, DataNode &) const;

    String mUrl; // 0x0
    std::map<String, DataNode> mDataMap; // 0xc
};

class DataResultList : public Updatable {
public:
    DataResultList();
    virtual ~DataResultList();
    virtual void Update(Message *);
    virtual void SetWrapper(ContextWrapper *);

    void Clear();
    void Print(TextStream &);
    DataResult *GetDataResult(int) const;
    int NumDataResults() const { return mDataResultList.size(); }

    Quazal::String *mQDataResultString; // 0x8
    std::list<DataResult> mDataResultList; // 0xc
    bool mUpdated; // 0x14
};