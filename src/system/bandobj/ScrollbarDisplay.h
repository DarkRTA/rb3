#pragma once
#include "bandobj/BandList.h"
#include "ui/UIComponent.h"
#include "rndobj/Mesh.h"
#include "rndobj/Group.h"

class ScrollbarDisplay : public UIComponent {
public:
    ScrollbarDisplay();
    OBJ_CLASSNAME(ScrollbarDisplay);
    OBJ_SET_TYPE(ScrollbarDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~ScrollbarDisplay();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();

    BandList* GetList() const { return m_pList.Ptr() ? m_pList.Ptr() : 0; }
    bool GetAlwaysShow() const { return mAlwaysShow; }
    float GetListXOffset() const { return mListXOffset; }
    float GetListYOffset() const { return mListYOffset; }
    float GetHeight() const { return mScrollbarHeight; }
    float GetMinThumbHeight() const { return mMinThumbHeight; }
    float GetSavedPosition() const { return m_fSavedPosition; }
    float GetSavedScale() const { return m_fSavedScale; }
    void SetList(BandList*);
    void SetAlwaysShow(bool);
    void SetListAttached(bool);
    bool GetListAttached() const;
    void SetListXOffset(float);
    void SetListYOffset(float);
    void SetHeight(float);
    void SetMinThumbHeight(float);
    void UpdateThumbScaleAndPosition();
    void UpdateSavedListInfo();
    float GetListHeight() const;
    void UpdateScrollbarHeightAndPosition();

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(ScrollbarDisplay);
    }
    NEW_OBJ(ScrollbarDisplay);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<BandList, ObjectDir> m_pList; // 0x10c
    float mScrollbarHeight; // 0x118
    bool mAlwaysShow; // 0x11c
    float mListXOffset; // 0x120
    float mListYOffset; // 0x124
    float mMinThumbHeight; // 0x128
    RndMesh* m_pTopBone; // 0x12c
    RndMesh* m_pBottomBone; // 0x130
    RndMesh* m_pThumbTopBone; // 0x134
    RndMesh* m_pThumbBottomBone; // 0x138
    RndGroup* m_pThumbGroup; // 0x13c
    int unk140; // 0x140
    int unk144; // 0x144
    int unk148; // 0x148
    int unk14c; // 0x14c
    float m_fSavedPosition; // 0x150
    float m_fSavedScale; // 0x154
};