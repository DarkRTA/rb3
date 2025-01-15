#pragma once
#include "obj/Data.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Overlay.h"

class CharDebug : public RndOverlay::Callback {
public:
    CharDebug() : mObjects(nullptr), mOnce(nullptr) {}
    virtual ~CharDebug(){}
    virtual float UpdateOverlay(RndOverlay*, float);

    void Once(Hmx::Object* obj){
        if(obj){
            ObjPtrList<Hmx::Object>& onceList = mOnce;
            ObjPtrList<Hmx::Object>::iterator iter = onceList.find(obj);
            if(iter == onceList.end()){
                onceList.push_back(obj);
            }
            else {
                onceList.erase(iter);
            }
        }
        mOverlay->SetOverlay(!mObjects.empty() || !mOnce.empty());
    }

    void Init();
    void SetObjects(DataArray*);
    static DataNode OnSetObjects(DataArray*);

    ObjPtrList<Hmx::Object> mObjects; // 0x4
    ObjPtrList<Hmx::Object> mOnce; // 0x14
    RndOverlay* mOverlay; // 0x24
};

void CharDeferHighlight(Hmx::Object*);
void CharInit();
void CharTerminate();

extern float gCharHighlightY;
extern CharDebug TheCharDebug;