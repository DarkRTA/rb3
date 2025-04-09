#include "midi/Midi.h"
#include "os/Debug.h"
#include "utl/MBT.h"

MidiReceiver::MidiReceiver() : mReader(0) {}

void MidiReceiver::Error(const char *msg, int tick) {
    MILO_ASSERT(mReader, 0x16);
    if (tick != -1) {
        MILO_WARN(
            "%s (%s): %s at %s",
            mReader->GetFilename(),
            mReader->CurrentTrackName(),
            msg,
            TickFormat(tick, *mReader->GetMeasureMap())
        );
    } else
        MILO_WARN("%s (%s): %s", mReader->GetFilename(), mReader->CurrentTrackName(), msg);
}

void MidiReceiver::SkipCurrentTrack() {
    MILO_ASSERT(mReader, 0x2B);
    mReader->SkipCurrentTrack();
}
