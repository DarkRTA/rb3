#ifndef OBJ_OBJMACROS_H
#define OBJ_OBJMACROS_H
#include "obj/Object.h"
#include "os/System.h"
#include "obj/PropSync_p.h"
#include "obj/MessageTimer.h"

const char* PathName(const Hmx::Object*);

// BEGIN CLASSNAME MACRO -------------------------------------------------------------------------------

#define OBJ_CLASSNAME(classname) \
    virtual Symbol ClassName() const { return StaticClassName(); } \
    static Symbol StaticClassName(){ \
        static Symbol name(#classname); \
        return name; \
    }

// END CLASSNAME MACRO ---------------------------------------------------------------------------------

// BEGIN SET TYPE MACRO --------------------------------------------------------------------------------

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

// END SET TYPE MACRO ----------------------------------------------------------------------------------

// BEGIN HANDLE MACROS ---------------------------------------------------------------------------------

#define BEGIN_HANDLERS(objType) \
DataNode objType::Handle(DataArray* _msg, bool _warn){ \
    Symbol sym = _msg->Sym(1); \
    MessageTimer timer((MessageTimer::Active()) ? static_cast<Hmx::Object*>(this) : 0, sym);

#define HANDLE(symbol, func) \
    if(sym == symbol){ \
        DataNode result = func(_msg); \
        if(result.Type() != kDataUnhandled) return DataNode(result); \
    }

#define HANDLE_EXPR(symbol, expr) \
    if (sym == symbol) return DataNode(expr);

#define HANDLE_ACTION(symbol, expr) \
    if(sym == symbol){ \
        expr; \
        return DataNode(0); \
    }

#define HANDLE_MESSAGE(msg) \
    if(sym == msg::Type()){ \
        DataNode result = OnMsg(msg(_msg)); \
        if(result.Type() != kDataUnhandled) return DataNode(result); \
    }

#define NEW_STATIC_SYMBOL(str) \
    static Symbol _s(#str);

#define HANDLE_STATIC(sym, func) { \
    NEW_STATIC_SYMBOL(sym) \
    HANDLE(_s, func); \
}

#define HANDLE_EXPR_STATIC(symbol, expr) { \
    NEW_STATIC_SYMBOL(symbol) \
    HANDLE_EXPR(_s, expr) \
}

#define HANDLE_ACTION_STATIC(symbol, expr) { \
    NEW_STATIC_SYMBOL(symbol) \
    HANDLE_ACTION(_s, expr) \
}

#define HANDLE_SUPERCLASS(parent) \
    { \
        DataNode baseResult = parent::Handle(_msg, false); \
        if (baseResult.Type() != kDataUnhandled) return baseResult; \
    }

#define HANDLE_MEMBER(member) \
    { \
        DataNode baseResult = member.Handle(_msg, false); \
        if (baseResult.Type() != kDataUnhandled) return baseResult; \
    }

#define HANDLE_MEMBER_PTR(member) \
    { \
        if (member) {\
            DataNode baseResult = member->Handle(_msg, false); \
            if (baseResult.Type() != kDataUnhandled) return baseResult; \
        } \
    }

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

#define SYNC_PROP(symbol, member) \
        if(sym == symbol) return PropSync(member, _val, _prop, _i + 1, _op);

#define SYNC_PROP_METHOD(symbol, member, method) \
        if(sym == symbol){ \
            if(_op == kPropSet) method; \
            else { \
                if(_op == (PropOp)0x40) return false; \
                _val = DataNode(member); \
            } \
            return true; \
        }

#define SYNC_PROP_ACTION(symbol, member, opmask, action) \
        if(sym == symbol){ \
            bool synced = PropSync(member, _val, _prop, _i + 1, _op); \
            if(!synced) return false; \
            else { \
                if(!(_op & (opmask))){ \
                    action; \
                } \
                return true; \
            } \
        }

#define SYNC_PROP_STATIC(symbol, member) { \
    NEW_STATIC_SYMBOL(symbol) \
    SYNC_PROP(symbol, member) \
}

#define SYNC_SUPERCLASS(parent) \
        return parent::SyncProperty(_val, _prop, _i, _op);

#define END_PROPSYNCS \
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

#define GET_COPY(objType) \
    const objType* c = dynamic_cast<const objType*>(o);

#define GET_COPY_AND_ASSERT(objType, line_num) \
    const objType* c = dynamic_cast<const objType*>(o); \
    MILO_ASSERT(c, line_num);

#define BEGIN_COPY_CHECKED \
    if(c){

#define COPY_MEMBER(mem) \
        mem = c->mem;

#define END_COPY_CHECKED \
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

#define ASSERT_REVS(rev1, rev2) \
    ASSERT_REV(rev1) \
    ASSERT_ALTREV(rev2)

// for loading in a version number that isn't a class's gRev/gAltRev
#define ASSERT_GLOBAL_REV(ver, rev_name) \
    if (ver > rev_name){ \
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), rev_name, ver); \
    }

#define LOAD_SUPERCLASS(parent) \
    parent::Load(bs);

#define END_LOADS \
}

// END LOAD MACROS -------------------------------------------------------------------------------------

// BEGIN ADDTONOTIFIES MACRO ---------------------------------------------------------------------------

#define ADD_NOTIFS \
namespace {\
    bool AddToNotifies(const char* str, std::list<class String>& list){\
        if(list.size() > 0x10) return false;\
        for(std::list<class String>::iterator it = list.begin(); it != list.end(); it++){\
            bool strFound = !strcmp(it->c_str(), str);\
            if(strFound) return false;\
        }\
        list.push_back(str);\
        return true;\
    }\
}

// END ADDTONOTIFIES MACRO -----------------------------------------------------------------------------

#endif