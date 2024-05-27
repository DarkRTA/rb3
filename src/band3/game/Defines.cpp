#include "Defines.h"

TrackType ScoreTypeToTrackType(ScoreType scoreType) {
    TrackType trackType;
    switch(scoreType) {
        case 0:

    }
    return trackType;
}

ControllerType TrackTypeToControllerType(TrackType trackType) {
    switch (trackType) {
        case 0:
        return kControllerDrum;
        case 1:
        case 2:
        return kControllerGuitar;
        case 3:
        return kControllerVocals;
        case 4:
        case 5:
        return kControllerNone;
        case 6:
        case 8:
        return (ControllerType)4;
        default: 
        return (ControllerType)5;
    }
}
