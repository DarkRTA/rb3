#include "Scoring.h"
#include "os/System.h"
#include "os/Debug.h"

Scoring* TheScoring;

OverdriveConfig::OverdriveConfig(DataArray* cfg){
    rechargeRate = cfg->FindFloat("recharge_rate");
    starPhrase = cfg->FindFloat("star_phrase");
    commonPhrase = cfg->FindFloat("common_phrase");
    fillBoost = cfg->FindFloat("fill_boost");
    whammyRate = cfg->FindFloat("whammy_rate");
    readyLevel = cfg->FindFloat("ready_level");
    multiplier = cfg->FindInt("multiplier");
    crowdBoost = cfg->FindFloat("crowd_boost");
    MILO_ASSERT(( 0) <= (rechargeRate) && (rechargeRate) <= ( 1), 0x22);
    MILO_ASSERT(( 0) <= (starPhrase) && (starPhrase) <= ( 1), 0x23);
    MILO_ASSERT(( 0) <= (readyLevel) && (readyLevel) <= ( 1), 0x24);
}

Scoring::Scoring() : unk8c(SystemConfig("scoring")), unk90(unk8c->FindArray("overdrive", true)), unkc0(0) {
    MILO_ASSERT(!TheScoring, 0x2C);
    TheScoring = this;

    unk8c->FindArray("points", true);
    DataArray* streakarr = unk8c->FindArray("streaks", true);
    DataArray* multarr = streakarr->FindArray("multipliers", true);
    DataArray* energyarr = streakarr->FindArray("energy", true);

    unkb0 = unk8c->FindArray("unison_phrase", true)->FindFloat("reward");
    unkb4 = unk8c->FindArray("unison_phrase", true)->FindFloat("penalty");
    InitializeStreakList(unk78, multarr);
    InitializeStreakList(unk80, energyarr);

    DataArray* pointarr = unk8c->FindArray("streaks", true);
    for(int i = 1; i < pointarr->Size(); i++){
        int idx = SymToTrackType(pointarr->Array(i)->Sym(0));
        int head = pointarr->Array(i)->FindInt("head");
        int tail = pointarr->Array(i)->FindInt("tail");
        int chord = pointarr->Array(i)->FindInt("chord");
        PointInfo& info = mPointInfo[idx];
        info.headPoints = head;
        info.tailPoints = tail;
        info.chordPoints = chord;
    }
}

Scoring::~Scoring(){
    MILO_ASSERT(TheScoring, 0x48);
    TheScoring = 0;
}

int Scoring::GetHeadPoints(TrackType instrument) const {
    MILO_ASSERT(instrument < kNumTrackTypes, 0xCA);
    return mPointInfo[instrument].headPoints;
}

int Scoring::GetTailPoints(TrackType instrument, int i) const {
    MILO_ASSERT(instrument < kNumTrackTypes, 0xD0);
    float f = ((float)i / 480.0f) * (float)mPointInfo[instrument].tailPoints;
    if(f > 0) return f + 0.5f;
    else return f - 0.5f;
}

int Scoring::GetChordPoints(TrackType instrument) const {
    MILO_ASSERT(instrument < kNumTrackTypes, 0xD7);
    return mPointInfo[instrument].chordPoints;
}

int Scoring::GetStreakMult(int i, Symbol s) const {
    return GetStreakData(i, s, unk78);
}

DataArray* Scoring::GetCrowdConfig(Difficulty diff, BandUser* user) const {
    DataArray* diffarr = unk8c->FindArray("crowd", true)->FindArray(diff, true);
    Symbol key = user ? user->GetTrackSym() : "default";
    DataArray* ret = diffarr->FindArray(key, false);
    if(ret) return ret;
    else return diffarr->FindArray("default", true);
}

int Scoring::GetBandNumStars(int i) const {
    int stars = GetNumStarsFloat(i, mStarThresholds);
    if(stars < 0) return 0;
    else if(stars > 6) return 6;
    else return stars;
}

float Scoring::GetBandNumStarsFloat(int i) const {
    return GetNumStarsFloat(i, mStarThresholds);
}

int Scoring::GetBandScoreForStars(int stars) const {
    MILO_ASSERT(stars < mStarThresholds.size(), 0x18A);
    return mStarThresholds[stars];
}

Symbol Scoring::GetStarRating(int numStars) const {
    if(numStars == 0) return gNullStr;
    else {
        DataArray* ratings = unk8c->FindArray("star_ratings", "symbols")->Array(1);
        MILO_ASSERT(( 1) <= (numStars) && (numStars) <= ( ratings->Size()), 0x1BE);
        return ratings->Sym(numStars - 1);
    }
}

void Scoring::GetSoloAward(int i, Symbol s, int& iref, Symbol& sref){
    DataArray* soloblock = GetSoloBlock(s);
    DataArray* awardarr = soloblock->FindArray("awards", true);
    for(int idx = awardarr->Size() - 1; idx >= 1; idx--){
        DataArray* arr = awardarr->Array(idx);
        if(i >= arr->Int(0)){
            iref = arr->Int(1);
            sref = arr->Sym(2);
            return;
        }
    }
    MILO_FAIL("no solo award for %s: %i%%", s, i);
}

DataArray* Scoring::GetSoloBlock(Symbol s) const {
    DataArray* soloarr = unk8c->FindArray("solo", true);
    DataArray* blockarr = soloarr->FindArray(s, false);
    return blockarr ? blockarr : soloarr->FindArray("default", true);
}

float Scoring::GetSoloGemReward(Symbol s){
    return GetSoloBlock(s)->FindFloat("reward");
}

float Scoring::GetSoloGemPenalty(Symbol s){
    return GetSoloBlock(s)->FindFloat("penalty");
}

void Scoring::PrintStarThresholds() const {}