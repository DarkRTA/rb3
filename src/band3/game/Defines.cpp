#include "Defines.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "meta_band/OvershellPanel.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"
#include "utl/Symbol.h"

Symbol ControllerTypeToSym(ControllerType controllerType) {
    MILO_ASSERT_RANGE_EQ(controllerType, 0, kNumControllerTypes, 0xF);
    return DataGetMacro("CHAR_INSTRUMENT_SYMBOLS")->Sym(controllerType);
}

ControllerType SymToControllerType(Symbol s) {
    for (int i = 0; i < 6; i++) {
        if (s == ControllerTypeToSym((ControllerType)i)) {
            return (ControllerType)i;
        }
    }
    MILO_ASSERT(false, 0x1D);
    return kControllerNone;
}

ControllerType TrackTypeToControllerType(TrackType trackType) {
    switch (trackType) {
    case kTrackDrum:
        return kControllerDrum;
    case kTrackVocals:
        return kControllerVocals;
    case kTrackGuitar:
    case kTrackBass:
        return kControllerGuitar;
    case kTrackKeys:
    case kTrackRealKeys:
        return kControllerKeys;
    case kTrackRealGuitar:
    case kTrackRealBass:
        return kControllerRealGuitar;
    default:
        return kControllerNone;
    }
}

TrackType ControllerTypeToTrackType(ControllerType ct, bool alt) {
    switch (ct) {
    case kControllerDrum:
        return kTrackDrum;
    case kControllerVocals:
        return kTrackVocals;
    case kControllerGuitar:
        return alt ? kTrackBass : kTrackGuitar;
    case kControllerKeys:
        return alt ? kTrackRealKeys : kTrackKeys;
    case kControllerRealGuitar:
        return alt ? kTrackRealBass : kTrackRealGuitar;
    default:
        return kTrackNone;
    }
}

ScoreType TrackTypeToScoreType(TrackType trackTy, bool b2, bool b3) {
    switch (trackTy) {
    case kTrackDrum:
        return b3 ? kScoreRealDrum : kScoreDrum;
    case kTrackBass:
        return kScoreBass;
    case kTrackGuitar:
        return kScoreGuitar;
    case kTrackVocals:
        return b2 ? kScoreHarmony : kScoreVocals;
    case kTrackKeys:
        return kScoreKeys;
    case kTrackRealGuitar:
        return kScoreRealGuitar;
    case kTrackRealBass:
        return kScoreRealBass;
    case kTrackRealKeys:
        return kScoreRealKeys;
    case kTrackNone:
    case kTrackPending:
    case kTrackPendingVocals:
        return kScoreBand;
    default:
        MILO_FAIL("unrecognized TrackType!");
        return kNumScoreTypes;
    }
}

TrackType ScoreTypeToTrackType(ScoreType scoreType) {
    switch (scoreType) {
    case kScoreDrum:
        return kTrackDrum;
    case kScoreRealDrum:
        return kTrackDrum;
    case kScoreBass:
        return kTrackBass;
    case kScoreGuitar:
        return kTrackGuitar;
    case kScoreVocals:
        return kTrackVocals;
    case kScoreHarmony:
        return kTrackVocals;
    case kScoreKeys:
        return kTrackKeys;
    case kScoreRealGuitar:
        return kTrackRealGuitar;
    case kScoreRealBass:
        return kTrackRealBass;
    case kScoreRealKeys:
        return kTrackRealKeys;
    case kScoreBand:
        return kTrackNone;
    default:
        MILO_FAIL("no TrackType for this ScoreType!");
        return kTrackNone;
    }
}

static inline const char *ScoreSymbolsMacro() { return "SCORE_TYPE_SYMBOLS"; }

FORCE_LOCAL_INLINE
Symbol ScoreTypeToSym(ScoreType s) { return DataGetMacro(ScoreSymbolsMacro())->Sym(s); }
END_FORCE_LOCAL_INLINE

static Symbol ForceScoreTypeToSym(ScoreType s) { return ScoreTypeToSym(s); }

ScoreType SymToScoreType(Symbol s) {
    for (int i = 0; i < kNumScoreTypes; i++) {
        if (s == ScoreTypeToSym((ScoreType)i)) {
            return (ScoreType)i;
        }
    }
    MILO_ASSERT(false, 0xA3);
    return kNumScoreTypes;
}

Difficulty SymToDifficulty(Symbol s) {
    for (int i = 0; i < kNumDifficulties; i++) {
        if (s == DifficultyToSym((Difficulty)i)) {
            return (Difficulty)i;
        }
    }
    MILO_ASSERT(false, 0xAE);
    return kNumDifficulties;
}

Difficulty DefaultDifficulty() {
    return (Difficulty)SystemConfig("tour")->FindInt("default_difficulty");
}

static inline const char *DiffSymbolsMacro() { return "DIFF_SYMBOLS"; }

FORCE_LOCAL_INLINE
Symbol DifficultyToSym(Difficulty diff) {
    return DataGetMacro(DiffSymbolsMacro())->Sym(diff);
}
END_FORCE_LOCAL_INLINE

Symbol DifficultyToShortSym(Difficulty diff) {
    return DataGetMacro("DIFF_SHORT_SYMBOLS")->Sym(diff);
}

void GetTracksPlayableByController(
    ControllerType ct, std::vector<TrackType> &tracks, OvershellPanel *panel
) {
    switch (ct) {
    case kControllerRealGuitar:
        tracks.push_back(kTrackRealBass);
        tracks.push_back(kTrackRealGuitar);
        break;
    case kControllerGuitar:
        tracks.push_back(kTrackBass);
        tracks.push_back(kTrackGuitar);
        if (!panel || panel->CanGuitarPlayKeys()) {
            tracks.push_back(kTrackKeys);
        }
        break;
    case kControllerKeys:
        tracks.push_back(kTrackBass);
        tracks.push_back(kTrackGuitar);
        tracks.push_back(kTrackKeys);
        tracks.push_back(kTrackRealKeys);
        break;
    case kControllerDrum:
        tracks.push_back(kTrackDrum);
        break;
    case kControllerVocals:
        tracks.push_back(kTrackVocals);
        break;
    default:
        MILO_WARN("No tracks playable by controller %i", ct);
        break;
    }
}

bool IsTrackPlayableByController(TrackType trackType, ControllerType cType) {
    std::vector<TrackType> tracks;
    GetTracksPlayableByController(cType, tracks, nullptr);
    return std::find(tracks.begin(), tracks.end(), trackType) != tracks.end();
}

void GetTracksRepresentativeOfPart(TrackType ty, std::vector<TrackType> &tracks) {
    switch (ty) {
    case kTrackGuitar:
    case kTrackRealGuitar:
        tracks.push_back(kTrackGuitar);
        tracks.push_back(kTrackRealGuitar);
        break;
    case kTrackBass:
    case kTrackRealBass:
        tracks.push_back(kTrackBass);
        tracks.push_back(kTrackRealBass);
        break;
    case kTrackKeys:
    case kTrackRealKeys:
        tracks.push_back(kTrackKeys);
        tracks.push_back(kTrackRealKeys);
        break;
    case kTrackVocals:
        tracks.push_back(kTrackVocals);
        break;
    case kTrackDrum:
        tracks.push_back(kTrackDrum);
        break;
    default:
        MILO_WARN("No tracks representative of part %i", ty);
        break;
    }
}

bool RepresentSamePart(TrackType t1, TrackType t2) {
    std::vector<TrackType> trackRepresentatives;
    GetTracksRepresentativeOfPart(t1, trackRepresentatives);
    return std::find(trackRepresentatives.begin(), trackRepresentatives.end(), t2)
        != trackRepresentatives.end();
}

bool IsRepresentativePartPlayableByController(TrackType t, ControllerType c) {
    std::vector<TrackType> trackRepresentatives;
    GetTracksRepresentativeOfPart(t, trackRepresentatives);
    for (int i = 0; i < trackRepresentatives.size(); i++) {
        if (IsTrackPlayableByController(trackRepresentatives[i], c))
            return true;
    }
    return false;
}

bool ControllerHasRepresentativePartPriority(ControllerType c, TrackType t) {
    switch (c) {
    case kControllerGuitar:
    case kControllerRealGuitar:
        return (t - 1U <= 7) && ((1 << (t - 1U)) & 0xA3);
    case kControllerKeys:
        return t == kTrackKeys || t == kTrackRealKeys;
    case kControllerDrum:
        return t == kTrackDrum;
    case kControllerVocals:
        return t == kTrackVocals;
    default:
        MILO_WARN("No priority tracks for controller %i", c);
        return false;
    }
}

void CensorString(String &) {}