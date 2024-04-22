#include "TourProgress.h"
#include "obj/Object.h"
#include "utl/Symbols.h"

TourProgress::TourProgress() : mQuests(*this) {

}

TourProgress::~TourProgress() { }

BEGIN_HANDLERS(TourProgress)
    HANDLE_ACTION(set_on_tour, SetOnTour(_msg->Int(2)))
END_HANDLERS

int TourProgress::SecBetweenUploads() const { return 45; }