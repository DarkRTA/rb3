#ifndef BEATMATCH_RGUTL_H
#define BEATMATCH_RGUTL_H
#include <vector>
#include "beatmatch/GameGem.h"
#include "beatmatch/RGState.h"

void RGSetTuning(const std::vector<int>&);
unsigned char RGGetTuning(int);
bool AddChordLevel(char*, int, int, int&, const char*, bool);
void RGParseOverrideChord(char*, int, const char*);
bool RGContainsNote(unsigned char, const GameGem&);
void RGStringContainsNote(unsigned char, const GameGem&, unsigned char&);
void HandleSlashChords(char*, int, const GameGem&, int, int&); // could return a bool?
bool HandleInterval(char*, int, const GameGem&, int, int&);
void HandleNoThird(char*, int, const GameGem&, int, int&);
void HandleNoSeventh(char*, int, const GameGem&, int, int&);
void HandleNoSeventhMinor(char*, int, const GameGem&, int, int&);
bool RGGetHeldFretRange(const RGState&, int&, int&);
void RGGetFretLabelInfo(const RGState&, int&, int&);
const char* RGFretNumberToString(int);

#endif
