#ifndef RB3_TRAININGMGR_HPP
#define RB3_TRAININGMGR_HPP
#include "hmx/object.hpp"

class TrainingMgr : public Hmx::Object {
public:
    TrainingMgr();
    virtual ~TrainingMgr();
    virtual DataNode Handle(DataArray*, bool);

    static TrainingMgr* NewObject();
    void SetMinimumDifficulty(int);
    void SetReturnInfo(Symbol, Symbol);
    void SetCurrentLesson(int);
    void ClearCurrentLesson();
    
    int user; // user, the type is LocalBandUser*
    int minDiff; // minimum difficulty
    Symbol retScreen; // return screen
    Symbol quitToken; // quit token
    int curLesson; // current lesson
};

#endif
