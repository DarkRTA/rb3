#ifndef MIDI_DATAEVENT_H
#define MIDI_DATAEVENT_H
#include "obj/Data.h"
#include <vector>
#include <list>

class DataEvent {
public:
    DataEvent() : start(0.0f), end(0.0f), mMsg(0) { }
    DataEvent(float s, float e, DataArray* da) : start(s), end(e), mMsg(da) {
        if(mMsg) mMsg->AddRef();
    }
    ~DataEvent(){ if(mMsg) mMsg->Release(); }

    void SetMsg(DataArray* da){
        if(mMsg) mMsg->Release();
        mMsg = da;
        if(mMsg) mMsg->AddRef();
    }
    DataArray* Msg() const { return mMsg; }

    float start; // 0x0
    float end; // 0x4
    DataArray* mMsg; // 0x8
};

class DataEventList {
public:
    struct CompEv {
        float start;
        float end;
        int value;
    };

    DataEventList();
    ~DataEventList();
    void InsertEvent(float, float, const DataNode&, int);
    void Reset(float f);
    void Clear();
    void Compress(DataArray*, int);
    void SecOffset(float);
    int Size() const { return mSize; }
    int FindStartFromBack(float) const;
    const DataEvent& Event(int) const;
    DataEvent* NextEvent(float);
    float* EndPtr(int);
    void Invert(float);
    int CurIndex() const { return mCurIndex; }

    int mCurIndex; // 0x0
    int mSize; // 0x4
    std::vector<DataEvent> mEvents; // 0x8
    std::vector<CompEv, unsigned int> mComps; // 0x10
    int mElement; // 0x1c
    DataEvent mTemplate; // 0x20, 0x24, 0x28
    DataType mCompType; // 0x2c
    int* mValue; // 0x30
};

#endif
