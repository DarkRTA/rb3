#include "ui/UIGuide.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(UIGuide);

UIGuide::UIGuide() : mType(kGuideVertical), mPos(0.5f) {
    
}

UIGuide::~UIGuide(){
    
}

SAVE_OBJ(UIGuide, 0x21);

void UIGuide::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> (int&)mType >> mPos;
}

BEGIN_COPYS(UIGuide)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(UIGuide)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mType)
        COPY_MEMBER(mPos)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_PROPSYNCS(UIGuide);
    SYNC_PROP(pos, mPos);
    SYNC_PROP(type, (int&)mType);
END_PROPSYNCS;

BEGIN_HANDLERS(UIGuide);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x47);
END_HANDLERS;
