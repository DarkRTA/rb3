#include "ContextChecker.h"
#include "decomp.h"
#include "game/Defines.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/GameMode.h"
#include "math/Rand.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include <set>
#include <vector>

namespace {
    std::set<Symbol> gUsedContexts;
    String gStoredContext;
    Rand gContextRand(0);
    int gContextWeight = 10;

    bool IsContextUsed(Symbol ctx) {
        return gUsedContexts.find(ctx) != gUsedContexts.end();
    }

    Symbol GetSong() {}

    bool InternalCheckContext(const DataArray *a);
    bool CheckContextAnd(const DataArray *a) {
        for (int i = 1; i < a->Size(); i++) {
            if (!InternalCheckContext(a->Array(i)))
                return false;
        }
        return true;
    }

    bool CheckContextOr(const DataArray *a) {
        for (int i = 1; i < a->Size(); i++) {
            if (InternalCheckContext(a->Array(i)))
                return true;
        }
        return false;
    }

    bool CheckContextNot(const DataArray *arr) {
        MILO_ASSERT(arr->Size() == 2, 0x42);
        return !InternalCheckContext(arr->Array(1));
    }

    bool CheckContextModeProperty(const DataArray *arr) {
        MILO_ASSERT(arr->Size() == 3, 0x52);
        return *TheGameMode->Property(arr->Sym(1), true) == arr->Node(2);
    }

    bool CheckContextDiff(const DataArray *a) {
        Difficulty avg = TheGameConfig->GetAverageDifficulty();
        for (int i = 1; i < a->Size(); i++) {
            if (SymToDifficulty(a->Sym(i)) == avg)
                return true;
        }
        return false;
    }

    bool CheckContextInstrument(const DataArray *a) {
        for (int i = 1; i < a->Size(); i++) {
            if (TheGameConfig->IsInstrumentUsed(a->Sym(i)))
                return true;
        }
        return false;
    }

    bool CheckContextSong(const DataArray *a) {
        Symbol song = GetSong();
        for (int i = 1; i < a->Size(); i++) {
            if (a->Sym(i) == song)
                return true;
        }
        return false;
    }

    bool CheckContextLastSong(const DataArray *a) {
        Symbol song = GetSong();
        for (int i = 1; i < a->Size(); i++) {
            if (a->Sym(i) == song)
                return true;
        }
        return false;
    }

    bool CheckContextArtist(const DataArray *a) {
        Symbol song = GetSong();
        BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(
            TheSongMgr.GetSongIDFromShortName(song, true)
        );
        for (int i = 1; i < a->Size(); i++) {
            if (streq(a->Str(i), data->Artist()))
                return true;
        }
        return false;
    }

    bool CheckContextCity(const DataArray *a) { return false; }

    bool CheckContextVenue(const DataArray *a) {
        Symbol venue = MetaPerformer::Current()->GetVenue();
        for (int i = 1; i < a->Size(); i++) {
            if (a->Sym(i) == venue)
                return true;
        }
        return false;
    }

    bool CheckContextNumRestarts(const DataArray *arr) {
        if (!TheGame)
            return false;
        Performer *mainPerformer = TheGame->GetMainPerformer();
        MILO_ASSERT(mainPerformer, 0xA2);
        int numRestarts = mainPerformer->GetNumRestarts();
        MILO_ASSERT(arr->Size() >= 2, 0xA6);
        int aRestarts = arr->Int(1);
        if (aRestarts == numRestarts)
            return true;
        else
            return false;
    }

    bool CheckContextNumRestartsGreater(const DataArray *arr) {
        if (!TheGame)
            return false;
        Performer *mainPerformer = TheGame->GetMainPerformer();
        MILO_ASSERT(mainPerformer, 0xB6);
        int numRestarts = mainPerformer->GetNumRestarts();
        MILO_ASSERT(arr->Size() >= 2, 0xBA);
        int aRestarts = arr->Int(1);
        if (numRestarts > aRestarts)
            return true;
        else
            return false;
    }

    bool CheckContextNumRestartsNot(const DataArray *arr) {
        if (!TheGame)
            return false;
        Performer *mainPerformer = TheGame->GetMainPerformer();
        MILO_ASSERT(mainPerformer, 0xCA);
        int numRestarts = mainPerformer->GetNumRestarts();
        MILO_ASSERT(arr->Size() >= 2, 0xCE);
        int aRestarts = arr->Int(1);
        if (numRestarts != aRestarts)
            return true;
        else
            return false;
    }

#pragma push
#pragma pool_data off
    bool InternalCheckContext(const DataArray *a) {
        static Symbol sym_and = "and";
        static Symbol sym_or = "or";
        static Symbol sym_not = "not";
        static Symbol mode_property = "mode_property";
        static Symbol diff = "diff";
        static Symbol instrument = "instrument";
        static Symbol song = "song";
        static Symbol artist = "artist";
        static Symbol last_song = "last_song";
        static Symbol city = "city";
        static Symbol venue = "venue";
        static Symbol unlocked = "unlocked";
        static Symbol weight = "weight";
        static Symbol song_specific = "song_specific";
        static Symbol num_restarts = "num_restarts";
        static Symbol num_restarts_greater = "num_restarts_greater";
        static Symbol num_restarts_not = "num_restarts_not";
        static Symbol singer = "singer";
        static Symbol songtype = "songtype";
        static Symbol new_ar_console = "new_ar_console";
        Symbol ctxSym = a->Sym(0);
        if (ctxSym == sym_and) {
            return CheckContextAnd(a);
        } else if (ctxSym == sym_or) {
            return CheckContextOr(a);
        } else if (ctxSym == sym_not) {
            return CheckContextNot(a);
        } else if (ctxSym == mode_property) {
            return CheckContextModeProperty(a);
        } else if (ctxSym == diff) {
            return CheckContextDiff(a);
        } else if (ctxSym == instrument) {
            return CheckContextInstrument(a);
        } else if (ctxSym == song) {
            return CheckContextSong(a);
        } else if (ctxSym == artist) {
            return CheckContextArtist(a);
        } else if (ctxSym == last_song) {
            return CheckContextLastSong(a);
        } else if (ctxSym == city) {
            return CheckContextCity(a);
        } else if (ctxSym == venue) {
            return CheckContextVenue(a);
        } else if (ctxSym == num_restarts) {
            return CheckContextNumRestarts(a);
        } else if (ctxSym == num_restarts_greater) {
            return CheckContextNumRestartsGreater(a);
        } else if (ctxSym == num_restarts_not) {
            return CheckContextNumRestartsNot(a);
        } else if (ctxSym == unlocked) {
            return false;
        } else if (ctxSym == weight) {
            gContextWeight = a->Int(1);
            return true;
        } else if (ctxSym == song_specific) {
            return true;
        } else {
            MILO_WARN(
                "Data array at file %s line %d was not valid context-checker",
                a->File(),
                a->Line()
            );
            return false;
        }
    }
#pragma pop
}

int CheckContext(const DataArray *a) { return gContextWeight & CheckContextAnd(a); }

void HandleContextUsed(Symbol ctx) { gUsedContexts.insert(ctx); }

void PotentiallyCreateAndAddEntry(
    Symbol s, const char *c, int i, bool b, std::vector<WeightedEntry> &vec, int &iref
) {
    bool b1 = false;
    if (b) {
        if (IsContextUsed(s))
            b1 = true;
    }
    if (!b1) {
        iref += i;
        vec.push_back(WeightedEntry(iref, s, c));
    }
}

bool IsSongSpecificEntry(const DataArray *a) {
    for (int i = 1; i < a->Size(); i++) {
        if (a->Array(i)->Sym(0) == song_specific)
            return true;
    }
    return false;
}

std::vector<Symbol> GetSongSpecificEntriesForCategory(Symbol, bool) {
    return std::vector<Symbol>();
}

std::vector<Symbol> GetSongSpecificEntries(const DataArray *a) {
    for (int i = 1; i < a->Size(); i++) {
        DataArray *thisEntry = a->Array(i);
        if (thisEntry->Sym(0) == song_specific) {
            MILO_ASSERT(thisEntry->Size() >= 3, 0x164);
            Symbol cat = thisEntry->Sym(1);
            return GetSongSpecificEntriesForCategory(cat, thisEntry->Sym(2) == last_song);
        }
    }
    std::vector<Symbol> empty;
    return empty;
}

int InqMatchedEntries(const DataArray *a, bool b, std::vector<WeightedEntry> &vec) {
    int ret = 0;
    for (int i = 1; i < a->Size(); i++) {
        DataArray *curArr = a->Array(i);
        int ctx = CheckContext(curArr);
        if (ctx > 0) {
            if (IsSongSpecificEntry(curArr)) {
                std::vector<Symbol> entries = GetSongSpecificEntries(curArr);
                if (!entries.empty()) {
                    float f1 = (float)ctx / (float)entries.size();
                    if (f1 < 1.0f)
                        f1 = 1.0f;
                    int i1 = f1;
                    FOREACH (it, entries) {
                        PotentiallyCreateAndAddEntry(gNullStr, it->mStr, i1, b, vec, ret);
                    }
                }
            } else {
                PotentiallyCreateAndAddEntry(curArr->Sym(0), nullptr, ctx, b, vec, ret);
            }
        }
    }
    return ret;
}

const char *RandomContextSensitiveItemInternal(const DataArray *, bool, bool) {}

const char *RandomContextSensitiveItem(const DataArray *a, bool b) {
    const char *item = RandomContextSensitiveItemInternal(a, false, b);
    if (b && item == gNullStr) {
        MILO_FAIL("No valid context-sensitive item");
    }
    return item;
}

DECOMP_FORCEACTIVE(ContextChecker, "( index + 1 ) < arr->Size()", "")

DataNode OnRandomContext(DataArray *a) {
    return RandomContextSensitiveItem(a->Array(1), true);
}

DataNode OnRandomContextCount(DataArray *a) { return a->Array(1)->Size() - 1; }

DataNode OnRandomContextAllowFailure(DataArray *a) {
    return RandomContextSensitiveItem(a->Array(1), false);
}

void SeedRandomContext(int seed) { gContextRand.Seed(seed); }

DataNode OnSeedRandomContext(DataArray *a) {
    SeedRandomContext(a->Int(1));
    return 1;
}

DataNode OnHandleContextUsed(DataArray *a) {
    HandleContextUsed(a->Sym(1));
    return 1;
}

void ContextCheckerInit() {
    DataRegisterFunc("random_context", OnRandomContext);
    DataRegisterFunc("random_context_allow_failure", OnRandomContextAllowFailure);
    DataRegisterFunc("seed_random_context", OnSeedRandomContext);
    DataRegisterFunc("handle_context_used", OnHandleContextUsed);
    DataRegisterFunc("random_context_count", OnRandomContextCount);
    gContextRand.Seed(RandomInt());
}