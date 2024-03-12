#include "obj/MsgSource.h"
#include "utl/Symbols.h"

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
        for(std::list<EventSinkElem>::iterator inner_it = it->sinks.begin(); inner_it != it->sinks.end(); inner_it++){
            Hmx::Object* o = inner_it->obj;
            if(o) o->Release(o);
        }
    }
}

BEGIN_HANDLERS(MsgSource);
    HANDLE(add_sink, OnAddSink);
    HANDLE(remove_sink, OnRemoveSink);
    StaticClassName();
    HANDLE_SUPERCLASS(Hmx::Object);
END_HANDLERS;
