#include "meta_band/BandScreen.h"
#include "meta_band/BandUI.h"
#include "meta_band/Utl.h"
#include "obj/Data.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Messages.h"

void BandScreen::Enter(UIScreen *s) {
    UIScreen::Enter(s);
    const DataNode &handled = HandleType(block_wipe_in_msg);
    if (handled.Type() == kDataUnhandled || !handled.Int()) {
        TheBandUI.WipeInIfNecessary();
    }
}

bool BandScreen::Entering() const { return UIScreen::Entering() || TheBandUI.WipingIn(); }

void BandScreen::Exit(UIScreen *s) {
    UIScreen::Exit(s);
    TheBandUI.WipeOutIfNecessary();
    UnloadInterstitials();
}

bool BandScreen::Exiting() const { return UIScreen::Exiting() || TheBandUI.WipingOut(); }

void BandScreen::LoadPanels() {
    if (!TheBandUI.mShowVignettes) {
        FOREACH (it, mPanelList) {
            if (IsVignette(it->mPanel)) {
                it->mAlwaysLoad = false;
            }
        }
    }
    UIScreen::LoadPanels();
    if (TheUI.GetTransitionState() == kTransitionTo && TheUI.PushDepth() == 0) {
        MILO_ASSERT(TheUI.TransitionScreen() == this, 0x45);
        LoadInterstitials();
    }
}

bool BandScreen::CheckIsLoaded() { return UIScreen::CheckIsLoaded(); }
bool BandScreen::IsLoaded() const { return UIScreen::IsLoaded(); }

void BandScreen::LoadInterstitials() {
    if (TheBandUI.mShowVignettes) {
        TheBandUI.mInterstitialMgr->GetInterstitialsFromScreen(this, mExtraPanels);
        FOREACH (it, mExtraPanels) {
            UIPanel *cur = *it;
            cur->CheckLoad();
            cur->CheckIsLoaded();
        }
    }
}

void BandScreen::UnloadInterstitials() {
    FOREACH_REVERSE(it, mExtraPanels) { (*it)->CheckUnload(); }
}

BEGIN_HANDLERS(BandScreen)
    HANDLE_SUPERCLASS(UIScreen)
    HANDLE_CHECK(0x88)
END_HANDLERS