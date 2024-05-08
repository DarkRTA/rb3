#include "Track.h"
#include "obj/Object.h"

void TrackInit() {
    Hmx::Object::RegisterFactory(TrackDir::StaticClassName(), TrackDir::NewObject);
    Hmx::Object::RegisterFactory(TrackWidget::StaticClassName(), TrackWidget::NewObject);
}