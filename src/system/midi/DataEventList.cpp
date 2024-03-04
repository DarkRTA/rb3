#include "midi/DataEvent.h"

DataEventList::DataEventList() : mCurIndex(0), mSize(0), mElement(-1), mCompType(kDataUnhandled), mValue(0) {
    
}
