#include "obj/Msg.h"

void MsgSource::Sink::Export(DataArray* da){
    switch(mode){
        case kHandle: obj->Handle(da, false); break;
        case kExport: obj->Export(da, false); break;
        case kType: obj->HandleType(da); break;
        case kExportType: obj->Export(da, true); break;
    }
}

MsgSource::~MsgSource(){
    for(std::list<Sink>::iterator it = mSinks.begin(); it != mSinks.end(); it++){
        Hmx::Object* o = it->obj;
        if(o) o->Release(o);
    }
    for(std::list<EventSink>::iterator it = mEventSinks.begin(); it != mEventSinks.end(); it++){
        for(std::list<Sink>::iterator sit = it->sinks.begin(); sit != it->sinks.end(); sit++){
            Hmx::Object* o = sit->obj;
            if(o) o->Release(o);
        }
    }
    mEventSinks.clear();
    mSinks.clear();
}
