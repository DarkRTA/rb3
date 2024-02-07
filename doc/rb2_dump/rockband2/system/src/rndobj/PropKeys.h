/*
    Compile unit: C:\rockband2\system\src\rndobj\PropKeys.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804EEEFC -> 0x804F1390
*/
// Range: 0x804EEEFC -> 0x804EEF04
unsigned char PropKeys::FrameFromIndex() {}

// Range: 0x804EEF04 -> 0x804EEF0C
int PropKeys::NumKeys() {}

// Range: 0x804EEF0C -> 0x804EEF58
class Keys & PropKeys::AsFloatKeys() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EEF58 -> 0x804EEFA4
class Keys & PropKeys::AsColorKeys() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EEFA4 -> 0x804EEFF0
class ObjKeys & PropKeys::AsObjectKeys() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EEFF0 -> 0x804EF03C
class Keys & PropKeys::AsBoolKeys() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF03C -> 0x804EF088
class Keys & PropKeys::AsQuatKeys() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF088 -> 0x804EF0D4
class Keys & PropKeys::AsVector3Keys() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF0D4 -> 0x804EF11C
class Quat PropKeys::QuatAt() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF11C -> 0x804EF168
unsigned char PropKeys::BoolAt() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF168 -> 0x804EF1B4
class Object * PropKeys::ObjectAt() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF1B4 -> 0x804EF220
class Color PropKeys::ColorAt() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF220 -> 0x804EF26C
float PropKeys::FloatAt() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF26C -> 0x804EF274
unsigned char PropKeys::SetFrameException() {}

// Range: 0x804EF274 -> 0x804EF2B8
void Vector3Keys::Load(class Vector3Keys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804EF2B8 -> 0x804EF2FC
void Vector3Keys::Save(class Vector3Keys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804EF2FC -> 0x804EF314
int Vector3Keys::NumKeys() {}

// Range: 0x804EF314 -> 0x804EF3B8
int Vector3Keys::RemoveKey() {}

// Range: 0x804EF3B8 -> 0x804EF678
void Vector3Keys::CloneKey(class Vector3Keys * const this /* r28 */) {}

// Range: 0x804EF678 -> 0x804EF6B4
unsigned char Vector3Keys::FrameFromIndex() {}

// Range: 0x804EF6B4 -> 0x804EF6DC
float Vector3Keys::EndFrame() {}

// Range: 0x804EF6DC -> 0x804EF6E4
class Keys & Vector3Keys::AsVector3Keys() {}

// Range: 0x804EF6E4 -> 0x804EF7BC
void * Vector3Keys::~Vector3Keys(class Vector3Keys * const this /* r30 */) {}

// Range: 0x804EF7BC -> 0x804EF804
class Vector3 PropKeys::Vector3At() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804EF804 -> 0x804EF848
void QuatKeys::Load(class QuatKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804EF848 -> 0x804EF88C
void QuatKeys::Save(class QuatKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804EF88C -> 0x804EF8A4
int QuatKeys::NumKeys() {}

// Range: 0x804EF8A4 -> 0x804EF948
int QuatKeys::RemoveKey() {}

// Range: 0x804EF948 -> 0x804EFC10
void QuatKeys::CloneKey(class QuatKeys * const this /* r28 */) {}

// Range: 0x804EFC10 -> 0x804EFC4C
unsigned char QuatKeys::FrameFromIndex() {}

// Range: 0x804EFC4C -> 0x804EFC74
float QuatKeys::EndFrame() {}

// Range: 0x804EFC74 -> 0x804EFC7C
class Keys & QuatKeys::AsQuatKeys() {}

// Range: 0x804EFC7C -> 0x804EFD54
void * QuatKeys::~QuatKeys(class QuatKeys * const this /* r30 */) {}

// Range: 0x804EFD54 -> 0x804EFD98
void BoolKeys::Load(class BoolKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804EFD98 -> 0x804EFDDC
void BoolKeys::Save(class BoolKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804EFDDC -> 0x804EFDF4
int BoolKeys::NumKeys() {}

// Range: 0x804EFDF4 -> 0x804EFE80
int BoolKeys::RemoveKey() {}

// Range: 0x804EFE80 -> 0x804F011C
void BoolKeys::CloneKey(class BoolKeys * const this /* r28 */) {}

// Range: 0x804F011C -> 0x804F0158
unsigned char BoolKeys::FrameFromIndex() {}

// Range: 0x804F0158 -> 0x804F0180
float BoolKeys::EndFrame() {}

// Range: 0x804F0180 -> 0x804F0188
class Keys & BoolKeys::AsBoolKeys() {}

// Range: 0x804F0188 -> 0x804F0260
void * BoolKeys::~BoolKeys(class BoolKeys * const this /* r30 */) {}

// Range: 0x804F0260 -> 0x804F02AC
void ObjectKeys::Load(class ObjectKeys * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class Object * sOwner;
}

// Range: 0x804F02AC -> 0x804F02F0
void ObjectKeys::Save(class ObjectKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804F02F0 -> 0x804F0308
int ObjectKeys::NumKeys() {}

// Range: 0x804F0308 -> 0x804F0414
int ObjectKeys::RemoveKey(class ObjectKeys * const this /* r27 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
}

// Range: 0x804F0414 -> 0x804F0798
void ObjectKeys::CloneKey(class ObjectKeys * const this /* r28 */) {
    // References
    // -> struct [anonymous] __vt__11ObjectStage;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> class Object * sOwner;
}

// Range: 0x804F0798 -> 0x804F07D4
unsigned char ObjectKeys::FrameFromIndex() {}

// Range: 0x804F07D4 -> 0x804F07FC
float ObjectKeys::EndFrame() {}

// Range: 0x804F07FC -> 0x804F0804
class ObjKeys & ObjectKeys::AsObjectKeys() {}

// Range: 0x804F0804 -> 0x804F0918
void * ObjectKeys::~ObjectKeys(class ObjectKeys * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
}

// Range: 0x804F0918 -> 0x804F095C
void ColorKeys::Load(class ColorKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804F095C -> 0x804F09A0
void ColorKeys::Save(class ColorKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804F09A0 -> 0x804F09B8
int ColorKeys::NumKeys() {}

// Range: 0x804F09B8 -> 0x804F0A5C
int ColorKeys::RemoveKey() {}

// Range: 0x804F0A5C -> 0x804F0D24
void ColorKeys::CloneKey(class ColorKeys * const this /* r28 */) {}

// Range: 0x804F0D24 -> 0x804F0D60
unsigned char ColorKeys::FrameFromIndex() {}

// Range: 0x804F0D60 -> 0x804F0D88
float ColorKeys::EndFrame() {}

// Range: 0x804F0D88 -> 0x804F0D90
class Keys & ColorKeys::AsColorKeys() {}

// Range: 0x804F0D90 -> 0x804F0E68
void * ColorKeys::~ColorKeys(class ColorKeys * const this /* r30 */) {}

// Range: 0x804F0E68 -> 0x804F0EAC
void FloatKeys::Load(class FloatKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804F0EAC -> 0x804F0EF0
void FloatKeys::Save(class FloatKeys * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804F0EF0 -> 0x804F0F08
int FloatKeys::NumKeys() {}

// Range: 0x804F0F08 -> 0x804F0F94
int FloatKeys::RemoveKey() {}

// Range: 0x804F0F94 -> 0x804F1230
void FloatKeys::CloneKey(class FloatKeys * const this /* r28 */) {}

// Range: 0x804F1230 -> 0x804F126C
unsigned char FloatKeys::FrameFromIndex() {}

// Range: 0x804F126C -> 0x804F1294
float FloatKeys::EndFrame() {}

// Range: 0x804F1294 -> 0x804F129C
class Keys & FloatKeys::AsFloatKeys() {}

// Range: 0x804F129C -> 0x804F1374
void * FloatKeys::~FloatKeys(class FloatKeys * const this /* r30 */) {}

// Range: 0x804F1374 -> 0x804F1378
void PropKeys::SetToCurrentVal() {}

// Range: 0x804F1378 -> 0x804F1380
int PropKeys::RemoveKey() {}

// Range: 0x804F1380 -> 0x804F1384
void PropKeys::CloneKey() {}

// Range: 0x804F1384 -> 0x804F1388
void PropKeys::SetFrame() {}

// Range: 0x804F1388 -> 0x804F1390
float PropKeys::EndFrame() {}


