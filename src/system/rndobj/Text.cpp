#include "Text.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Font.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"

//static std::set<RndText*> RndText::mTextMeshSet;

INIT_REVS(RndText)

void RndText::Init() {
    RegisterFactory(StaticClassName(), NewObject);
}

void RndText::Save(BinStream&) { MILO_ASSERT(0, 171); }
void RndText::Load(BinStream& bs) {
    int dump;
    LOAD_REVS(bs)
    ASSERT_REVS(21, 0)
    if (gRev > 15) Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    if (gRev < 7) {
        ObjPtrList<Hmx::Object, class ObjectDir> dir(this, kObjListNoNull);
        bs >> dump;
        bs >> dir;
    }

    UpdateText(true);
}

void RndText::UpdateText(bool) {
    if (mDeferUpdate) {
        unk9p2 = true;
        return;
    }
}

void RndText::SetSize(float f) {
    if (mSize == f) return;
    mSize = f;
    UpdateText(true);
}

BEGIN_COPYS(RndText)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndTransformable)
    if (ty == kCopyFromMax) return;
    GET_COPY(RndText)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mFont)
    END_COPY_CHECKED
    UpdateText(true);
END_COPYS

void RndText::Print() {
    TheDebug << "   font: " << mFont << "\n";
}

RndText::RndText() : mFont(this, NULL), mWrapWidth(0), unk_c8(1), unk_e0(this, NULL) {}

RndText::~RndText() {
    MILO_ASSERT(mDeferUpdate == 0, 723);
}

void RndText::SetFont(RndFont* f) {
    mFont = f;
    UpdateText(true);
}

void RndText::ReserveLines(int i) { mLines.reserve(i); }

class String RndText::TextASCII() const {
    class String s;
    s.resize(UTF8StrLen(unk_cc.c_str()) + 1);
    UTF8toASCIIs(s.mStr, s.mCap, unk_cc.c_str(), '*');
    return s;
}

void RndText::SetTextASCII(const char*) {
    class String s;
    
}

BEGIN_HANDLERS(RndText)
    HANDLE(set_fixed_length, OnSetFixedLength)
    HANDLE(set_font, OnSetFont)
    HANDLE(set_align, OnSetAlign)
    HANDLE(set_text, OnSetText)
    HANDLE(set_size, OnSetSize)
    HANDLE(set_wrap_width, OnSetWrapWidth)
    HANDLE(set_color, OnSetColor)

    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(2789)
END_HANDLERS