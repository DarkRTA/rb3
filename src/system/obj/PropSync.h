#ifndef OBJ_PROPSYNC_H
#define OBJ_PROPSYNC_H
#include "Object.h"
#include "vector2.hpp"
#include "vector3.hpp"
#include "sphere.hpp"
#include "transform.hpp"
#include "Mtx.h"
#include "Color.h"
#include "FilePath.h"
#include "Rect.h"
#include "box.hpp"
#include "Symbol.h"

bool PropSync(String&, DataNode&, DataArray*, int, PropOp);
bool PropSync(FilePath&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Color&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Matrix3&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Sphere&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector2&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Vector3&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Transform&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Hmx::Rect&, DataNode&, DataArray*, int, PropOp);
bool PropSync(Box&, DataNode&, DataArray*, int, PropOp);

bool PropSync(int& iref, DataNode& node, DataArray* da, int i, PropOp op){
    da->Size();
    if(op == (PropOp)1) node = DataNode(iref);
    else iref = node.Int(0);
    return true;
}

bool PropSync(float& f, DataNode& node, DataArray* da, int i, PropOp op){
    da->Size();
    if(op == (PropOp)1) node = DataNode(f);
    else f = node.Float(0);
    return true;
}

bool PropSync(bool& b, DataNode& node, DataArray* da, int i, PropOp op){
    da->Size();
    if(op == (PropOp)1) node = DataNode(b);
    else b = node.Int(0) != 0;
    return true;
}

bool PropSync(Symbol& sym, DataNode& node, DataArray* da, int i, PropOp op){
    da->Size();
    if(op == (PropOp)1) node = DataNode(sym);
    else sym = node.Str(0);
    return true;
}

#endif
