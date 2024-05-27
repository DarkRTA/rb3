#include "meta/FixedSizeSaveableStream.h"

static void idk(FixedSizeSaveableStream* s){
    s->FinishWrite();
    s->FinishStream();
}