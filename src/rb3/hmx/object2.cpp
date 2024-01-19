#include "object.hpp"
#include "types.h"
#include "rb3/symbol.hpp"

extern uint fn_802623AC(u32, u32);
extern uint fn_80262684(u32);
extern uint fn_8026267C(u32); // r3 >>= 16;
extern uint fn_80328AA0();
extern void fn_803278AC(uint, Hmx::Object *);
extern void fn_8033DD4C(TypeProps *, TypeProps *, Hmx::Object *);
extern void *fn_8000FFC8(Hmx::Object *);
extern void *MemAllocTemp(int, int);
extern void MemFree(void *);
extern bool fn_8000FCA4(Symbol *, Symbol *);
extern u16 lbl_808E44AA, lbl_808E44AC;

namespace Hmx {

    void Object::SaveType(BinStream &bin) {
        bin << fn_802623AC(0, 2);
        bin << Type();
    }

    void Object::SaveRest(BinStream &bin) {
        props.Save(bin, this);
        bin << (unsigned int)0;
    }

    void Object::LoadType(BinStream &bin) {
        uint idiot;
        bin >> idiot;
        lbl_808E44AA = fn_80262684(idiot);
        lbl_808E44AC = fn_8026267C(idiot);
        Symbol bastard;
        bin >> bastard;
        SetType(bastard);
        uint test = fn_802623AC(lbl_808E44AC, lbl_808E44AA);
        fn_803278AC(test, this);
    }

    void Object::LoadRest(BinStream &bin) {
        uint tmp = fn_80328AA0();
        lbl_808E44AA = fn_80262684(tmp);
        lbl_808E44AC = fn_8026267C(tmp);
        props.Load(bin, ((u32)lbl_808E44AA - 2 >> 0x1FU), this);
        if (lbl_808E44AA != 0) {
            uint tmp2;
            bin >> tmp2;
            if (tmp2 != 0) {
                void *pv = MemAllocTemp(tmp2 + 1, 1);
                bin.Read(pv, tmp2);
                MemFree(pv); // why is it going in the trash
            }
        }
    }

    void Object::Save(BinStream &bin) {
        SaveType(bin);
        SaveRest(bin);
    }

    void Object::Copy(Object *dst, int huh) {
        if (huh == 2)
            return;
        Symbol dstClName = dst->ClassName();
        Symbol srcClName = ClassName();
        if (fn_8000FCA4(&dstClName, &srcClName)) {
            DataArray *datray = dst->getDa();
            SetTypeDef(datray);
            fn_8033DD4C(&props, &dst->props, this);
            return;
        } else if (dst->getDa() != NULL || getDa() != NULL) {
            dst->ClassName();
            ClassName();
            dst->Name();
            Name();
            dst->Type();
        }
    }

    void Object::Load(BinStream &bin) {
        LoadType(bin);
        LoadRest(bin);
    }
}
