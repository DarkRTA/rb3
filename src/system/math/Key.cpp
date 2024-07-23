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

// fn_802E35A8 - InterpTangent(const Vector3&, const Vector3&, const Vector3&, const Vector3&, float, Vector3&)
// i absolutely hate inlines
void InterpTangent(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float f, Vector3& vout){
    float scale = f * f;
    Scale(v1, scale * 6.0f - f * 6.0f, vout);
    Vector3 vtmp;
    Scale(v2, -(f * 4.0f - scale * 3.0f) + 1.0f, vtmp);
    Add(vout, vtmp, vout);
    Scale(v3, scale * -6.0f + f * 6.0f, vtmp);
    Add(vout, vtmp, vout);
    Scale(v4, -(f * 2.0f - f * 3.0f), vtmp);
    Add(vout, vtmp, vout);
}

// fn_802E36D4 - InterpVector(const Keys<Vector3, Vector3>&, const Key<Vector3>*, const Key<Vector3>*, float, bool, Vector3&, Vector3*)
// https://decomp.me/scratch/PHQ02 - retail
void InterpVector(const Keys<Vector3, Vector3>& keys, const Key<Vector3>* key1, const Key<Vector3>* key2, float f, bool b, Vector3& vref, Vector3* vptr){
    if(keys.size() < 3){
        b = false;
        if(keys.size() < 2){
            if(vptr) vptr->Set(0.0f,1.0f,0.0f);
            if(keys.size() != 0) vref = key1->value;
            else vref.Set(0,0,0);
            return;
        }
    }
}