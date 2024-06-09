#include "Gem.h"
#include "beatmatch/RGUtl.h"
#include "os/Debug.h"

Gem::Gem(const GameGem& gg, unsigned int ui, float f1, float f2, bool b1, int i1, int i2, bool b2) :
    mGameGem(&gg), mStart(f1), mEnd(f2), mTailStart(0), mSlots(ui), mBeardTick(i1), unk_0x3C(0),
    unk_0x40(0), unk_0x44(0), unk_0x48(0), unk_0x4C(""), mFirstFretString(-1), mFretPos(0), unk_0x65(-1) {
    InitChordInfo(i2, b2);
}

Gem::~Gem() { mTails.clear(); }

Gem& Gem::operator=(const Gem& g) {
    (GameGem&)(*mGameGem) = *(g.mGameGem);
    mSlots = g.mSlots;

    mStart = g.mStart;
    mTailStart = g.mTailStart;
    mEnd = g.mEnd;

    mHopo = g.mHopo;
    mMissed = g.mMissed;
    mHit = g.mHit;
    mReleased = g.mReleased;
    mInvisible = g.mInvisible;

    mTails = g.mTails;
    mWidgets = g.mWidgets;
}

bool Gem::OnScreen(float) {

}

bool Gem::UseRGChordStyle() const {
    bool r = false;
    if (mGameGem->IsRealGuitarChord() || unk_0x67_1 || mGameGem->IsMuted()) r = true;
    return r;
}

void Gem::AddStrumInstance(Symbol s1, Symbol s2) {
    if (mGemManager == NULL || mGemManager->unk_0x0 == 0) return;
    int lowString = mGameGem->GetLowestString();
    int highString = mGameGem->GetHighestString();
    MILO_ASSERT(lowString != -1, 572);
    MILO_ASSERT(highString != -1, 573);
    Symbol t0;
    if (!mGemManager->GetChordWidgetName(s1, s2, t0)) {
        MILO_WARN("could not find widget for %s for %s chord gem in %s", t0, s1, s2);
        return;
    } 
}

void Gem::Miss() { }

void Gem::Hit() {
    for (int i = 0; i < mTails.size(); i++) mTails[i]->Hit();
    mBeard = false;
    RemoveAllInstances();
    mHit = true;
}

void Gem::Release() {
    for (int i = 0; i < mTails.size(); i++) mTails[i]->Release();
    mReleased = true;
}

void Gem::KillDuration() {
    for (int i = 0; i < mTails.size(); i++) mTails[i]->Done();
}

void Gem::Reset() {
    mHit = false;
    mMissed = false;
    mReleased = false;
    mTailStart = 0.0;
    mBeard = false;
    mBeardTick = -1;
}

float Gem::GetStart() const {
    if (mBeard);
    else return mStart;
}

void Gem::SetFretPos(int i) {
    mFretPos = i;
}

void Gem::GetChordFretLabelInfo(String& s, int& i) const {
    s = RGFretNumberToString(mFirstFret);
    i = mFirstFretString;
}
