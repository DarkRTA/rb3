#include "math/Vec.h"
#include <vector>

#pragma push
#pragma dont_inline on
std::vector<Vector3>& CharDeformDummyFunc(){
    Vector3 v(0,0,0);
    std::vector<Vector3> vecs;
    vecs.push_back(v);
    return vecs;
}
#pragma pop