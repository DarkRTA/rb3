#pragma once
#include "game/BandUser.h"
#include "meta/StoreEnumeration.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralMsgs.h"
#include "os/JoypadMsgs.h"
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"

class TokenRedemptionPanel : public UIListProvider, public UIPanel {
public:
    enum RedemptionState {
        kIdle = 0,
        kRequestingOffers = 2,
        kPurchasing = 7,
        kReportingPurchase = 8
    };
    TokenRedemptionPanel();
    virtual ~TokenRedemptionPanel() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual int NumData() const;
    OBJ_CLASSNAME(TokenRedemptionPanel);
    OBJ_SET_TYPE(TokenRedemptionPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Enter();
    virtual void Poll();
    virtual void Unload();

    const char *GetListString(int) const;
    void GetOffersForToken(const char *, LocalBandUser *);
    void GetPreviousOffersForUser(LocalBandUser *);
    void EnumerateOffers(LocalBandUser *);
    void ShowPurchaseUIForOffer(int, LocalBandUser *);

    DataNode OnMsg(const ButtonDownMsg &);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);

    int mRedemptionState; // 0x3c
    String mActiveToken; // 0x40
    DataResultList mResultList; // 0x4c
    std::vector<String> mListData; // 0x64
    int mSelectedOfferIndex; // 0x6c
    StoreEnumeration *mEnumeration; // 0x70
    StoreEnumeration *mPurchaser; // 0x74 - StorePurchaser*?
};