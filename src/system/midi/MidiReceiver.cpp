#include "midi/Midi.h"
#include "os/Debug.h"
#include "utl/MBT.h"

MidiReceiver::MidiReceiver() : mReader(0) {
    
}

void MidiReceiver::Error(const char* cc, int i){
    MILO_ASSERT(mReader, 0x16);
    if(i != -1){
        MILO_WARN("%s (%s): %s at %s", mReader->GetFilename(), mReader->mCurTrackName.c_str(), cc, TickFormat(i, *mReader->mMeasureMap));
    }
    else MILO_WARN("%s (%s): %s", mReader->GetFilename(), mReader->mCurTrackName.c_str(), cc);
}

void MidiReceiver::SkipCurrentTrack(){
    MILO_ASSERT(mReader, 0x2B);
    mReader->SkipCurrentTrack();
}
