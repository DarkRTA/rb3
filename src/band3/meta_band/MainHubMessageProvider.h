#pragma once
#include "game/Defines.h"
#include "meta_band/AppLabel.h"
#include "meta_band/MainHubPanel.h"
#include "obj/Object.h"
#include "ui/UIListProvider.h"

enum TickerDataType {

};

class TickerData {
public:
    TickerData() : isSet(0) {}

    ScoreType unk0;
    int unk4;
    bool unk8;
    bool unk9;
    bool isSet; // 0xa
};

class MainHubMessageProvider : public UIListProvider, public Hmx::Object {
public:
    MainHubMessageProvider(MainHubPanel*);
    virtual ~MainHubMessageProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void SetData(DataNode);

    void SetMessageLabel(AppLabel*, int) const;
    void AddUnlinkedMotd(const char*);
    void ClearData();
    bool IsTickerDataValid(TickerDataType);
    void AddTickerData(TickerDataType, int, int, bool, bool);

    DataNode mMessages; // 0x20
    MainHubPanel* mMainHub; // 0x28
    TickerData mRoleStanding; // 0x2c
    TickerData unk38; // 0x38
    TickerData unk44; // 0x44
    String unk50; // 0x50
};