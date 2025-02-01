#include "utl/Loader.h"
#include "Std.h"
#include "os/Archive.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/System.h"
#include "utl/BinStream.h"
#include "utl/MemMgr.h"
#include "utl/Option.h"
#include "obj/DataFunc.h"

#include "decomp.h"

LoadMgr TheLoadMgr;
void (*LoadMgr::sFileOpenCallback)(const char *);

LoadMgr::LoadMgr()
    : mLoaders(), mPlatform(kPlatformWii), mEditMode(0), mCacheMode(0), mFactories(),
      mPeriod(10.0f), mLoading(), mTimer(), mAsyncUnload(0), mLoaderPos(kLoadFront) {}

void LoadMgr::SetEditMode(bool b) {
    mEditMode = b;
    static DataNode &edit_mode = DataVariable("edit_mode");
    edit_mode = DataNode(mEditMode);
}

static DataNode OnLoadMgrPrint(DataArray *da) {
    TheLoadMgr.Print();
    return DataNode(0);
}

static DataNode OnSetLoadMgrDebug(DataArray *da) {
    TheLoadMgr.mCacheMode = da->Int(1) != 0;
    return DataNode(0);
}

static DataNode OnSetEditMode(DataArray *da) {
    TheLoadMgr.SetEditMode(da->Int(1));
    return DataNode(0);
}

static DataNode OnSetLoaderPeriod(DataArray *da) {
    return TheLoadMgr.SetLoaderPeriod(da->Float(1));
}

static DataNode OnSysPlatformSym(DataArray *da) {
    return DataNode(PlatformSymbol(TheLoadMgr.GetPlatform()));
}

void LoadMgr::Init() {
    SetEditMode(false);
    if (OptionBool("null_platform", false))
        mPlatform = kPlatformNone;
    DataRegisterFunc("loadmgr_debug", OnSetLoadMgrDebug);
    DataRegisterFunc("loadmgr_print", OnLoadMgrPrint);
    DataRegisterFunc("set_edit_mode", OnSetEditMode);
    DataRegisterFunc("set_loader_period", OnSetLoaderPeriod);
    DataRegisterFunc("sysplatform_sym", OnSysPlatformSym);
    DataVariable("sysplatform") = DataNode((int)mPlatform);
}

Loader *LoadMgr::ForceGetLoader(const FilePath &fp) {
    if (fp.empty())
        return 0;
    else {
        Loader *gotten = GetLoader(fp);
        if (!gotten) {
            gotten = TheLoadMgr.AddLoader(fp, kLoadFront);
            if (!gotten) {
                MILO_WARN("Don't recognize file %s", FilePath(fp));
            }
        }
        if (gotten) {
            TheLoadMgr.PollUntilLoaded(gotten, 0);
        }
        return gotten;
    }
}

Loader *LoadMgr::GetLoader(const FilePath &fp) const {
    if (fp.empty())
        return 0;
    else {
        Loader *theLoader = 0;
        for (std::list<Loader *>::const_iterator it = mLoaders.begin();
             it != mLoaders.end();
             ++it) {
            if ((*it)->mFile == fp) {
                theLoader = *it;
                break;
            }
        }
        return theLoader;
    }
}

Loader *LoadMgr::AddLoader(const FilePath &file, LoaderPos pos) {
    if (file.empty())
        return NULL;
    if (sFileOpenCallback != NULL) {
        sFileOpenCallback(file.c_str());
    }
    const char *ext = FileGetExt(file.c_str());
    for (std::list<std::pair<String, LoaderFactoryFunc *> >::iterator it =
             mFactories.begin();
         it != mFactories.end();
         ++it) {
        if (it->first == ext) {
            return (it->second)(file, pos);
        }
    }
    return new FileLoader(file, file.c_str(), pos, 0, false, true, NULL);
}

void LoadMgr::PollUntilLoaded(Loader *ldr1, Loader *ldr2) {
    // SetGPHangDetectEnabled(false, "PollUntilLoaded"); this is a __FUNCTION__
    Loader *theLdr = ldr1;
    while (!theLdr->IsLoaded()) {
        unk1c = 1e+30f;
        if (ldr2 && ldr2 == mLoading.front()) {
#ifdef MILO_DEBUG
            MILO_FAIL(
                "PollUntilLoaded circular dependency %s on %s",
                ldr2->DebugText(),
                ldr1->DebugText()
            );
#endif
        }
        PollFrontLoader();
        if (!ListFind(mLoading, theLdr))
            break;
        if (mLoading.front()->IsLoaded()) {
            mLoading.pop_front();
        }
    }
    // SetGPHangDetectEnabled(true, "PollUntilLoaded");
}

void LoadMgr::PollUntilEmpty() {}

void LoadMgr::Print() {
    for (std::list<Loader *>::iterator it = mLoading.begin(); it != mLoading.end();
         it++) {
        TheDebug << (*it)->mFile.c_str() << " " << LoaderPosString((*it)->mPos, 0)
                 << "\n";
    }
}

const char *LoadMgr::LoaderPosString(LoaderPos pos, bool abbrev) {
    static const char *names[4] = {
        "kLoadFront", "kLoadBack", "kLoadFrontStayBack", "kLoadStayBack"
    };
    static const char *abbrevs[4] = { "F", "B", "FSB", "SB" };
    MILO_ASSERT(pos >= 0 && pos <= kLoadStayBack, 0x11D);
    if (abbrev)
        return abbrevs[pos];
    else
        return names[pos];
}

int LoadMgr::AsyncUnload() const { return mAsyncUnload; }
void LoadMgr::StartAsyncUnload() { mAsyncUnload++; }
void LoadMgr::FinishAsyncUnload() { mAsyncUnload--; }

void LoadMgr::Poll() {
    if (mPeriod <= 0)
        return;
    mTimer.Restart();
    unk1c = mPeriod;
    while (!mLoading.empty()) {
        PollFrontLoader();
        if (!mLoading.empty()) {
            if (mLoading.front()->IsLoaded()) {
                mLoading.pop_front();
            }
        }
        if (CheckSplit())
            return;
    }
}

void LoadMgr::PollFrontLoader() { MILO_WARN("deleted"); }

void LoadMgr::RegisterFactory(const char *cc, LoaderFactoryFunc *func) {
    for (std::list<std::pair<String, LoaderFactoryFunc *> >::iterator it =
             mFactories.begin();
         it != mFactories.end();
         it++) {
        if ((*it).first == cc) {
            MILO_WARN("More than one LoadMgr factory for extension \"%s\"!", cc);
        }
    }
    mFactories.push_back(std::pair<String, LoaderFactoryFunc *>(String(cc), func));
}

Loader::Loader(const FilePath &fp, LoaderPos pos) : mPos(pos), mFile(fp) {
    mHeap = GetCurrentHeapNum();
    MILO_ASSERT(MemNumHeaps() == 0 || (mHeap != kNoHeap && mHeap != kSystemHeap), 446);
    MILO_ASSERT(!streq(MemHeapName(mHeap), "fast"), 448);
    TheLoadMgr.mLoaders.push_front(this);
    if (mPos == kLoadFront) {
        TheLoadMgr.mLoading.push_front(this);
    } else if (mPos == kLoadStayBack) {
        TheLoadMgr.mLoading.push_back(this);
    } else {
        std::list<Loader *>::iterator it = TheLoadMgr.mLoading.begin();
        for (; it != TheLoadMgr.mLoading.end();) {
            if ((*it)->GetPos() <= 1) {
                ++it;
                break;
            }
        }
        TheLoadMgr.mLoading.insert(it, this);
    }
}

Loader::~Loader() {
    TheLoadMgr.mLoading.remove(this);
    TheLoadMgr.mLoaders.remove(this);
}

FileLoader::FileLoader(
    const FilePath &loaderFile,
    const char *file,
    LoaderPos pos,
    int flags,
    bool temp,
    bool warn,
    BinStream *bs
)
    : Loader(loaderFile, pos), mFile(NULL), mStream(bs), mBuffer(NULL), mBufLen(0),
      mAccessed(0), mTemp(temp), mWarn(warn), mFlags(flags), mFilename(file), unk3c(0),
      unk40(-1), mState(0) {
    if (mStream) {
        mState = &FileLoader::LoadStream;
    } else {
        mState = &FileLoader::OpenFile;
    }
}

void FileLoader::AllocBuffer() {
    if (mTemp) {
        mBuffer = (char *)_MemAllocTemp(mBufLen, 0);
    } else {
        mBuffer = (char *)_MemAlloc(mBufLen, 32);
    }
}

void FileLoader::OpenFile() {
    Archive *old = TheArchive;
    const char *fname = mFilename.c_str();
    bool oldusingcd = UsingCD();
    bool b1 = gHostFile && FileMatch(fname, gHostFile);
    if (b1) {
        SetUsingCD(false);
        TheArchive = nullptr;
    }
    {
        MemDoTempAllocations mem(true, false);
        mFile = NewFile(fname, mFlags | 2);
    }
    if (b1) {
        SetUsingCD(oldusingcd);
        TheArchive = old;
    }

    if (!mFile && *fname != '\0' && mWarn) {
        MILO_WARN(
            "Could not load: %s (actually %s)",
            FileLocalize(Loader::mFile.c_str(), 0),
            fname
        );
    }
    if (mFile && !mFile->Fail()) {
        mBufLen = mFile->Size();
        AllocBuffer();
        mFile->ReadAsync((void *)mBuffer, mBufLen);
        mState = &FileLoader::LoadFile;
    } else {
        mState = &FileLoader::DoneLoading;
    }
}

const char *FileLoader::DebugText() {
    return MakeString("FileLoader: %s", Loader::mFile.c_str());
}

void FileLoader::LoadFile() {
    int asdf;
    if (mFile->ReadDone(asdf)) {
        if (mFile->Fail()) {
            mBufLen = 0;
            _MemFree((void *)mBuffer);
            mBuffer = nullptr;
        }
        RELEASE(mFile);
        mState = &FileLoader::DoneLoading;
    }
}

void FileLoader::DoneLoading() {}

FileLoader::~FileLoader() {
    if (!mAccessed) {
        _MemFree((void *)mBuffer);
        delete mFile;
    }
}

int FileLoader::GetSize() { return mBufLen; }

const char *FileLoader::GetBuffer(int *size) {
    MILO_ASSERT(IsLoaded(), 0x287);
    if (size)
        *size = mBufLen;
    mAccessed = true;
    return (const char *)mBuffer;
}

bool FileLoader::IsLoaded() const { return mState == &FileLoader::DoneLoading; }

void FileLoader::PollLoading() {
    while (!TheLoadMgr.CheckSplit() && TheLoadMgr.GetFirstLoading() == this && !IsLoaded()
    ) {
        (this->*mState)();
    }
}

void FileLoader::LoadStream() {
    EofType t;
    while (t = mStream->Eof(), t != NotEof) {
        MILO_ASSERT(t == TempEof, 0x2A8);
        if (TheLoadMgr.CheckSplit())
            return;
    }
    if (!mBuffer) {
        int size;
        *mStream >> size;
        if (size == -1) {
            *mStream >> unk40;
            *mStream >> mBufLen;
        } else {
            unk40 = 0;
            mBufLen = size;
        }
        AllocBuffer();
    }
    int i2 = unk40 > 0 ? 0x10000 : mBufLen;
    while (true) {
        int i3 = Min(mBufLen - unk3c, i2);
        while (t = mStream->Eof(), t != NotEof) {
            MILO_ASSERT(t == TempEof, 0x2C9);
            if (TheLoadMgr.CheckSplit())
                return;
        }
        if (i3 == 0)
            break;
        mStream->Read((void *)(mBuffer + unk3c), i3);
        unk3c += i3;
    }
    mState = &FileLoader::DoneLoading;
}