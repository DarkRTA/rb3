#include "synth/Utl.h"

float CalcSpeedFromTranspose(float f) { return std::pow(2.0f, f / 12.0f); }