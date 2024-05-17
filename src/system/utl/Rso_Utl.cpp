#include "Rso_Utl.h"
#include "os/Debug.h"

#define MAX_RSO_INITERS 8

RsoInitFunc gRsoIniters[MAX_RSO_INITERS];
RsoDeinitFunc gRsoDeiniters[MAX_RSO_INITERS];
int gRsoIniterCount;

void RsoAddIniter(RsoInitFunc init, RsoDeinitFunc deinit) {
    MILO_ASSERT(gRsoIniterCount < MAX_RSO_INITERS, 84);
    if (gRsoIniterCount < 8) {
        gRsoIniters[gRsoIniterCount] = init;
        gRsoDeiniters[gRsoIniterCount] = deinit;
        gRsoIniterCount++;
    }
}