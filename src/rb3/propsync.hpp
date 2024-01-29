#ifndef RB3_PROPSYNC_HPP
#define RB3_PROPSYNC_HPP
#include "hmx/object.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "sphere.hpp"

bool PropSync(String&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Sphere&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector2&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector3&, DataNode&, DataArray*, int, PropOp);

bool PropSync(float& f, DataNode& node, DataArray* da, int i, PropOp op){
    da->GetNodeCount();
    if(op == (PropOp)1) node = DataNode(f);
    else f = node.Float(0);
    return true;
}

#endif
