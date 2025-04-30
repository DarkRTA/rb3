#pragma once
#include "obj/Data.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Overlay.h"

class CharDebug : public RndOverlay::Callback {
public:
    CharDebug() : mObjects(nullptr), mOnce(nullptr) {}
    virtual ~CharDebug() {}
    virtual float UpdateOverlay(RndOverlay *, float);

    void Once(Hmx::Object *obj) {
        if (obj) {
            ObjPtrList<Hmx::Object> &onceList = mOnce;
            ObjPtrList<Hmx::Object>::iterator iter = onceList.find(obj);
            if (iter == onceList.end()) {
                onceList.push_back(obj);
            } else {
                onceList.erase(iter);
            }
        }
        mOverlay->SetShowing(!mObjects.empty() || !mOnce.empty());
    }

    void Init();
    void SetObjects(DataArray *msg) {
        int obj_node = 1;
        int cmp2;
        int siz = msg->Size();
        int x = siz ^ 1;
        int y = x >> 1;
        uint cmp = uint(y - (x & siz)) >> 31;
        if (cmp) {
            cmp = CONST_ARRAY(msg)->Node(1).Type() == kDataSymbol;
        }
        if (cmp) {
            cmp = msg->Sym(1) == "clear";
            if (!cmp) {
                cmp = msg->Sym(1) == "once";
            }
        }
        if (cmp) {
            obj_node = 2;
            cmp2 = msg->Sym(1) == "clear";
            cmp = msg->Sym(1) == "once";
        }
        if (cmp2) {
            mOnce.clear();
        }
        while (obj_node < msg->Size()) {
            mOnce.push_back(msg->GetObj(obj_node));
            obj_node++;
        }

        bool show = !mObjects.empty() || !mOnce.empty();
        RndOverlay *ovl = mOverlay;
        ovl->mShowing = show;
        ovl->mTimer.Restart();
    }
    static DataNode OnSetObjects(DataArray *);

    ObjPtrList<Hmx::Object> mObjects; // 0x4
    ObjPtrList<Hmx::Object> mOnce; // 0x14
    RndOverlay *mOverlay; // 0x24
};

void CharDeferHighlight(Hmx::Object *);
void CharInit();
void CharTerminate();

extern float gCharHighlightY;
extern CharDebug TheCharDebug;