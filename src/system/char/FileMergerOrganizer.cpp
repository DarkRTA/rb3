#include "char/FileMergerOrganizer.h"
#include "FileMergerOrganizer.h"
#include "char/FileMerger.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols.h"

FileMergerOrganizer *TheFileMergerOrganizer;
std::map<Symbol, CatData> gCatPriority;
int gNextCatPriority = 1;
bool gOrganizing;
bool gGenderChirality;

bool FileMergerSort(const FileMerger::Merger *m1, const FileMerger::Merger *m2) {
    CatData &m1data = gCatPriority[m1->mName];
    CatData &m2data = gCatPriority[m2->mName];
    if (m2data.priority == 0) {
#ifdef MILO_DEBUG
        if (gOrganizing) {
#endif
            MILO_WARN("unknown file merger organizer category %s", m2->mName);
            m2data.priority = gNextCatPriority++;
            m2data.unk4 = false;
#ifdef MILO_DEBUG
        }
#endif
    }
    if (m1data.priority == 0) {
#ifdef MILO_DEBUG
        if (gOrganizing) {
#endif
            MILO_WARN("unknown file merger organizer category %s", m2->mName);
            m1data.priority = gNextCatPriority++;
            m1data.unk4 = false;
#ifdef MILO_DEBUG
        }
#endif
    }

    CatData aData = m1data;
    CatData bData = m2data;

    if (m1->loading.empty()) {
        aData.priority -= gNextCatPriority;
        MILO_ASSERT(aData.priority < 0, 0x5B);
    }
    if (m2->loading.empty()) {
        bData.priority -= gNextCatPriority;
        MILO_ASSERT(bData.priority < 0, 0x5B);
    }
    if (aData.unk4 && bData.unk4) {
        // const char* str1 = strstr(m1->loading.c_str(), "female");
        // const char* str2 = strstr(m2->loading.c_str(), "female");
        bool females = strstr(m1->loading.c_str(), "female")
            && strstr(m2->loading.c_str(), "female");
        if (females)
            return gGenderChirality != females;
    }
    if (aData.priority == bData.priority) {
        return strcmp(m1->loading.c_str(), m2->loading.c_str()) < 0;
    } else
        return aData.priority < bData.priority;
}

FileMerger::Merger *FileMergerOrganizer::FrontInactiveMerger(OrganizedFileMerger *ofm) {
    std::list<FileMerger::Merger *>::iterator it = ofm->merger->mFilesPending.begin();
    if (ofm->merger->mCurLoader)
        it++;
    if (it == ofm->merger->mFilesPending.end())
        return nullptr;
    else
        return *it;
}

void FileMergerOrganizer::StartLoad() {
    gGenderChirality = RandomInt() & 1;
    RELEASE(mStartOrg);
    CheckDone();
}

void FileMergerOrganizer::CheckDone() {
    MILO_ASSERT(mActiveOrg == NULL, 0x93);
    MILO_ASSERT(mStartOrg == NULL, 0x94);
    OrganizedFileMerger *o5 = nullptr;
    FileMerger::Merger *m4 = nullptr;
    for (std::list<OrganizedFileMerger>::iterator it = unk20.begin(); it != unk20.end();
         ++it) {
        OrganizedFileMerger *curr = &*it;
        MILO_ASSERT(curr->state != kPendingLoad, 0x9F);
        FileMerger::Merger *front = FrontInactiveMerger(curr);
        if (!front) {
            RemoveFileMerger(curr);
            return;
        }
        if (!o5 || !FileMergerSort(m4, front)) {
            o5 = curr;
            m4 = front;
        }
    }
    if (o5)
        Dispatch(o5);
}

void FileMergerOrganizer::Dispatch(FileMergerOrganizer::OrganizedFileMerger *ofm) {
    MILO_ASSERT(mActiveOrg == NULL, 0xC0);
    mActiveOrg = ofm;
    if (mActiveOrg->state != kFailedLoad) {
        for (std::list<OrganizedFileMerger>::iterator it = unk20.begin();
             it != unk20.end();
             ++it) {
            OrganizedFileMerger *curr = &*it;
            MILO_ASSERT(curr->state != kPendingLoad, 0xC9);
        }
    }
    if (ofm->state == kFinishLoad) {
        ofm->merger->FinishLoading(ofm->merger->mCurLoader);
    } else if (ofm->state == kFailedLoad) {
        ofm->merger->FailedLoading(ofm->merger->mCurLoader);
    } else if (ofm->state == 0) {
        ofm->merger->LaunchNextLoader();
    } else {
        MILO_FAIL("Unknown dispatch state %d\n", ofm->state);
    }
    ofm->state = kPendingLoad;
}

void FileMergerOrganizer::AddFileMerger(FileMerger *fm) {
    if (!gOrganizing)
        fm->LaunchNextLoader();
    else {
        MILO_ASSERT(fm->mOrganizer == fm, 0xF1);
        MILO_ASSERT(fm->mCurLoader == NULL, 0xF2);
        for (std::list<OrganizedFileMerger>::iterator it = unk20.begin();
             it != unk20.end();
             it++) {
            OrganizedFileMerger *curr = &*it;
            MILO_ASSERT(curr->merger != fm, 0xF6);
        }
        fm->mOrganizer = this;
        OrganizedFileMerger ofm;
        ofm.merger = fm;
        ofm.state = (OrganizedState)0;
        unk20.push_back(ofm);
        if (mActiveOrg == 0 && !mStartOrg) {
            mStartOrg = new FileMergerOrganizerLoader();
        }
    }
}

void FileMergerOrganizer::RemoveFileMerger(FileMergerOrganizer::OrganizedFileMerger *ofm
) {
    MILO_ASSERT(!mActiveOrg, 0x10A);
    if (ofm->merger->mCurLoader) {
        Dispatch(ofm);
    }
    FileMerger *merger = ofm->merger;
    if (!merger->mCurLoader) {
        merger->mOrganizer = merger;
        for (std::list<OrganizedFileMerger>::iterator it = unk20.begin();
             it != unk20.end();
             it++) {
            if (&*it == ofm) {
                unk20.erase(it);
                break;
            }
        }
        mActiveOrg = nullptr;
        CheckDone();
    }
}

void FileMergerOrganizer::FinishLoading(Loader *l) {
    OrganizedFileMerger *org = mActiveOrg;
    MILO_ASSERT(org->merger->mCurLoader == l, 0x138);
    MILO_ASSERT(org->merger->mFilesPending.front()->loading == l->LoaderFile(), 0x139);
    MILO_ASSERT(org->state == kPendingLoad, 0x13A);
    org->state = (OrganizedState)1;
    mActiveOrg = nullptr;
    if (l->LoaderFile().empty()) {
        if (FrontInactiveMerger(org)) {
            Dispatch(org);
        } else
            RemoveFileMerger(org);
    } else
        CheckDone();
}

void FileMergerOrganizer::FailedLoading(Loader *l) {
    OrganizedFileMerger *org = nullptr;
    for (std::list<OrganizedFileMerger>::iterator it = unk20.begin(); it != unk20.end();
         ++it) {
        org = &*it;
        if (org->merger->mCurLoader && org->merger->mCurLoader == l)
            break;
    }
    MILO_ASSERT(org, 0x167);
    MILO_ASSERT(org->merger->mFilesPending.front()->loading == l->LoaderFile(), 0x16A);
    MILO_ASSERT(org->merger->mCurLoader == l, 0x16B);
    MILO_ASSERT(org->state == kPendingLoad || (org->state == kFinishLoad && mActiveOrg != org), 0x16D);
    org->state = (OrganizedState)2;
    OrganizedFileMerger *oldOrg = mActiveOrg;
    mActiveOrg = nullptr;
    Dispatch(org);
    MILO_ASSERT(org->merger->mCurLoader == NULL, 0x178);
    org->state = (OrganizedState)0;
    if (oldOrg == org)
        oldOrg = nullptr;
    mActiveOrg = oldOrg;
    if (!mActiveOrg && !mStartOrg) {
        for (std::list<OrganizedFileMerger>::iterator it = unk20.begin();
             it != unk20.end();
             ++it) {
            OrganizedFileMerger *curr = &*it;
            MILO_ASSERT(curr->state != kPendingLoad, 0x187);
        }
        mStartOrg = new FileMergerOrganizerLoader();
    }
}

void FileMergerOrganizer::Init() {
    MILO_ASSERT(gNextCatPriority == 1, 0x192);
    Register();
    DataArray *cfg = SystemConfig("file_merger_organizer");
    DataArray *catArr = cfg->FindArray("category_order", false);
    DataArray *genderArr = cfg->FindArray("gender_order", false);
    if (catArr) {
        for (; gNextCatPriority < catArr->Size(); gNextCatPriority++) {
            DataArray *curCatArr = catArr->Array(gNextCatPriority);
            for (int i = 0; i < curCatArr->Size(); i++) {
                Symbol key = curCatArr->Sym(i);
                CatData &val = gCatPriority[key];
                val.priority = gNextCatPriority;
                val.unk4 = genderArr && genderArr->Contains(key);
            }
            gOrganizing = true;
        }
    }
    FileMergerOrganizer::NewObject(); // ???
}

FileMergerOrganizer::FileMergerOrganizer() : mActiveOrg(0), mStartOrg(0) {
    MILO_ASSERT(TheFileMergerOrganizer == NULL, 0x1B2);
    TheFileMergerOrganizer = this;
}

void FileMergerOrganizer::Save(BinStream &) {
    MILO_FAIL("Can't save TheFileMergerOrganizer");
}

BEGIN_LOADS(FileMergerOrganizer)
    MILO_FAIL("Can't load TheFileMergerOrganizer");
END_LOADS

BEGIN_COPYS(FileMergerOrganizer)
    MILO_FAIL("Can't copy TheFileMergerOrganizer");
END_COPYS

BEGIN_HANDLERS(FileMergerOrganizer)
    HANDLE_ACTION(add_file_merger, AddFileMerger(_msg->Obj<FileMerger>(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1CF)
END_HANDLERS

BEGIN_PROPSYNCS(FileMergerOrganizer)
END_PROPSYNCS

inline void FileMergerOrganizerLoader::PollLoading() {
    TheFileMergerOrganizer->StartLoad();
}