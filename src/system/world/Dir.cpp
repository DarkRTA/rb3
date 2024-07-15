#include "world/Dir.h"
#include "world/Crowd.h"
#include "world/LightPreset.h"
#include "world/SpotlightDrawer.h"
#include "rndobj/Mat.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"
#include "string.h"
#include "obj/ObjVersion.h"
#include "utl/STLHelpers.h"
#include "utl/Messages.h"

INIT_REVS(WorldDir)

WorldDir* TheWorld;
WorldDir* gLastWorld;
std::vector<FilePath> gOldChars;
ObjectDir* gOldTexDir;

WorldDir::WorldDir() : mPresetOverrides(this), mBitmapOverrides(this), mMatOverrides(this), mHideOverrides(this, kObjListNoNull), mCamShotOverrides(this, kObjListNoNull),
    mPS3PerPixelShows(this, kObjListNoNull), mPS3PerPixelHides(this, kObjListNoNull), mCrowds(this, kObjListNoNull), unk25c(0), mShowFakeHud(0), mHud(this, 0),
    mCameraManager(this), mPresetManager(this), mEchoMsgs(0), unk308(0), unk309(1), mTestPreset1(this, 0), mTestPreset2(this, 0), mTestAnimationTime(10.0f) {
    mGlowMat = Hmx::Object::New<RndMat>();
}

#pragma push
#pragma pool_data off
void SetTheWorld(WorldDir* dir){
    static DataNode& world = DataVariable("world");
    world = DataNode(dir);
    TheWorld = dir;
    if(dir) gLastWorld = dir;
}
#pragma pop

void WorldDir::Init(){
    Register();
    SetTheWorld(0);
}

WorldDir::~WorldDir(){
    delete mGlowMat;
    SpotlightDrawer::sCurrent->ClearLights();
    if(TheWorld == this) SetTheWorld(0);
}

void WorldDir::Enter(){
    if(!TheWorld){
        SetTheWorld(this);
        static DataNode& n = DataVariable("world.last_entered");
        n = DataNode(this);
    }
    mPresetManager.Enter();
    mCameraManager.Enter();
    PanelDir::Enter();
    ClearDeltas();
    unk308 = true;
    TheRnd->SetProcAndLock(false);
    TheRnd->ResetProcCounter();
    mDrawItr = mDraws.begin();
    if(TheWorld == this) SetTheWorld(0);
}

void WorldDir::ClearDeltas(){
    mDeltaSincePoll[0] = 0;
    mDeltaSincePoll[1] = 0;
    mDeltaSincePoll[2] = 0;
    mDeltaSincePoll[3] = 0;
}

void WorldDir::AccumulateDeltas(float* f){
    for(int i = 0; i < 4; i++){
        float deltatime = TheTaskMgr.DeltaTime((TaskUnits)i);
        *f++ = deltatime;
        mDeltaSincePoll[i] += deltatime;
    }
}

void WorldDir::ExtendDeltas(){
    for(int i = 0; i < 4; i++){
        TheTaskMgr.SetDeltaTime((TaskUnits)i, mDeltaSincePoll[i]);
    }
}

void WorldDir::RestoreDeltas(float* f){
    for(int i = 0; i < 4; i++){
        mDeltaSincePoll[i] = 0;
        TheTaskMgr.SetDeltaTime((TaskUnits)i, *f++);
    }
}

void WorldDir::Poll(){
    START_AUTO_TIMER("world_poll");
    if(TheWorld && TheWorld != this) RndDir::Poll();
    else {
        SetTheWorld(this);
        float deltas[4];
        AccumulateDeltas(deltas);
        bool b = true;
        if(!unk308 && TheRnd->mProcCmds & 2 == 0) b = false;
        if(b){
            ExtendDeltas();
            HandleType(select_camera_msg);
            if(unk309) mCameraManager.PrePoll();
            mPresetManager.Poll();
            RndDir::Poll();
            if(unk309) mCameraManager.Poll();
            RestoreDeltas(deltas);
        }
        SetTheWorld(0);
    }
}

SAVE_OBJ(WorldDir, 0xFC);

#pragma push
#pragma dont_inline on
BEGIN_COPYS(WorldDir)
    COPY_SUPERCLASS(PanelDir)
    CREATE_COPY(WorldDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFakeHudFilename)
        SyncHides(false);
        COPY_MEMBER(mHideOverrides)
        SyncHides(true);
        SyncBitmaps(false);
        COPY_MEMBER(mBitmapOverrides)
        SyncBitmaps(true);
        SyncMats(false);
        COPY_MEMBER(mMatOverrides)
        SyncMats(true);
        SyncPresets(false);
        COPY_MEMBER(mPresetOverrides)
        SyncPresets(true);
        SyncCamShots(false);
        COPY_MEMBER(mCamShotOverrides)
        SyncCamShots(true);
        COPY_MEMBER(mPS3PerPixelHides)
        COPY_MEMBER(mPS3PerPixelShows)
        COPY_MEMBER(mTestPreset1)
        COPY_MEMBER(mTestPreset2)
        COPY_MEMBER(mTestAnimationTime)
        COPY_MEMBER(mHud)
        SyncHUD();
    END_COPYING_MEMBERS
END_COPYS
#pragma pop

// fn_8059A2C8
BinStream& operator>>(BinStream& bs, WorldDir::BitmapOverride& c){
    bs >> c.original;
    if(gOldTexDir){
        FilePath bitmap;
        bs >> bitmap;
        if(!bitmap.empty()){
            const char* chr = strrchr(bitmap.c_str(), 0x2F);
            if(!chr) chr = bitmap.c_str();
            else chr = chr + 1;
            c.replacement = gOldTexDir->Find<RndTex>(chr, false);
            if(!c.replacement){
                MILO_WARN("Loading %s synchronously, please resave %s", chr, gOldTexDir->mLoader->mFile);
                c.replacement = gOldTexDir->NewTex(chr);
                c.replacement->SetBitmap(bitmap);
            }
            else {
                MILO_ASSERT(c.replacement->File() == bitmap, 0x152);
            }
        }
        else c.replacement = 0;
    }
    else bs >> c.replacement;
    return bs;
}

void WorldDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0x19, 0);
    MILO_ASSERT(gRev >= 4, 0x163);
    if(gRev != 0 && gRev < 5){
        ObjPtr<RndCam, ObjectDir> ptr(this, 0);
        bs >> ptr;
    }
    if(gRev == 2 || gRev == 3 || gRev == 4 || gRev == 5 || gRev == 6 || gRev == 7 || gRev == 8 || 
        gRev == 9 || gRev == 10 || gRev == 11 || gRev == 12 || gRev == 13 || gRev == 14 || gRev == 15 ||
        gRev == 16 || gRev == 17 || gRev == 18 || gRev == 19 || gRev == 20){
        int i, j;
        bs >> i >> j;
    }
    if(gRev > 9) bs >> mFakeHudFilename;
    if(gRev < 9){
        if(gRev > 7) OldLoadProxies(bs, 0);
        else if(gRev > 2) bs >> gOldChars;
    }
    PushRev(packRevs(gAltRev, gRev), this);
    PanelDir::PreLoad(bs);
}

// fn_8059A600
void WorldDir::PostLoad(BinStream& bs){
    PanelDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev == 5){
        ObjPtr<RndCam, ObjectDir> camPtr(this, 0);
        bs >> camPtr;
        SetCam(camPtr);
    }
    if(gRev < 8){
        for(int i = 0; i < gOldChars.size(); i++){
            RndDir* p = dynamic_cast<RndDir*>(Hmx::Object::NewObject(DirLoader::GetDirClass(gOldChars[i].c_str())));
            MILO_ASSERT(p, 0x199);
            p->SetProxyFile(gOldChars[i], 0);
            char buf[0x80];
            bs.ReadString(buf, 0x80);
            p->SetName(buf, this);
            RndTransformable* tp = p;
            tp->Load(bs);
            bool showing;
            bs >> showing;
            float fff;
            bs >> fff;
            if(p){
                p->SetShowing(showing);
                p->SetOrder(fff);
            }
            bs.ReadString(buf, 0x80);
            if(p && *buf != '\0'){
                p->SetEnv(Find<RndEnviron>(buf, true));
            }
        }
        gOldChars.clear();
    }
    if(gRev < 0x19){
        if(gRev > 0xA){
            Transform tf;
            bs >> tf;
        }
        else if(gRev > 6 && mCam){
            mCam->Load(bs);
        }
    }
    if(gRev > 0xB){
        SyncHides(false);
        bs >> mHideOverrides;
        SyncHides(true);
        SyncBitmaps(false);
        gOldTexDir = gRev > 0xC ? 0 : Dir();
        bs >> mBitmapOverrides;
        SyncBitmaps(true);
    }
    if(gRev > 0xD){
        SyncMats(false);
        bs >> mMatOverrides;
        SyncMats(true);
    }
    if(gRev > 0xE){
        SyncPresets(false);
        bs >> mPresetOverrides;
        SyncPresets(true);
    }
    if(gRev > 0xF){
        SyncCamShots(false);
        mCamShotOverrides.Load(bs, false);
        SyncCamShots(true);
    }
    if(gRev > 0x10 && gRev != 0x17){
        bs >> mPS3PerPixelHides >> mPS3PerPixelShows;
    }
    if(gRev == 0x12 || gRev == 0x13 || gRev == 0x14 || gRev == 0x15){
        Symbol s; bs >> s;
    }
    if(gRev > 0x12){
        bs >> mTestPreset1 >> mTestPreset2 >> mTestAnimationTime;
    }
    if(gRev > 0x13) bs >> mHud;
    SyncHUD();
}

void WorldDir::SyncObjects(){
    PanelDir::SyncObjects();
    mCameraManager.SyncObjects();
    mPresetManager.SyncObjects();
    mCrowds.clear();
    for(ObjDirItr<WorldCrowd> it(this, true); it; ++it){
        mCrowds.push_back(it);
    }
    for(ObjPtrList<WorldCrowd, ObjectDir>::iterator it = mCrowds.begin(); it != mCrowds.end(); ++it){
        (*it)->CleanUpCrowdFloor();
    }
    if(mHud) VectorRemove(mDraws, mHud);
    mDrawItr = mDraws.begin();
}