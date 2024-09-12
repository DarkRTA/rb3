#include "bandobj/BandSwatch.h"
#include "math/Rand.h"

ColorPalette* BandSwatch::sDummyPalette;

void BandSwatch::Init(){
    Register();
    sDummyPalette = Hmx::Object::New<ColorPalette>();
    if(TheLoadMgr.EditMode()){
        for(int i = 0; i < 10; i++){
            sDummyPalette->mColors.push_back(Hmx::Color(RandomFloat(), RandomFloat(), RandomFloat()));
        }
    }
}

void BandSwatch::Terminate(){
    RELEASE(sDummyPalette);
}

BandSwatch::BandSwatch() : unk1f0(this, 0) {
    MILO_ASSERT(sDummyPalette, 0x30);
}

BandSwatch::~BandSwatch(){
    
}