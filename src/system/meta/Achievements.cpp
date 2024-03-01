#include "Achievements.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "utl/Symbols4.h"

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

BEGIN_HANDLERS(Achievements);
    HANDLE_ACTION(set_allow_achievements, SetAllowAchievements(_msg->Int(2) != 0));
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x74);
END_HANDLERS;
