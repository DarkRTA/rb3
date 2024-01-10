#ifndef RB3_MSGSOURCE_HPP
#define RB3_MSGSOURCE_HPP
#include "hmx/object.hpp"
#include <list>

class MsgSource : public virtual Hmx::Object {
public:
    MsgSource();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~MsgSource();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Export(DataArray*, bool);

    static Symbol StaticClassName();
    DataNode OnAddSink(DataArray*);
    DataNode OnRemoveSink(DataArray*);

    std::list<int> list1;
    std::list<int> list2;
    int unk18;
};

#endif
