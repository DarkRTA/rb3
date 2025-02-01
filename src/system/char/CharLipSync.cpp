#include "char/CharLipSync.h"
#include "decomp.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/PropAnim.h"
#include "rndobj/PropKeys.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

INIT_REVS(CharLipSync)

CharLipSync::Generator::Generator() : mLipSync(0), mLastCount(0), mWeights() {}

void CharLipSync::Generator::Init(CharLipSync *sync) {
    mLipSync = sync;
    mLipSync->mData.resize(0);
    mWeights.resize(mLipSync->mVisemes.size());
    for (int i = 0; i < mWeights.size(); i++) {
        mWeights[i].unk0 = 0;
        mWeights[i].unk1 = 0;
    }
    mLastCount = mLipSync->mData.size();
    mLipSync->mData.push_back(0);
    mLipSync->mFrames = 0;
}

void CharLipSync::Generator::AddWeight(int i, float f) { Clamp<float>(0, 255, f); }

void CharLipSync::Generator::NextFrame() {
    int count = mLipSync->mData.size() - mLastCount;
    MILO_ASSERT(count >= 0 && count < 256, 0x40);
    mLipSync->mData[mLastCount] = count;
    mLastCount = mLipSync->mData.size();
    mLipSync->mData.push_back(0);
    mLipSync->mFrames++;
}

void CharLipSync::Generator::Finish() {
    mLipSync->mData.pop_back();
    std::vector<bool> bools;
    bools.resize(mLipSync->mVisemes.size());
    for (int i = 0; i < bools.size(); i++)
        bools[i] = false;

    int idx = 0;
    for (int i = 0; i < mLipSync->mFrames; i++) {
        int count = mLipSync->mData[idx++];
        MILO_ASSERT(count <= mLipSync->mVisemes.size(), 0x57);
        for (int j = 0; j < count; j++) {
            int viseme = mLipSync->mData[idx++];
            MILO_ASSERT(viseme < mLipSync->mVisemes.size(), 0x5B);
            if (mLipSync->mData[idx] != 0) {
                bools[viseme] = true;
            }
        }
    }

    for (int i = 0; i < bools.size(); i) {
        if (!bools[i]) {
            bools.erase(bools.begin() + i);
            RemoveViseme(i);
        } else
            i++;
    }
}

void CharLipSync::Generator::RemoveViseme(int visemeIdx) {
    mLipSync->mVisemes.erase(mLipSync->mVisemes.begin() + visemeIdx);

    int idx = 0;
    for (int i = 0; i < mLipSync->mFrames; i++) {
        int count = mLipSync->mData[idx++];
        for (int j = 0; j < count; j++) {
            MILO_WARN("data[cur] < mLipSync->mVisemes.size()");
        }
    }
}

CharLipSync::PlayBack::PlayBack()
    : mLipSync(0), mPropAnim(0), mClips(0), mIndex(0), mOldIndex(0), mFrame(-1) {}

void CharLipSync::PlayBack::Set(CharLipSync *lipsync, ObjectDir *dir) {
    mClips = dir;
    if (lipsync->GetPropAnim()) {
        mPropAnim = lipsync->GetPropAnim();
        MILO_ASSERT(mPropAnim->GetRate() == RndAnimatable::k30_fps, 0xA4);
        std::vector<PropKeys *> &keys = mPropAnim->mPropKeys;
        mWeights.resize(keys.size());
        int idx = 0;
        for (std::vector<PropKeys *>::iterator it = keys.begin(); it != keys.end();
             ++it) {
            String str((*it)->mProp->Str(0));
            ObjPtr<CharClip> &clip = mWeights[idx].unk0;
            clip = mClips->Find<CharClip>(str.c_str(), false);
            if (!clip)
                MILO_WARN("could not find %s", str.c_str());
            idx++;
        }
    } else {
        mLipSync = lipsync;
        mWeights.resize(mLipSync->mVisemes.size());
        for (int i = 0; i < mWeights.size(); i++) {
            ObjPtr<CharClip> &clip = mWeights[i].unk0;
            clip = mClips->Find<CharClip>(mLipSync->mVisemes[i].c_str(), false);
            if (!clip) {
                MILO_WARN("could not find %s", mLipSync->mVisemes[i].c_str());
            }
        }
    }
}

void CharLipSync::PlayBack::Reset() {
    mIndex = 0;
    mFrame = -1;
    for (int i = 0; i < mWeights.size(); i++) {
        Weight &weight = mWeights[i];
        weight.unk10 = 0;
        weight.unk14 = 0;
        weight.unkc = 0;
    }
}

void CharLipSync::PlayBack::Poll(float f) {}

CharLipSync::CharLipSync() : mPropAnim(this), mFrames(0) {}

CharLipSync::~CharLipSync() {}

SAVE_OBJ(CharLipSync, 0x155)

BEGIN_LOADS(CharLipSync)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mVisemes;
    bs >> mFrames;
    bs >> mData;
    if (gRev != 0)
        bs >> mPropAnim;
END_LOADS

DECOMP_FORCEACTIVE(
    CharLipSync,
    "; song: ",
    "\n",
    "(visemes\n",
    "   ",
    ")\n",
    "(frames ; @ 30fps\n",
    "   ( ",
    " "
)

void CharLipSync::Parse(DataArray *arr) {
    DataArray *visemesArr = arr->FindArray("visemes", true);
    mVisemes.resize(visemesArr->Size() - 1);
    for (int i = 1; i < visemesArr->Size(); i++) {
        mVisemes[i - 1] = visemesArr->Str(i);
    }
    Generator gen;
    gen.Init(this);
    DataArray *framesArr = arr->FindArray("frames", true);
    for (int i = 1; i < framesArr->Size(); i++) {
        DataArray *innerArr = framesArr->Array(i);
        for (int j = 0; j < innerArr->Size(); j++) {
            gen.AddWeight(j, innerArr->Float(j));
        }
        gen.NextFrame();
    }
    gen.Finish();
}

BEGIN_COPYS(CharLipSync)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharLipSync)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mVisemes)
        COPY_MEMBER(mFrames)
        COPY_MEMBER(mData)
        COPY_MEMBER(mPropAnim)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_PROPSYNCS(CharLipSync)
    SYNC_PROP_STATIC(frames, mFrames)
    SYNC_PROP_SET(duration, Duration(), )
    SYNC_PROP_MODIFY_STATIC(visemes, mVisemes, )
    SYNC_PROP(prop_anim, mPropAnim)
END_PROPSYNCS

BEGIN_HANDLERS(CharLipSync)
    HANDLE(parse, OnParse)
    HANDLE(parse_array, OnParseArray)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1E3)
END_HANDLERS

DataNode CharLipSync::OnParse(DataArray *arr) {
    FilePath fp(arr->Str(2));
    DataArray *read = DataReadFile(fp.c_str(), true);
    if (read) {
        Parse(read);
        read->Release();
    }
    return 0;
}

DataNode CharLipSync::OnParseArray(DataArray *arr) {
    DataArray *read = arr->Array(2);
    if (read) {
        Parse(read);
        read->Release();
    }
    return 0;
}