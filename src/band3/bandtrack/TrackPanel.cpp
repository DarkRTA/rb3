#include "bandtrack/TrackPanel.h"
#include "os/System.h"

TrackPanel* TheTrackPanel;

TrackPanel* GetTrackPanel(){
    return TheTrackPanel;
}

TrackPanel::TrackPanel() : mConfig(SystemConfig("track_graphics")), unk4c(2), unk50(this, 0), unk5c(0), unk5d(0), unk5e(0), unk5f(0), unk60(0), unk61(1), unk62(0), mAutoVocals(0),
    unk7c(0), unk80(0), unk84(0), unk88(5), unk8c(-1.0f) {
    for(int i = 0; i < 5; i++){
        mTrackSlots.push_back(TrackSlot());
    }
    TheTrackPanel = this;
}

TrackPanel::~TrackPanel(){
    CleanUpReloadChecks();
    TheTrackPanel = nullptr;
}