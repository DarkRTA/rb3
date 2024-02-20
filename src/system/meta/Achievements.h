#ifndef META_ACHIEVEMENTS_H
#define META_ACHIEVEMENTS_H

#include "obj/Object.h"

class LocalUser;

class Achievements : public Hmx::Object {
public:
    int unk_1c;
    bool mAllowAchievements;

    Achievements();
    virtual ~Achievements();

    virtual DataNode Handle(DataArray*, bool);

    void Poll();
    void Terminate();

    void Submit(LocalUser*, Symbol, int);

    void SetAllowAchievements(bool);

    static void Init();
};

Achievements* TheAchievements;

#endif // META_ACHIEVEMENTS_H
