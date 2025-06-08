#pragma once
#include "meta/StoreArtLoaderPanel.h"
#include "meta/StoreOffer.h"
#include "utl/NetLoader.h"

class StoreInfoPanel : public StoreArtLoaderPanel {
public:
    class RecommendedEntry {
    public:
        String unk0;
        String unkc;
        String unk18;
    };
    StoreInfoPanel();
    OBJ_CLASSNAME(UIPanel);
    OBJ_SET_TYPE(UIPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~StoreInfoPanel();
    virtual void Enter();
    virtual void Poll();
    virtual void Unload();
    virtual bool SyncProperty(DataNode &_val, DataArray *_prop, int _i, PropOp _op);

    void ClearData();
    void FetchRecommendations();
    void RotateRecommendation();
    void GetRecommendationIndexPath(const char *, String &);
    const RecommendedEntry *CurrentRecommendation() const;
    bool ParseRecommendations(DataArray *);
    RndTex *GetRecommendationTex(int);
    void PushRecommendationFailure();
    void PushRecommendationsReady();

    ObjPtr<StoreOffer> mOffer; // 0x40, 0x44, 0x48
    std::vector<RecommendedEntry> mRecommendations; // 0x4c, 0x50, 0x52
    DataNetLoader *mLoader; // 0x54
    int mCurRecommendationIdx; // 0x58
    bool unk5c; // 0x5c
    std::vector<RndTex *> mCoverArtTexs; // 0x60
};

extern StoreInfoPanel *TheStoreInfoPanel;