#ifndef UTL_SONGINFOAUDIOTYPE_H
#define UTL_SONGINFOAUDIOTYPE_H
#include "utl/Symbol.h"

enum SongInfoAudioType {
    kAudioTypeDrum,
    kAudioTypeGuitar,
    kAudioTypeBass,
    kAudioTypeVocals,
    kAudioTypeKeys,
    kAudioTypeUnknown,
    kAudioTypeMulti
};

SongInfoAudioType SymbolToAudioType(Symbol);

#endif
