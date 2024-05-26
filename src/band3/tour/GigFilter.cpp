#include "GigFilter.h"

GigFilter::GigFilter() {
    mName = Symbol(" ");
}

GigFilter::~GigFilter() {

}

void GigFilter::Init(const DataArray*) {

}

Symbol GigFilter::GetName() const {
    return mName;
}

bool GigFilter::IsInternal() const {
    return mIsInternal;
}

void GigFilter::GetFilter() const {

}

void GigFilter::GetFilteredPartSym() const {

}

// void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, int, Symbol) const {}

void GigFilter::GetWeight() const {

}