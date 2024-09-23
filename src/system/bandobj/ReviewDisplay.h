#pragma once
#include "ui/UIComponent.h"

class ReviewDisplay : public UIComponent {
public:
    ReviewDisplay();
    OBJ_CLASSNAME(ReviewDisplay);
    OBJ_SET_TYPE(ReviewDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~ReviewDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();
    virtual void UpdateDisplay(bool);

    void SetToToken(Symbol);
    void SetValues(int, bool);

    static Symbol GetSymbolForReviewScore(int);
    static int GetReviewScoreForSymbol(Symbol);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(ReviewDisplay);
    }
    NEW_OBJ(ReviewDisplay);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    RndAnimatable* mReviewAnim; // 0x10c
    RndAnimatable* mFocusAnim; // 0x110
    int mScore; // 0x114
};