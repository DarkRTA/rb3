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

void MsgSource::AddSink(Hmx::Object* s, Symbol sym1, Symbol sym2, MsgSource::SinkMode mode){
    MILO_ASSERT(s, 0x5D);
    RemoveSink(s, sym1);
    s->AddRef(this);
    if(sym1.Null()){
        MILO_ASSERT(s != this, 0x66);
        if(mExporting == 0){
            Sink theSink;
            theSink.mode = mode;
            theSink.obj = s;
            mSinks.push_back(theSink);
        }
    }
}

void MsgSource::EventSink::Add(Hmx::Object* o, MsgSource::SinkMode mode, Symbol sym, bool b){
    EventSinkElem s;
    s.obj = o;
    s.mode = mode;
    s.handler = sym;
    if(b){
        sinks.push_back(s);
    }
    else {
        sinks.push_back(s);
    }
}

void MsgSource::EventSink::Remove(Hmx::Object* o, MsgSource* src, bool exporting){
    std::list<EventSinkElem>::iterator it = sinks.begin();
    for(; it != sinks.end(); it++){
        if(it->obj == o){
            break;
        }
    }
    it->obj->Release(src);
    // sinks.remove(*elem);
    // sinks.remove(*it);
}

void MsgSource::Replace(Hmx::Object* o1, Hmx::Object* o2){
    RemoveSink(o1, Symbol());
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

bool PropSync(MsgSource::Sink& sink, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == obj){
            return PropSync<Hmx::Object>(sink.obj, node, prop, i + 1, op);
        }
        if(sym == mode){
            int x = sink.mode;
            bool ret = PropSync(x, node, prop, i + 1, op);
            sink.mode = (MsgSource::SinkMode)x;
            return ret;
        }
    }
    return true;
}

BEGIN_PROPSYNCS(MsgSource)
    SYNC_PROP(sinks, mSinks)
    SYNC_PROP(event_sinks, mEventSinks)
END_PROPSYNCS