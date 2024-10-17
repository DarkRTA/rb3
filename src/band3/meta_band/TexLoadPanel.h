#pragma once
#include "os/ContentMgr.h"
#include "rndobj/Mesh.h"
#include "rndobj/Tex.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"
#include "utl/Str.h"

class DynamicTex {
public:
    DynamicTex(const char*, const char*, bool, bool);
    virtual ~DynamicTex();

    RndTex* mTex; // 0x4
    String mMatName; // 0x8
    RndMat* mMat; // 0x14
    FileLoader* mLoader; // 0x18
    bool unk1c; // 0x1c
};

bool operator==(const DynamicTex*, const String&);

class DLCTex : public DynamicTex {
public:
    enum State {
        kMounting = 1,
        kLoaded = 3
    };

    void StartLoading();

    Symbol unk20; // 0x20
    int mState; // 0x24
    RndTex* unk28; // 0x28
};

class TexLoadPanel : public UIPanel, public ContentMgr::Callback {
public:
    TexLoadPanel();
    OBJ_CLASSNAME(TexLoadPanel);
    OBJ_SET_TYPE(TexLoadPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TexLoadPanel(){}
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();
    virtual void ContentMounted(const char*, const char*);    
    virtual void ContentFailed(const char*);    
    virtual const char* ContentDir(){ return 0; }

    bool RegisterForContent() const;
    bool TexturesLoaded() const;
    void FinalizeTexturesChunk();
    DLCTex* NextDLCTex();
    DynamicTex* AddTex(const char*, const char*, bool, bool);
    
    int unk3c; // 0x3c
    std::vector<DynamicTex*> mTexs; // 0x40
    int mCurrentFinalizingTexture; // 0x48
};