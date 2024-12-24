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
            unsigned char tunedNote = (gTunedNotes[i] + fret) % 12;
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
            unsigned char tunedNote = (gTunedNotes[i] + fret) % 12;
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
            unsigned char tunedNote = (gTunedNotes[i] + gem.GetFret(i)) % 12;
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
    if(noteToAddLevelTo == (root + 7) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "5", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 1) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(b2)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 2) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(2)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 5) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(4)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 6) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(b5)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 8) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(b6)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 9) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(6)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 10) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(b7)", false);
        return true;
    }
    else if(noteToAddLevelTo == (root + 11) % 12){
        AddChordLevel(buf, bufLen, i4, iRef, "(7)", false);
        return true;
    }
    else return false;
}

void HandleNoThird(char* buf, int bufLen, const GameGem& gem, int i4, int& iRef){
    unsigned char root = gem.GetRootNote();
    if(RGContainsNote((root + 10) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "7", false)) return;
    }
    else if(RGContainsNote((root + 11) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "M7", false)) return;
    }

    bool has9th = RGContainsNote((root + 9) % 12, gem);
    bool has5th = RGContainsNote((root + 5) % 12, gem);
    bool has4th = RGContainsNote((root + 4) % 12, gem);
    bool has3rd = RGContainsNote((root + 3) % 12, gem);

    if(has9th && has5th && !has4th && !has3rd){
        AddChordLevel(buf, bufLen, i4, iRef, "sus4/6", true);
        return;
    }
        if(has9th){
        if (!AddChordLevel(buf, bufLen, i4, iRef, "sus6", true)) {
            return;
        }
    }
    else if(has5th){
        if (!AddChordLevel(buf, bufLen, i4, iRef, "sus4", true)) {
            return;
        }
    }
    else if(RGContainsNote((root + 6) % 12, gem)){
        if (!AddChordLevel(buf, bufLen, i4, iRef, "sus#4", true)) {
            return;
        }
    }
    else if(RGContainsNote((root + 2) % 12, gem)){
        if (!AddChordLevel(buf, bufLen, i4, iRef, "sus2", true)) {
            return;
        }
    }
    else if(RGContainsNote((root + 1) % 12, gem)){
        if (!AddChordLevel(buf, bufLen, i4, iRef, "susb2", true)) {
            return;
        }
    }
    HandleSlashChords(buf, bufLen, gem, i4, iRef);
}

void HandleNoSeventh(char* buf, int bufLen, const GameGem& gem, int i4, int& iRef){
    unsigned char root = gem.GetRootNote();
    if(RGContainsNote((root + 6) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "#4", true)) return;
    }
    else if(RGContainsNote((root + 8) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "+", true)) return;
    }

    if(RGContainsNote((root + 3) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "#9", true)) return;
    }

    if(RGContainsNote((root + 1) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "b2", true)) return;
    }
    else if(RGContainsNote((root + 2) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "2", true)) return;
    }

    if(
        (!RGContainsNote((root + 5) % 12, gem) || AddChordLevel(buf, bufLen, i4, iRef, "4", true)) &&
        (!RGContainsNote((root + 9) % 12, gem) || AddChordLevel(buf, bufLen, i4, iRef, "6", true))
    ){
        HandleSlashChords(buf,bufLen,gem,i4,iRef);
    }
}

void HandleNoSeventhMinor(char* buf, int bufLen, const GameGem& gem, int i4, int& iRef){
    unsigned char root = gem.GetRootNote();
    bool has6th = RGContainsNote((root + 6) % 12, gem);
    if(!has6th && !AddChordLevel(buf, bufLen, i4, iRef, "m", false)) return;
    if(has6th && !AddChordLevel(buf, bufLen, i4, iRef, "0", true)) return;

    if(RGContainsNote((root + 8) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "#5", true)) return;
    }
    
    if(RGContainsNote((root + 1) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "b2", true)) return;
    }
    else if(RGContainsNote((root + 2) % 12, gem)){
        if(!AddChordLevel(buf, bufLen, i4, iRef, "2", true)) return;
    }

    if(
        (!RGContainsNote((root + 5) % 12, gem) || AddChordLevel(buf, bufLen, i4, iRef, "4", true)) &&
        (!RGContainsNote((root + 9) % 12, gem) || AddChordLevel(buf, bufLen, i4, iRef, "6", true))
    ){
        HandleSlashChords(buf,bufLen,gem,i4,iRef);
    }
}

void RGGetFretLabelInfo(const GameGem& gem, int& i1, int& i2, bool b){
    RGState state;
    RGGameGemToRGState(gem, state, b);
    RGGetFretLabelInfo(state, i1, i2);
}

void RGGetFretLabelInfo(const RGState& state, int& i1, int& i2){
    i2 = -1;
    i1 = -1;
    for(unsigned int i = 0; i < 6; i++){
        int fret = state.GetFret(i);
        if(fret < 0) continue;
        if(fret >= 0){
            if(fret == 0){
                if(i2 == -1){
                    i2 = 0;
                    i1 = i;
                }
            }
            else if(i2 <= 0 || fret < i2){
                i2 = fret;
                i1 = i;
            }
        }
    }
}

void RGGameGemToRGState(const GameGem& gem, RGState& state, bool b){
    for(unsigned int i = 0; i < 6; i++){
        int fret = gem.GetFret(i);
        if(!b && gem.GetRGNoteType(i) == 1) fret = -1;
        state.FretDown(i, fret);
    }
}

unsigned int RGGetChordShapeID(const GameGem& gem, bool b){
    MILO_ASSERT(gem.IsRealGuitarChord(), 0x296);
    int low = -1;
    int high = -1;
    int range = RGGetHeldFretRange(gem, low, high, 1);
    if(high - low > 5) MILO_WARN("Chord span is too large; truncating higher frets!");
    range = range != 0 ? 2 - low : 0;
    unsigned int mask = 0;
    for(unsigned int i = 0; i < 6; i++){
        int fret = gem.GetFret(i);
        if(!b && gem.GetRGNoteType(i) == 1) fret = -1;
        MILO_ASSERT(fret > -2, 0x2B4);
        fret = fret < 1 ? fret + 1 : Min(fret + range, 7);
        mask |= fret << (i * 4);
    }
    unsigned int strumMask = 0x3F;
    if(gem.GetRGStrumType() != kRGNoStrum){
        strumMask = RGGetStrumBitMask(gem);
    }
    return mask | strumMask << 0x18;
}

unsigned int RGGetStrumBitMask(const GameGem& gem){
    unsigned int mask = 0;
    int low = gem.GetLowestString();
    int high = gem.GetHighestString();
    float diff = (high - low) + 1;
    switch(gem.GetRGStrumType()){
        case kRGStrum:
            for(int i = 0; i < 6; i++){
                float prod = diff * 0.2f;
                float i_f = i;
                float highf = high - prod;
                float lowf = prod + low;
                if(i_f >= lowf && i_f <= highf){
                    mask |= (1 << i);
                }
            }
            break;
        case kRGStrumLow:
            for(int i = 0; i < 6; i++){
                if(i < diff * 0.4f - low){
                    mask |= (1 << i);
                }
            }
            break;
        case kRGStrumHigh:
            for(int i = 0; i < 6; i++){
                if(-(diff * 0.4f - high) < i){
                    mask |= (1 << i);
                }
            }
            break;
        default:
            mask = 0x3F;
            break;
    }
    return mask;
}

void RGUnpackChordShapeID(unsigned int ui, std::vector<int>& ivec, std::vector<bool>* bvec){
    ivec.clear();
    for(int i = 0; i < 6; i++){
        int push = ((ui >> i) & 0xF) - 1;
        ivec.push_back(push);
    }
    if(bvec){
        bvec->clear();
        for(int i = 0; i < 6; i++){
            bool push = (ui >> 0x18) >> i;
            bvec->push_back(push);
        }
    }
}

bool RGGetHeldFretRange(const GameGem& gem, int& i1, int& i2, bool b){
    RGState state;
    RGGameGemToRGState(gem, state, b);
    return RGGetHeldFretRange(state, i1, i2);
}

bool RGGetHeldFretRange(const RGState& state, int& i1, int& i2){
    i1 = 0x7FFFFFFF;
    i2 = 0x80000000;
    bool ret = false;
    for(unsigned int i = 0; i < 6; i++){
        int fret = state.GetFret(i);
        MILO_ASSERT(fret >= -1, 0x334);
        if(fret > 0){
            MinEq(i1, fret);
            MaxEq(i1, fret);
            ret = true;
        }
    }
    if(!ret){
        i1 = -1;
        i2 = -1;
    }
    return ret;
}

const char* RGFretNumberToString(int i){
    return MakeString("%c", i + 0x41);
}

const char* RGGetNoteName(unsigned char note, int){
    MILO_ASSERT(note < sizeof(gNoteNames), 0x34E);
}