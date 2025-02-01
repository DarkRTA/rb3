#include "rndobj/Overlay.h"
#include "decomp.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Rnd.h"

bool RndOverlay::sTopAligned = true;
std::list<RndOverlay *> RndOverlay::sOverlays;

void RndOverlay::Init() {
    DataArray *cfg = SystemConfig("rnd");
    DataArray *overlaysArr = cfg->FindArray("overlays", true);
    for (int i = 1; i < overlaysArr->Size(); i++) {
        sOverlays.push_back(new RndOverlay(overlaysArr->Array(i)));
    }
}

void RndOverlay::Terminate() {
    for (std::list<RndOverlay *>::iterator i = sOverlays.begin(); i != sOverlays.end();
         i) {
        delete *i;
        i = sOverlays.erase(i);
    }
}

RndOverlay::~RndOverlay() {}

static float DrawOverlayLine(RndOverlay *o);

void RndOverlay::DrawAll(bool b) {
    float toUse = sTopAligned ? 0.0212f : 0.9788f;
    for (std::list<RndOverlay *>::const_iterator it = sOverlays.begin();
         it != sOverlays.end();
         ++it) {
        RndOverlay *cur = *it;
        if (!b || cur->mModal) {
            if (sTopAligned)
                toUse = cur->Draw(toUse);
            else if (cur->Showing()) {
                toUse -= DrawOverlayLine(cur);
                cur->Draw(toUse);
            }
        }
    }
}

static inline float DrawOverlayLine(RndOverlay *o) {
    unsigned int numlines = o->mLines.size();
    return TheRnd->DrawStringScreen("", Vector2(0, 0), o->mTextColor, true).y * numlines
        + 0.0268f;
}

void RndOverlay::TogglePosition() { sTopAligned = !sTopAligned; }

RndOverlay *RndOverlay::Find(Symbol s, bool fail) {
    for (std::list<RndOverlay *>::iterator it = sOverlays.begin(); it != sOverlays.end();
         it++) {
        if (s == (*it)->mName)
            return *it;
    }
    if (fail)
        MILO_FAIL("Could not find overlay \"%s\"", s);
    return 0;
}

RndOverlay::RndOverlay(const DataArray *da)
    : mShowing(0), mLines(), mLine(), mBackColor(0.0f, 0.0f, 0.0f, 0.2f), mTextColor(),
      mCursorChar(-1), mCallback(0), mTimer(), mTimeout(0.0f), mModal(0), mDumpCount(0) {
    mName = da->Str(0);
    int lines = 1;
    da->FindData("lines", lines, false);
    SetLines(lines);
    da->FindData("showing", mShowing, false);
    da->FindData("color", mBackColor, false);
    da->FindData("modal", mModal, false);
    da->FindData("text_color", mTextColor, false);
}

void RndOverlay::SetLines(int lines) {
    MILO_ASSERT(lines >= 1, 117);
    if (lines != mLines.size()) {
        mLines.resize(lines);
        mLine = mLines.begin();
    }
}

void RndOverlay::SetTimeout(float f) { mTimeout = f * 1000.0f + SystemMs(); }

String &RndOverlay::CurrentLine() {
    if (mLine == mLines.begin()) {
        String newstr;
        mLine = mLines.insert(mLines.erase(mLine), newstr);
        mLine->reserve(0x7F);
    }
    return *mLine;
}

void RndOverlay::Clear() {
    for (std::list<String>::iterator it = mLines.begin(); it != mLines.end(); ++it) {
        (*it).erase();
    }
    mLine = mLines.begin();
    mCursorChar = -1;
}

float RndOverlay::Draw(float) {
    if (mTimeout > 0 && mShowing) {
        if (SystemMs() > mTimeout) {
            mShowing = false;
            mTimeout = 0;
        }
    }
}

void RndOverlay::Print(const char *cc) {
    for (const char *p = cc; *p != '\0'; p++) {
        if (mLine == mLines.begin()) {
            String str;
        }
        char curChar = *p;
        if (curChar == '\n') {
            ++mLine;
        } else
            *mLine += curChar;
    }
}