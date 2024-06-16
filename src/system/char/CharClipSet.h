#ifndef CHAR_CHARCLIPSET_H
#define CHAR_CHARCLIPSET_H
#include "obj/Dir.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Dir.h"
#include "char/CharClip.h"
#include "utl/MemMgr.h"

class CharClipSet : public ObjectDir, public RndDrawable, public RndAnimatable {
public:
    CharClipSet();
    OBJ_CLASSNAME(CharClipSet);
    OBJ_SET_TYPE(CharClipSet);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CharClipSet();
    virtual void PostSave(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void ResetEditorState();
    virtual void DrawShowing();
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void SetBpm(int);
    virtual void PreSave(BinStream&);

    void ResetPreviewState();

    FilePath mCharFilePath;
    ObjPtr<RndDir, ObjectDir> mPreviewChar;
    ObjPtr<CharClip, ObjectDir> mPreviewClip;
    int mFilterFlags;
    int mBpm;
    bool mPreviewWalk;
    ObjPtr<CharClip, ObjectDir> mStillClip;

    DELETE_OVERLOAD
};

#endif