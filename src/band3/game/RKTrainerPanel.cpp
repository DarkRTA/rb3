#include "game/RKTrainerPanel.h"
#include "game/Defines.h"
#include "game/ProTrainerPanel.h"
#include "obj/ObjMacros.h"

RKTrainerPanel::RKTrainerPanel() {}

RKTrainerPanel::~RKTrainerPanel() {}

void RKTrainerPanel::SetSongSectionComplete(
    BandProfile *profile, int i1, Difficulty diff, int i2
) {
    for (int i = 0; i <= diff; i++) {
        profile->SetProKeyboardSongLessonSectionComplete(
            i1, (Difficulty)i, GetCurrSection()
        );
        if (AllSectionsFinished()) {
            profile->SetProKeyboardSongLessonComplete(i1, (Difficulty)i);
        }
    }
}

bool RKTrainerPanel::IsSongSectionComplete(
    BandProfile *profile, int i1, Difficulty diff, int i2
) {
    return profile->IsProKeyboardSongLessonSectionComplete(i1, diff, i2);
}

BEGIN_HANDLERS(RKTrainerPanel)
    HANDLE_SUPERCLASS(ProTrainerPanel)
    HANDLE_CHECK(0x2F)
END_HANDLERS