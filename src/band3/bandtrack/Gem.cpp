#include "Gem.h"
#include "beatmatch/RGUtl.h"

Gem::Gem(const GameGem& gg, unsigned int ui, float f1, float f2, bool b1, int i1, int i2, bool b2) :
    mGameGem(&gg), mStart(f1), mEnd(f2), mTailStart(0), mSlots(ui), mBeardTick(i1), unk_0x3C(0),
    unk_0x40(0), unk_0x44(0), unk_0x48(0), unk_0x4C(""), mFirstFretString(-1), mFretPos(0), unk_0x65(-1) {
    InitChordInfo(i2, b2);
}

Gem::~Gem() { }

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
