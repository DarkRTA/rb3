#ifndef RNDOBJ_TEXT_H
#define RNDOBJ_TEXT_H

#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Trans.h"
#include "rndobj/Font.h"
#include <set>

class RndText : public RndDrawable, public RndTransformable {
public:
    enum Style {

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
    virtual ~RndText();
    virtual void Highlight();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    NEW_OBJ(RndText)
    OBJ_CLASSNAME(RndText)
    OBJ_SET_TYPE(RndText)

    float GetStringWidthUTF8(const char*, const char*, bool, Style*) const;
    void ReserveLines(int);
    void UpdateText(bool);
    void SetFont(RndFont*);
    String TextASCII() const; void SetTextASCII(const char*);
    float Size() const { return mSize; } void SetSize(float);
    void GetMeshes(std::vector<RndMesh*>&);
    void SetFixedLength(int);

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
    String unk_cc; // 0xcc
    RndFont* unkd8; // 0xd8
    float mSize; // 0xdc
    float mItalicStrength; // 0xe0
    int unke4; // packed color? Hmx::Color32?
    bool unke8;
    bool unke9;
    float unkec;
    int unkf0;
    float unkf4;
    float unkf8;
    int unkfc;
    bool unk100;
    bool unk101;
    float unk104;
    std::map<unsigned int, MeshInfo> unk108;
    Alignment mAlign : 8; // 0x120
    CapsMode mCapsMode : 8; // 0x121
    int unk122 : 8;
    int unk123 : 8;
    int mDeferUpdate : 4; // 0x124
    int unk128;
    float unk12c;
    float unk130;

    static void Init();
    static std::set<RndText*> mTextMeshSet;

    DECLARE_REVS
};

#endif // RNDOBJ_TEXT_H
