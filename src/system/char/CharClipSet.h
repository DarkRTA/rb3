#pragma once
#include "obj/Dir.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Dir.h"
#include "char/CharClip.h"
#include "utl/MemMgr.h"

/** "A <a href='#CharClip'>CharClip</a> container." */
class CharClipSet : public ObjectDir, public RndDrawable, public RndAnimatable {
public:
    struct AlphaSort {
        bool operator()(CharClip* c1, CharClip* c2) const {
            return strcmp(c1->Name(), c2->Name()) < 0;
        }
    };

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
    virtual void SetBpm(int);
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void PreSave(BinStream&);
    
    void ResetPreviewState();
    void RandomizeGroups();
    void SortGroups();
    void RecenterAll();
    void LoadCharacter();
    DataNode OnListClips(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharClipSet)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharClipSet)
    }

    /** "Preview base character to use- for example, char/male/male_guitar.milo for male guitarist" */
    FilePath mCharFilePath; // 0xb0
    ObjPtr<RndDir> mPreviewChar; // 0xbc
    /** "Pick a clip to play" */
    ObjPtr<CharClip> mPreviewClip; // 0xc8
    /** "Flags for filtering preview clip" */
    int mFilterFlags; // 0xd4
    /** "bpm for clip playing" */
    int mBpm; // 0xd8
    /** "Allow preview character to move around and walk?" */
    bool mPreviewWalk; // 0xdc
    /** "Set this to view drummer play anims" */
    ObjPtr<CharClip> mStillClip; // 0xe0
};
