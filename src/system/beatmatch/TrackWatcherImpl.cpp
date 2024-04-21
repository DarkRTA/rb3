#include "beatmatch/TrackWatcherImpl.h"

TrackWatcherImpl::~TrackWatcherImpl(){
    EndAllSustainedNotes();
}