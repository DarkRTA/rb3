#include "GraphicsUtl.h"
#include "rndobj/Trans.h"
#include "rndobj/Group.h"
#include "rndobj/Utl.h"

void UnhookGroupParents(Hmx::Object* obj) {
    do {
        RndGroup* g = GroupOwner(obj);
        if (g == NULL) break;
        g->RemoveObject(obj);
    } while (true);
}

void UnhookAllParents(Hmx::Object* obj) {
    UnhookGroupParents(obj);
    RndTransformable* trans = dynamic_cast<RndTransformable*>(obj);
    if (trans) trans->SetTransParent(NULL, false);
}
