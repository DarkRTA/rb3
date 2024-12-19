#pragma once
#include "obj/Object.h"

class LocalUser;

/**
 * @brief Handles Achievements/Trophies.
 */
class Achievements : public Hmx::Object {
public:

    Achievements();
    virtual ~Achievements(){}
    virtual DataNode Handle(DataArray*, bool);

    void Poll();
    void Submit(LocalUser*, Symbol, int);
    void SetAllowAchievements(bool);

    int unk_1c; // if i had to guess, this would be a LocalUser*
    bool mAllowAchievements; // 0x20

    static void Init();
    static void Terminate();
};

extern Achievements* TheAchievements;
