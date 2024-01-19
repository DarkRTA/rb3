#include "rndcam.hpp"
#include "rnddrawable.hpp"
extern "C" void fn_805D66F8(BinStream&);
extern "C" float fn_806598A0(float, float);

void RndCam::Save(BinStream& file) {
    return;
}

void RndCam::Load(BinStream& file) {
    uint ver;
    file >> ver;
    if (ver > 10) {
        Hmx::Object::Load(file);
    }
    RndTransformable::Load(file);
    if (ver < 10) {
        fn_805D66F8(file);
    }
    if (ver == 8) {
        //objptrlist stuff
        uint why;
        file >> why;
    }
    file >> a >> b >> c;
    if (ver < 12) {
        d = fn_806598A0(c, 0.75);
    }
    if (ver < 2) {
        uint empty;
        file >> empty;
    }

    if (ver < 3) {
        uint garbage;
        file >> garbage;
    }
    if (ver > 3) {

    }
    if (ver > 4) {

    }
    if (ver == 6) {
        uint asdf;
        file >> asdf;
    }
    fn_805CD500();
}

void RndCam::Copy(Hmx::Object* obj, CopyType type) {
    RndCam* from = dynamic_cast<RndCam*>(obj);
    if (from != nullptr && type != r) {
        screen_space_render = from->screen_space_render;
        huh = from->huh;
    }
    return;
}

RndCam::RndCam() /*: huh(0.0f, 1.0f)*/ {
    screen_space_render.Set(0.0f, 0.0f, 1.0f, 1.0f);

}

RndCam::~RndCam() {
    if (sCurrent == this) sCurrent = nullptr;
    delete target_tex;
}
/* TODO find the tu this comes from
RndCam* RndCam::fn_803F8F64() {
    Hmx::Object* obj = Hmx::Object::NewObject(StaticClassName());
    return dynamic_cast<RndCam*>(obj);
}
*/
