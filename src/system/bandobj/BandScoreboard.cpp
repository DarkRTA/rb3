#include "bandobj/BandScoreboard.h"
#include "obj/ObjVersion.h"
#include "rndobj/PropAnim.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

INIT_REVS(BandScoreboard)

BandScoreboard::BandScoreboard() : mScore(-1), mThousandsCommaMesh(this, 0), mMillionsCommaMesh(this, 0), mNumMeshes(this), mSrcMeshes(this), mStarDisplay(this, 0) {

}

BandScoreboard::~BandScoreboard(){

}

void BandScoreboard::SetScore(int score){
    SetupScore();
    if(score >= 0 && score != mScore){
        mScore = score;
        mThousandsCommaMesh->SetShowing(score >= 1000);
        mMillionsCommaMesh->SetShowing(score >= 1000000);
        for(int i = 0; i < mNumMeshes.size(); i++){
            RndMesh* mesh = mNumMeshes[i];
            if(score == 0){
                if(i == 0){
                    mesh->SetGeomOwner(mSrcMeshes[0]);
                }
                else mesh->SetShowing(false);
            }
            else {
                int mod = score % 10;
                score /= 10;
                mesh->SetGeomOwner(mSrcMeshes[mod]);
                mesh->SetShowing(true);
            }
        }
    }
}

void BandScoreboard::SetNumStars(float f, bool b){
    if(mStarDisplay) mStarDisplay->SetNumStars(f, b);
}

float BandScoreboard::GetNumStars() const {
    if(mStarDisplay) return mStarDisplay->GetNumStars();
    else return 0;
}

void BandScoreboard::Reset(){
    ResetScore();
    if(mStarDisplay) mStarDisplay->Reset();
}

void BandScoreboard::SetupScore(){
    if(mNumMeshes.empty()){
        mSrcMeshes.clear();
        const char* separatorStr = Localize(locale_separator, 0);
        MILO_ASSERT(separatorStr, 0x6D);
        char localized = *separatorStr;
        float frame = 0;
        switch(localized){
            case ',': frame = 0;
                break;
            case '.': frame = 1.0f;
                break;
            case ' ':
            case -0x3E: frame = 2.0f;
                break;
            default:
                MILO_WARN("Unknown thousands separator in scoreboard: '%c'.", localized);
                break;
        }
        Find<RndPropAnim>("locale_config.anim", true)->SetFrame(frame, 1.0f);
        mThousandsCommaMesh = Find<RndMesh>("thousands_comma.mesh", true);
        mMillionsCommaMesh = Find<RndMesh>("millions_comma.mesh", true);
        for(int i = 0; i < 8; i++){
            const char* meshname = MakeString("num%d.mesh", i);
            mNumMeshes.push_back(ObjPtr<RndMesh, ObjectDir>(this, Find<RndMesh>(meshname, true)));
        }
        for(int i = 0; i < 10; i++){
            const char* meshname = MakeString("%d_source.mesh", i);
            mSrcMeshes.push_back(ObjPtr<RndMesh, ObjectDir>(this, Find<RndMesh>(meshname, true)));
        }
    }
}

void BandScoreboard::ResetScore(){
    mScore = -1;
    SetScore(0);
}

SAVE_OBJ(BandScoreboard, 0xA3)

BEGIN_COPYS(BandScoreboard)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(BandScoreboard)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax)
            COPY_MEMBER(mStarDisplay)
    END_COPYING_MEMBERS
END_COPYS

void BandScoreboard::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    if(gRev >= 1 && !IsProxy()) bs >> mStarDisplay;
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

void BandScoreboard::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
}

BEGIN_PROPSYNCS(BandScoreboard)
    SYNC_PROP_SET(score, mScore, SetScore(_val.Int()))
    SYNC_PROP_SET(num_stars, GetNumStars(), SetNumStars(_val.Float(), true))
    SYNC_PROP(star_display, mStarDisplay)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(BandScoreboard)
    HANDLE_ACTION(reset, Reset())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0xE0)
END_HANDLERS
