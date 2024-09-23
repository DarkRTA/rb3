#ifndef BANDTRACK_GEMMANAGER_H
#define BANDTRACK_GEMMANAGER_H

#include "utl/Symbol.h"
#include "system/track/TrackDir.h"
#include "TrackConfig.h"

class GemManager {
    public:
    bool GetChordWidgetName(class Symbol, class Symbol, class Symbol&);

    bool GetWidgetName(class Symbol &, int, class Symbol);

    TrackWidget *GetWidgetByName(Symbol);

    int GetMaxSlots() const;

    TrackDir *mTrackDir;
    TrackConfig *mTrackConfig;
};

#endif // BANDTRACK_GEMMANAGER_H
