#include "TourPerformerRemote.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "tour/TourPerformer.h"
#include "tour/TourProgress.h"
#include "utl/Symbols.h"

TourPerformerRemote::TourPerformerRemote(BandUserMgr &bum) : TourPerformerImpl(bum) {}

TourPerformerRemote::~TourPerformerRemote() {}

void TourPerformerRemote::SyncLoad(BinStream &bs, uint ui) {
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 38);
    pProgress->SyncLoad(bs);
    bs >> mQuestFilter;
    {
        uint bs_name = 0;
        bs >> bs_name;
        mFilterType = (TourSetlistType)bs_name;
    };
    mGigData.erase(mGigData.begin(), mGigData.end());
    int siz;
    bs >> siz;
    for (int i = 0; i < siz; i++) {
        GigData gd(420);
        bs >> gd.unk0;
        bs >> gd.unk4;
        bs >> gd.unk8;
        bs >> gd.unkc;
        mGigData.push_back(gd);
    }
}

void TourPerformerRemote::OnSynchronized(uint ui) {
    DataArray *pDA;
    {
        DataNode dn = update_tour_display;
        pDA = new DataArray(1);
        pDA->Node(0) = dn;
    }
    pDA->Execute();
    pDA->Release();
}