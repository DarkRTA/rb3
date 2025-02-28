#pragma once
#include "game/Defines.h"

bool IsLeaderLocal();
const char *GetFontCharFromInstrument(Symbol, int);
const char *GetFontCharFromTrackType(TrackType, int);
const char *GetFontCharForProDrums(int);
const char *GetFontCharForHarmonyMics(int, int);
const char *GetFontCharFromScoreType(ScoreType, int);
const char *GetFontCharFromControllerType(ControllerType, int);
bool IsVignette(class UIPanel *);