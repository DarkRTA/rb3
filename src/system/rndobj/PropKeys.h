#pragma once
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "os/Debug.h"
#include "obj/ObjectStage.h"
#include "math/Key.h"
#include "obj/Msg.h"

/** Set PropKeys' internal rev value for saving/loading. */
void SetPropKeysRev(int rev);

class ObjKeys : public Keys<ObjectStage, Hmx::Object *> {
public:
    ObjKeys(Hmx::Object *o) : mOwner(o) {}
    Hmx::Object *mOwner; // 0x8

    // fn_80632140
    void operator=(const ObjKeys &keys) {
        Hmx::Object *oldowner = ObjectStage::sOwner;
        if (this != &keys) {
            resize(keys.size());
            ObjKeys::const_iterator keysit = keys.begin();
            for (ObjKeys::iterator it = begin(); it != end(); it++, keysit++) {
                *it = *keysit;
            }
        }
        ObjectStage::sOwner = oldowner;
    }

    int Add(Hmx::Object *obj, float f, bool b) {
        Hmx::Object *oldOwner = ObjectStage::sOwner;
        ObjectStage::sOwner = mOwner;
        int add = Keys<ObjectStage, Hmx::Object *>::Add(ObjectStage(obj), f, b);
        ObjectStage::sOwner = oldOwner;
        return add;
    }
};

/** A keyframes interface. Keeps track of a target object and any of its properties to
 * animate. */
class PropKeys : public ObjRef {
public:
    enum AnimKeysType {
        kFloat,
        kColor,
        kObject,
        kBool,
        kQuat,
        kVector3,
        kSymbol
    };

    enum Interpolation {
        kStep,
        kLinear,
        kSpline,
        kSlerp,
        kHermite,
        kEaseIn,
        kEaseOut
    };

    enum ExceptionID {
        kNoException,
        kTransQuat,
        kTransScale,
        kTransPos,
        kDirEvent,
        kHandleInterp,
        kMacro
    };

    PropKeys(Hmx::Object *, Hmx::Object *);
    virtual ~PropKeys();
    virtual Hmx::Object *RefOwner() { return nullptr; }
    virtual void Replace(Hmx::Object *, Hmx::Object *) {}
    /** The first frame of these keys. */
    virtual float StartFrame() { return 0; }
    /** The last frame of these keys. */
    virtual float EndFrame() { return 0; }
    /** Given a supplied index, get the corresponding frame.
     * @param [in] index The index of the keys.
     * @param [out] frame The corresponding frame of the key at the given index.
     * @returns True if the index exists in the keys, false if not.
     */
    virtual bool FrameFromIndex(int index, float &frame) { return false; }
    virtual void SetFrame(float f1, float f2) {}
    /** Duplicate the key at the given index. */
    virtual void CloneKey(int idx) {}
    virtual int SetKey(float);
    /** Remove the key at the given index.
     * @param [in] idx The index of the key to remove.
     * @returns The new amount of keys.
     */
    virtual int RemoveKey(int idx) { return 0; }
    /** Get the number of keys. */
    virtual int NumKeys() { return 0; }
    /** Set the value of the keyframe at the supplied index, to the current value of
     * mTarget's property mProp. */
    virtual void SetToCurrentVal(int idx) {}
    /** TODO: currently unknown */
    virtual int SetFrameException(float) { return 0; }
    /** Save the keys to a BinStream. */
    virtual void Save(BinStream &);
    /** Load the keys from a BinStream. */
    virtual void Load(BinStream &);
    /** Copy the supplied PropKeys metadata into this. */
    virtual void Copy(const PropKeys *);
    /** Get these keys, as a collection of float keys. */
    virtual Keys<float, float> &AsFloatKeys() {
        MILO_ASSERT(false, 0xA7);
        return *(Keys<float, float> *)0;
    }
    /** Get these keys, as a collection of color keys. */
    virtual Keys<Hmx::Color, Hmx::Color> &AsColorKeys() {
        MILO_ASSERT(false, 0xA9);
        return *(Keys<Hmx::Color, Hmx::Color> *)0;
    }
    /** Get these keys, as a collection of Object keys. */
    virtual ObjKeys &AsObjectKeys() {
        MILO_ASSERT(false, 0xAB);
        return *(ObjKeys *)0;
    }
    /** Get these keys, as a collection of bool keys. */
    virtual Keys<bool, bool> &AsBoolKeys() {
        MILO_ASSERT(false, 0xAD);
        return *(Keys<bool, bool> *)0;
    }
    /** Get these keys, as a collection of Quat keys. */
    virtual Keys<Hmx::Quat, Hmx::Quat> &AsQuatKeys() {
        MILO_ASSERT(false, 0xAF);
        return *(Keys<Hmx::Quat, Hmx::Quat> *)0;
    }
    /** Get these keys, as a collection of Vector3 keys. */
    virtual Keys<Vector3, Vector3> &AsVector3Keys() {
        MILO_ASSERT(false, 0xB1);
        return *(Keys<Vector3, Vector3> *)0;
    }
    /** Get these keys, as a collection of Symbol keys. */
    virtual Keys<Symbol, Symbol> &AsSymbolKeys() {
        MILO_ASSERT(false, 0xB3);
        return *(Keys<Symbol, Symbol> *)0;
    }
    /** Get the float value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int FloatAt(float frame, float &val) {
        MILO_ASSERT(false, 0xB6);
        return -1;
    }
    /** Get the color value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int ColorAt(float frame, Hmx::Color &val) {
        MILO_ASSERT(false, 0xB8);
        return -1;
    }
    /** Get the Object value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int ObjectAt(float frame, Hmx::Object *&val) {
        MILO_ASSERT(false, 0xBA);
        return -1;
    }
    /** Get the bool value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int BoolAt(float frame, bool &val) {
        MILO_ASSERT(false, 0xBC);
        return -1;
    }
    /** Get the quat value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int QuatAt(float frame, Hmx::Quat &val) {
        MILO_ASSERT(false, 0xBE);
        return -1;
    }
    /** Get the Vector3 value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int Vector3At(float frame, Vector3 &val) {
        MILO_ASSERT(false, 0xC0);
        return -1;
    }
    /** Get the Symbol value associated with the supplied frame.
     * @param [in] frame The keyframe to get a value from.
     * @param [out] val The retrieved value.
     * @returns The index in the vector where this keyframe resides.
     */
    virtual int SymbolAt(float frame, Symbol &val) {
        MILO_ASSERT(false, 0xC2);
        return -1;
    }

    /** Set the property. The supplied node must contain a DataArray. */
    void SetProp(DataNode &prop);
    /** Set the target object. */
    void SetTarget(Hmx::Object *target);
    /** Set the prop exception ID. */
    void SetPropExceptionID();
    /** Change the frame value of the keyframe at the supplied index.
     * @param [in] idx The index of the keyframe to modify.
     * @param [in] frame The new frame value.
     * @param [in] resort If true, re-sort the keys after modifying the keyframe.
     */
    void ChangeFrame(int idx, float frame, bool resort);
    /** Re-sort the keys in ascending frame order. */
    void ReSort();
    /** Set the interp handler. */
    void SetInterpHandler(Symbol);
    /** Print the keys member data and keyframes to the debug console. */
    void Print();
    void ResetLastKeyFrameIndex() { mLastKeyFrameIndex = -2; }
    Symbol InterpHandler() const { return mInterpHandler; }
    static unsigned int PropExceptionID(Hmx::Object *, DataArray *);

    static unsigned short gRev;
    static Message sInterpMessage;

    /** The target object to animate properties on. */
    ObjOwnerPtr<Hmx::Object> mTarget; // 0x4
    /** The property of the target object to animate. */
    DataArray *mProp; // 0x10
    RndTransformable *mTrans; // 0x14
    /** The handler name of any propagated interp messages. */
    Symbol mInterpHandler; // 0x18
    /** The index of the last keyframe that was modified. */
    unsigned int mLastKeyFrameIndex : 22;
    /** The animation keys type. */
    unsigned int mKeysType : 3; // represents the enum AnimKeysType
    /** The key interpolation type. */
    unsigned int mInterpolation : 3; // represents the enum Interpolation
    unsigned int mPropExceptionID : 3; // represents the enum ExceptionID
    unsigned int unk18lastbit : 1;
};

/** A collection of float keys to animate on its target object's properties. */
class FloatKeys : public PropKeys, public Keys<float, float> {
public:
    FloatKeys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target) {
        mKeysType = kFloat;
    }
    virtual ~FloatKeys() {}
    virtual Keys<float, float> &AsFloatKeys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys *);
    virtual int FloatAt(float, float &);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

/** A collection of color keys to animate on its target object's properties. */
class ColorKeys : public PropKeys, public Keys<Hmx::Color, Hmx::Color> {
public:
    ColorKeys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target) {
        mKeysType = kColor;
    }
    virtual ~ColorKeys() {}
    virtual Keys<Hmx::Color, Hmx::Color> &AsColorKeys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys *);
    virtual int ColorAt(float, Hmx::Color &);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

/** A collection of Object keys to animate on its target object's properties. */
class ObjectKeys : public PropKeys, public ObjKeys {
public:
    ObjectKeys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target), ObjKeys(targetOwner) {
        mKeysType = kObject;
        mInterpolation = kStep;
    }
    virtual ~ObjectKeys() {}
    virtual ObjKeys &AsObjectKeys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            ObjKeys::Add((*this)[idx].value.Ptr(), (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        Hmx::Object *oldOwner = ObjectStage::sOwner;
        ObjectStage::sOwner = mOwner;
        bs >> *this;
        ObjectStage::sOwner = oldOwner;
    }
    virtual void Copy(const PropKeys *);
    virtual int ObjectAt(float, Hmx::Object *&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

/** A collection of bool keys to animate on its target object's properties. */
class BoolKeys : public PropKeys, public Keys<bool, bool> {
public:
    BoolKeys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target) {
        mKeysType = kBool;
        mInterpolation = kStep;
    }
    virtual ~BoolKeys() {}
    virtual Keys<bool, bool> &AsBoolKeys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys *);
    virtual int BoolAt(float, bool &);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

/** A collection of quat keys to animate on its target object's properties. */
class QuatKeys : public PropKeys, public Keys<Hmx::Quat, Hmx::Quat> {
public:
    QuatKeys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target), mVec(Vector3::sZero) {
        mKeysType = kQuat;
    }
    virtual ~QuatKeys() {}
    virtual Keys<Hmx::Quat, Hmx::Quat> &AsQuatKeys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys *);
    virtual int QuatAt(float, Hmx::Quat &);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    Vector3 mVec; // 0x28
};

/** A collection of Vector3 keys to animate on its target object's properties. */
class Vector3Keys : public PropKeys, public Keys<Vector3, Vector3> {
public:
    Vector3Keys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target) {
        mKeysType = kVector3;
    }
    virtual ~Vector3Keys() {}
    virtual Keys<Vector3, Vector3> &AsVector3Keys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys *);
    virtual int Vector3At(float, Vector3 &);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

/** A collection of Symbol keys to animate on its target object's properties. */
class SymbolKeys : public PropKeys, public Keys<Symbol, Symbol> {
public:
    SymbolKeys(Hmx::Object *targetOwner, Hmx::Object *target)
        : PropKeys(targetOwner, target) {
        mKeysType = kSymbol;
        mInterpolation = kStep;
        unk28 = -1;
        unk2c = -1;
        unk30 = 0;
    }
    virtual ~SymbolKeys() {}
    virtual Keys<Symbol, Symbol> &AsSymbolKeys() {
        if (this)
            return *this;
    }
    virtual float StartFrame() { return FirstFrame(); }
    virtual float EndFrame() { return LastFrame(); }
    virtual bool FrameFromIndex(int idx, float &f) {
        if (idx >= size())
            return false;
        else
            f = (*this)[idx].frame;
        return true;
    }
    virtual void SetFrame(float f1, float f2);
    virtual void CloneKey(int idx) {
        if (!mProp || !mTarget)
            return;
        if (idx >= 0 && idx < size()) {
            Add((*this)[idx].value, (*this)[idx].frame, false);
        }
    }
    virtual int SetKey(float);
    virtual int RemoveKey(int idx) {
        Remove(idx);
        return size();
    }
    virtual int NumKeys() { return size(); }
    virtual void SetToCurrentVal(int);
    virtual void Save(BinStream &bs) {
        PropKeys::Save(bs);
        bs << *this;
    }
    virtual void Load(BinStream &bs) {
        PropKeys::Load(bs);
        bs >> *this;
    }
    virtual void Copy(const PropKeys *);
    virtual int SymbolAt(float, Symbol &);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int unk28; // 0x28
    int unk2c; // 0x2c
    bool unk30; // 0x30
};
