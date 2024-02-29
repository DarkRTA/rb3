#include "obj/PropSync_p.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

bool PropSync(class String& str, DataNode& node, DataArray* prop, int i, PropOp op){
    MILO_ASSERT(i == prop->Size() && (op & (kPropSet|kPropGet|kPropInsert)), 0x12);
    if(op == kPropGet) node = DataNode(str.c_str());
    else str = node.Str(0);
    return true;
}

// bool PropSync(FilePath& fp, DataNode& node, DataArray* da, int i, PropOp op){
//     da->Size();
//     if(op == (PropOp)1) node = DataNode(fp.FilePathRelativeToRoot());
//     else fp.SetRoot(node.Str(0));
//     return true;
// }

// bool PropSync(Hmx::Color& color, DataNode& node, DataArray* da, int i, PropOp op){
//     da->Size();
//     if(op == (PropOp)1) node = DataNode((int)color.Pack());
//     else color.Unpack(node.Int(0));
//     return true;
// }

// extern "C" int fn_80338AA8(int*);
// int fn_80338AA8(int* i){
//     return *i | 0xFF000000;
// }

// extern void Scale(const Vector3&, float, Vector3&);
// extern void Scale(const Vector3 &, const Hmx::Matrix3 &, Hmx::Matrix3 &);

// bool PropSync(Hmx::Matrix3& mtx, DataNode& node, DataArray* da, int i, PropOp op){
//     da->Size();
//     Symbol sym = da->Sym(i);
//     Vector3 rotation, scale;
//     bool result = false;

//     static Symbol SymPitch("pitch");
//     if(sym == SymPitch){
//         MakeEulerScale(mtx, rotation, scale);
//         Scale(rotation, 57.295776f, rotation);
//         result = PropSync(rotation.x, node, da, i + 1, op);
//     }
//     static Symbol SymRoll("roll");
//     if(sym == SymRoll){
//         MakeEulerScale(mtx, rotation, scale);
//         Scale(rotation, 57.295776f, rotation);
//         result = PropSync(rotation.y, node, da, i + 1, op);
//     }
//     static Symbol SymYaw("yaw");
//     if(sym == SymYaw){
//         MakeEulerScale(mtx, rotation, scale);
//         Scale(rotation, 57.295776f, rotation);
//         result = PropSync(rotation.z, node, da, i + 1, op);
//     }
//     static Symbol SymXScale("x_scale");
//     if(sym == SymXScale){
//         MakeEulerScale(mtx, rotation, scale);
//         Scale(rotation, 57.295776f, rotation);
//         result = PropSync(scale.x, node, da, i + 1, op);
//     }
//     static Symbol SymYScale("y_scale");
//     if(sym == SymYScale){
//         MakeEulerScale(mtx, rotation, scale);
//         Scale(rotation, 57.295776f, rotation);
//         result = PropSync(scale.y, node, da, i + 1, op);
//     }
//     static Symbol SymZScale("z_scale");
//     if(sym == SymZScale){
//         MakeEulerScale(mtx, rotation, scale);
//         Scale(rotation, 57.295776f, rotation);
//         result = PropSync(scale.z, node, da, i + 1, op);
//     }

//     if (result && op != 1) {
//         Scale(rotation, 0.0174532923847f, rotation);
//         MakeRotMatrix(rotation, mtx, true);
//         Scale(scale, mtx, mtx);
//     }

//     return result;
// }

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

// bool PropSync(Transform& tf, DataNode& node, DataArray* da, int i, PropOp op){
//     int cnt = da->Size();
//     if(i == cnt) return true;
//     else {
//         Symbol sym = da->Sym(i);
//         if(sym == SymX){
//             return PropSync(tf.trans.x, node, da, i + 1, op);
//         }
//         if(sym == SymY){
//             return PropSync(tf.trans.y, node, da, i + 1, op);
//         }
//         if(sym == SymZ){
//             return PropSync(tf.trans.z, node, da, i + 1, op);
//         }
//         else return PropSync(tf.rot, node, da, i, op);
//     }
//     return true;
// }

// bool PropSync(Hmx::Rect& rect, DataNode& node, DataArray* da, int i, PropOp op){
//     int cnt = da->Size();
//     if(i == cnt) return true;
//     else {
//         Symbol sym = da->Sym(i);
//         if(sym == SymX){
//             return PropSync(rect.x1, node, da, i + 1, op);
//         }
//         if(sym == SymY){
//             return PropSync(rect.y1, node, da, i + 1, op);
//         }
//         if(sym == SymW){
//             return PropSync(rect.x2, node, da, i + 1, op);
//         }
//         if(sym == SymH){
//             return PropSync(rect.y2, node, da, i + 1, op);
//         }
//     }
//     return false;
// }

// bool PropSync(Box& box, DataNode& node, DataArray* da, int i, PropOp op){
//     int cnt = da->Size();
//     if(i == cnt) return true;
//     else {
//         Symbol sym = da->Sym(i);
//         if(sym == SymMinX){
//             return PropSync(box.minX, node, da, i + 1, op);
//         }
//         if(sym == SymMaxX){
//             return PropSync(box.maxX, node, da, i + 1, op);
//         }
//         if(sym == SymMinY){
//             return PropSync(box.minY, node, da, i + 1, op);
//         }
//         if(sym == SymMaxY){
//             return PropSync(box.maxY, node, da, i + 1, op);
//         }
//         if(sym == SymMinZ){
//             return PropSync(box.minZ, node, da, i + 1, op);
//         }
//         if(sym == SymMaxZ){
//             return PropSync(box.maxZ, node, da, i + 1, op);
//         }
//     }
//     return false;
// }
