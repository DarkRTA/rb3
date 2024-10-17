#pragma once
#include "BandProfile.h"
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "obj/Object.h"

class Lesson {
public:
    Lesson(Symbol, Symbol, Symbol, Symbol, TrackType);
    ~Lesson();
    Difficulty GetDifficulty() const;

    Symbol mTrainer; // 0x0
    Symbol mCategory; // 0x4
    Symbol mName; // 0x8
    Symbol mSong; // 0xc
    TrackType mTrackType; // 0x10
};

class LessonMgr : public Hmx::Object {
public:
    LessonMgr();
    virtual ~LessonMgr();

    Lesson* GetLesson(Symbol) const;
    TrackType GetTrackTypeFromTrainer(Symbol);
    std::vector<Symbol>* GetLessonsFromCategory(Symbol) const;
    int GetCompletedCountFromTrainer(BandProfile*, Symbol);
    int GetTotalCountFromTrainer(Symbol);
    Difficulty GetDifficulty() const;

    static void Init();
    static LessonMgr* GetLessonMgr();

    std::vector<Symbol> mTrainers; // 0x1c
    std::map<Symbol, std::vector<Symbol>*> mTrainerToCategoriesMap; // 0x24
    std::map<Symbol, std::vector<Symbol>*> mCategoryToLessonsMap; // 0x3c
    std::map<Symbol, Lesson*> mLessonsMap; // 0x54
};