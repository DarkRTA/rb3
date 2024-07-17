#include "math/Key.h"
#include "math/Vec.h"

// fn_802E33CC - SplineTangent(const Keys<Vector3, Vector3>&, int, Vector3&)
// https://decomp.me/scratch/uaX0T - retail
// https://decomp.me/scratch/g4W1K - debug (i hate inlining)
void SplineTangent(const Keys<Vector3, Vector3>& keys, int i, Vector3& vout){
    int size = keys.size();
    MILO_ASSERT(size > 1, 0x17);
    if(size == 2){
        Subtract(keys[1].value, keys[0].value, vout);
    }
    else if(i <= 0){
        Subtract(keys[1].value, keys[0].value, vout);
        Scale(vout, 1.5f, vout);
        Vector3 vtmp;
        Subtract(keys[2].value, keys[0].value, vtmp);
        Scale(vtmp, 0.25f, vtmp);
        Subtract(vout, vtmp, vout);
    }
    else if(i >= size - 1){
        Subtract(keys[size - 1].value, keys[size - 2].value, vout);
        Scale(vout, 1.5f, vout);
        Vector3 vtmp;
        Subtract(keys[size - 1].value, keys[size - 3].value, vtmp);
        Scale(vtmp, 0.25f, vtmp);
        Subtract(vout, vtmp, vout);        
    }
    else {
        Subtract(keys[i + 1].value, keys[i - 1].value, vout);
        Scale(vout, 0.5f, vout);
    }
}

// fn_802E36D4 - InterpVector(const Keys<Vector3, Vector3>&, const Key<Vector3>*, const Key<Vector3>*, float, bool, Vector3&, Vector3*)