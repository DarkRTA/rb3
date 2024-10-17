#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class LessonProvider : public UIListProvider, public Hmx::Object {
public:
    LessonProvider();
    virtual ~LessonProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir*);
    
    void Update(Symbol);
};