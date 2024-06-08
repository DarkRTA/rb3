#include "Gem.h"
#include "beatmatch/RGUtl.h"

Gem::Gem(const GameGem& gg, unsigned int ui, float f1, float f2, bool b1, int i1, int i2, bool b2) : 
    unk_0x4(&gg), unk_0x20(f1), unk_0x24(f2), unk_0x28(0), unk_0x2C(ui), unk_0x38(i1), unk_0x3C(0), 
    unk_0x40(0), unk_0x44(0), unk_0x48(0), unk_0x4C(""), unk_0x60(-1), unk_0x64(0), unk_0x65(-1) {
    InitChordInfo(i2, b2);
}

Gem::~Gem() { }

Gem& Gem::operator=(const Gem& g) {
    (GameGem&)(*unk_0x4) = *(g.unk_0x4);
    unk_0x2C = g.unk_0x2C;
    unk_0x30 = g.unk_0x30;
    unk_0x8 = g.unk_0x8;
}

bool Gem::OnScreen(float) {

}



void Gem::Miss() { }

void Gem::Hit() {
    for (int i = 0; i < unk_0x30.size(); i++) unk_0x30[i]->Hit();
    unk_0x66_5 = false;
    RemoveAllInstances();
    unk_0x66_0 = true;
}

void Gem::Release() {
    for (int i = 0; i < unk_0x30.size(); i++) unk_0x30[i]->Release();
    unk_0x66_2 = true;
}

void Gem::Reset() {
    unk_0x28 = 0;
    unk_0x38 = -1;
}

float Gem::GetStart() const {
    if (unk_0x66_5);
    else return unk_0x20;
}

void Gem::SetFretPos(int i) {
    unk_0x64 = i;
}

void Gem::GetChordFretLabelInfo(String& s, int& i) const {
    s = RGFretNumberToString(unk_0x5C);
    i = unk_0x60;
}
