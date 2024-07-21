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
    void RandomizeGroups();
    void SortGroups();
    void RecenterAll();
    void LoadCharacter();
    DataNode OnListClips(DataArray*);

    DECLARE_REVS;

    FilePath mCharFilePath; // 0xb0
    ObjPtr<RndDir, ObjectDir> mPreviewChar; // 0xbc
    ObjPtr<CharClip, ObjectDir> mPreviewClip; // 0xc8
    int mFilterFlags; // 0xd4
    int mBpm; // 0xd8
    bool mPreviewWalk; // 0xdc
    ObjPtr<CharClip, ObjectDir> mStillClip; // 0xe0

    DELETE_OVERLOAD
};

#endif