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

    };

    class Line {

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

    DataNode OnSetFixedLength(DataArray*);
    DataNode OnSetFont(DataArray*);
    DataNode OnSetAlign(DataArray*);
    DataNode OnSetText(DataArray*);
    DataNode OnSetSize(DataArray*);
    DataNode OnSetWrapWidth(DataArray*);
    DataNode OnSetColor(DataArray*);

    std::vector<Line, unsigned short> mLines;
    ObjOwnerPtr<RndFont, ObjectDir> mFont;
    float mWrapWidth, unk_c8;
    String unk_cc;
    float mSize; // 0xdc
    float mItalicStrength; // 0xe0
    ObjOwnerPtr<RndMesh, ObjectDir> unk_e0;

    int mDeferUpdate : 4;

    static void Init();
    static std::set<RndText*> mTextMeshSet;

    DECLARE_REVS
};

#endif // RNDOBJ_TEXT_H
