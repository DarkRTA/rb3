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
    
MsgSource::MsgSource() : mSinks(), mEventSinks(), mExporting(0) {}

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
