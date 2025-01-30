#pragma once
// These headers are prerequisites for the macros here to function correctly
// #include "obj/Object.h" // We're included
#include "os/System.h" /* IWYU pragma: keep */
#include "obj/PropSync_p.h" /* IWYU pragma: keep */
#include "obj/MessageTimer.h" /* IWYU pragma: keep */

/** Get this Object's path name.
 * @param [in] obj The Object.
 * @returns The Object's path name, or "NULL Object" if it doesn't exist.
*/
const char* PathName(const class Hmx::Object* obj);

// BEGIN CLASSNAME MACRO -------------------------------------------------------------------------------

#define OBJ_CLASSNAME(classname) \
    virtual Symbol ClassName() const { return StaticClassName(); } \
    static Symbol StaticClassName(){ \
        static Symbol name(#classname); \
        return name; \
    }

// END CLASSNAME MACRO ---------------------------------------------------------------------------------

// BEGIN SET TYPE MACRO --------------------------------------------------------------------------------
#ifdef MILO_DEBUG
#define OBJ_SET_TYPE(classname) \
    virtual void SetType(Symbol classname){ \
        static DataArray* types = SystemConfig("objects", StaticClassName(), "types"); \
        if(classname.Null()) SetTypeDef(0); \
        else { \
            DataArray* found = types->FindArray(classname, false); \
            if(found != 0) SetTypeDef(found); \
            else { \
                MILO_WARN("%s:%s couldn't find type %s", ClassName(), PathName(this), classname); \
                SetTypeDef(0); \
            } \
        } \
    }
#else
#define OBJ_SET_TYPE(classname) \
    virtual void SetType(Symbol classname){ \
        static DataArray* types = SystemConfig("objects", StaticClassName(), "types"); \
        if(classname.Null()) SetTypeDef(0); \
        else { \
            DataArray* found = types->FindArray(classname, false); \
            if(found != 0) SetTypeDef(found); \
            else { \
                MILO_WARN("%s:%s couldn't find type %s", PathName(this), ClassName(), classname); \
                SetTypeDef(0); \
            } \
        } \
    }
#endif

// END SET TYPE MACRO ----------------------------------------------------------------------------------

// BEGIN HANDLE MACROS ---------------------------------------------------------------------------------

#ifdef MILO_DEBUG
    #define BEGIN_HANDLERS(objType) \
    DataNode objType::Handle(DataArray* _msg, bool _warn){ \
        Symbol sym = _msg->Sym(1); \
        MessageTimer timer((MessageTimer::Active()) ? static_cast<Hmx::Object*>(this) : 0, sym);
#else
    #define BEGIN_HANDLERS(objType) \
    DataNode objType::Handle(DataArray* _msg, bool _warn){ \
        Symbol sym = _msg->Sym(1);
#endif

#define _HANDLE_CHECKED(expr) \
    { \
        DataNode result = expr; \
        if(result.Type() != kDataUnhandled) return result; \
    }

#define HANDLE(symbol, func) \
    if(sym == symbol) _HANDLE_CHECKED(func(_msg))

#define HANDLE_EXPR(symbol, expr) \
    if (sym == symbol) return expr;

#define HANDLE_ACTION(symbol, action) \
    if (sym == symbol) { \
        /* for style, require any side-actions to be performed via comma operator */ \
        (action); \
        return 0; \
    }

#define HANDLE_ACTION_IF(symbol, cond, action) \
    if (sym == symbol) { \
        if (cond) { \
            /* for style, require any side-actions to be performed via comma operator */ \
            (action); \
        } \
        return 0; \
    }

#define HANDLE_ACTION_IF_ELSE(symbol, cond, action_true, action_false) \
    if (sym == symbol) { \
        if (cond) { \
            /* for style, require any side-actions to be performed via comma operator */ \
            (action_true); \
        } else { \
            (action_false); \
        } \
        return 0; \
    }

#define HANDLE_CONDITION(cond, expr) \
    if (cond) return expr;

#define HANDLE_MESSAGE(msg) \
    if(sym == msg::Type()) _HANDLE_CHECKED(OnMsg(msg(_msg)))

#define _NEW_STATIC_SYMBOL(str) \
    static Symbol _s(#str);

#define HANDLE_STATIC(sym, func) { \
    _NEW_STATIC_SYMBOL(sym) \
    HANDLE(_s, func); \
}

#define HANDLE_EXPR_STATIC(symbol, expr) { \
    _NEW_STATIC_SYMBOL(symbol) \
    HANDLE_EXPR(_s, expr) \
}

#define HANDLE_ACTION_STATIC(symbol, expr) { \
    _NEW_STATIC_SYMBOL(symbol) \
    HANDLE_ACTION(_s, expr) \
}

#define HANDLE_METHOD(func) \
    _HANDLE_CHECKED(func(_msg))

#define HANDLE_FORWARD(func) \
    _HANDLE_CHECKED(func(_msg, false))

#define HANDLE_SUPERCLASS(parent) \
    HANDLE_FORWARD(parent::Handle)

#define HANDLE_VIRTUAL_SUPERCLASS(parent) \
    if(ClassName() == StaticClassName()) HANDLE_SUPERCLASS(parent)

#define HANDLE_MEMBER(member) \
    HANDLE_FORWARD(member.Handle)

#define HANDLE_MEMBER_PTR(member) \
    if (member) HANDLE_FORWARD(member->Handle)

#define HANDLE_ARRAY(array) \
    { \
        /* this needs to be placed up here to match Hmx::Object::Handle */ \
        DataArray* found; \
        if(array && (found = array->FindArray(sym, false))){ \
            _HANDLE_CHECKED(found->ExecuteScript(1, this, _msg, 2)) \
        } \
    }

#define HANDLE_LOG(...) \
    if(!_warn) MILO_LOG(__VA_ARGS__);

#define HANDLE_LOG_IF(cond, ...) \
    if((cond) && !_warn) MILO_LOG(__VA_ARGS__);

#define HANDLE_WARN(...) \
    if(_warn) MILO_WARN(__VA_ARGS__);

#define HANDLE_WARN_IF(cond, ...) \
    if((cond) && _warn) MILO_WARN(__VA_ARGS__);

#define HANDLE_CHECK(line_num) \
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, line_num, PathName(this), sym);

#define END_HANDLERS \
    return DataNode(kDataUnhandled, 0); \
}

// END HANDLE MACROS -----------------------------------------------------------------------------------

// BEGIN SYNCPROPERTY MACROS ---------------------------------------------------------------------------

#define BEGIN_PROPSYNCS(objType) \
bool objType::SyncProperty(DataNode& _val, DataArray* _prop, int _i, PropOp _op){ \
    if(_i == _prop->Size()) return true; \
    else { \
        Symbol sym = _prop->Sym(_i);

#define BEGIN_CUSTOM_PROPSYNC(objType) \
bool PropSync(objType& o, DataNode& _val, DataArray* _prop, int _i, PropOp _op){ \
    if(_i == _prop->Size()) return true; \
    else { \
        Symbol sym = _prop->Sym(_i);

#define SYNC_PROP(symbol, member) \
        if(sym == symbol) return PropSync(member, _val, _prop, _i + 1, _op);

// TODO: make specific sync macros for objects and bitfields?

// for propsyncs that do something extra if the prop op is specifically kPropSet
#define SYNC_PROP_SET(symbol, member, func) \
        if(sym == symbol){ \
            if(_op == kPropSet){ \
                func; \
            } \
            else { \
                if(_op == (PropOp)0x40) return false; \
                _val = DataNode(member); \
            } \
            return true; \
        }

// for propsyncs that do NOT use size or get - aka, any combo of set, insert, remove, and handle is used
#define SYNC_PROP_MODIFY(symbol, member, func) \
        if(sym == symbol){ \
            bool synced = PropSync(member, _val, _prop, _i + 1, _op); \
            if(!synced) return false; \
            else { \
                if(!(_op & (kPropSize|kPropGet))){ \
                    func; \
                } \
                return true; \
            } \
        }

// for SYNC_PROP_MODIFY uses where the condition order is flipped
// if you know how to make this macro and SYNC_PROP_MODIFY into one singular macro,
// while still matching every instance of SYNC_PROP_MODIFY being used regardless of condition order,
// by all means please do so, because idk how to do it here
#define SYNC_PROP_MODIFY_ALT(symbol, member, func) \
        if(sym == symbol){ \
            bool synced = PropSync(member, _val, _prop, _i + 1, _op); \
            if(synced){ \
                if(!(_op & (kPropSize|kPropGet))){ \
                    func; \
                } \
                return true; \
            } \
            else return false; \
        }

#define SYNC_PROP_BITFIELD(symbol, mask_member, line_num) \
        if(sym == symbol){ \
            _i++; \
            if(_i < _prop->Size()){ \
                DataNode& node = _prop->Node(_i); \
                int res = 0; \
                switch(node.Type()){ \
                    case kDataInt: \
                        res = node.Int(); \
                        break; \
                    case kDataSymbol: { \
                        const char* bitstr = node.Sym().Str(); \
                        MILO_ASSERT_FMT(strncmp("BIT_", bitstr, 4) == 0, "%s does not begin with BIT_", bitstr); \
                        Symbol bitsym(bitstr + 4); \
                        const Symbol& test = Symbol(bitsym); \
                        DataArray* macro = DataGetMacro(test); \
                        MILO_ASSERT_FMT(macro, "PROPERTY_BITFIELD %s could not find macro %s", symbol, test); \
                        res = macro->Int(0); \
                        break; \
                    } \
                    default: \
                        MILO_ASSERT(0, line_num); \
                        break; \
                } \
                MILO_ASSERT(_op <= kPropInsert, line_num); \
                if(_op == kPropGet){ \
                    int final = mask_member & res; \
                    _val = DataNode(final > 0); \
                } \
                else { \
                    if(_val.Int() != 0) mask_member |= res; \
                    else mask_member &= ~res; \
                } \
                return true; \
            } \
            else return PropSync(mask_member, _val, _prop, _i, _op); \
        }

#define SYNC_PROP_STATIC(symbol, member) { \
    _NEW_STATIC_SYMBOL(symbol) \
    SYNC_PROP(_s, member) \
}

#define SYNC_PROP_SET_STATIC(symbol, member, func) { \
    _NEW_STATIC_SYMBOL(symbol) \
    SYNC_PROP_SET(_s, member, func) \
}

#define SYNC_PROP_MODIFY_STATIC(symbol, member, func) { \
    _NEW_STATIC_SYMBOL(symbol) \
    SYNC_PROP_MODIFY(_s, member, func) \
}

#define SYNC_PROP_BITFIELD_STATIC(symbol, mask_member, line_num) { \
    _NEW_STATIC_SYMBOL(symbol) \
    SYNC_PROP_BITFIELD(_s, mask_member, line_num) \
}

#define SYNC_SUPERCLASS(parent) \
        if(parent::SyncProperty(_val, _prop, _i, _op)) return true;

#define END_PROPSYNCS \
        return false; \
    } \
}

#define END_CUSTOM_PROPSYNC \
        return false; \
    } \
}

// END SYNCPROPERTY MACROS -----------------------------------------------------------------------------

// BEGIN SAVE MACRO ------------------------------------------------------------------------------------

#define SAVE_OBJ(objType, line_num) \
void objType::Save(BinStream&){ \
    MILO_ASSERT(0, line_num); \
}

// END SAVE MACRO --------------------------------------------------------------------------------------

// BEGIN COPY MACROS -----------------------------------------------------------------------------------

#define BEGIN_COPYS(objType) \
void objType::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){

#define COPY_SUPERCLASS(parent) \
    parent::Copy(o, ty);

#define COPY_VIRTUAL_SUPERCLASS(parent) \
    if(ClassName() == StaticClassName()) COPY_SUPERCLASS(Hmx::Object)

#define COPY_SUPERCLASS_FROM(parent, obj) \
    parent::Copy(obj, ty);

#define CREATE_COPY(objType) \
    const objType* c = dynamic_cast<const objType*>(o);

// copy macro where you specify the variable name (used in asserts in some copy methods)
#define CREATE_COPY_AS(objType, var_name) \
    const objType* var_name = dynamic_cast<const objType*>(o);

#define BEGIN_COPYING_MEMBERS \
    if(c){

// copy macro where you specify the variable name (used in asserts in some copy methods)
#define BEGIN_COPYING_MEMBERS_FROM(copy_name) \
    if(copy_name){

#define COPY_MEMBER(mem) \
        mem = c->mem;

// copy macro where you specify the variable name (used in asserts in some copy methods)
#define COPY_MEMBER_FROM(copy_name, member) \
        member = copy_name->member;

#define END_COPYING_MEMBERS \
    }

#define END_COPYS \
}

// END COPY MACROS -------------------------------------------------------------------------------------

// BEGIN LOAD MACROS -----------------------------------------------------------------------------------

#define DECLARE_REVS \
    static unsigned short gRev; \
    static unsigned short gAltRev;

#define INIT_REVS(objType) \
    unsigned short objType::gRev = 0; \
    unsigned short objType::gAltRev = 0;

#define BEGIN_LOADS(objType) \
void objType::Load(BinStream& bs){

#define LOAD_REVS(bs) \
    int rev; \
    bs >> rev; \
    gRev = getHmxRev(rev); \
    gAltRev = getAltRev(rev);

#define ASSERT_REV(ver) \
    if ((ver == 0) ? (gRev != ver) : (gRev > ver)){ \
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)ver); \
    }

#define ASSERT_ALTREV(ver) \
    if ((ver == 0) ? (gAltRev != ver) : (gAltRev > ver)){ \
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)ver); \
    }

#ifdef VERSION_SZBE69_B8
    #define ASSERT_REVS(rev1, rev2) \
        ASSERT_REV(rev1) \
        ASSERT_ALTREV(rev2)
#else
    #define ASSERT_REVS(rev1, rev2)
#endif

// for loading in a version number that isn't a class's gRev/gAltRev
#ifdef VERSION_SZBE69_B8
    #define ASSERT_GLOBAL_REV(ver, rev_name) \
        if (ver > rev_name){ \
            MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), ver, rev_name); \
        }

    #define ASSERT_OLD_REV(ver) \
        if (gRev < ver) { \
            MILO_FAIL("%s can't load old %s version %d < %d.  Use RB2 Milo to load.", PathName(this), ClassName(), gRev, ver); \
        }

    #define ASSERT_OLD_ALTREV(ver) \
        if (gRev < ver) { \
            MILO_FAIL("%s can't load old %s alt version %d < %d.  Use RB2 Milo to load.", PathName(this), ClassName(), gAltRev, ver); \
        }
#else
    #define ASSERT_GLOBAL_REV(ver, rev_name)
    #define ASSERT_OLD_REV(ver)
    #define ASSERT_OLD_ALTREV(ver)
#endif

#define LOAD_SUPERCLASS(parent) \
    parent::Load(bs);

#define LOAD_BITFIELD(type, name) { \
    type bs_name; \
    bs >> bs_name; \
    name = bs_name; \
}

#define LOAD_BITFIELD_ENUM(type, name, enum_name) { \
    type bs_name; \
    bs >> bs_name; \
    name = (enum_name)bs_name; \
}

#define END_LOADS \
}

// END LOAD MACROS -------------------------------------------------------------------------------------

// BEGIN OBJ INITIALIZER MACROS ------------------------------------------------------------------------

#define NEW_OBJ(objType) \
    static Hmx::Object* NewObject() { return new objType; }

#define REGISTER_OBJ_FACTORY(objType) \
    Hmx::Object::RegisterFactory(objType::StaticClassName(), objType::NewObject);

#define REGISTER_OBJ_FACTORY_FUNC(objType) \
    static void Register() { \
        REGISTER_OBJ_FACTORY(objType)\
    }

// END OBJ INITIALIZER MACROS --------------------------------------------------------------------------

// BEGIN OBJREF ITERATION MACROS -----------------------------------------------------------------------

#define FOREACH_OBJREF(it, obj) \
    std::vector<ObjRef*>::const_reverse_iterator it = obj->Refs().rbegin(); \
    std::vector<ObjRef*>::const_reverse_iterator it##End = obj->Refs().rend(); \
    for(; it != itEnd; ++it)

#define FOREACH_OBJREF_POST(it, obj) \
    std::vector<ObjRef*>::const_reverse_iterator it = obj->Refs().rbegin(); \
    std::vector<ObjRef*>::const_reverse_iterator it##End = obj->Refs().rend(); \
    for(; it != itEnd; it++)

// END OBJREF ITERATION MACROS -------------------------------------------------------------------------