#include "propsync.hpp"
#include "symbols.hpp"

bool PropSync(String& str, DataNode& node, DataArray* da, int i, PropOp op){
    da->GetNodeCount();
    if(op == (PropOp)1) node = DataNode(str.c_str());
    else str = node.Str(0);
    return true;
}

bool PropSync(Hmx::Color& color, DataNode& node, DataArray* da, int i, PropOp op){
    da->GetNodeCount();
    if(op == (PropOp)1) node = DataNode((int)color.Pack());
    else color.Unpack(node.Int(0));
    return true;
}

extern void MakeEulerScale(const Hmx::Matrix3&, Vector3&, Vector3&);
extern void Scale(const Vector3&, float, Vector3&);

bool PropSync(Hmx::Matrix3& mtx, DataNode& node, DataArray* da, int i, PropOp op){
    Vector3 vec1;
    Vector3 vec2;

    da->GetNodeCount();
    Symbol sym = da->GetSymAtIndex(i);
    static Symbol SymPitch("pitch");
    if(sym == SymPitch){
        MakeEulerScale(mtx, vec1, vec2);
        Scale(vec1, 57.295776f, vec2);
        return PropSync(mtx.row1, node, da, i, op);
    }
    static Symbol SymRoll("roll");
    if(sym == SymRoll){
        MakeEulerScale(mtx, vec1, vec2);
        Scale(vec1, 57.295776f, vec2);
        return PropSync(mtx.row2, node, da, i, op);
    }
    static Symbol SymYaw("yaw");
    if(sym == SymYaw){
        MakeEulerScale(mtx, vec1, vec2);
        Scale(vec1, 57.295776f, vec2);
        return PropSync(mtx.row3, node, da, i, op);
    }
    static Symbol SymXScale("x_scale");
    if(sym == SymXScale){
        MakeEulerScale(mtx, vec1, vec2);
        Scale(vec1, 57.295776f, vec2);
        return PropSync(mtx.row1, node, da, i, op);
    }
    static Symbol SymYScale("y_scale");
    if(sym == SymYScale){
        MakeEulerScale(mtx, vec1, vec2);
        Scale(vec1, 57.295776f, vec2);
        return PropSync(mtx.row2, node, da, i, op);
    }
    static Symbol SymZScale("z_scale");
    if(sym == SymZScale){
        MakeEulerScale(mtx, vec1, vec2);
        Scale(vec1, 57.295776f, vec2);
        return PropSync(mtx.row3, node, da, i, op);
    }
}

bool PropSync(Sphere& sphere, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(sphere.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(sphere.y, node, da, i + 1, op);
        }
        if(sym == SymZ){
            return PropSync(sphere.z, node, da, i + 1, op);
        }
        if(sym == SymRadius){
            return PropSync(sphere.radius, node, da, i + 1, op);
        }
        else return false;
    }
    return true;
}

bool PropSync(Vector2& vec, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(vec.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(vec.y, node, da, i + 1, op);
        }
        else return false;
    }
    return true;
}

bool PropSync(Vector3& vec, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(vec.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(vec.y, node, da, i + 1, op);
        }
        if(sym == SymZ){
            return PropSync(vec.z, node, da, i + 1, op);
        }
        else return false;
    }
    return true;
}

bool PropSync(Transform& tf, DataNode& node, DataArray* da, int i, PropOp op){
    int cnt = da->GetNodeCount();
    if(i == cnt) return true;
    else {
        Symbol sym = da->GetSymAtIndex(i);
        if(sym == SymX){
            return PropSync(tf.trans.x, node, da, i + 1, op);
        }
        if(sym == SymY){
            return PropSync(tf.trans.y, node, da, i + 1, op);
        }
        if(sym == SymZ){
            return PropSync(tf.trans.z, node, da, i + 1, op);
        }
        else return PropSync(tf.rot, node, da, i, op);
    }
    return true;
}