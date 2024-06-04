#include "world/LightHue.h"
#include "utl/Loader.h"

INIT_REVS(LightHue)

LightHue::LightHue() : mLoader(0), mPath(), mKeys() {

}

LightHue::~LightHue(){

}

BEGIN_COPYS(LightHue)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(LightHue, c)
    if(c){
        COPY_MEM(c, mPath)
        COPY_MEM(c, mKeys)
    }
END_COPYS

SAVE_OBJ(LightHue, 0x27)

BEGIN_LOADS(LightHue)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void LightHue::PreLoad(BinStream& bs){
    char buf[0x100];
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs.ReadString(buf, 0x100);
    mPath.SetRoot(buf);
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