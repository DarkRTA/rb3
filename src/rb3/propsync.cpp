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

bool PropSync(Hmx::Matrix3& mtx, DataNode& node, DataArray* da, int i, PropOp op){

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