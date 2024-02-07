/*
    Compile unit: C:\rockband2\system\src\rndobj\PropKeys.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804E7FFC -> 0x804EED84
*/
static int gRev; // size: 0x4, address: 0x80A53700
// Range: 0x804E7FFC -> 0x804E8004
void SetPropKeysRev() {
    // References
    // -> static int gRev;
}

class Object * sOwner; // size: 0x4, address: 0x80A53704
// Range: 0x804E8004 -> 0x804E8068
float CalcSpline() {
    // Local variables
    float t2; // f9
    float t3; // f10
}

// Range: 0x804E8068 -> 0x804E83A0
class BinStream & __rs(class BinStream & d /* r30 */, class ObjectStage & s /* r31 */) {
    // Local variables
    class ObjectDir * dir; // r28
    class ObjPtr dirPtr; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __vt__29ObjPtr<9ObjectDir,9ObjectDir>;
    // -> static int gRev;
}

// Range: 0x804E83A0 -> 0x804E84A4
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjectStage & s /* r31 */) {
    // Local variables
    class ObjPtr dirPtr; // r1+0x14

    // References
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__29ObjPtr<9ObjectDir,9ObjectDir>;
}

// Range: 0x804E84A4 -> 0x804E851C
void * PropKeys::PropKeys(class PropKeys * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__8PropKeys;
}

// Range: 0x804E851C -> 0x804E85D4
void * PropKeys::~PropKeys(class PropKeys * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__8PropKeys;
}

// Range: 0x804E85D4 -> 0x804E869C
void PropKeys::SetProp(class PropKeys * const this /* r30 */) {
    // Local variables
    class DataArray * in; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804E869C -> 0x804E8764
int PropKeys::SetKey(class PropKeys * const this /* r30 */, float frame /* f31 */) {
    // Local variables
    float f; // r1+0x8
    int i; // r31
}

// Range: 0x804E8764 -> 0x804E883C
void PropKeys::SetTarget(class PropKeys * const this /* r30 */, class Object * o /* r31 */) {}

// Range: 0x804E883C -> 0x804E885C
void Interp() {}

// Range: 0x804E885C -> 0x804E88A0
void PropKeys::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804E88A0 -> 0x804E8994
void PropKeys::Load(class PropKeys * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int iVal; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x804E8994 -> 0x804E89A0
void PropKeys::Copy() {}

// Range: 0x804E89A0 -> 0x804E8C2C
void PropKeys::Print(class PropKeys * const this /* r29 */) {
    // Local variables
    class TextStream & d; // r31
    int i; // r30
    float frame; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804E8C2C -> 0x804E8EC4
enum ExceptionID PropKeys::PropExceptionID(class Object * o /* r29 */, class DataArray * path /* r30 */) {
    // Local variables
    class String propString; // r1+0x34
}

// Range: 0x804E8EC4 -> 0x804E8F44
void PropKeys::SetPropExceptionID(class PropKeys * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

class FloatKeys : public PropKeys, public Keys {
    // total size: 0x30
};
// Range: 0x804E8F44 -> 0x804E984C
float FloatKeys::FloatAt(class FloatKeys * const this /* r31 */, float frame /* f30 */) {
    // Local variables
    float v; // f31
    const float * prev; // r25
    int before; // r27
    int after; // r28
    float f; // f0
    int between; // r26
    float t; // f31
    float points[4]; // r1+0x8
}

// Range: 0x804E984C -> 0x804E9930
void FloatKeys::SetFrame(class FloatKeys * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class ColorKeys : public PropKeys, public Keys {
    // total size: 0x30
};
// Range: 0x804E9930 -> 0x804E9E34
class Color ColorKeys::ColorAt(class ColorKeys * const this /* r24 */, float frame /* f31 */) {
    // Local variables
    class Color c; // r1+0x10
    const class Color * prev; // r25
    float v; // f0
}

// Range: 0x804E9E34 -> 0x804E9F7C
void ColorKeys::SetFrame(class ColorKeys * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class ObjectKeys : public PropKeys, public ObjKeys {
    // total size: 0x34
};
// Range: 0x804E9F7C -> 0x804EA1D4
class Object * ObjectKeys::ObjectAt(class ObjectKeys * const this /* r25 */, float frame /* f31 */) {
    // Local variables
    class Object * obj; // r1+0x8
}

// Range: 0x804EA1D4 -> 0x804EA2C4
void ObjectKeys::SetFrame(class ObjectKeys * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class BoolKeys : public PropKeys, public Keys {
    // total size: 0x30
};
// Range: 0x804EA2C4 -> 0x804EA52C
unsigned char BoolKeys::BoolAt(class BoolKeys * const this /* r23 */, float frame /* f31 */) {
    // Local variables
    unsigned char b; // r24
}

// Range: 0x804EA52C -> 0x804EA610
void BoolKeys::SetFrame(class BoolKeys * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class QuatKeys : public PropKeys, public Keys {
    // total size: 0x30
};
// Range: 0x804EA610 -> 0x804EA920
class Quat QuatKeys::QuatAt(class Quat * q /* r24 */, class QuatKeys * const this /* r25 */, float frame /* f30 */) {
    // Local variables
    float f; // f31
    const class Quat * prev; // r27
    const class Quat * next; // r26
}

// Range: 0x804EA920 -> 0x804EAB4C
void QuatKeys::SetFrame(class QuatKeys * const this /* r31 */, float frame /* f31 */) {
    // Local variables
    class Matrix3 cur; // r1+0x60
    class Vector3 scale; // r1+0x20
    class Matrix3 m; // r1+0x30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

class Vector3Keys : public PropKeys, public Keys {
    // total size: 0x30
};
// Range: 0x804EAB4C -> 0x804EB06C
class Vector3 Vector3Keys::Vector3At(class Vector3Keys * const this /* r24 */, float frame /* f31 */) {
    // Local variables
    class Vector3 v; // r1+0x10
    float f; // f0
    const class Vector3 * prev; // r25
}

// Range: 0x804EB06C -> 0x804EB45C
void Vector3Keys::SetFrame(class Vector3Keys * const this /* r31 */, float frame /* f31 */) {
    // Local variables
    class Matrix3 cur; // r1+0x70
    class Vector3 rot; // r1+0x30
    class Matrix3 m; // r1+0x40

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x804EB45C -> 0x804EB728
int FloatKeys::SetKey(class FloatKeys * const this /* r28 */, float frame /* f31 */) {
    // Local variables
    int retVal; // r29
}

// Range: 0x804EB728 -> 0x804EBA38
int ColorKeys::SetKey(class ColorKeys * const this /* r28 */, float frame /* f31 */) {
    // Local variables
    int retVal; // r29
}

// Range: 0x804EBA38 -> 0x804EBDB0
int ObjectKeys::SetKey(class ObjectKeys * const this /* r28 */, float frame /* f31 */) {
    // Local variables
    int retVal; // r29

    // References
    // -> struct [anonymous] __vt__11ObjectStage;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> class Object * sOwner;
}

// Range: 0x804EBE24 -> 0x804EC0F0
int BoolKeys::SetKey(class BoolKeys * const this /* r28 */, float frame /* f31 */) {
    // Local variables
    int retVal; // r29
}

// Range: 0x804EC0F0 -> 0x804EC3FC
int QuatKeys::SetKey(class QuatKeys * const this /* r28 */, float frame /* f31 */) {
    // Local variables
    int retVal; // r29
}

// Range: 0x804EC3FC -> 0x804EC6FC
int Vector3Keys::SetKey(class Vector3Keys * const this /* r28 */, float frame /* f31 */) {
    // Local variables
    int retVal; // r29
}

// Range: 0x804EC6FC -> 0x804EC794
void FloatKeys::SetToCurrentVal(class FloatKeys * const this /* r29 */, int index /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EC794 -> 0x804EC8C8
void ColorKeys::SetToCurrentVal(class ColorKeys * const this /* r30 */, int index /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EC8C8 -> 0x804EC9FC
void ObjectKeys::SetToCurrentVal(class ObjectKeys * const this /* r29 */, int index /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11ObjectStage;
    // -> class Object * sOwner;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EC9FC -> 0x804ECAA0
void BoolKeys::SetToCurrentVal(class BoolKeys * const this /* r29 */, int index /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804ECAA0 -> 0x804ECCDC
void QuatKeys::SetToCurrentVal(class QuatKeys * const this /* r30 */, int index /* r31 */) {
    // Local variables
    class Matrix3 m; // r1+0x20

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x804ECCDC -> 0x804ECE1C
void Vector3Keys::SetToCurrentVal(class Vector3Keys * const this /* r30 */, int index /* r31 */) {
    // Local variables
    class Vector3 s; // r1+0x10

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x804ECE1C -> 0x804ED284
void FloatKeys::Copy(class FloatKeys * const this /* r25 */, const class PropKeys * keys /* r26 */) {
    // Local variables
    const class FloatKeys * rhs; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P6Key<f>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__8PropKeys;
    // -> struct [anonymous] __RTTI__9FloatKeys;
}

struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x804ED284 -> 0x804ED7DC
void ColorKeys::Copy(class ColorKeys * const this /* r25 */, const class PropKeys * keys /* r26 */) {
    // Local variables
    const class ColorKeys * rhs; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P17Key<Q23Hmx5Color>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__8PropKeys;
    // -> struct [anonymous] __RTTI__9ColorKeys;
}

struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x804ED7DC -> 0x804EDE9C
void ObjectKeys::Copy(class ObjectKeys * const this /* r24 */, const class PropKeys * keys /* r27 */) {
    // Local variables
    const class ObjectKeys * rhs; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P18Key<11ObjectStage>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__11ObjectStage;
    // -> struct [anonymous] __RTTI__8PropKeys;
    // -> struct [anonymous] __RTTI__10ObjectKeys;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
}

struct {
    // total size: 0x8
} __RTTI__P18Key<11ObjectStage>; // size: 0x8, address: 0x808FE648
struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x804EDE9C -> 0x804EE304
void BoolKeys::Copy(class BoolKeys * const this /* r25 */, const class PropKeys * keys /* r26 */) {
    // Local variables
    const class BoolKeys * rhs; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P6Key<b>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__8PropKeys;
    // -> struct [anonymous] __RTTI__8BoolKeys;
}

struct {
    // total size: 0x8
} __RTTI__P6Key<b>; // size: 0x8, address: 0x808FE660
struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x804EE304 -> 0x804EE85C
void QuatKeys::Copy(class QuatKeys * const this /* r25 */, const class PropKeys * keys /* r26 */) {
    // Local variables
    const class QuatKeys * rhs; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P16Key<Q23Hmx4Quat>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__8PropKeys;
    // -> struct [anonymous] __RTTI__8QuatKeys;
}

struct {
    // total size: 0x8
} __RTTI__P16Key<Q23Hmx4Quat>; // size: 0x8, address: 0x808FE680
struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x804EE85C -> 0x804EED84
void Vector3Keys::Copy(class Vector3Keys * const this /* r25 */, const class PropKeys * keys /* r26 */) {
    // Local variables
    const class Vector3Keys * rhs; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P13Key<7Vector3>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__8PropKeys;
    // -> struct [anonymous] __RTTI__11Vector3Keys;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x6C
} __vt__11Vector3Keys; // size: 0x6C, address: 0x808FE6F0
struct {
    // total size: 0x8
} __RTTI__11Vector3Keys; // size: 0x8, address: 0x808FE790
struct {
    // total size: 0x6C
} __vt__8QuatKeys; // size: 0x6C, address: 0x808FE798
struct {
    // total size: 0x8
} __RTTI__8QuatKeys; // size: 0x8, address: 0x808FE838
struct {
    // total size: 0x6C
} __vt__8BoolKeys; // size: 0x6C, address: 0x808FE840
struct {
    // total size: 0x8
} __RTTI__8BoolKeys; // size: 0x8, address: 0x808FE8E0
struct {
    // total size: 0x6C
} __vt__10ObjectKeys; // size: 0x6C, address: 0x808FE8E8
struct {
    // total size: 0x8
} __RTTI__10ObjectKeys; // size: 0x8, address: 0x808FE990
struct {
    // total size: 0x6C
} __vt__9ColorKeys; // size: 0x6C, address: 0x808FE998
struct {
    // total size: 0x8
} __RTTI__9ColorKeys; // size: 0x8, address: 0x808FEA38
struct {
    // total size: 0x6C
} __vt__9FloatKeys; // size: 0x6C, address: 0x808FEA40
struct {
    // total size: 0x8
} __RTTI__9FloatKeys; // size: 0x8, address: 0x808FEAE0
struct {
    // total size: 0x8
} __RTTI__9Keys<f,f>; // size: 0x8, address: 0x808FEB10
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std54vector<6Key<f>,Q211stlpmtx_std21StlNodeAlloc<6Key<f>>>; // size: 0x8, address: 0x808FEB70
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std60_Vector_base<6Key<f>,Q211stlpmtx_std21StlNodeAlloc<6Key<f>>>; // size: 0x8, address: 0x808FEBC8
struct {
    // total size: 0x8
} __RTTI__31Keys<Q23Hmx5Color,Q23Hmx5Color>; // size: 0x8, address: 0x808FEC08
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std78vector<17Key<Q23Hmx5Color>,Q211stlpmtx_std33StlNodeAlloc<17Key<Q23Hmx5Color>>>; // size: 0x8, address: 0x808FEC70
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std84_Vector_base<17Key<Q23Hmx5Color>,Q211stlpmtx_std33StlNodeAlloc<17Key<Q23Hmx5Color>>>; // size: 0x8, address: 0x808FECD0
struct {
    // total size: 0x8
} __RTTI__9Keys<b,b>; // size: 0x8, address: 0x808FED00
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std54vector<6Key<b>,Q211stlpmtx_std21StlNodeAlloc<6Key<b>>>; // size: 0x8, address: 0x808FED60
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std60_Vector_base<6Key<b>,Q211stlpmtx_std21StlNodeAlloc<6Key<b>>>; // size: 0x8, address: 0x808FEDB8
struct {
    // total size: 0x8
} __RTTI__29Keys<Q23Hmx4Quat,Q23Hmx4Quat>; // size: 0x8, address: 0x808FEDF0
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std76vector<16Key<Q23Hmx4Quat>,Q211stlpmtx_std32StlNodeAlloc<16Key<Q23Hmx4Quat>>>; // size: 0x8, address: 0x808FEE58
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std82_Vector_base<16Key<Q23Hmx4Quat>,Q211stlpmtx_std32StlNodeAlloc<16Key<Q23Hmx4Quat>>>; // size: 0x8, address: 0x808FEEB8
struct {
    // total size: 0x8
} __RTTI__23Keys<7Vector3,7Vector3>; // size: 0x8, address: 0x808FEEF0
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std70vector<13Key<7Vector3>,Q211stlpmtx_std29StlNodeAlloc<13Key<7Vector3>>>; // size: 0x8, address: 0x808FEF50
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std76_Vector_base<13Key<7Vector3>,Q211stlpmtx_std29StlNodeAlloc<13Key<7Vector3>>>; // size: 0x8, address: 0x808FEFB0
struct {
    // total size: 0x6C
} __vt__8PropKeys; // size: 0x6C, address: 0x808FEFB8
struct {
    // total size: 0x8
} __RTTI__8PropKeys; // size: 0x8, address: 0x808FF030
struct {
    // total size: 0x8
} __RTTI__7ObjKeys; // size: 0x8, address: 0x808FF060
struct {
    // total size: 0x8
} __RTTI__34Keys<11ObjectStage,PQ23Hmx6Object>; // size: 0x8, address: 0x808FF0A0
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std80vector<18Key<11ObjectStage>,Q211stlpmtx_std34StlNodeAlloc<18Key<11ObjectStage>>>; // size: 0x8, address: 0x808FF108
struct {
    // total size: 0x8
} __RTTI__Q211stlpmtx_std86_Vector_base<18Key<11ObjectStage>,Q211stlpmtx_std34StlNodeAlloc<18Key<11ObjectStage>>>; // size: 0x8, address: 0x808FF170
struct {
    // total size: 0x18
} __vt__11ObjectStage; // size: 0x18, address: 0x808FF178
struct {
    // total size: 0x8
} __RTTI__11ObjectStage; // size: 0x8, address: 0x808FF1B0

