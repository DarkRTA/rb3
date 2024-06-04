#include "ui/UIGuide.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short UIGuide::gRev = 0;
unsigned short UIGuide::gAltRev = 0;

UIGuide::UIGuide() : mType(0), mPos(0.5f) {
    
}

UIGuide::~UIGuide(){
    
}

SAVE_OBJ(UIGuide, 0x21);

void UIGuide::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> mType >> mPos;
}

BEGIN_COPYS(UIGuide)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(UIGuide, c)
    if(c){
        COPY_MEM(c, mType)
        COPY_MEM(c, mPos)
    }
END_COPYS

BEGIN_PROPSYNCS(UIGuide);
    SYNC_PROP(pos, mPos);
    SYNC_PROP(type, mType);
END_PROPSYNCS;

BEGIN_HANDLERS(UIGuide);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x47);
END_HANDLERS;
