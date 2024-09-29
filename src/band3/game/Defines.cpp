#include "Defines.h"
#include <os/Debug.h>
#include <obj/DataUtl.h>

TrackType ControllerTypeToTrackType(ControllerType controllerType, bool alt) {
    switch (controllerType) {
    case kControllerDrum:
        return kTrackDrum;
    case kControllerVocals:
        return kTrackVocals;
    case kControllerGuitar:
        return alt ? kTrackBass : kTrackGuitar;
    case kControllerRealGuitar:
        return alt ? kTrackRealBass : kTrackRealGuitar;
    case kControllerKeys:
        return alt ? kTrackRealKeys : kTrackKeys;
    default:
        return kTrackNone;
    }
}

TrackType ScoreTypeToTrackType(ScoreType scoreType) {
    TrackType trackType;
    switch (scoreType) {
    case kScoreDrum:
        trackType = kTrackDrum;
        break;
    case kScoreBass:
        trackType = kTrackBass;
        break;
    case kScoreGuitar:
        trackType = kTrackGuitar;
        break;
    case kScoreVocals:
        trackType = kTrackVocals;
        break;
    case kScoreHarmony:
        trackType = kTrackVocals;
        break;
    case kScoreKeys:
        trackType = kTrackKeys;
        break;
    case kScoreRealDrum:
        trackType = kTrackDrum;
        break;
    case kScoreRealGuitar:
        trackType = kTrackRealGuitar;
        break;
    case kScoreRealBass:
        trackType = kTrackRealBass;
        break;
    case kScoreRealKeys:
        trackType = kTrackRealKeys;
        break;
    case kScoreBand:
        trackType = kTrackNone;
        break;
    default:
        TheDebug.Fail(MakeString("no TrackType for this ScoreType!"));
        trackType = kTrackNone;
    }
    return trackType;
}

ControllerType TrackTypeToControllerType(TrackType trackType) {
    switch (trackType) {
    case kTrackDrum:
        return kControllerDrum;
    case kTrackGuitar:
    case kTrackBass:
        return kControllerGuitar;
    case kTrackVocals:
        return kControllerVocals;
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
