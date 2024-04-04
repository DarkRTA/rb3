// #include "Utl.h"
#include "math/Color.h"
#include "math/Geo.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include <cmath>

RndEnviron* FindEnviron(RndDrawable*) {

}

void CalcBox(RndMesh* m, Box& b) {
    m->mOwner->mOwner;
    m->mOwner->mOwner;
    m->mOwner->mOwner;
}

void SortXfms(RndMultiMesh*, const Vector3&) {
    MILO_ASSERT(0, 3150);
}

void RandomXfms(RndMultiMesh*) {
    MILO_ASSERT(0, 3173);
}

void MoveXfms(RndMultiMesh* mm, const Vector3& v) {
    for (std::list<Transform>::iterator i = mm->mTransforms.begin(); i != mm->mTransforms.end(); i++) {
        i->v.x += v.x;
        i->v.y += v.y;
        i->v.z += v.z;
    }

}

const char* CacheResource(const char*, Hmx::Object*);

FileLoader* ResourceFactory(const FilePath& f, LoaderPos p) {
    return new FileLoader(f, CacheResource(f.c_str(), NULL), p, 0, false, true, NULL);
}


DataNode DataFindEnviron(DataArray* da) {
    return DataNode(FindEnviron(da->Obj<RndDrawable>(1)));
}

float ConvertFov(float a, float b) {
    float x = tan(a / 2);
    return atan(b * x) * 2;
}

void PreMultiplyAlpha(Hmx::Color& c) {
    c.red *= c.alpha;
    c.green *= c.alpha;
    c.blue *= c.alpha;
}
