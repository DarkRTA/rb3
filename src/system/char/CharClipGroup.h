#ifndef CHAR_CHARCLIPGROUP_H
#define CHAR_CHARCLIPGROUP_H
#include "obj/Object.h"
#include "obj/ObjVector.h"
#include "obj/ObjPtr_p.h"
#include "char/CharClip.h"

class CharClipGroup : public virtual Hmx::Object {
public:
    CharClipGroup();
    OBJ_CLASSNAME(CharClipGroup);
    OBJ_SET_TYPE(CharClipGroup);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual ~CharClipGroup(){}
    
    CharClip* GetClip(int);
    bool HasClip(CharClip*) const;

    DECLARE_REVS;

    ObjVector<ObjOwnerPtr<CharClip, ObjectDir> > mClips;
    int mWhich;
    int mFlags; 
};

#endif