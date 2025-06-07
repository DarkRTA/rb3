#include "meta_band/StoreInfoPanel.h"
#include "meta/StoreArtLoaderPanel.h"
#include "meta_band/BandStoreOffer.h"
#include "net/Net.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "ui/UIPanel.h"
#include "utl/Messages2.h"
#include "utl/Messages3.h"
#include "utl/NetLoader.h"
#include "utl/Std.h"
#include "utl/Symbols.h"

StoreInfoPanel *TheStoreInfoPanel;

StoreInfoPanel::StoreInfoPanel()
    : mOffer(this), mLoader(0), mCurRecommendationIdx(0), unk5c(0) {
    TheStoreInfoPanel = this;
}

StoreInfoPanel::~StoreInfoPanel() { ClearData(); }

void StoreInfoPanel::Enter() {
    if (mOffer == 0) {
        MILO_FAIL("StoreInfoPanel needs an offer set before Enter()!");
    }
    UIPanel::Enter();
}

void StoreInfoPanel::Poll() {
    StoreArtLoaderPanel::Poll();
    if (mLoader != 0) {
        mLoader->PollLoading();
        if (mLoader->IsLoaded()) {
            if (mLoader->unk_0x4 != 0) {
                if (ParseRecommendations(mLoader->unk_0x4)) {
                    mCurRecommendationIdx = 0;
                    PushRecommendationsReady();
                } else {
                    PushRecommendationFailure();
                }
            } else {
                PushRecommendationFailure();
            }
            RELEASE(mLoader);
        } else {
            if (mLoader->HasFailed()) {
                PushRecommendationFailure();
                RELEASE(mLoader);
            }
        }
    } else {
        if (mRecommendations.size() && !unk5c && IsAllArtLoadedOrFailed()) {
            MILO_ASSERT(mRecommendations.size() == mCoverArtTexs.size(), 0x67);
            for (int i = 0; i < mRecommendations.size(); i++) {
                RndBitmap *bmp = GetBmp(mRecommendations[i].unkc);
                if (bmp) {
                    MILO_ASSERT(!mCoverArtTexs[i], 0x6F);
                    RndTex *tex = Hmx::Object::New<RndTex>();
                    mCoverArtTexs[i] = tex;
                    mCoverArtTexs[i]->SetBitmap(*bmp, nullptr, false);
                }
            }
            unk5c = true;
            PushRecommendationsReady();
        }
    }
}

void StoreInfoPanel::Unload() {
    ClearData();
    StoreArtLoaderPanel::Unload();
}

void StoreInfoPanel::ClearData() {
    mOffer = nullptr;
    unk5c = 0;
    DeleteAll(mCoverArtTexs);
    mCoverArtTexs.resize(0);
    RELEASE(mLoader);
    ClearAndShrink(mRecommendations);
    ClearArt();
}

void StoreInfoPanel::FetchRecommendations() {
    if (!mLoader) {
        MILO_ASSERT(mOffer, 0x98);
        BandStoreOffer *offer = dynamic_cast<BandStoreOffer *>(mOffer.Ptr());
        MILO_ASSERT(offer, 0x9C);
        String str20;
        if (!offer->Exists()) {
            str20 = offer->mPackedData->GetOfferId();
            String path;
            GetRecommendationIndexPath(str20.c_str(), path);
            mLoader = new DataNetLoader(path);
        } else
            PushRecommendationFailure();
    }
}

void StoreInfoPanel::RotateRecommendation() {
    mCurRecommendationIdx = (mCurRecommendationIdx + 1) % mRecommendations.size();
}

const StoreInfoPanel::RecommendedEntry *StoreInfoPanel::CurrentRecommendation() const {
    MILO_ASSERT(!mRecommendations.empty(), 200);
    return &mRecommendations[mCurRecommendationIdx];
}

bool StoreInfoPanel::ParseRecommendations(DataArray *data) {
    MILO_ASSERT(data, 0xCE);
    data->AddRef();
    ClearAndShrink(mRecommendations);
    DataArray *cnt = data->FindArray(content, false);
    if (cnt) {
        int cap = cnt->Size() - 1;
        for (int i = 0; i < cap; i++) {
            RecommendedEntry entry;
            DataArray *result = cnt->Array(i + 1);
            if (result->Size() >= 3) {
                entry.unk0 = result->Str(0);
                entry.unkc = "/dlc_store";
                entry.unkc += result->Str(1);
                entry.unk18 = result->Str(2);
                EnsureArtLoader(entry.unkc);
                mRecommendations.push_back(entry);
                mCoverArtTexs.push_back(nullptr);
            } else {
                TheDebug
                    << "StoreInfoPanel::ParseRecommendations: invalid recommendation result:\n"
                    << result << "\n";
            }
        }
    }
    data->Release();
    return !mRecommendations.empty();
}

void StoreInfoPanel::GetRecommendationIndexPath(const char *cc, String &str) {
    static const char *pathFmt = "dlc_store/%s/%s/related/%s.dta";
    Symbol regionSym = PlatformRegionToSymbol(ThePlatformMgr.GetRegion());
    str = MakeString(pathFmt, regionSym, SystemLanguage(), cc);
    Server *server = TheNet.GetServer();
    if (server && server->IsConnected()) {
        str += MakeString("?pid=%u", server->GetMasterProfileID());
    }
}

void StoreInfoPanel::PushRecommendationFailure() { HandleType(no_recommendations_msg); }
void StoreInfoPanel::PushRecommendationsReady() { HandleType(recommendations_ready_msg); }

RndTex *StoreInfoPanel::GetRecommendationTex(int idx) {
    int numRecs = mRecommendations.size();
    int mod = (idx + mCurRecommendationIdx - 1) % numRecs;
    if (mod < 0)
        mod += numRecs;
    return mCoverArtTexs[mod];
}

BEGIN_PROPSYNCS(StoreInfoPanel)
    SYNC_PROP(cur_offer, mOffer)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS

BEGIN_HANDLERS(StoreInfoPanel)
    HANDLE_ACTION(fetch_recommendations, FetchRecommendations())
    HANDLE_EXPR(recommendation_path, CurrentRecommendation()->unk18)
    HANDLE_ACTION(rotate_recommendation, RotateRecommendation())
    HANDLE_EXPR(get_recommendation_tex, GetRecommendationTex(_msg->Int(2)))
    HANDLE_ACTION(clear_data, ClearData())
    HANDLE_SUPERCLASS(StoreArtLoaderPanel)
    HANDLE_CHECK(0x132)
END_HANDLERS