#include "beatmatch/RGUtl.h"
#include "os/Debug.h"
#include <string.h>
#include <stdio.h>

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
const char** gCurrNoteNames;

void RGSetTuning(const std::vector<int>& vec){
    unsigned char* stringPtr = gStringNotes;
    unsigned char* tunedPtr = gTunedNotes;
    for(int i = 0; i < vec.size(); i++){
        int note = vec[i] + *stringPtr;
        MILO_ASSERT_RANGE(note, 0, 256, 0x45);
        *tunedPtr = note;
        stringPtr++;
        tunedPtr++;
    }
}

unsigned char RGGetTuning(int string){
    MILO_ASSERT_RANGE(string, 0, 6, 0x4C);
    return gTunedNotes[string];
}

bool AddChordLevel(char* buffer, int bufferLen, int i3, int& i4, const char* cc, bool bbb){
    char localBuf[256];
    int bufIdx = 0;
    if(bbb && !gSuperscriptStarted){
        const char* start = "<gtr>";
        MILO_ASSERT(strlen(buffer) + strlen(start) < bufferLen - 1, 0x5B);
        strcat(buffer, start);
        gSuperscriptStarted = true;
    }
    else if(!bbb && gSuperscriptStarted){
        const char* end = "</gtr>";
        MILO_ASSERT(strlen(buffer) + strlen(end) < bufferLen - 1, 0x62);
        strcat(buffer, end);
        gSuperscriptStarted = false;
    }
    for(char* p = (char*)cc; *p != 0; p++){
        if(*p == '#'){
            localBuf[bufIdx++] = -0x3E;
            localBuf[bufIdx++] = -0x54;
        }
        else if(*p == 'b'){
            localBuf[bufIdx++] = -0x3E;
            localBuf[bufIdx++] = -0x56;
        }
        else if(*p == '0'){
            localBuf[bufIdx++] = -0x3E;
            localBuf[bufIdx++] = -0x55;
        }
        else {
            localBuf[bufIdx++] = *p;
        }
    }
    bool ret = false;
    localBuf[bufIdx] = '\0';
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
    for(unsigned int i = 0; i < 6; i++){
        char fret = gem.GetFret(i);
        if(0 <= fret){
            unsigned char tunedNote = (gTunedNotes[i] + fret) % 0xC;
            if(tunedNote == uc) return true;
        }
    }
    return false;
}

void RGStringContainsNote(unsigned char uc, const GameGem& gem, unsigned char& ucRef){
    ucRef = 0;
    for(unsigned int i = 0; i < 6; i++){
        char fret = gem.GetFret(i);
        if(0 <= fret){
            unsigned char tunedNote = (gTunedNotes[i] + fret) % 0xC;
            if(tunedNote == uc) ucRef |= 1 << i;
        }
    }
}

void HandleSlashChords(char* buf, int bufLen, const GameGem& gem, int i4, int& iRef){
    char localbuf[16];
    if(gem.GetShowSlashes()){
        int slashIdx = gSlashNote;
        if(slashIdx != gem.GetRootNote()){
            sprintf(localbuf, "/%s", gCurrNoteNames[slashIdx]);
            if (AddChordLevel(buf, bufLen, i4, iRef, localbuf, false)) {
                return;
            }
        }
    }
}

bool HandleInterval(char* buf, int bufLen, const GameGem& gem, int i4, int& iRef){
    unsigned char root = gem.GetRootNote();
    unsigned char noteToAddLevelTo = -1;
    for(unsigned int i = 0; i < 6; i++){
        if(gem.GetFret(i) >= 0){
            unsigned char tunedNote = (gTunedNotes[i] + gem.GetFret(i)) % 0xC;
            if(tunedNote != root){
                if(noteToAddLevelTo == 0xFF){
                    noteToAddLevelTo = tunedNote;
                }
                else if(noteToAddLevelTo != tunedNote){
                    return false;
                }
            }
        }
    }    
    if(noteToAddLevelTo == (root + 7) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "5", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 1) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(b2)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 2) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(2)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 5) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(4)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 6) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(b5)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 8) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(b6)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 9) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(6)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 10) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(b7)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 11) % 0xC){
        AddChordLevel(buf, bufLen, i4, iRef, "(7)", false);
        return true;
    }
    else return false;
}