#pragma once
#include "obj/Data.h"
#include "utl/Symbol.h"

// every method in here is weak
class Message {
public:
    // Message(); // if there IS a void ctor for Msg i can't find it

    Message(Symbol type){
        mData = new DataArray(2);
        mData->Node(1) = DataNode(type);
    }

    Message(Symbol type, const DataNode & arg1){
        mData = new DataArray(3);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2){
        mData = new DataArray(4);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3){
        mData = new DataArray(5);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4){
        mData = new DataArray(6);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5){
        mData = new DataArray(7);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6){
        mData = new DataArray(8);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6, const DataNode & arg7){
        mData = new DataArray(9);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
        mData->Node(8) = arg7;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6, const DataNode & arg7, const DataNode & arg8){
        mData = new DataArray(10);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
        mData->Node(8) = arg7;
        mData->Node(9) = arg8;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6, const DataNode & arg7, const DataNode & arg8, const DataNode & arg9){
        mData = new DataArray(11);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
        mData->Node(8) = arg7;
        mData->Node(9) = arg8;
        mData->Node(10) = arg9;
    }

    Message(DataArray* da) : mData(da) { da->AddRef(); }

    Message(int i){
        mData = new DataArray(i + 2);
    }

    virtual ~Message(){ mData->Release(); }

    DataArray* mData;
    operator DataArray*() const { return mData; }
    DataArray* operator->() const { return mData; }

    void SetType(Symbol type){
        mData->Node(1) = DataNode(type);
    }

    Symbol Type() const { return mData->Sym(1); }

    DataNode& operator[](int idx){
        return mData->Node(idx + 2);
    }

};

#define DECLARE_MESSAGE(classname, type) \
    class classname : public Message { \
    public: \
        classname(DataArray* da) : Message(da) {} \
        virtual ~classname(){} \
        static Symbol Type(){ \
            static Symbol t(type); \
            return t; \
        } \

#define END_MESSAGE };

#include "obj/Object.h"
#include <list>

class MsgSource : public virtual Hmx::Object {
public:
    enum SinkMode {
        kHandle = 0,
        kExport = 1,
        kType = 2,
        kExportType = 3,
    };

    struct Sink {
        Sink(){}
        Sink(Hmx::Object* o, SinkMode m) : obj(o), mode(m) {}
        Hmx::Object* obj;
        SinkMode mode;
        void Export(DataArray*);
    };

    struct EventSinkElem : public Sink {
        EventSinkElem(){}
        EventSinkElem(Hmx::Object* o, SinkMode m, Symbol s) : Sink(o, m), handler(s) {}
        Symbol handler;
    };

    struct EventSink {
        EventSink(){}
        EventSink(Symbol s) : ev(s) {}
        Symbol ev;
        std::list<EventSinkElem> sinks;

        void Add(Hmx::Object*, SinkMode, Symbol, bool);
        void Remove(Hmx::Object*, MsgSource*, bool);
    };
    
    MsgSource();
    OBJ_CLASSNAME(MsgSource);
    OBJ_SET_TYPE(MsgSource);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~MsgSource();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Export(DataArray*, bool);

    void ChainSource(MsgSource*, MsgSource*);
    void AddSink(Hmx::Object*, Symbol = Symbol(), Symbol = Symbol(), SinkMode = kHandle);
    void RemoveSink(Hmx::Object*, Symbol = Symbol());
    void MergeSinks(MsgSource*);
    DataNode OnAddSink(DataArray*);
    DataNode OnRemoveSink(DataArray*);

    NEW_OBJ(MsgSource)
    static void Init(){
        REGISTER_OBJ_FACTORY(MsgSource)
    }

    std::list<Sink> mSinks; // 0x8
    std::list<EventSink> mEventSinks; // 0x10
    int mExporting; // 0x18
};