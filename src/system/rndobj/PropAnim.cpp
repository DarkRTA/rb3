#include "rndobj/PropAnim.h"
#include "utl/STLHelpers.h"

RndPropAnim::RndPropAnim() : mLastFrame(0.0f), mInSetFrame(0), mLoop(0) {

}

RndPropAnim::~RndPropAnim(){
    RemoveKeys();
}

SAVE_OBJ(RndPropAnim, 0x43);

PropKeys* RndPropAnim::AddKeys(Hmx::Object* o, DataArray* da, PropKeys::AnimKeysType ty){
    PropKeys* theKeys = GetKeys(o, da);
    if(theKeys){
        switch(ty){
            case PropKeys::kFloat:
                theKeys = new FloatKeys(this, o);
                break;
            case PropKeys::kColor:
                theKeys = new ColorKeys(this, o);
                break;
            case PropKeys::kObject:
                theKeys = new ObjectKeys(this, o);
                break;
            case PropKeys::kBool:
                theKeys = new BoolKeys(this, o);
                break;
            case PropKeys::kQuat:
                theKeys = new QuatKeys(this, o);
                break;
            case PropKeys::kVector3:
                theKeys = new Vector3Keys(this, o);
                break;
            case PropKeys::kSymbol:
                theKeys = new SymbolKeys(this, o);
                break;
            default:
                MILO_WARN("Unable to create animation for keysType");
                return 0;
        }
        if(da){
            DataNode node(da, kDataArray);
            theKeys->SetProp(node);
        }
        mPropKeys.push_back(theKeys);
    }
    return theKeys;
}

void RndPropAnim::RemoveKeys(){
    DeleteRange(mPropKeys.begin(), mPropKeys.end());
    mPropKeys.clear();
}
