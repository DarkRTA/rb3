#include "meta_band/ChooseColorPanel.h"
#include "meta_band/ClosetMgr.h"
#include "os/Debug.h"

ChooseColorPanel::ChooseColorPanel() : mCurrentOutfitConfig(0), mCurrentOutfitPiece(0), mNumOptions(-1), unk60(-1) {
    mClosetMgr = ClosetMgr::GetClosetMgr();
    MILO_ASSERT(mClosetMgr, 0x19);
}