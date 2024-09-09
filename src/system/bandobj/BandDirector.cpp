#include "bandobj/BandDirector.h"

DataArray* BandDirector::sPropArr;
BandDirector* TheBandDirector;

BandDirector::VenueLoader::VenueLoader() : mDir(0), mLoader(0) {}

BandDirector::VenueLoader::~VenueLoader(){
    MILO_ASSERT(!mLoader, 0x3C);
    delete mDir;
}

void BandDirector::VenueLoader::Unload(bool async){
    if(mDir) mDir->SetName(mDir->Name(), mDir);
    if(async) TheLoadMgr.StartAsyncUnload();
    RELEASE(mLoader);
    RELEASE(mDir);
    if(async) TheLoadMgr.FinishAsyncUnload();
    mName = "";
    TheBandDirector->VenueLoaded(0);
}

void BandDirector::VenueLoader::Load(const FilePath& fp, LoaderPos pos, bool async){
    Unload(async);
    mName = FileGetBase(fp.c_str(), 0);
    if(!mName.Null() && mName != "none"){
        mLoader = new DirLoader(fp, pos, this, 0, 0, false);
        if(!async) TheLoadMgr.PollUntilLoaded(mLoader, 0);
    }
}

void BandDirector::VenueLoader::FinishLoading(Loader* l){
    MILO_ASSERT(l == mLoader, 0x67);
    mDir = dynamic_cast<WorldDir*>(mLoader->GetDir());
    RELEASE(mLoader);
    TheBandDirector->VenueLoaded(mDir);
}

void BandDirector::Init(){
    Register();
    sPropArr = new DataArray(1);
}

void BandDirector::Terminate(){
    sPropArr->Release();
}

BandDirector::BandDirector() : unk34(this, 0), unk40(this, 0), unk4c(this, 0), unk58(0), unk74(this, 0), unk80(this, 0), unk8c(this, 0), unk98(this, 0),
    unka4(0), unkb0(0), unkb4(1), unkb5(0), unkb6(0), unkb8(this, 0), unkc4(this, 0), unkd0(this, 0), unke0(-1e+30f), unke4(0), unke5(1), unk108(-1.0f), unk10c(0),
    unk110(0), unk114(0) {
    static DataNode& banddirector = DataVariable("banddirector");
    banddirector = DataNode(this);
    unkb6 = !TheLoadMgr.EditMode();
    if(TheBandDirector){
        MILO_WARN("Trying to make > 1 BandDirector, which should be single");
    }
    else TheBandDirector = this;
    unke8.reserve(100);
}

BandDirector::~BandDirector(){
    if(TheBandDirector == this){
        static DataNode& banddirector = DataVariable("banddirector");
        banddirector = DataNode((Hmx::Object*)0);
        TheBandDirector = 0;
    }
    else MILO_WARN("Deleting second BandDirector, should be singleton");
}