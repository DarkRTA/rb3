#pragma once
#include "os/Debug.h"

enum MidiMetaEvent {
    kSequenceNumber = 0,
    kTextEvent = 1,
    kCopyrightNotice = 2,
    kTrackname = 3,
    kInstrumentName = 4,
    kLyricEvent = 5,
    kMarkerText = 6,
    kCuePoint = 7,
    kChannelPrefix = 0x20,
    kMidiPort = 0x21,
    kEndOfTrack = 0x2F,
    kTempoSetting = 0x51,
    kSMPTEOffset = 0x54,
    kTimeSignature = 0x58,
    kKeySignature = 0x59,
    kSequencerSpecific = 0x7F
};

enum MidiStatusType {
    kNoteOff = 0x80,
    kNoteOn = 0x90,
    kAfterTouch = 0xA0,
    kController = 0xB0,
    kProgramChange = 0xC0,
    kChannelPressure = 0xD0,
    kPitchModulation = 0xE0,
    kSysEx = 0xF0
};

inline unsigned char MidiGetStatus(unsigned char uc) {}

/** Does this midi message have a status? */
inline bool MidiIsStatus(unsigned char status) { return status & 0x80; }

/** Get the MidiStatusType of this midi message. */
inline unsigned char MidiGetType(unsigned char status) {
    MILO_ASSERT(MidiIsStatus(status), 0x2f);
    return status & 0xF0;
}

/** Is this midi message a SysEx message? */
inline bool MidiIsSystem(unsigned char uc) { return MidiGetType(uc) == kSysEx; }

/** Get the channel associated with this midi message. */
inline unsigned char MidiGetChannel(unsigned char status) {
    MILO_ASSERT(MidiIsStatus(status), 0x40);
    MILO_ASSERT(!MidiIsSystem(status), 0x41);
    return status & 0xF;
}
