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

    struct EventSink {
        Symbol ev;
        std::list<Sink> sinks;
    };

    std::list<Sink> mSinks;
    std::list<EventSink> mEventSinks;
    int mExporting;

    MsgSource() : mSinks(), mEventSinks(), mExporting(0) {}
    virtual ~MsgSource();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(MsgSource);
    OBJ_SET_TYPE(MsgSource);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Export(DataArray*, bool);

    void ChainSource(MsgSource*, MsgSource*);
    void AddSink(Hmx::Object*, Symbol, Symbol, SinkMode);
};

#endif
