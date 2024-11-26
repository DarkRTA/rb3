#pragma once
#include "math/Color.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Trans.h"
#include "rndobj/Font.h"
#include <float.h>
#include <set>

class RndText : public RndDrawable, public RndTransformable {
public:
    class Style {
    public:
        Style(RndFont* f, float sz, float ital, const Hmx::Color32& col, float z) : 
            font(f), size(sz), italics(ital), color(col), brk(true), pre(false), zOffset(z) {}

        RndFont* font; // 0x0
        float size; // 0x4
        float italics; // 0x8
        Hmx::Color32 color; // 0xc
        bool brk; // 0x10
        bool pre; // 0x11
        float zOffset; // 0x14
    };

    enum Alignment {
        kTopLeft =      0x11,
        kTopCenter =    0x12,
        kTopRight =     0x14,
        kMiddleLeft =   0x21,
        kMiddleCenter = 0x22,
        kMiddleRight =  0x24,
        kBottomLeft =   0x41,
        kBottomCenter = 0x42,
        kBottomRight =  0x44
    };

    enum CapsMode {
        kCapsModeNone = 0,
        kForceLower = 1,
        kForceUpper = 2,
    };

    // size 0x60
    class Line {
    public:
        Style mLineStyle; // 0x0
        const char* unk18;
        const char* unk1c;
        int unk20;
        int unk24;
        Transform unk28;
        float unk58;
        int unk5c;
    };

    class MeshInfo {
    public:
        MeshInfo() : unk0(0), unk4(0), displayableChars(0) {}
        RndMesh* unk0;
        int unk4;
        int displayableChars; // 0x8
    };

    RndText();
    OBJ_CLASSNAME(RndText)
    OBJ_SET_TYPE(RndText)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void Draw();
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight(){ RndDrawable::Highlight(); }
    virtual ~RndText();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual const char* FindPathName();
    virtual void Print();

    NEW_OBJ(RndText)

    float GetStringWidthUTF8(const char*, const char*, bool, Style*) const;
    void SyncMeshes();
    void ReserveLines(int);
    void UpdateText(bool);
    void SetFont(RndFont*);
    String TextASCII() const;
    void SetTextASCII(const char*);
    float Size() const { return mStyle.size; }
    void SetSize(float);
    void GetMeshes(std::vector<RndMesh*>&);
    void SetFixedLength(int);
    void GetCurrentStringDimensions(float&, float&);
    Alignment GetAlignment() const { return (Alignment)mAlign; }
    RndFont* GetFont() const { return mFont; }
    float MaxLineWidth() const;
    void SetMarkup(bool);
    void ResizeText(int);
    void SetText(const char*);
    void DeferUpdateText();
    void ResolveUpdateText();
    void SetWrapWidth(float);
    void SetItalics(float);
    void SetAltSizeAndZOffset(float, float);
    void SetAlignment(Alignment);
    void SetLeading(float);
    void SetColor(const Hmx::Color32&);
    void SetMeshForceNoQuantize();
    void SetMeshForceNoUpdate();
    void SetData(Alignment, const char*, RndFont*, float, float, float, float, const Hmx::Color32&, bool, CapsMode, int);
    void SetAltStyle(RndFont*, float, const Hmx::Color32*, float, float, bool);
    void WrapText(const char*, const Style&, std::vector<Line>&);
    void GetVerticalBounds(float&, float&) const;
    void GetStringDimensions(float&, float&, std::vector<Line>&, const char*, float);
    const char* ParseMarkup(const char*, RndText::Style*, float, float) const;
    float GetHorizontalAlignOffset(const RndText::Line&, RndText::Alignment) const;
    void RotateLineVerts(const RndText::Line&, RndMesh::Vert*, RndMesh::Vert*);
    RndFont* GetDefiningFont(unsigned short&, RndFont*) const;
    void UpdateMesh(RndFont*);
    void CreateLines(RndFont*);

    DataNode OnSetFixedLength(DataArray*);
    DataNode OnSetFont(DataArray*);
    DataNode OnSetAlign(DataArray*);
    DataNode OnSetText(DataArray*);
    DataNode OnSetSize(DataArray*);
    DataNode OnSetWrapWidth(DataArray*);
    DataNode OnSetColor(DataArray*);

    std::vector<Line> mLines; // 0xb0
    ObjOwnerPtr<RndFont, ObjectDir> mFont; // 0xb8
    float mWrapWidth; // 0xc4
    float mLeading; // 0xc8
    String mText; // 0xcc - either ASCII or UTF8 text
    Style mStyle; // 0xd8
    Style mAltStyle; // 0xf0
    std::map<unsigned int, MeshInfo> mMeshMap; // 0x108
    unsigned char mAlign; // 0x120
    unsigned char mCapsMode; // 0x121
    int mFixedLength : 16; // 0x122
    int mDeferUpdate : 4; // 0x124
    int unk124b4 : 3;
    int unk124b4p1 : 1; // ???
    int unk128; // 0x128 - actually a ptr to some class
    float unk12c; // 0x12c
    float unk130; // 0x130

    static void Init();
    static void Register(){ REGISTER_OBJ_FACTORY(RndText); }
    static void CollectGarbage();
    static void ResetFaces(RndMesh*, int);
    static std::set<RndText*> mTextMeshSet;

    DECLARE_REVS
};

class RndTextUpdateDeferrer {
public:
    RndTextUpdateDeferrer(RndText* text) : mText(text) {
        text->DeferUpdateText();
    }
    ~RndTextUpdateDeferrer(){
        mText->ResolveUpdateText();
    }

    RndText* mText; // 0x0
};