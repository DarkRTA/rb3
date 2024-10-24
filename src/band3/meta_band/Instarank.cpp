#include "meta_band/Instarank.h"
#include "Utl.h"
#include "game/Defines.h"
#include "os/Debug.h"
#include "ui/UILabel.h"
#include "utl/Locale.h"
#include "utl/STLHelpers.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <cstdlib>
#include <cstring>

Instarank::Instarank() : mIsValid(0), unk8(0), unkc(0), unk10(kScoreBand), unk14(0), unk18(0) {

}

void Instarank::Clear(){
    mIsValid = false;
    unk8 = 0;
    unkc = false;
    unk14 = 0;
    unk18 = false;
    unk1c = "";
    unk28 = "";
}

void Instarank::Init(int i1, bool b1, ScoreType ty, int i2, bool b2, String s1, String s2){
    mIsValid = true;
    unk8 = i1;
    unk10 = ty;
    unkc = b1;
    unk14 = i2;
    unk18 = b2;
    unk1c = s1;
    unk28 = s2;
}

void Instarank::UpdateRankLabel(UILabel* label){
    MILO_ASSERT(mIsValid, 0x3A);
    MILO_ASSERT(label, 0x3B);
    if(unk18){
        label->SetTokenFmt(instarank_percentile, unk14);
    }
    else {
        label->SetTokenFmt(instarank_rank, LocalizeSeparatedInt(unk14));
    }
}

bool Instarank::HasHighscore() const {
    MILO_ASSERT(mIsValid, 0x4B);
    char buf[0x100];
    strncpy(buf, unk1c.c_str(), 0xff);
    const char* tok = strtok(buf, "|");
    char tokc = *tok;
    return tokc == 'a' || tokc == 'b';
}

void Instarank::UpdateString1Label(UILabel* label){
    MILO_ASSERT(mIsValid, 0x58);
    MILO_ASSERT(label, 0x59);
    char buf[0x100];
    strncpy(buf, unk1c.c_str(), 0xff);
    const char* tok = strtok(buf, "|");
    char tokc = *tok;
    const char* fontc = GetFontCharFromScoreType(unk10, 0);
    switch(tokc){
        case 'a':
            label->SetTokenFmt(instarank_highscore_percentile, unk14, fontc);
            break;
        case 'b':
            label->SetTokenFmt(instarank_highscore_rank, LocalizeSeparatedInt(unk14), fontc);
            break;
        case 'c':
            label->SetTokenFmt(instarank_previousbest_rank, fontc, LocalizeSeparatedInt(atoi_s(strtok(0, "|"))), LocalizeSeparatedInt(1));
            break;
        case 'd':
            label->SetTokenFmt(instarank_rival_percentile, LocalizeSeparatedInt(atoi_s(strtok(0, "|"))), atoi_s(strtok(0, "|")), fontc);
            break;
        case 'e':
            label->SetTokenFmt(instarank_rival_rank, LocalizeSeparatedInt(atoi_s(strtok(0, "|"))), LocalizeSeparatedInt(atoi_s(strtok(0, "|"))), fontc);
            break;
        default:
            MILO_ASSERT(false, 0x8C);
            break;
    }
}