#ifndef RNDOBJ_MOVIE_H
#define RNDOBJ_MOVIE_H
#include "rndobj/Anim.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"

class RndMovie : public RndAnimatable {
public:
    RndMovie();
    OBJ_CLASSNAME(Movie);
    OBJ_SET_TYPE(Movie);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMovie(){}
    virtual bool Loop(){ return mLoop; }
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SetFile(const FilePath&, bool);
    virtual void SetTex(RndTex*);

    NEW_OBJ(RndMovie)
    DELETE_OVERLOAD;
    DECLARE_REVS;

    FilePath mFile;
    bool mStream;
    bool mLoop;
    ObjOwnerPtr<RndTex, class ObjectDir> mTex;
    
};

#endif
