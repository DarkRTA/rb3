#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

#include "utl/Symbol.h"
enum Difficulty {
    kDifficultyEasy,
    kDifficultyMedium,
    kDifficultyHard,
    kDifficultyExpert
};

Difficulty DefaultDifficulty();
Symbol DifficultyToSym(Difficulty);

#endif // GAME_DEFINES_H