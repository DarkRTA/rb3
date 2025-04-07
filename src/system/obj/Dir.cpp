#include "obj/Dir.h"
#include "obj/Data.h"
#include "obj/DirUnloader.h"
#include "obj/MessageTimer.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/DataFunc.h"
#include "obj/ObjVersion.h"
#include "obj/Utl.h"
#include "decomp.h"
#include "os/Debug.h"
#include "rndwii/Rnd.h"
#include "utl/Loader.h"
#include "utl/Option.h"
#include "utl/Messages.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

DECOMP_FORCEACTIVE(Dir, "%s: subdir %s included more than once", "uniq%x", __FILE__)

const char *kNotObjectMsg = "Could not find %s in dir \"%s\"";

namespace {
    int gPreloadIdx = 0;
    ObjDirPtr<ObjectDir> gPreloaded[128];

    void DeleteShared() {
        for (; gPreloadIdx > 0; gPreloadIdx--) {
            gPreloaded[gPreloadIdx - 1] = 0;
        }
    }
}

ObjectDir *ObjectDir::sMainDir;
ObjectDir *gDir;

INIT_REVS(ObjectDir);

inline ObjectDir::InlinedDir::InlinedDir() {}
inline ObjectDir::InlinedDir::InlinedDir(
    ObjectDir *d, const FilePath &fp, bool b, InlineDirType ty
)
    : dir(d) {
    file = fp;
    shared = b;
    inlineDirType = ty;
}

BinStream &operator>>(BinStream &bs, InlineDirType &ty) {
    unsigned char uc;
    bs >> uc;
    ty = (InlineDirType)uc;
    return bs;
}

void ObjectDir::Reserve(int hashSize, int stringSize) {
    if (mHashTable.Size() < hashSize)
        mHashTable.Resize(hashSize, 0);
    mStringTable.Reserve(stringSize);
}

void ObjectDir::SyncObjects() {
#ifdef MILO_DEBUG
    std::vector<ObjectDir *> dirs;
    int which = 0;
    ObjectDir *dir;
    while (true) {
        int next = which++;
        dir = NextSubDir(next);
        if (!dir)
            break;
        if (std::find(dirs.begin(), dirs.end(), dir) != dirs.end()) {
            MILO_WARN(
                "%s: subdir %s included more than once", PathName(this), PathName(dir)
            );
        } else {
            dirs.push_back(dir);
        }
    }
#endif
    HandleType(sync_objects_msg);
}

void ObjectDir::SetSubDir(bool b) {
    if (b) {
        mIsSubDir = true;
        SetName(0, 0);
        SetTypeDef(0);
    }
}

bool ObjectDir::HasSubDir(ObjectDir *dir) {
    ObjectDir *subdir;
    int i = 0;
    int j = 0;

    while (1) {
        j = i;
        i = j + 1;

        subdir = NextSubDir(j);
        if (subdir) {
            if (subdir == dir) {
                return true;
            }
        } else {
            break;
        }
    }

    return false;
}

bool ObjectDir::SaveSubdirs() {
    bool ret = false;
    if (!IsProxy() || mProxyFile.empty() || gLoadingProxyFromDisk) {
        ret = true;
    }
    return ret;
}

SAVE_OBJ(ObjectDir, 0x1A2)

InlineDirType ObjectDir::InlineSubDirType() { return mInlineSubDirType; }

#pragma push
#pragma dont_inline on
FilePath &lol(ObjDirPtr<ObjectDir> &dptr, const FilePath &fp) {
    dptr.LoadFile(fp, 0, 0, kLoadFront, 0);
    return dptr.GetFile();
}
#pragma pop

void ObjectDir::PostSave(BinStream &bs) { SyncObjects(); }

void ObjectDir::PreLoadInlined(const FilePath &fp, bool shared, InlineDirType type) {
    MILO_ASSERT(type != kInlineNever, 0x285);
    if (type == kInlineAlways && shared) {
        MILO_WARN("Can't share kInlineAlways Dirs");
        shared = false;
    }
    InlinedDir iDir;
    iDir.file = fp;
    iDir.shared = shared;
    iDir.inlineDirType = type;
    mInlinedDirs.push_back(iDir);
}

ObjDirPtr<ObjectDir> ObjectDir::PostLoadInlined() {
    MILO_ASSERT(mInlinedDirs.size() > 0, 0x296);
    InlinedDir iDir = mInlinedDirs.back();
    mInlinedDirs.pop_back();
    if (mInlinedDirs.size() == 0) {
        ClearAndShrink(mInlinedDirs);
    }
    if (iDir.shared && iDir.file.length() != 0 && !iDir.dir) {
        MILO_WARN("Couldn't load shared inlined file %s\n", iDir.file);
    }
    return iDir.dir;
}

void ObjectDir::Load(BinStream &bs) {
    PreLoad(bs);
    PostLoad(bs);
    if (IsProxy() && !mProxyFile.empty()) {
        class Loader *ldr = TheLoadMgr.GetLoader(mProxyFile);
        if (ldr)
            TheLoadMgr.PollUntilLoaded(ldr, 0);
    }
}

void ObjectDir::OldLoadProxies(BinStream &bs, int i) {
    int x;
    bs >> x;
    if (x != 0)
        MILO_FAIL("Proxies not allowed here");
}

BinStream &operator>>(BinStream &bs, ObjectDir::Viewport &vp) {
    bs >> vp.mXfm;
    if (ObjectDir::gRev < 0x12) {
        int i;
        bs >> i;
    }
    return bs;
}

#pragma push
#pragma pool_data off
#pragma dont_inline on
void ObjectDir::PreLoad(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(0x1B, 0);
    if (gRev > 0x15)
        Hmx::Object::LoadType(bs);
    else if (gRev >= 2 && gRev <= 16)
        Hmx::Object::Load(bs);
    if (gRev < 3) {
        int i, j;
        bs >> i >> j;
        Reserve(i, j);
    }
    if (gRev > 0x19) {
        if (gRev < 0x1B) {
            bool b;
            bs >> b;
            mAlwaysInlined = b;
        } else
            bs >> mAlwaysInlined;
        int toAlloc;
        bs >> toAlloc;
        if (toAlloc) {
            char *v = (char *)_MemOrPoolAlloc(toAlloc + 1, FastPool);
            mAlwaysInlineHash = v;
            bs.Read(v, toAlloc);
            char *ptr = (char *)mAlwaysInlineHash;
            ptr[toAlloc] = 0;
        }
    }
    if (gRev > 1) {
        std::vector<Viewport> vec;
        int i;
        bs >> vec;
        bs >> i;
    }
    if (gRev > 0xC) {
        if (gRev > 0x13) {
            if (!gLoadingProxyFromDisk)
                bs >> mInlineProxy;
            else {
                bool b;
                bs >> b;
            }
        }
        if (gLoadingProxyFromDisk || mProxyOverride) {
            bool fail = false;
            if (mProxyOverride && AllowsInlineProxy())
                fail = true;
            if (fail)
                MILO_FAIL("You cannot override an inlined proxy!");
            FilePath fp;
            bs >> fp;
            mProxyOverride = false;
        } else {
            FilePath fp;
            bs >> fp;
            if (!fp.empty() && fp == mProxyFile) {
                mProxyOverride = true;
            } else {
                mProxyFile = fp;
                mProxyOverride = false;
            }
        }
    }
    if (gRev >= 2 && gRev <= 10) {
        char buf[0x80];
        bs.ReadString(buf, 0x80);
    }
    if (gRev >= 4 && gRev <= 10) {
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        mCurCam = FindObject(buf, false);
    }
    if (gRev == 5) {
        char buf[0x80];
        bs.ReadString(buf, 0x80);
    }

    static std::vector<FilePath> inlinedSubDirs;
    static std::vector<FilePath> notInlinedSubDirs;
    if (gRev > 2) {
        bs >> notInlinedSubDirs;
        std::vector<int> intVec;
        if (gRev == 0x17)
            bs >> intVec;
        if (gRev > 0x14) {
            bs >> mInlineSubDirType;
            bs >> inlinedSubDirs;
        } else
            inlinedSubDirs.clear();

        int i20 = 0;
        if (SaveSubdirs() || inlinedSubDirs.size() != 0
            || notInlinedSubDirs.size() != 0) {
            for (int i = 0; i < mSubDirs.size(); i++) {
                RemovingSubDir(mSubDirs[i]);
            }
            if (!bs.Cached()
                && mSubDirs.size() == notInlinedSubDirs.size() + inlinedSubDirs.size()) {
                i20 = 1;
            } else {
                mSubDirs.reserve(notInlinedSubDirs.size() + inlinedSubDirs.size());
                mSubDirs.resize(notInlinedSubDirs.size() + inlinedSubDirs.size());
            }
        } else
            i20 = 2;

        for (int i = 0; i != notInlinedSubDirs.size(); i++) {
            bool filesneq = mSubDirs[i].GetFile() != notInlinedSubDirs[i];
            if (i20 == 0 || filesneq) {
                bool b17 = false;
                if (intVec.size() != 0) {
                    b17 = intVec[i] != 0;
                }
                LoadSubDir(i, notInlinedSubDirs[i], bs, !b17);
            }
        }

        if (gRev > 0x17) {
            int numNotInlined = notInlinedSubDirs.size();
            for (int i = 0; i < inlinedSubDirs.size(); i++) {
                bool getfileres =
                    mSubDirs[i + numNotInlined].GetFile() != inlinedSubDirs[i];
                InlineDirType dType;
                if (gRev > 0x18) {
                    unsigned char b;
                    bs >> b;
                    MILO_ASSERT_RANGE_EQ(b, kInlineCached, kInlineCachedShared, 0x3C3);
                    dType = (InlineDirType)b;
                } else
                    dType = kInlineCached;
                inlinedSubDirs[i] = GetSubDirPath(inlinedSubDirs[i], bs);
                PreLoadInlined(inlinedSubDirs[i], false, dType);
                if (i20 == 1) {
                    PushRev(getfileres, this);
                }
            }
            PushRev(numNotInlined, this);
            if (!bs.Cached()) {
                PushRev(i20, this);
            }
        }
    }
    if (gRev == 12 || gRev == 13) {
        OldLoadProxies(bs, gRev);
    }
    if (gRev < 0x13) {
        if (gRev > 0xF) {
            int inlineProxy;
            bs >> inlineProxy;
            MILO_ASSERT(inlineProxy != 1, 0x3E1);
        } else if (gRev > 0xE) {
            bool inlineProxy;
            bs >> inlineProxy;
            MILO_ASSERT(!inlineProxy, 0x3E6);
        }
    }

    std::vector<bool> boolvec;
    boolvec.resize(mInlinedDirs.size());
    for (int i = 0; i < mInlinedDirs.size(); i++) {
        if (gRev < 0x19 && !bs.Cached()) {
            boolvec[i] = true;
        } else {
            bool b;
            bs >> b;
            boolvec[i] = b;
        }
    }
    for (int i = 0; i < mInlinedDirs.size(); i++) {
        InlinedDir &curIDir = mInlinedDirs[i];
        FilePath fpath(curIDir.file);
        if (!bs.Cached() || !boolvec[i]) {
            if (!boolvec[i] && (curIDir.inlineDirType == kInlineAlways || bs.Cached())) {
                curIDir.dir.LoadInlinedFile(fpath, &bs);
            } else if (IsProxy() && !mProxyFile.empty()) {
                curIDir.dir = nullptr;
            } else {
                curIDir.dir.LoadFile(fpath, true, curIDir.shared, kLoadFront, true);
            }
        }
    }
    if (gRev >= 21 && gRev <= 23) {
        int offset = notInlinedSubDirs.size();
        MILO_ASSERT(mSubDirs.capacity() >= offset + inlinedSubDirs.size(), 0x41A);
        for (int i = 0; i < inlinedSubDirs.size(); i++) {
            mSubDirs[i + offset].LoadInlinedFile(inlinedSubDirs[i], &bs);
        }
    }
    mIsSubDir = false;
    PushRev(packRevs(gAltRev, gRev), this);
}
#pragma pop

#pragma push
#pragma dont_inline on
void ObjectDir::PostLoad(BinStream &bs) {
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    for (int i = mInlinedDirs.size() - 1; i >= 0; i--) {
        InlinedDir &iDir = mInlinedDirs[i];
        int tempgRev = gRev;
        iDir.dir.PostLoad(mLoader);
        gRev = tempgRev;
        if (iDir.inlineDirType == (InlineDirType)3) {
            iDir.shared = true;
        }
        if (iDir.shared) {
            FilePath &fp = iDir.file;
            DirLoader *last = DirLoader::FindLast(fp);
            if (last) {
                if (last->IsLoaded()) {
                    iDir.dir = last->GetDir();
                } else {
                    MILO_WARN("Can't share unloaded dir %s", fp);
                }
            }
        } else {
            if (iDir.dir.IsLoaded()) {
                delete iDir.dir->mLoader;
                iDir.dir->mLoader = 0;
            }
        }
    }
    if (gRev > 0x17) {
        int revs2 = bs.Cached() ? 0 : PopRev(this);
        int offset = PopRev(this);
        MILO_ASSERT_RANGE_EQ(offset, 0, mSubDirs.size(), 0x466);
        if (revs2 != 2) {
            for (int i = mSubDirs.size() - offset - 1; i >= 0; i--) {
                bool bbb = false;
                if (revs2 == 1) {
                    bbb = PopRev(this) != 0;
                }
                ObjDirPtr<ObjectDir> inlinedDirPtr = PostLoadInlined();
                ObjDirPtr<ObjectDir> &curDirPtr = mSubDirs[i + offset];
                if (revs2 == 0 || bbb) {
                    curDirPtr = inlinedDirPtr;
                }
                AddedSubDir(curDirPtr);
            }
            for (offset = offset - 1; offset >= 0; offset--) {
                ObjDirPtr<ObjectDir> &offsetPtr = mSubDirs[offset];
                offsetPtr.PostLoad(mLoader);
                AddedSubDir(offsetPtr);
            }
        }
    } else {
        for (int i = 0; i < mSubDirs.size(); i++) {
            ObjDirPtr<ObjectDir> &curDirPtr = mSubDirs[i];
            curDirPtr.PostLoad(mLoader);
            AddedSubDir(curDirPtr);
            if (curDirPtr.IsLoaded()) {
                if (curDirPtr->InlineSubDirType() != kInlineNever) {
                    delete curDirPtr->mLoader;
                    curDirPtr->mLoader = 0;
                }
            }
        }
    }
    if (gRev > 10) {
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        bs.ReadString(buf, 0x80);
        mCurCam = FindObject(buf, true);
    }
    if (gRev > 0x15)
        LoadRest(bs);
    else if (gRev > 0x10)
        Hmx::Object::Load(bs);
    HandleType(change_proxies_msg);
    if (mProxyOverride) {
        bool overridden = false;
        mProxyOverride = false;
        if (LOADMGR_EDITMODE || (IsProxy() && !AllowsInlineProxy())) {
            overridden = true;
        }
        if (!overridden)
            MILO_FAIL("You cannot override an inlined proxy!");
    } else {
        if (IsProxy() && !mProxyFile.empty()) {
            DeleteObjects();
            DeleteSubDirs();
            DirLoader *dl = new DirLoader(
                mProxyFile, kLoadFront, 0, InlineProxy(bs) ? &bs : 0, this, false
            );
        }
    }
}
#pragma pop

void ObjectDir::TransferLoaderState(ObjectDir *otherDir) {
    mProxyFile = otherDir->mProxyFile;
    mProxyOverride = otherDir->mProxyOverride;
    mLoader = otherDir->mLoader;
    otherDir->mLoader = 0;
}

void ObjectDir::SetProxyFile(const FilePath &fp, bool b) {
    if (!IsProxy()) {
        MILO_WARN("Can't set proxy file if own dir");
    } else {
        mProxyFile = fp;
        mProxyOverride = b;
        if (!b) {
            DeleteObjects();
            DeleteSubDirs();
            if (!mProxyFile.empty()) {
                TheLoadMgr.PollUntilLoaded(
                    new DirLoader(mProxyFile, kLoadFront, 0, 0, this, false), 0
                );
            }
        }
    }
}

BEGIN_COPYS(ObjectDir)
    COPY_SUPERCLASS(Hmx::Object)
    if (ty != kCopyFromMax) {
        CREATE_COPY(ObjectDir)
        BEGIN_COPYING_MEMBERS
            if (!IsProxy()) {
                for (int i = 0; i < mSubDirs.size(); i++) {
                    RemovingSubDir(mSubDirs[i]);
                }
                COPY_MEMBER(mSubDirs)
                for (int i = 0; i < mSubDirs.size(); i++) {
                    AddedSubDir(mSubDirs[i]);
                }
            }
            COPY_MEMBER(mInlineProxy)
            COPY_MEMBER(mInlineSubDirType)
        END_COPYING_MEMBERS
    }
END_COPYS

Hmx::Object *ObjectDir::FindObject(const char *name, bool parentDirs) {
    Entry *entry = FindEntry(name, false);
    if (entry && entry->obj)
        return entry->obj;
    for (int i = 0; i < mSubDirs.size(); i++) {
        if (mSubDirs[i]) {
            Hmx::Object *found = mSubDirs[i]->FindObject(name, false);
            if (found)
                return found;
        }
    }
    if (strlen(name) != 0) {
        if (strcmp(name, Name()) == 0) {
            return this;
        }
    }
    if (parentDirs) {
        if (Dir() && Dir() != this) {
            return Dir()->FindObject(name, parentDirs);
        }
        if (this != sMainDir) {
            return sMainDir->FindObject(name, false);
        }
    }
    return nullptr;
}

void ObjectDir::RemovingObject(Hmx::Object *obj) {
    if (obj != mCurCam)
        return;
    else
        mCurCam = nullptr;
}

void ObjectDir::AddedSubDir(ObjDirPtr<ObjectDir> &dirPtr) {
    ObjectDir *dir = dirPtr;
    if (dir) {
        dir->InlineSubDirType();
        dir->SetSubDir(true);
        for (ObjDirItr<Hmx::Object> it(dir, true); it != 0; ++it) {
            AddedObject(it);
        }
    }
}

void ObjectDir::RemovingSubDir(ObjDirPtr<ObjectDir> &dirPtr) {
    ObjectDir *dir = dirPtr;
    if (dir) {
        dir->SetSubDir(false);
        for (ObjDirItr<Hmx::Object> it(dir, true); it != 0; ++it) {
            RemovingObject(it);
        }
    }
}

ObjectDir::ObjectDir()
    : mHashTable(0, Entry(), Entry(), 0), mStringTable(0), mProxyOverride(false),
      mInlineProxy(true), mLoader(0), mIsSubDir(false), mInlineSubDirType(kInlineNever),
      mPathName(gNullStr), mCurCam(0), mAlwaysInlined(false),
      mAlwaysInlineHash(gNullStr) {}

void ObjectDir::ResetEditorState() { mCurCam = 0; }

void ObjectDir::DeleteObjects() {
    MILO_ASSERT(gSuppressPointTest>=0, 0x602);
    gSuppressPointTest++;
    for (ObjDirItr<Hmx::Object> it(this, true); it != 0; ++it) {
        if (it != this)
            delete it;
    }
    MILO_ASSERT(gSuppressPointTest>0, 0x60C);
    gSuppressPointTest--;
}

void ObjectDir::DeleteSubDirs() {
    for (int i = 0; i < mSubDirs.size(); i++) {
        RemovingSubDir(mSubDirs[i]);
    }
    mSubDirs.clear();
}

bool ObjectDir::InlineProxy(BinStream &bs) {
    bool ret = false;
    if (AllowsInlineProxy() && bs.Cached()) {
        ret = true;
    }
    return ret;
}

ObjectDir::~ObjectDir() {
    mSubDirs.clear();
    delete mLoader;
    if (TheLoadMgr.AsyncUnload()) {
        new DirUnloader(this);
    } else {
        DeleteObjects();
        DeleteSubDirs();
    }
    if (!IsProxy()) {
        SetName(0, 0);
    }
    if (mPathName != gNullStr) {
        _MemOrPoolFree(strlen(mPathName) + 1, FastPool, (void *)mPathName);
    }
    if (mAlwaysInlineHash != gNullStr) {
        _MemOrPoolFree(strlen(mAlwaysInlineHash) + 1, FastPool, (void *)mAlwaysInlineHash);
    }
}

ObjectDir::Entry *ObjectDir::FindEntry(const char *name, bool add) {
    if (name == 0 || *name == '\0')
        return 0;
    else {
        Entry *entry = mHashTable.Find(name);
        if (!entry && add) {
            Entry newEntry;
            newEntry.name = SymbolCacheLookup(name);
            if (!newEntry.name) {
                mStringTable.Add(newEntry.name);
            }
            entry = mHashTable.Insert(newEntry);
        }
        return entry;
    }
}

ObjectDir *ObjectDir::NextSubDir(int &which) {
    MILO_ASSERT(which >= 0, 0x695);
    ObjectDir *ret = this;
    if (which == 0)
        return ret;
    else {
        which--;
        ret = nullptr;
        for (int i = 0; i < mSubDirs.size(); i++) {
            if (mSubDirs[i]) {
                ret = mSubDirs[i]->NextSubDir(which);
                if (ret)
                    break;
            }
        }
    }
    return ret;
}

void ObjectDir::AppendSubDir(const ObjDirPtr<ObjectDir> &dPtr) {
    mSubDirs.push_back(dPtr);
    AddedSubDir(mSubDirs.back());
}

void ObjectDir::RemoveSubDir(const ObjDirPtr<ObjectDir> &dPtr) {
    std::vector<ObjDirPtr<ObjectDir> >::iterator it = mSubDirs.begin();
    while (it != mSubDirs.end()) {
        if ((*it) == dPtr) {
            RemovingSubDir(*it);
            it = mSubDirs.erase(it);
            if (it == mSubDirs.end())
                break;
        }
        ++it;
    }
}

static DataNode OnLoadObjects(DataArray *da) {
    return DirLoader::LoadObjects(FilePath(da->Str(1)), 0, 0);
}

static DataNode OnPathName(DataArray *da) { return PathName(da->Obj<Hmx::Object>(1)); }

static DataNode OnReserveToFit(DataArray *da) {
    ReserveToFit(da->Obj<ObjectDir>(1), da->Obj<ObjectDir>(2), da->Int(3));
    return 0;
}

static DataNode OnInitObject(DataArray *da) {
    InitObject(da->Obj<Hmx::Object>(1));
    return 0;
}

void CheckForDuplicates() {
    DataArray *cfg = SystemConfig("objects");
    std::list<Symbol> syms;
    for (int i = 1; i < cfg->Size(); i++) {
        syms.push_back(cfg->Array(i)->Sym(0));
    }
    syms.sort();
    Symbol previous;
    bool fail = false;
    for (std::list<Symbol>::iterator it = syms.begin(); it != syms.end();
         previous = *it, ++it) {
        Symbol cur = *it;
        if (cur == previous) {
            MILO_WARN("Duplicate object %s in config", cur);
            fail = true;
        }
    }
    if (fail)
        MILO_FAIL("duplicate objects found in configs, bailing");
    syms.unique();
}

void ObjectDir::PreInit(int i, int j) {
    sRevStack.reserve(0x80);
    Hmx::Object::Init();
    ObjectDir::Register();
    MsgSource::Init();
    sMainDir = new ObjectDir();
    sMainDir->Reserve(i, j);
    sMainDir->SetName("main", sMainDir);
    DataSetThis(sMainDir);
    if (UsingCD())
        DirLoader::SetCacheMode(true);
    TheLoadMgr.RegisterFactory("milo", DirLoader::New);
    TheLoadMgr.RegisterFactory("milo_xbox", DirLoader::New);
    TheLoadMgr.RegisterFactory("milo_ps3", DirLoader::New);
    TheLoadMgr.RegisterFactory("milo_pc", DirLoader::New);
    TheLoadMgr.RegisterFactory("milo_ps2", DirLoader::New);
    TheLoadMgr.RegisterFactory("milo_wii", DirLoader::New);
    TheLoadMgr.RegisterFactory("rnd", DirLoader::New);
    TheLoadMgr.RegisterFactory("m2", DirLoader::New);
    TheLoadMgr.RegisterFactory("gh", DirLoader::New);
    TheLoadMgr.RegisterFactory("kr", DirLoader::New);
    DataRegisterFunc("load_objects", OnLoadObjects);
    DataRegisterFunc("init_object", OnInitObject);
    DataRegisterFunc("path_name", OnPathName);
    DataRegisterFunc("reserve_to_fit", OnReserveToFit);
}

void ObjectDir::Init() {
    MessageTimer::Init();
    CheckForDuplicates();
    DirLoader::sPrintTimes = OptionBool("loader_times", false);
}

void ObjectDir::Terminate() { DeleteShared(); }

void ObjectDir::Iterate(DataArray *da, bool b) {
    const DataNode &eval = da->Evaluate(2);
    Symbol sym1;
    Symbol sym2;
    if (eval.Type() == kDataSymbol) {
        const char *inNode = eval.mValue.symbol;
        sym1 = STR_TO_SYM(inNode);
    } else {
        DataArray *arr = eval.mValue.array;
        sym1 = arr->Sym(0);
        sym2 = arr->Sym(1);
    }
#ifdef MILO_DEBUG
    static DataArray *objects = SystemConfig("objects");
    objects->FindArray(sym1);
#endif
    DataNode *var = da->Var(3);
    DataNode node(*var);
// i really hate debug sometimes
#ifdef MILO_DEBUG
    bool b1 = false;
    for (ObjDirItr<Hmx::Object> it(this, b); it != 0; ++it) {
        bool b2 = false;
        if (IsASubclass(it->ClassName(), sym1)) {
            b1 = true;
            if (!sym2.Null()) {
                if (it->Type() != sym2) {
                    b1 = false;
                }
            }
            if (b1)
                b2 = true;
        }
        if (b2) {
            *var = DataNode(it);
            for (int i = 4; i < da->Size(); i++) {
                da->Command(i)->Execute();
            }
        }
    }
#else
    for (ObjDirItr<Hmx::Object> it(this, b); it != 0; ++it) {
        if (IsASubclass(it->ClassName(), sym1) && (sym2.Null() || it->Type() == sym2)) {
            *var = DataNode(it);
            for (int i = 4; i < da->Size(); i++) {
                da->Command(i)->Execute();
            }
        }
    }
#endif
    *var = node;
}

FilePath ObjectDir::GetSubDirPath(const FilePath &fp, const BinStream &bs) {
    static Message msg("change_subdir", DataNode(gNullStr));
    ((DataArray *)msg)->Node(2) = DataNode(fp.c_str());
    DataNode handled = HandleType(msg);
    FilePath localFP;
    if (handled.Type() == kDataUnhandled)
        localFP = fp;
    else {
        const char *strcmp2 = "stream_cache";
        const char *strcmp1 = handled.Str();
        bool matched = strcmp(strcmp1, strcmp2) == 0;
        if (matched) {
            bool bscached = bs.Cached();
            const char *cached = DirLoader::CachedPath(fp.c_str(), bscached);
            const char *pd = ".";
            FilePath period;
            period.Set(pd, cached);
            localFP = period;
        } else {
            const char *cc2 = handled.Str();
            const char *cc1 = FileRoot();
            FilePath root;
            root.Set(cc1, cc2);
            localFP = root;
        }
    }
    return localFP;
}

void ObjectDir::LoadSubDir(int i, const FilePath &fp, BinStream &bs, bool b) {
    if (IsProxy() && !mProxyFile.empty()) {
        mSubDirs[i] = 0;
    } else {
        FilePath subdirpath = GetSubDirPath(fp, bs);
        if (streq(mPathName, subdirpath.c_str())) {
            MILO_WARN(
                "%s trying to subdir self in slot %d, setting NULL", PathName(this), i
            );
            mSubDirs[i] = 0;
        } else
            mSubDirs[i].LoadFile(subdirpath, true, b, kLoadFront, true);
    }
}

bool ObjectDir::HasDirPtrs() const {
    FOREACH_OBJREF (it, this) {
        if ((*it)->IsDirPtr())
            return true;
    }
    return false;
}

BEGIN_HANDLERS(ObjectDir)
    HANDLE_ACTION(iterate, Iterate(_msg, true))
    HANDLE_ACTION(iterate_self, Iterate(_msg, false))
    HANDLE_ACTION(save_objects, DirLoader::SaveObjects(_msg->Str(2), this))
    HANDLE(find, OnFind)
    HANDLE_EXPR(exists, FindObject(_msg->Str(2), false) != nullptr)
    HANDLE_ACTION(sync_objects, SyncObjects())
    HANDLE_EXPR(is_proxy, IsProxy())
    HANDLE_EXPR(proxy_dir, mLoader ? mLoader->mProxyDir : NULL_OBJ)
    HANDLE_EXPR(
        proxy_name, mLoader ? (mLoader->mProxyName ? mLoader->mProxyName : "") : ""
    )
    HANDLE_ACTION(
        add_names,
        Reserve(
            mHashTable.mSize + _msg->Int(2) * 2, mStringTable.Size() + _msg->Int(2) * 0x14
        )
    )
    HANDLE_ACTION(override_proxy, SetProxyFile(FilePath(_msg->Str(2)), true))
    HANDLE_ACTION(delete_loader, RELEASE(mLoader))
    HANDLE_EXPR(get_path_name, mPathName)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7FD)
END_HANDLERS

ObjectDir *SyncSubDir(const FilePath &fp, ObjectDir *dir) {
    Loader *ldr = TheLoadMgr.GetLoader(fp);
    DirLoader *dirldr;
    if (dir->IsProxy())
        dirldr = dynamic_cast<DirLoader *>(ldr);
    else
        dirldr = dynamic_cast<DirLoader *>(TheLoadMgr.ForceGetLoader(fp));
    if (!dirldr)
        return 0;
    else {
        ObjectDir *odir = dirldr->GetDir();
        if (odir) {
            for (ObjDirItr<Hmx::Object> it(dir, false); it != 0; ++it) {
                Hmx::Object *found = odir->FindObject(it->Name(), false);
                if (found) {
                    if (found != odir) {
                        if (it != dir) {
                            MILO_WARN(
                                "%s exists in dir and subdir, so replacing %s with %s",
                                it->Name(),
                                PathName(it),
                                PathName(found)
                            );
                            while (!it->Refs().empty()) {
                                it->Refs().back()->Replace(it, found);
                            }
                            delete it;
                        }
                    }
                }
            }
        }
        return odir;
    }
}

DataNode ObjectDir::OnFind(DataArray *da) {
    Hmx::Object *found = FindObject(da->Str(2), false);
    if (da->Size() > 3) {
        if (da->Int(3) != 0 && !found) {
            MILO_FAIL("Couldn't find %s in %s", da->Str(2), Name());
        }
    }
    return DataNode(found);
}

bool PropSyncSubDirs(
    std::vector<ObjDirPtr<ObjectDir> > &vec,
    DataNode &val,
    DataArray *prop,
    int i,
    PropOp op
) {
    ObjectDir *theGDir = gDir;
    if (op == kPropSize) {
        MILO_ASSERT(i == prop->Size(), 0x8AE);
        val = DataNode((int)vec.size());
        return true;
    }
    MILO_ASSERT(i == prop->Size() - 1, 0x8B3);
    std::vector<ObjDirPtr<ObjectDir> >::iterator vecIt = vec.begin() + prop->Int(i);
    ObjDirPtr<ObjectDir> &ptr = *vecIt;
    switch (op) {
    case kPropGet:
        val = DataNode(ptr.GetFile().FilePathRelativeToRoot());
        break;
    case kPropSet:
        theGDir->RemovingSubDir(ptr);
        ptr = SyncSubDir(FilePath(val.Str()), theGDir);
        theGDir->AddedSubDir(ptr);
        break;
    case kPropRemove:
        theGDir->RemovingSubDir(ptr);
        vec.erase(vecIt);
        break;
    case kPropInsert:
        vecIt = vec.insert(
            vecIt, ObjDirPtr<ObjectDir>(SyncSubDir(FilePath(val.Str()), theGDir))
        );
        theGDir->AddedSubDir(*vecIt);
        break;
    default:
        return false;
    }
    return true;
}

void ObjectDir::SetPathName(const char *path) {
    if (mPathName != gNullStr) {
        _MemOrPoolFree(strlen(mPathName) + 1, FastPool, (void *)mPathName);
    }
    if (path != 0 && *path != '\0') {
        mPathName = (char *)_MemOrPoolAlloc(strlen(path) + 1, FastPool);
        strcpy((char *)mPathName, path);
        mStoredFile.SetRoot(mPathName);
    } else
        mPathName = gNullStr;
}

BEGIN_PROPSYNCS(ObjectDir)
    gDir = this;
    {
        static Symbol _s("subdirs");
        if (sym == _s) {
            PropSyncSubDirs(mSubDirs, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    if (sym == proxy_file) {
        if (_op == kPropSet) {
            SetProxyFile(FilePath(_val.Str()), false);
        } else {
            if (_op == (PropOp)0x40)
                return false;
            _val = DataNode(ProxyFile().FilePathRelativeToRoot());
        }
        return true;
    }
    SYNC_PROP(inline_proxy, mInlineProxy)
    SYNC_PROP_SET(path_name, mPathName, )
END_PROPSYNCS

#define DIM(x) 0x80U

void PreloadSharedSubdirs(Symbol sym) {
    DataArray *arr = SystemConfig("preload_subdirs")->FindArray(sym, false);
    if (arr) {
        for (int i = 1; i < arr->Size(); i++) {
            DataArray *thisArr = arr->Array(i);
            const char *thisStr = thisArr->Str(0);
            bool mem = false;
            if (thisArr->Size() > 1) {
                MemPushHeap(MemFindHeap(thisArr->Sym(1).Str()));
                mem = true;
            }
            MILO_ASSERT(gPreloadIdx < DIM(gPreloaded), 0x998);
            gPreloaded[gPreloadIdx++].LoadFile(
                FilePath(thisStr), false, true, kLoadFront, false
            );
            if (mem)
                MemPopHeap();
        }
    }
}
