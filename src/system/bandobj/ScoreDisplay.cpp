#include "bandobj/ScoreDisplay.h"

ScoreDisplay::ScoreDisplay() : unk114(0), unk118(1000000), unk11c(0), unk120(0), unk124(this, 0) {
    unk110 = Hmx::Object::New<BandLabel>();
}

ScoreDisplay::~ScoreDisplay(){
    
}