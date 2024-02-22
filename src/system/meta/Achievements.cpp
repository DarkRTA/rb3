#include "Achievements.h"
#include "obj/Dir.h"

void Achievements::Init() {
    TheAchievements = new Achievements;
    TheAchievements->SetName("achievements", ObjectDir::sMainDir);
}

void Achievements::Poll() {return;}

void Achievements::Terminate() {
    delete TheAchievements;
    TheAchievements = 0;
}

Achievements::~Achievements() {}

Achievements::Achievements() : unk_1c(0), mAllowAchievements(true) {}

void Achievements::Submit(LocalUser* l, Symbol s, int i) {return;}

void Achievements::SetAllowAchievements(bool b) {mAllowAchievements = b;}

DataNode Achievements::Handle(DataArray*, bool) {

}
