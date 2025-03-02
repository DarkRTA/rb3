#pragma once
#include "meta/StorePanel.h"
#include "obj/Msg.h"

class BandStorePanel : public StorePanel, public MsgSource {
public:
    BandStorePanel();
    OBJ_CLASSNAME(BandStorePanel);
    OBJ_SET_TYPE(BandStorePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~BandStorePanel();

    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;

    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual bool IsSongInLibrary(const int &) const;
    virtual void ExitStore(StoreError) const;
    virtual int StoreUser() const; // fix ret type
    virtual void MakeNewOffer(const StorePackedOfferBase *, bool);
    virtual StoreOffer *FindOffer(Symbol) const;
    virtual bool EnumerateSubsetOfOfferIDs() const { return false; }
    virtual void LoadArt(const char *, UIPanel *);
    virtual int UpdateOffers(const std::list<EnumProduct> &, bool);
    virtual void StoreUserProfileSwappedToUser(LocalUser *);

    static BandStorePanel *Instance();
};