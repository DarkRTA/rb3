#include "beatmatch/RGUtl.h"
#include "os/Debug.h"
#include <string.h>

const char* gNoteNames[] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};
const char* gNoteFlatNames[] = {
    "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"
};
unsigned char gStringNotes[6] = { 0x28, 0x2D, 0x32, 0x37, 0x3B, 0x40 };
unsigned char gTunedNotes[6] = { 0x28, 0x2D, 0x32, 0x37, 0x3B, 0x40 };
int gSlashNote = -1;
int gSlashString = -1;
int gSlashFret = -1;
bool gSuperscriptStarted;

void RGSetTuning(const std::vector<int>& vec){
    unsigned char* stringPtr = gStringNotes;
    unsigned char* tunedPtr = gTunedNotes;
    int i5 = 0;
    for(int i = 0; i < vec.size(); i++){
        int note = *stringPtr + i + i5;
        MILO_ASSERT(( 0) <= (note) && (note) < ( 256), 0x45);
        *tunedPtr = note;
        stringPtr++;
        tunedPtr++;
        i5 += 4;
    }
}

unsigned char RGGetTuning(int string){
    MILO_ASSERT(( 0) <= (string) && (string) < ( 6), 0x4C);
    return gTunedNotes[string];
}

#define start "<gtr>"
#define end "</gtr>"

bool AddChordLevel(char* buffer, int bufferLen, int i3, int& i4, const char* cc, bool bbb){
    char localBuf[256];
    int bufIdx = 0;
    if(bbb && !gSuperscriptStarted){
        MILO_ASSERT(strlen(buffer) + strlen(start) < bufferLen - 1, 0x5B);
        strcat(buffer, start);
        gSuperscriptStarted = true;
    }
    else if(!bbb && gSuperscriptStarted){
        MILO_ASSERT(strlen(buffer) + strlen(end) < bufferLen - 1, 0x62);
        strcat(buffer, end);
        gSuperscriptStarted = false;
    }
    for(char* p = (char*)cc; *p != 0; p++){
        if(*p == 0x23){
            localBuf[bufIdx] = -0x3E;
            localBuf[bufIdx + 1] = -0x54;
            bufIdx += 2;
        }
        else if(*p == 0x62){
            localBuf[bufIdx] = -0x3E;
            localBuf[bufIdx + 1] = -0x56;
            bufIdx += 2;
        }
        else if(*p == 0x30){
            localBuf[bufIdx] = -0x3E;
            localBuf[bufIdx + 1] = -0x55;
            bufIdx += 2;
        }
        else {
            localBuf[bufIdx] = *p;
            bufIdx += 1;
        }
    }
    bool ret = false;
    localBuf[bufIdx] = 0;
    if(strlen(buffer) + strlen(localBuf) >= bufferLen - 1) return false;
    else {
        strcat(buffer, localBuf);
        if(i4++ + 1 < i3 || i3 == -1) ret = true;
    }
    return ret;
}

void RGParseOverrideChord(char* buf, int bufLen, const char* cc){
    int x = 0;
    gSuperscriptStarted = false;
    *buf = 0;
    AddChordLevel(buf, bufLen, 3, x, cc, false);
}

bool RGContainsNote(unsigned char uc, const GameGem& gem){
    unsigned char* tunedPtr = gTunedNotes;
    for(unsigned int i = 0; i < 6; i++){
        char fret = gem.GetFret(i);
        if(0 <= fret && ((*tunedPtr + fret) % 0xC & 0xFFU) == uc) return true;
        tunedPtr++;
    }
    return false;
}

void RGStringContainsNote(unsigned char uc, const GameGem& gem, unsigned char& ucRef){
    ucRef = 0;
    unsigned char* tunedPtr = gTunedNotes;
    for(unsigned int i = 0; i < 6; i++){
        char fret = gem.GetFret(i);
        if(0 <= fret && ((*tunedPtr + fret) % 0xC & 0xFFU) == uc){
            ucRef |= 1 << i;
        }
        tunedPtr++;
    }
}