#include "bandobj/BandSwatch.h"
#include "math/Rand.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

ColorPalette* BandSwatch::sDummyPalette;

void BandSwatch::Init(){
    TheUI->InitResources("BandSwatch");
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

BandSwatch::BandSwatch() : mColorPalette(this, 0) {
    MILO_ASSERT(sDummyPalette, 0x30);
}

BandSwatch::~BandSwatch(){
    
}

BEGIN_HANDLERS(BandSwatch)
    HANDLE_ACTION(set_colors, SetColors(_msg->Obj<ColorPalette>(2)))
    HANDLE_SUPERCLASS(UIList)
    HANDLE_CHECK(0x94)
END_HANDLERS

BEGIN_PROPSYNCS(BandSwatch)
    SYNC_PROP_MODIFY_ALT(color_palette, mColorPalette, UpdateColors())
    SYNC_SUPERCLASS(UIList)
END_PROPSYNCS