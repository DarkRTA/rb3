#ifndef MIDI_MIDIPARSER_H
#define MIDI_MIDIPARSER_H

#include "obj/MsgSource.h"
#include "midi/DataEvent.h"
#include <list>

class MidiParser : public MsgSource { // 0xd0
public: 
    struct PostProcess {
        PostProcess();
        bool a;
        float b;
        float c;
        float d;
        float e;
        float f;
        float g;
        bool h;
        float j;
    };

    struct Note {

    };

    MidiParser();
    virtual ~MidiParser();

    void Clear();
    void Reset(float);

    DataEventList* mEvents;

    static Hmx::Object* NewObject();
    static void Init();

    static std::list<MidiParser> sParsers;
};

#endif // MIDI_MIDIPARSER_H
