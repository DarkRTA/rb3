#include "utl/Loader.h"
#include "utl/Option.h"
#include "obj/DataFunc.h"

LoadMgr TheLoadMgr;

LoadMgr::LoadMgr() : mLoaders(), mPlatform(kPlatformWii), mEditMode(0), mCacheMode(0), unk10(), unk18(10.0f), unk20(), mTimer(), unk58(0), unk5c(0) {

}

void LoadMgr::SetEditMode(bool b){
    mEditMode = b;
    static DataNode* edit_mode = DataVariable("edit_mode");
    *edit_mode = DataNode(mEditMode);
}

static DataNode OnLoadMgrPrint(DataArray* da){
    TheLoadMgr.Print();
    return DataNode(0);
}

static DataNode OnSetLoadMgrDebug(DataArray* da){
    TheLoadMgr.mCacheMode = da->Int(1) != 0;
    return DataNode(0);
}

static DataNode OnSetEditMode(DataArray* da){
    TheLoadMgr.SetEditMode(da->Int(1));
    return DataNode(0);
}

static DataNode OnSetLoaderPeriod(DataArray* da){
    float theFloat = da->Float(1);
    float ret = TheLoadMgr.unk18;
    TheLoadMgr.unk1c = theFloat;
    TheLoadMgr.unk18 = theFloat;
    return DataNode(ret);
}

static DataNode OnSysPlatformSym(DataArray* da){
    return DataNode(PlatformSymbol(TheLoadMgr.mPlatform));
}

void LoadMgr::Init(){
    SetEditMode(false);
    if(OptionBool("null_platform", false)) mPlatform = kPlatformNone;
    DataRegisterFunc("loadmgr_debug", OnSetLoadMgrDebug);
    DataRegisterFunc("loadmgr_print", OnLoadMgrPrint);
    DataRegisterFunc("set_edit_mode", OnSetEditMode);
    DataRegisterFunc("set_loader_period", OnSetLoaderPeriod);
    DataRegisterFunc("sysplatform_sym", OnSysPlatformSym);
    *DataVariable("sysplatform") = DataNode(mPlatform);
}

Loader* LoadMgr::ForceGetLoader(const FilePath& fp){
    if(fp.empty()) return 0;
    else {
        Loader* gotten = GetLoader(fp);
        if(!gotten){
            gotten = TheLoadMgr.AddLoader(fp, kLoadFront);
            if(!gotten){
                MILO_WARN("Don't recognize file %s", FilePath(fp));
            }
        }
        if(gotten){
            TheLoadMgr.PollUntilLoaded(gotten, 0);
        }
        return gotten;
    }
}

Loader* LoadMgr::GetLoader(const FilePath& fp) const {
    if(fp.empty()) return 0;
    else {
        Loader* theLoader = 0;
        for(std::list<Loader*>::const_iterator it = mLoaders.begin(); it != mLoaders.end(); it++){
            if((*it)->mFile == fp){
                theLoader = *it;
                break;
            }
        }
        return theLoader;
    }
}