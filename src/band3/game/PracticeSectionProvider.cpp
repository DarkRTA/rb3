#include "game/PracticeSectionProvider.h"

PracticeSectionProvider::PracticeSectionProvider() : unk2c(0), unk30(0), unk34(0), unk38(0), unk3c(1), unk40(0), unk44(0), unk48(0) {
    SetName("practice_section_provider", ObjectDir::sMainDir);
    unk20.reserve(100);
}