#include "meta_band/ParentalControlPanel.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"

ParentalControlPanel::ParentalControlPanel() : unk38(0), unk3c(0) {}

void ParentalControlPanel::Enter() {
    UIPanel::Enter();
    unk3c = true;
}

void ParentalControlPanel::Poll() {
    UIPanel::Poll();
    if (unk3c) {
        HandleType(done_msg);
    }
}