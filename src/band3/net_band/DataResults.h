#pragma once
#include "obj/Msg.h"
#include "utl/Str.h"
#include "network/Platform/String.h"
#include <list>
#include <map>

class ContextWrapper;

class Updatable {
public:
    Updatable(){}
    virtual ~Updatable(){}
    virtual void Update(Message*) = 0;
    virtual void SetWrapper(ContextWrapper*) = 0;
};

class DataResult {
public:
    DataResult(){}
    virtual ~DataResult(){}

    bool GetDataResultValue(String, DataNode&) const;

    String mUrl; // 0x0
    std::map<String, DataNode> mDataMap; // 0xc
};

class DataResultList : public Updatable {
public:
    DataResultList();
    virtual ~DataResultList();
    virtual void Update(Message*);
    virtual void SetWrapper(ContextWrapper*);

    void Clear();
    DataResult* GetDataResult(int) const;
    int NumDataResults() const { return mDataResultList.size(); }

    int unk4; // 0x4
    Quazal::String* mQDataResultString; // 0x8
    std::list<DataResult> mDataResultList; // 0xc
    bool mUpdated; // 0x14
};