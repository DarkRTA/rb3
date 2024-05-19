#include "ui/PanelDir.h"
#include "ui/UIComponent.h"
#include "rndobj/Cam.h"

PanelDir::PanelDir() : mFocusComponent(0), mPanel(0), mCam(this, 0), mCanEndWorld(1), mUseSpecifiedCam(0), mShowEditModePanels(0), mShowFocusComponent(1) {
    
}