#include "bandobj/BandButton.h"
#include "obj/Dir.h"

BandButton *TabInterfacePanelDeadStripped() {
    return ObjectDir::Main()->Find<BandButton>("lol", true);
}