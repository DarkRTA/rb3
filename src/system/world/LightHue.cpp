#include "world/LightHue.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"

INIT_REVS(LightHue)

LightHue::LightHue() : mLoader(0), mPath(), mKeys() {

}

LightHue::~LightHue(){
    delete mLoader;
}

BEGIN_COPYS(LightHue)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(LightHue)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPath)
        COPY_MEMBER(mKeys)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(LightHue, 0x27)

BEGIN_LOADS(LightHue)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void LightHue::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mPath;
    if(bs.Cached()){
        bs >> mKeys;
    }
    else if(!mPath.empty()){
        mLoader = new FileLoader(mPath, mPath.c_str(), kLoadFront, 0, false, true, 0);
    }
}

void LightHue::PostLoad(BinStream& bs){
    if(!bs.Cached()) Sync();
}

void LightHue::TranslateColor(const Hmx::Color& col, Hmx::Color& res){
    if(!mKeys.empty()){
        float maxcol = Max(1.0f, Max(col.red, col.green, col.blue));
        Hmx::Color col30;
        Multiply(col, 1.0f / maxcol, col30);
        float h, s, l;
        MakeHSL(col30, h, s, l);
        Vector3 vec;
        mKeys.AtFrame(h, vec);
        float clamped = Clamp(0.0f, 1.0f, l * vec.z * 2.0f);
        MakeColor(vec.x, s * vec.y, clamped, res);
        Multiply(res, maxcol, res);
    }
    else res = col;
}

BEGIN_HANDLERS(LightHue)
    HANDLE(save_default, OnSaveDefault)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x97)
END_HANDLERS

BEGIN_PROPSYNCS(LightHue)
    SYNC_PROP_MODIFY_ALT(path, mPath, Sync())
END_PROPSYNCS