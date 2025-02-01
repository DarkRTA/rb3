#ifndef RNDOBJ_MOVIE_H
#define RNDOBJ_MOVIE_H
#include "rndobj/Anim.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"

/**
 * @brief An object that plays a video file.
 * Original _objects description:
 * "A Movie object animates a compressed video through a
 * texture. It works on Xbox and PS2 now, soon GC."
 */
class RndMovie : public RndAnimatable {
public:
    RndMovie();
    OBJ_CLASSNAME(Movie);
    OBJ_SET_TYPE(Movie);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~RndMovie() {}
    virtual bool Loop() { return mLoop; }
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SetFile(const FilePath &, bool);
    virtual void SetTex(RndTex *);

    NEW_OVERLOAD;
    DECLARE_REVS;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMovie)
    static void Init() { REGISTER_OBJ_FACTORY(RndMovie) }

    /** "File - extension is automatically converted to platform" */
    FilePath mFile;

    /** "Stream the file for this movie?" */
    bool mStream;

    /** "Loop this movie?" */
    bool mLoop;

    /** "Texture to animate." */
    ObjOwnerPtr<RndTex, class ObjectDir> mTex;
};

#endif
