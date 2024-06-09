#ifndef UTL_MSGSOURCE_H
#define UTL_MSGSOURCE_H
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
        Hmx::Object* obj;
        SinkMode mode;
        void Export(DataArray*);
    };

    struct EventSinkElem : public Sink {
        Symbol handler;
    };

    struct EventSink {
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
    void AddSink(Hmx::Object*, Symbol, Symbol, SinkMode);
    void RemoveSink(Hmx::Object*, Symbol);
    DataNode OnAddSink(DataArray*);
    DataNode OnRemoveSink(DataArray*);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(MsgSource)
    static void Init(){
        REGISTER_OBJ_FACTORY(MsgSource)
    }

    std::list<Sink> mSinks;
    std::list<EventSink> mEventSinks;
    int mExporting;
};

#endif
