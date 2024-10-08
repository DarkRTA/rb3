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
    DataResult();
    virtual ~DataResult();

    String mUrl; // 0x0
    std::map<String, DataNode> mDataMap; // 0xc
};

class DataResultList : public Updatable {
public:
    DataResultList();
    virtual ~DataResultList();
    virtual void Update(Message*);
    virtual void SetWrapper(ContextWrapper*);

    int unk4;
    Quazal::String* unk8;
    std::list<DataResult> unkc;
    bool unk14;
};