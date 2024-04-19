#ifndef BEATMATCH_RGUTL_H
#define BEATMATCH_RGUTL_H
#include <vector>
#include "beatmatch/GameGem.h"

void RGSetTuning(const std::vector<int>&);
unsigned char RGGetTuning(int);
bool AddChordLevel(char*, int, int, int&, const char*, bool);
void RGParseOverrideChord(char*, int, const char*);
bool RGContainsNote(unsigned char, const GameGem&);
void RGStringContainsNote(unsigned char, const GameGem&, unsigned char&);

#endif
