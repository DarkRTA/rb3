#ifndef MIDI_DATAEVENT_H
#define MIDI_DATAEVENT_H
#include "obj/Data.h"
#include <vector>

class DataEvent {
public:
    float start;
    float end;
    DataArray* mMsg;
};

class DataEventList {
public:
    struct CompEv {
        float start;
        float end;
        int value;
    };
    int mCurIndex;
    int mSize;
    std::vector<DataEvent> mEvents;
    std::vector<CompEv> mComps;
    int mElement;
    DataEvent mTemplate;
    DataType mCompType;
    int* mValue;
};

#endif
