#ifndef RNDOBJ_GRAPH_H
#define RNDOBJ_GRAPH_H
#include <vector>
#include "math/Vec.h"
#include "math/Color.h"
#include "obj/Object.h"
#include "rndobj/Cam.h"
#include "utl/Str.h"

class Drawable {
public:
    Drawable(){}
    virtual ~Drawable(){}
    virtual void Draw() = 0;
    virtual void DrawFixedZ(float) = 0;
};

class Line : public Drawable {
public:
    Line(const Vector3& va, const Vector3& vb, const Hmx::Color& clr, bool b) : mA(va), mB(vb), mCol(clr), mZBuf(b) {}
    virtual ~Line(){}
    virtual void Draw();
    virtual void DrawFixedZ(float);

    Vector3 mA;
    Vector3 mB;
    Hmx::Color mCol;
    bool mZBuf;
};

class DrawString : public Drawable {
public:
    DrawString(const char* cc, const Vector2& v, const Hmx::Color& clr) : mPos(v), mText(cc), mCol(clr) {}
    virtual ~DrawString(){}
    virtual void Draw();
    virtual void DrawFixedZ(float);

    Vector2 mPos;
    String mText;
    Hmx::Color mCol;
};

class DrawString3D : public Drawable {
public:
    DrawString3D(const char* cc, const Vector3& v, const Hmx::Color& clr) : mPos(v), mText(cc), mCol(clr) {}
    virtual ~DrawString3D(){}
    virtual void Draw();
    virtual void DrawFixedZ(float);

    Vector3 mPos;
    String mText;
    Hmx::Color mCol;
};

class DrawSphere : public Drawable {
public:
    DrawSphere(const Vector3& v, float r, const Hmx::Color& clr) : mCenter(v), mRadius(r), mCol(clr) {}
    virtual ~DrawSphere(){}
    virtual void Draw();
    virtual void DrawFixedZ(float);

    Vector3 mCenter;
    float mRadius;
    Hmx::Color mCol;
};

class RndGraph {
public:
    RndGraph(const void*);
    ~RndGraph();

    void Draw();
    void Reset();
    void AddLine(const Vector3&, const Vector3&, const Hmx::Color&, bool);
    void AddSphere(const Vector3&, float, const Hmx::Color&);
    void AddString(const char*, const Vector2&, const Hmx::Color&);
    void AddString3D(const char*, const Vector3&, const Hmx::Color&);

    bool mEnable;
    bool mDrawFixedZ;
    float mZ;
    void* mId;
    std::vector<Drawable*> mStuff;

    static void Init();
    static void Terminate();
    static void ResetAll();
    static RndGraph* Get(const void*);
    static void Free(const void*, bool);
    static void SetCamera(RndCam*);
    static RndGraph* GetOneFrame();
};

class FakeGraph {

};

#endif
