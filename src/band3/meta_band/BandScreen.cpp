#include "meta_band/BandScreen.h"
#include "meta_band/BandUI.h"
#include "obj/Data.h"
#include "ui/UIScreen.h"
#include "utl/Messages.h"

void BandScreen::Enter(UIScreen *s) {
    UIScreen::Enter(s);
    DataNode handled = HandleType(block_wipe_in_msg);
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

void BandScreen::LoadPanels() {}

BEGIN_HANDLERS(BandScreen)
    HANDLE_SUPERCLASS(UIScreen)
    HANDLE_CHECK(0x88)
END_HANDLERS