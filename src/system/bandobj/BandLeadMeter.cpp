#include "bandobj/BandLeadMeter.h"

BandLeadMeter::BandLeadMeter() : unk18c(this, 0), unk198(this, 0), unk1a4(this, 0), unk1b0(this, 0), unk1bc(this, 0), unk1c8(this, 0), unk1d4(this, 0), unk1e0(this, 0),
    unk1ec(this, 0), unk1f8(this, 0), unk204(10000), unk208(0) {
    SyncScores();
}