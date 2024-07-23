#include "obj/MsgSource.h"
#include "obj/Object.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"

void MsgSource::Sink::Export(DataArray* da){
    switch(mode){
        case kHandle: obj->Handle(da, false); break;
        case kExport: obj->Export(da, false); break;
        case kType: obj->HandleType(da); break;
        case kExportType: obj->Export(da, true); break;
    }
}
    
MsgSource::MsgSource() : mSinks(), mEventSinks(), mExporting(0) {}

MsgSource::~MsgSource(){
    for(std::list<Sink>::iterator it = mSinks.begin(); it != mSinks.end(); it++){
        Hmx::Object* o = it->obj;
        if(o) o->Release(this);
    }
    for(std::list<EventSink>::iterator it = mEventSinks.begin(); it != mEventSinks.end(); it++){
        for(std::list<EventSinkElem>::iterator inner_it = it->sinks.begin(); inner_it != it->sinks.end(); inner_it++){
            Hmx::Object* o = inner_it->obj;
            if(o) o->Release(this);
        }
    }
}

void MsgSource::ChainSource(MsgSource* source, MsgSource* othersource){
    MILO_ASSERT(source, 0x3D);
    if(!othersource) othersource = this;
    if(!mSinks.empty()){
        source->AddSink(this, Symbol(), Symbol(), MsgSource::kHandle);
    }
    else {
        for(std::list<EventSink>::iterator it = othersource->mEventSinks.begin(); it != othersource->mEventSinks.end(); it++){
            source->AddSink(this, it->ev, Symbol(), MsgSource::kHandle);
        }
    }
}

void MsgSource::AddSink(Hmx::Object* s, Symbol ev, Symbol handler, MsgSource::SinkMode mode){
    MILO_ASSERT(s, 0x5D);
    RemoveSink(s, ev);
    s->AddRef(this);
    if(ev.Null()){
        MILO_ASSERT(s != this, 0x66);
        Sink theSink(s, mode);
        if(mExporting != 0){
            mSinks.push_front(theSink);
        }
        else mSinks.push_back(theSink);
    }
    else {
        if(handler.Null()) handler = ev;
        MILO_ASSERT((s != this) || (handler != ev), 0x75);
        for(std::list<EventSink>::iterator it = mEventSinks.begin(); it != mEventSinks.end(); ++it){
            if((*it).ev == ev){
                (*it).Add(s, mode, handler, mExporting != 0);
                return;
            }
        }
        mEventSinks.push_back(EventSink(ev)); // something seems to be up with this line specifically
        mEventSinks.back().Add(s, mode, handler, mExporting != 0);
    }
}

void MsgSource::EventSink::Add(Hmx::Object* o, MsgSource::SinkMode mode, Symbol sym, bool b){
    EventSinkElem s(o, mode, sym);
    if(b) sinks.push_front(s);
    else sinks.push_back(s);
}

// std::list<Sink> mSinks; // 0x8
// std::list<EventSink> mEventSinks; // 0x10
// int mExporting; // 0x18

void MsgSource::EventSink::Remove(Hmx::Object* o, MsgSource* src, bool exporting){
    for(std::list<EventSinkElem>::iterator it = sinks.begin(); it != sinks.end(); ++it){
        if(it->obj == o){
            it->obj->Release(src);
            it->obj = 0;
            if(!exporting) sinks.erase(it);
            return;
        }
    }
}

void MsgSource::Replace(Hmx::Object* o1, Hmx::Object* o2){
    RemoveSink(o1, Symbol());
}

void MsgSource::RemoveSink(Hmx::Object* s, Symbol ev){
    MILO_ASSERT(s, 0xA9);
    for(std::list<Sink>::iterator it = mSinks.begin(); it != mSinks.end(); ++it){
        if(it->obj == s){
            if(!ev.Null()){
                MILO_WARN("%s: removing global to %s for event %s, all other events will be wiped out", PathName(this), s->Name(), ev);
            }
            it->obj->Release(this);
            it->obj = 0;
            if(!mExporting) mSinks.erase(it);
            return;
        }
    }
    if(ev.Null()){
        for(std::list<EventSink>::iterator it = mEventSinks.begin(); it != mEventSinks.end(); ++it){
            (*it).Remove(s, this, mExporting != 0);
        }
    }
    else {
        for(std::list<EventSink>::iterator it = mEventSinks.begin(); it != mEventSinks.end(); ++it){
            if((*it).ev == ev){
                (*it).Remove(s, this, mExporting != 0);
                return;
            }
        }
    }
}

void MsgSource::MergeSinks(MsgSource* from){
    for(std::list<Sink>::iterator it = from->mSinks.begin(); it != from->mSinks.end(); ++it){
        AddSink(it->obj, Symbol(), Symbol(), it->mode);
    }
    for(std::list<EventSink>::iterator it = from->mEventSinks.begin(); it != from->mEventSinks.end(); ++it){
        for(std::list<EventSinkElem>::iterator elemIt = it->sinks.begin(); elemIt != it->sinks.end(); ++elemIt){
            AddSink(elemIt->obj, it->ev, elemIt->handler, elemIt->mode);
        }
    }
}

void MsgSource::Export(DataArray* da, bool b){
    if(b) HandleType(da);
    mExporting++;
    for(std::list<Sink>::iterator it = mSinks.begin(); it != mSinks.end(); it){
        if(it->obj){
            it->Export(da);
            it++;
        }
        else {
            if(mExporting == 1){
                it = mSinks.erase(it);
            }
            else it++;
        }
    }
    for(std::list<EventSink>::iterator it = mEventSinks.begin(); it != mEventSinks.end(); ++it){
        if(it->ev == da->Sym(1)){
            DataNode node(da->Node(1));
            for(std::list<EventSinkElem>::iterator elemIt = it->sinks.begin(); elemIt != it->sinks.end(); ++elemIt){
                if(elemIt->obj){
                    da->Node(1) = DataNode(elemIt->handler);
                    elemIt->Export(da);
                    elemIt++;
                }
                else {
                    if(mExporting == 1){
                        elemIt = it->sinks.erase(elemIt);
                    }
                    else elemIt++;
                }
            }
            da->Node(1) = node;
            // if some condition, then erase
            mEventSinks.erase(it);
            break;
        }
    }
    mExporting--;
}

BEGIN_HANDLERS(MsgSource);
    HANDLE(add_sink, OnAddSink);
    HANDLE(remove_sink, OnRemoveSink);
    if(ClassName() == StaticClassName()){
        HANDLE_SUPERCLASS(Hmx::Object);
    }
    Export(_msg, false);
END_HANDLERS;

DataNode MsgSource::OnAddSink(DataArray* da){
    if(da->Size() > 3) {
        SinkMode mode = (da->Size() > 4) ? (SinkMode)(da->Int(4)) : kHandle;
        DataArray* arr = da->Array(3);
        Hmx::Object* obj = da->GetObj(2);
        if(arr->Size() == 0){
            AddSink(obj, Symbol(), Symbol(), mode);
        }
        else {
            for(int i = 0; i < arr->Size(); i++){
                DataNode node(arr->Evaluate(i));
                if(node.Type() == kDataArray){
                    AddSink(obj, node.LiteralArray(0)->LiteralSym(0), node.LiteralArray(0)->LiteralSym(1), mode);
                }
                else {
                    AddSink(obj, node.LiteralSym(0), Symbol(), mode);
                }
            }
        }
    }
    else AddSink(da->GetObj(2), Symbol(), Symbol(), kHandle);
    return DataNode(0);
}

DataNode MsgSource::OnRemoveSink(DataArray* da){
    if(da->Size() > 3) {
        Hmx::Object* obj = da->GetObj(2);
        for(int i = 3; i < da->Size(); i++){
            RemoveSink(obj, da->Sym(i));
        }
    }
    else RemoveSink(da->GetObj(2), Symbol());
    return DataNode(0);
}

BEGIN_CUSTOM_PROPSYNC(MsgSource::Sink)
    SYNC_PROP(obj, (Hmx::Object*&)o.obj)
    SYNC_PROP(mode, (int&)o.mode)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(MsgSource::EventSinkElem)
    SYNC_PROP(handler, o.handler)
    SYNC_PROP(obj, (Hmx::Object*&)o.obj)
    SYNC_PROP(mode, (int&)o.mode)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(MsgSource::EventSink)
    SYNC_PROP(event, o.ev)
    SYNC_PROP(sinks, o.sinks)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(MsgSource)
    SYNC_PROP(sinks, mSinks)
    SYNC_PROP(event_sinks, mEventSinks)
END_PROPSYNCS