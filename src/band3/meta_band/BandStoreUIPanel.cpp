#include "meta_band/BandStoreUIPanel.h"
#include "meta_band/BandStorePanel.h"
#include "meta_band/InputMgr.h"
#include "obj/Data.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "utl/Symbols2.h"

DataNode BandStoreUIPanel::FilterButtonMsg(const ButtonDownMsg &msg) {
    BandStorePanel *panel = BandStorePanel::Instance();
    BandUser *inputUser = TheInputMgr->GetUser();
    if ((inputUser && inputUser != (User *)msg.GetUser())
        || (panel->IsEnumerating() || panel->InCheckout()))
        return 1;
    else
        return DataNode(kDataUnhandled, 0);
}

BEGIN_HANDLERS(BandStoreUIPanel)
    if (sym == button_down) {
        DataNode result = FilterButtonMsg(ButtonDownMsg(_msg));
        if (result.Type() != kDataUnhandled) {
            return result;
        }
    }
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x23)
END_HANDLERS
