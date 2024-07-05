#pragma once

#include "movie/Movie.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Tex.h"
#include "utl/FilePath.h"
#include "utl/MemMgr.h"

class TexMovie : public RndDrawable, public RndPollable {
    public:
    TexMovie();
    virtual ~TexMovie();
    OBJ_CLASSNAME(TexMovie)
    OBJ_SET_TYPE(TexMovie)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual void UpdatePreClearState();
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();

    void BeginMovie(BinStream*);
    void DrawToTexture();
    void DrawPreClear();
    void SetFile(const FilePath&);

    DataNode OnGetRenderTextures(DataArray*);
    DataNode OnPlayMovie(DataArray*);

    ObjOwnerPtr<RndTex, ObjectDir> mTex; // 0x28
    bool mLoop; // 0x34
    u8 unk_0x35; 
    bool mFillWidth; // 0x36
    FilePath unk_0x38;
    Movie mMovie; // 0x44

    DELETE_OVERLOAD
    DECLARE_REVS
};
