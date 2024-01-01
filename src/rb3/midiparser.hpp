#ifndef RB3_MIDIPARSER_HPP
#define RB3_MIDIPARSER_HPP
#include "msgsource.hpp"
#include "hmx/object.hpp"

class MidiParser : public MsgSource, public virtual Hmx::Object {
public:
    MidiParser();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~MidiParser();
    virtual void SetTypeDef(DataArray *);

    static Symbol StaticClassName();
};

#endif