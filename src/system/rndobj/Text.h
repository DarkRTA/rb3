#ifndef RNDOBJ_TEXT_H
#define RNDOBJ_TEXT_H

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
        Style()
            : font(0), size(0.0), italics(-1), unk_c(true), unk_d(false),
              color(0, 0, 0, 0), unk_28(0), unk_2c(FLT_MAX), brk(true), pre(true) {}

        // TrackWidget
        void *font;
        float size;
        float italics;

        bool unk_c;
        bool unk_d;

        Hmx::Color color;

        bool brk;
        bool pre;

        float zOffset;

        float unk_28;
        float unk_2c;
    };

    enum Alignment {
        kTopLeft = 17,
        kTopCenter = 18,
        kTopRight = 20,
        kMiddleLeft = 33,
        kMiddleCenter = 34,
        kMiddleRight = 36,
        kBottomLeft = 65,
        kBottomCenter = 66,
        kBottomRight = 68,
    };
    
    enum CapsMode {
        kCapsModeNone = 0,
        kForceLower = 1,
        kForceUpper = 2,
    };

    class Line {

    };

    class MeshInfo {

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
    void ReserveLines(int);
    void UpdateText(bool);
    void SetFont(RndFont*);
    String TextASCII() const; void SetTextASCII(const char*);
    float Size() const { return mSize; } void SetSize(float);
    void GetMeshes(std::vector<RndMesh*>&);
    void SetFixedLength(int);
    void GetCurrentStringDimensions(float&, float&);
    Alignment GetAlignment() const { return (Alignment)mAlign; }
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

    DataNode OnSetFixedLength(DataArray*);
    DataNode OnSetFont(DataArray*);
    DataNode OnSetAlign(DataArray*);
    DataNode OnSetText(DataArray*);
    DataNode OnSetSize(DataArray*);
    DataNode OnSetWrapWidth(DataArray*);
    DataNode OnSetColor(DataArray*);

    std::vector<Line, unsigned short> mLines; // 0xb0
    ObjOwnerPtr<RndFont, ObjectDir> mFont; // 0xb8
    float mWrapWidth; // 0xc4
    float mLeading; // 0xc8
    String unk_cc; // 0xcc - either ASCII or UTF8 text
    RndFont* unkd8; // 0xd8
    float mSize; // 0xdc
    float mItalicStrength; // 0xe0
    int mColor; // packed color? Hmx::Color32?
    bool unke8;
    bool unke9;
    float mZOffset;
    RndFont* unkf0;
    float mAltSize;
    float mAltItalicStrength;
    int mAltColor;
    bool unk100;
    bool unk101;
    float mAltZOffset;
    std::map<unsigned int, MeshInfo> unk108;
    unsigned char mAlign; // 0x120
    unsigned char mCapsMode; // 0x121
    int mFixedLength : 16; // 0x122
    int mDeferUpdate : 4; // 0x124
    int unk124b4 : 4;
    int unk128;
    float unk12c;
    float unk130;

    static void Init();
    static void Register(){ REGISTER_OBJ_FACTORY(RndText); }
    static std::set<RndText*> mTextMeshSet;

    DECLARE_REVS
};

#endif // RNDOBJ_TEXT_H
