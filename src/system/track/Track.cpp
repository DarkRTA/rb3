#include "track/TrackDir.h"
#include "track/TrackWidget.h"

void TrackInit() {
    TrackDir::Register();
    TrackWidget::Register();
}
