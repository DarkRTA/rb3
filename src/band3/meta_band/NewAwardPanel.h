#pragma once
#include "game/BandUser.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/Award.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "ui/UIListProvider.h"
#include "utl/Symbol.h"

class AwardAssetProvider : public UIListProvider, public Hmx::Object {
public:
    AwardAssetProvider(const std::vector<DynamicTex*>& icons) : unk20(gNullStr), mIcons(icons), mMaleMat(0), mFemaleMat(0), mUnisexMat(0) {}
    virtual ~AwardAssetProvider(){}
    virtual void InitData(RndDir*);
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual Symbol DataSymbol(int i_iIndex) const;
    virtual int NumData() const { return unk24.size(); }

    void Update(Symbol s);

    RndMat* GetMatForName(String& str) const {
        std::vector<DynamicTex*>::const_iterator it = std::find(mIcons.begin(), mIcons.end(), str);
        RndMat* ret;
        if(it != mIcons.end()) ret = (*it)->mMat;
        else {
            MILO_WARN("No Icon found for %s!", str.c_str());
            ret = nullptr;
        }
        return ret;
    }

    Symbol unk20; // 0x20
    std::vector<Symbol> unk24; // 0x24
    const std::vector<DynamicTex*>& mIcons; // 0x2c
    RndMat* mMaleMat; // 0x30
    RndMat* mFemaleMat; // 0x34
    RndMat* mUnisexMat; // 0x38
};

class NewAwardPanel : public TexLoadPanel {
public:
    NewAwardPanel();
    OBJ_CLASSNAME(NewAwardPanel);
    OBJ_SET_TYPE(NewAwardPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~NewAwardPanel(){}
    virtual void Enter();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();

    void PopAndShowFirstAward();
    void LoadIcons();
    int GetNumAssets() const;

    LocalBandUser* mUser; // 0x4c
    Symbol mAwardName; // 0x50
    Symbol mAwardReason; // 0x54
    AwardAssetProvider* m_pAwardAssetProvider; // 0x58
};