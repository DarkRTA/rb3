#include "math/Key.h"
#include "math/Vec.h"
#include "os/Debug.h"

// matches in retail with the right inline settings: https://decomp.me/scratch/xQcyC
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

// regswaps in retail with the right inline settings: https://decomp.me/scratch/lOd4o
// i absolutely hate inlines
void InterpTangent(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float f, Vector3& vout){
    float ftimes6;
    float scale3;
    float scale;
    ftimes6 = f * 6.0f;
    scale = f * f;
    Scale(v1, (scale * 6.0f) - ftimes6, vout);
    Vector3 vtmp;
    scale3 = scale * 3.0f;
    Scale(v2, 1.0f + (scale3 - (f * 4.0f)), vtmp);
    Add(vout, vtmp, vout);
    Scale(v3, (scale * -6.0f) + ftimes6, vtmp);
    Add(vout, vtmp, vout);
    Scale(v4, (scale3 - (f * 2.0f)), vtmp);
    Add(vout, vtmp, vout);
}

// fn_802E36D4 - InterpVector(const Keys<Vector3, Vector3>&, const Key<Vector3>*, const Key<Vector3>*, float, bool, Vector3&, Vector3*)
// https://decomp.me/scratch/hblrn - retail
void InterpVector(const Keys<Vector3, Vector3>& keys, const Key<Vector3>* prev, const Key<Vector3>* next, float ref, bool b, Vector3& vref, Vector3* vptr){
    if(keys.size() < 3){
        b = false;
        if(keys.size() < 2){
            if(vptr) vptr->Set(0.0f,1.0f,0.0f);
            if(keys.size() != 0) vref = prev->value;
            else vref.Set(0,0,0);
            return;
        }
    }
    int idx = prev - keys.begin();
    if(b){
        float fsq = ref * ref;
        float fcubed = fsq * ref;
        float fsq3 = fsq * 3.0f;
        Scale(prev->value, (fcubed * 2.0f - fsq3) + 1.0f, vref);
        Vector3 v70;
        SplineTangent(keys, idx, v70);
        Vector3 v7c;
        Vector3 v88;
        Scale(v70, ref + -(fsq * 2.0f - fcubed), v88);
        Add(vref, v88, vref);
        Scale(next->value, fcubed * -2.0f + fsq3, v88);
        Add(vref, v88, vref);
        SplineTangent(keys, idx + 1, v7c);
        Scale(v7c, fcubed - fsq, v88);
        Add(vref, v88, vref);
        if(vptr){
            InterpTangent(prev->value, v70, next->value, v7c, ref, *vptr);
        }        
    }
    else {
        Interp(prev->value, next->value, ref, vref);
        if(vptr){
            if(idx == keys.size() - 1){
                idx--;
            }
            Subtract(keys[idx+1].value, keys[idx].value, *vptr);
        }        
    }
}

void InterpVector(const Keys<Vector3, Vector3>& keys, bool b, float frame, Vector3& vref, Vector3* vptr){
    const Key<Vector3>* prev;
    const Key<Vector3>* next;
    float ref;
    keys.AtFrame(frame, prev, next, ref);
    InterpVector(keys, prev, next, ref, b, vref, vptr);
}

void QuatSpline(const Keys<Hmx::Quat, Hmx::Quat>& keys, const Key<Hmx::Quat>* prev, const Key<Hmx::Quat>* next, float ref, Hmx::Quat& qout){
    MILO_ASSERT(keys.size(), 0x9B);
    if(prev == next){
        qout = prev->value;
    }
}