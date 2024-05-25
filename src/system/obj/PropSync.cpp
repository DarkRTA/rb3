#include "obj/PropSync_p.h"
#include "math/Rot.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

bool PropSync(class String& str, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && (op & (kPropSet|kPropGet|kPropInsert)), 0x12);
    if(op == kPropGet) node = DataNode(str.c_str());
    else str = node.Str(0);
    return true;
}

bool PropSync(FilePath& fp, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && (op & (kPropSet|kPropGet|kPropInsert)), 0x1C);
    if(op == kPropGet) node = DataNode(fp.FilePathRelativeToRoot());
    else fp.SetRoot(node.Str(0));
    return true;
}

bool PropSync(Hmx::Color& color, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && (op & (kPropSet|kPropGet|kPropInsert)), 0x26);
    if(op == kPropGet) node = DataNode((int)color.Pack());
    else color.Unpack(node.Int(0));
    return true;
}

#pragma push
#pragma pool_data off
bool PropSync(Hmx::Matrix3& mtx, DataNode& node, DataArray* _prop, int _i, PropOp _op){
    MILO_ASSERT(_i == _prop->Size() - 1 && (_op & (kPropSet|kPropGet|kPropInsert)), 0x45);
    Symbol sym = _prop->Sym(_i);
    Vector3 rotation, scale;
    bool result = false;
    {
        static Symbol _s("pitch");
        if(sym == _s){
            MakeEulerScale(mtx, rotation, scale);
            Scale(rotation, 57.295776f, rotation);
            result = PropSync(rotation.x, node, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("roll");
        if(sym == _s){
            MakeEulerScale(mtx, rotation, scale);
            Scale(rotation, 57.295776f, rotation);
            result = PropSync(rotation.y, node, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("yaw");
        if(sym == _s){
            MakeEulerScale(mtx, rotation, scale);
            Scale(rotation, 57.295776f, rotation);
            result = PropSync(rotation.z, node, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("x_scale");
        if(sym == _s){
            MakeEulerScale(mtx, rotation, scale);
            Scale(rotation, 57.295776f, rotation);
            result = PropSync(scale.x, node, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("y_scale");
        if(sym == _s){
            MakeEulerScale(mtx, rotation, scale);
            Scale(rotation, 57.295776f, rotation);
            result = PropSync(scale.y, node, _prop, _i + 1, _op);
        }
    }
    {
        static Symbol _s("z_scale");
        if(sym == _s){
            MakeEulerScale(mtx, rotation, scale);
            Scale(rotation, 57.295776f, rotation);
            result = PropSync(scale.z, node, _prop, _i + 1, _op);
        }
    }
    if (result && _op != kPropGet) {
        Scale(rotation, 0.0174532923847f, rotation);
        MakeRotMatrix(rotation, mtx, true);
        Scale(scale, mtx, mtx);
    }
    return result;
}
#pragma pop

bool PropSync(class Sphere& sphere, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == x){
            return PropSync(sphere.center.x, node, prop, i + 1, op);
        }
        if(sym == y){
            return PropSync(sphere.center.y, node, prop, i + 1, op);
        }
        if(sym == z){
            return PropSync(sphere.center.z, node, prop, i + 1, op);
        }
        if(sym == radius){
            return PropSync(sphere.radius, node, prop, i + 1, op);
        }
        return false;
    }
}

bool PropSync(Vector2& vec, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == x){
            return PropSync(vec.x, node, prop, i + 1, op);
        }
        if(sym == y){
            return PropSync(vec.y, node, prop, i + 1, op);
        }
        return false;
    }
}

bool PropSync(Vector3& vec, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == x){
            return PropSync(vec.x, node, prop, i + 1, op);
        }
        if(sym == y){
            return PropSync(vec.y, node, prop, i + 1, op);
        }
        if(sym == z){
            return PropSync(vec.z, node, prop, i + 1, op);
        }
        return false;
    }
}

bool PropSync(Transform& tf, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == x){
            return PropSync(tf.v.x, node, prop, i + 1, op);
        }
        if(sym == y){
            return PropSync(tf.v.y, node, prop, i + 1, op);
        }
        if(sym == z){
            return PropSync(tf.v.z, node, prop, i + 1, op);
        }
        else return PropSync(tf.m, node, prop, i, op);
    }
    return true;
}

bool PropSync(Hmx::Rect& rect, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == x){
            return PropSync(rect.x, node, prop, i + 1, op);
        }
        if(sym == y){
            return PropSync(rect.y, node, prop, i + 1, op);
        }
        if(sym == w){
            return PropSync(rect.w, node, prop, i + 1, op);
        }
        if(sym == h){
            return PropSync(rect.h, node, prop, i + 1, op);
        }
    }
    return false;
}

bool PropSync(Box& box, DataNode& node, DataArray* prop, int i, PropOp op){
    if(i == prop->Size()) return true;
    else {
        Symbol sym = prop->Sym(i);
        if(sym == min_x){
            return PropSync(box.mMin.x, node, prop, i + 1, op);
        }
        if(sym == max_x){
            return PropSync(box.mMax.x, node, prop, i + 1, op);
        }
        if(sym == min_y){
            return PropSync(box.mMin.y, node, prop, i + 1, op);
        }
        if(sym == max_y){
            return PropSync(box.mMax.y, node, prop, i + 1, op);
        }
        if(sym == min_z){
            return PropSync(box.mMin.z, node, prop, i + 1, op);
        }
        if(sym == max_z){
            return PropSync(box.mMax.z, node, prop, i + 1, op);
        }
    }
    return false;
}
