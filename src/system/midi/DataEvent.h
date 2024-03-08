#ifndef MIDI_DATAEVENT_H
#define MIDI_DATAEVENT_H
#include "obj/Data.h"
#include <vector>
#include <list>

class DataEvent {
public:
    DataEvent() : start(0.0f), end(0.0f), mMsg(0) { }
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

    DataEventList();
    void Reset(float f);
    void Clear();

    int mCurIndex;
    int mSize;
    std::vector<DataEvent, unsigned short> mEvents;
    std::vector<CompEv, unsigned int> mComps;
    int mElement;
    DataEvent mTemplate;
    DataType mCompType;
    int* mValue;
};

#endif
