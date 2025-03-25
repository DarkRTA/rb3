#include "meta_band/SaveLoadStatusPanel.h"
#include "meta_band/SaveLoadManager.h"
#include "obj/ObjMacros.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Messages4.h"

SaveLoadStatusPanel::SaveLoadStatusPanel() : unk38(0), unk70(0), unk71(0) {}

SaveLoadStatusPanel::~SaveLoadStatusPanel() {}

void SaveLoadStatusPanel::FinishLoad() {
    UIPanel::FinishLoad();
    TheSaveLoadMgr->AddSink(this);
}

void SaveLoadStatusPanel::Draw() {
    UIPanel::Draw();
    if (unk71 && !unk70) {
        if (unk78.SplitMs() >= 3000.0f) {
            unk71 = false;
            ThePlatformMgr.mHomeMenuWii->unk_0x9 = false;
            Handle(hide_physical_write_icon_msg, true);
            QueueDeactivation();
        }
    }
    PollDeactivation();
}

void SaveLoadStatusPanel::Unload() {
    TheSaveLoadMgr->RemoveSink(this);
    UIPanel::Unload();
}

void SaveLoadStatusPanel::CancelDeactivation() {
    if (unk38)
        unk38 = false;
}

void SaveLoadStatusPanel::QueueDeactivation() {
    if (!unk38) {
        unk38 = true;
        unk40.Restart();
    }
}

void SaveLoadStatusPanel::PollDeactivation() {
    if (unk38) {
        if (unk40.SplitMs() >= 1000.0f) {
            unk38 = false;
            Handle(deactivate_msg, true);
        }
    }
}

DataNode SaveLoadStatusPanel::OnMsg(const SaveLoadMgrStatusUpdateMsg &msg) {
    switch (msg->Int(2)) {
    case 1:
        CancelDeactivation();
        if (!unk70) {
            ThePlatformMgr.mHomeMenuWii->unk_0x9 = true;
            unk70 = true;
            unk71 = true;
            unk78.Restart();
            Handle(show_physical_write_icon_msg, false);
        }
        break;
    case 2:
    case 5:
        unk70 = false;
        break;
    }
    return 0;
}

BEGIN_HANDLERS(SaveLoadStatusPanel)
    HANDLE_MESSAGE(SaveLoadMgrStatusUpdateMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xA3)
END_HANDLERS