#include "bandobj/BandSwatch.h"
#include "math/Rand.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

ColorPalette* BandSwatch::sDummyPalette;
INIT_REVS(BandSwatch);

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
    DeleteAll(unk1e8);
}

BEGIN_COPYS(BandSwatch)
    CREATE_COPY_AS(BandSwatch, s)
    MILO_ASSERT(s, 0x3D);
    COPY_MEMBER_FROM(s, mColorPalette)
    COPY_SUPERCLASS_FROM(UIList, s)
END_COPYS

SAVE_OBJ(BandSwatch, 0x48)

BEGIN_LOADS(BandSwatch)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandSwatch::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    if(gRev != 0) bs >> mColorPalette;
    UIList::PreLoad(bs);
}

RndMat* BandSwatch::Mat(int, int, UIListMesh*) const {
    return mResource->Dir()->Find<RndMat>("color.mat", true);
}

int BandSwatch::NumData() const { return unk1e8.size(); }

UIColor* BandSwatch::SlotColorOverride(int, int idx, UIListWidget*, UIColor* col) const {
    if(unk1e8.empty()) return col;
    else return unk1e8[idx];
}

void BandSwatch::SetColors(ColorPalette* palette){
    mColorPalette = palette;
}

void BandSwatch::UpdateColors(){
    DeleteAll(unk1e8);
    std::vector<Hmx::Color>& colors = mColorPalette.Ptr() ? mColorPalette->mColors : sDummyPalette->mColors;
    for(std::vector<Hmx::Color>::iterator it = colors.begin(); it != colors.end(); ++it){
        Hmx::Color hmxcol(*it);
        UIColor* newcol = Hmx::Object::New<UIColor>();
        newcol->SetColor(hmxcol);
        unk1e8.push_back(newcol);
    }
    Refresh(false);
}

void BandSwatch::Enter(){
    UIList::SetProvider(this);
    UpdateColors();
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