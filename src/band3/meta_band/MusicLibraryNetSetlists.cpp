#include "meta_band/MusicLibraryNetSetlists.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/ProfileMgr.h"
#include "net_band/RockCentral.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Utl.h"
#include "utl/BufStream.h"
#include "utl/NetCacheMgr.h"
#include "utl/Std.h"
#include "utl/Symbol.h"

MusicLibraryNetSetlists::MusicLibraryNetSetlists()
    : mFailed(0), mSucceeded(0), unk48(0), mPendingSetlistArt(0), unk50(gNullStr),
      mSetlistArtLoader(0) {}

MusicLibraryNetSetlists::~MusicLibraryNetSetlists() {
    CleanUp();
    DeleteAll(unk20);
    DeleteAll(unk28);
}

void MusicLibraryNetSetlists::Poll() {
    if (mSetlistArtLoader) {
        MILO_ASSERT(mPendingSetlistArt, 0x2C);
        if (mSetlistArtLoader->IsLoaded()) {
            RndBitmap bmap;
            BufStream bs(
                mSetlistArtLoader->GetBuffer(), mSetlistArtLoader->GetSize(), true
            );
            bmap.Load(bs);
            SwapDxtEndianness(&bmap);
            bmap.SetMip(nullptr);
            mPendingSetlistArt->SetBitmap(bmap, nullptr, false);
            TheNetCacheMgr->DeleteNetCacheLoader(mSetlistArtLoader);
            mSetlistArtLoader = nullptr;
            FinishGettingSetlistArt(true);
        } else if (mSetlistArtLoader->HasFailed()) {
            TheNetCacheMgr->DeleteNetCacheLoader(mSetlistArtLoader);
            mSetlistArtLoader = nullptr;
            FinishGettingSetlistArt(false);
        }
    }
}

void MusicLibraryNetSetlists::RefreshSetlists() {
    MILO_ASSERT(!mFailed && !mSucceeded, 0x4F);
    std::vector<BandProfile *> profiles = TheProfileMgr.GetSignedInProfiles();
    unk48 = false;
    TheRockCentral.GetAllSonglists(profiles, mDataResults, this);
}

void MusicLibraryNetSetlists::RefreshArchivedBattles() {
    std::vector<BandProfile *> profiles = TheProfileMgr.GetSignedInProfiles();
    unk48 = true;
    TheRockCentral.GetAllSonglists(profiles, mDataResults, this);
}

void MusicLibraryNetSetlists::CleanUp() {
    mFailed = false;
    mSucceeded = false;
    TheRockCentral.CancelOutstandingCalls(this);
    DeleteAll(unk20);
    DeleteAll(unk28);
    mDataResults.Clear();
    CleanUpArt();
    FOREACH (it, mSetlists) {
        RELEASE(it->unk4);
    }
    mSetlists.clear();
}

DataNode MusicLibraryNetSetlists::OnMsg(const RockCentralOpCompleteMsg &msg) {
    if (!mPendingSetlistArt) {
        if (msg.Success()) {
            mDataResults.Update(nullptr);
            ParseDataResultsIntoSetlists(unk48);
            mDataResults.Clear();
            if (!unk48) {
                RefreshArchivedBattles();
                return 1;
            }
            mSucceeded = true;
        } else {
            DeleteAll(unk20);
            DeleteAll(unk28);
            mDataResults.Clear();
            mFailed = true;
        }
        TheMusicLibrary->RebuildAndSortSetlists();
    } else
        FinishGettingSetlistArt(msg.Success());
    return 1;
}

void MusicLibraryNetSetlists::FinishGettingSetlistArt(bool b1) {
    if (b1 && mPendingSetlistArt->Height() && mPendingSetlistArt->Width()) {
        TheMusicLibrary->SetlistArtFinished();
    } else {
        RELEASE(mPendingSetlistArt);
    }
}

void MusicLibraryNetSetlists::ParseDataResultsIntoSetlists(bool archived) {
    std::vector<NetSavedSetlist *> &setlists = archived ? unk28 : unk20;
    DeleteAll(setlists);
    MILO_LOG("Setlists from net:\n");
    mDataResults.Print(TheDebug);
    MILO_LOG("\n");
    std::list<DataResult> &results = mDataResults.mDataResultList;
    FOREACH (it, results) {
    }
}

BEGIN_HANDLERS(MusicLibraryNetSetlists)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1FE)
END_HANDLERS