#pragma once
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "obj/Object.h"

class Lesson {
public:
    Lesson(Symbol, Symbol, Symbol, Symbol, TrackType);
    ~Lesson();
    Difficulty GetDifficulty() const;

    Symbol unk0;
    Symbol unk4;
    Symbol unk8;
    Symbol unkc;
    TrackType unk10;
};

class LessonMgr : public Hmx::Object {
public:
    LessonMgr();
    virtual ~LessonMgr();

    Lesson* GetLesson(Symbol) const;
    TrackType GetTrackTypeFromTrainer(Symbol);

    static void Init();
    static LessonMgr* GetLessonMgr();

    std::vector<Symbol> mTrainers; // 0x1c
    std::map<Symbol, std::vector<Symbol>*> mTrainerToCategoriesMap; // 0x24
    std::map<Symbol, std::vector<Symbol>*> mCategoryToLessonsMap; // 0x3c
    std::map<Symbol, Lesson*> mLessonsMap; // 0x54
};