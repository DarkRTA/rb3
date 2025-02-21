#pragma once
#include <vector>
#include "beatmatch/GameGem.h"
#include "beatmatch/RGState.h"

enum RGString {
    kRGStringELow = 0,
    kRGStringA = 1,
    kRGStringD = 2,
    kRGStringG = 3,
    kRGStringB = 4,
    kRGStringEHigh = 5,
    kNumRGStrings = 6,
    kNumStrings = 6
};

void RGSetTuning(const std::vector<int> &);
unsigned char RGGetTuning(int);
bool AddChordLevel(char *, int, int, int &, const char *, bool);
void RGParseOverrideChord(char *, int, const char *);
bool RGContainsNote(unsigned char, const GameGem &);
void RGStringContainsNote(unsigned char, const GameGem &, unsigned char &);
void HandleSlashChords(char *, int, const GameGem &, int, int &);
bool HandleInterval(char *, int, const GameGem &, int, int &);
void HandleNoThird(char *, int, const GameGem &, int, int &);
void HandleNoSeventh(char *, int, const GameGem &, int, int &);
void HandleNoSeventhMinor(char *, int, const GameGem &, int, int &);
bool RGGetHeldFretRange(const RGState &, int &, int &);
void RGGetFretLabelInfo(const RGState &, int &, int &);
const char *RGFretNumberToString(int);
void RGUnpackChordShapeID(unsigned int, std::vector<int> &, std::vector<bool> *);
void RGGameGemToRGState(const GameGem &, RGState &, bool);
const char *RGGetNoteName(unsigned char, int);
bool RGGetHeldFretRange(const GameGem &, int &, int &, bool);
unsigned int RGGetStrumBitMask(const GameGem &);
unsigned int RGGetChordShapeID(const GameGem &gem, bool b);
void RGGetChordName(char *, int, const GameGem &, int, int, bool);
void RGGetFretLabelInfo(const GameGem &, int &, int &, bool);