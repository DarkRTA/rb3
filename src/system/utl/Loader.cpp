#include "utl/Loader.h"
#include "Std.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/MemMgr.h"
#include "utl/Option.h"
#include "obj/DataFunc.h"
#include "rndwii/Rnd.h"

#include "decomp.h"

LoadMgr TheLoadMgr;
void (*LoadMgr::sFileOpenCallback)(const char*);

LoadMgr::LoadMgr() : mLoaders(), mPlatform(kPlatformWii), mEditMode(0), mCacheMode(0), mFactories(), mPeriod(10.0f), mLoading(), mTimer(), mAsyncUnload(0), mLoaderPos(kLoadFront) {

}

void LoadMgr::SetEditMode(bool b){
    mEditMode = b;
    static DataNode& edit_mode = DataVariable("edit_mode");
    edit_mode = DataNode(mEditMode);
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
    return TheLoadMgr.SetLoaderPeriod(da->Float(1));
}

static DataNode OnSysPlatformSym(DataArray* da){
    return DataNode(PlatformSymbol(TheLoadMgr.GetPlatform()));
}

void LoadMgr::Init(){
    SetEditMode(false);
    if(OptionBool("null_platform", false)) mPlatform = kPlatformNone;
    DataRegisterFunc("loadmgr_debug", OnSetLoadMgrDebug);
    DataRegisterFunc("loadmgr_print", OnLoadMgrPrint);
    DataRegisterFunc("set_edit_mode", OnSetEditMode);
    DataRegisterFunc("set_loader_period", OnSetLoaderPeriod);
    DataRegisterFunc("sysplatform_sym", OnSysPlatformSym);
    DataVariable("sysplatform") = DataNode((int)mPlatform);
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
        for(std::list<Loader*>::const_iterator it = mLoaders.begin(); it != mLoaders.end(); ++it){
            if((*it)->mFile == fp){
                theLoader = *it;
                break;
            }
        }
        return theLoader;
    }
}

Loader* LoadMgr::AddLoader(const FilePath& file, LoaderPos pos) {
    if (file.empty()) return NULL;
    if (sFileOpenCallback != NULL) {
        sFileOpenCallback(file.c_str());
    }
    const char* ext = FileGetExt(file.c_str());
    for(std::list<std::pair<String, LoaderFactoryFunc*> >::iterator it = mFactories.begin(); it != mFactories.end(); ++it){
        if(it->first == ext){
            return (it->second)(file, pos);
        }
    }
    return new FileLoader(file, file.c_str(), pos, 0, false, true, NULL);
}

void LoadMgr::PollUntilLoaded(Loader* ldr1, Loader* ldr2){
    SetGPHangDetectEnabled(false, "PollUntilLoaded");
    Loader* theLdr = ldr1;
    while(!theLdr->IsLoaded()){
        unk1c = 1e+30f;
        if(ldr2 && ldr2 == mLoading.front()){
#ifdef MILO_DEBUG
            MILO_FAIL("PollUntilLoaded circular dependency %s on %s", ldr2->DebugText(), ldr1->DebugText());
#endif
        }
        PollFrontLoader();
        if(!ListFind(mLoading, theLdr)) break;
        if(mLoading.front()->IsLoaded()){
            mLoading.pop_front();
        }
    }
    SetGPHangDetectEnabled(true, "PollUntilLoaded");
}

DECOMP_FORCEACTIVE(Loader,
    "PollUntilLoaded circular dependency %s on %s"
)

void LoadMgr::PollUntilEmpty() {
    
}

void LoadMgr::Print() {
    for (std::list<Loader*>::iterator it = mLoading.begin(); it != mLoading.end(); it++) {
        TheDebug << (*it)->mFile.c_str() << " " << LoaderPosString((*it)->mPos, 0)<< "\n";
    }
}

const char* LoadMgr::LoaderPosString(LoaderPos pos, bool abbrev){
    static const char* names[4] = { "kLoadFront", "kLoadBack", "kLoadFrontStayBack", "kLoadStayBack" };
    static const char* abbrevs[4] = { "F", "B", "FSB", "SB" };
    MILO_ASSERT(pos >= 0 && pos <= kLoadStayBack, 0x11D);
    if(abbrev) return abbrevs[pos];
    else return names[pos];
}

void LoadMgr::StartAsyncUnload() { mAsyncUnload++; }
void LoadMgr::FinishAsyncUnload() { mAsyncUnload--; }

void LoadMgr::RegisterFactory(const char* cc, LoaderFactoryFunc* func){
    for(std::list<std::pair<String, LoaderFactoryFunc*> >::iterator it = mFactories.begin(); it != mFactories.end(); it++){
        if((*it).first == cc){
            MILO_WARN("More than one LoadMgr factory for extension \"%s\"!", cc);
        }
    }
    mFactories.push_back(std::pair<String, LoaderFactoryFunc*>(String(cc), func));
}

Loader::Loader(const FilePath& fp, LoaderPos pos) : mPos(pos), mFile(fp) {
    mHeap = GetCurrentHeapNum();
    MILO_ASSERT(MemNumHeaps() == 0 || (mHeap != kNoHeap && mHeap != kSystemHeap), 446);
    MILO_ASSERT(!streq(MemHeapName(mHeap), "fast"), 448);
}

Loader::~Loader() {

}

FileLoader::FileLoader(const FilePath& fp, const char*, LoaderPos pos, int, bool, bool, BinStream* bs) : 
    Loader(fp, pos), mFile(NULL), mStream(bs), mBuffer(NULL), mBufLen(0) {

}
