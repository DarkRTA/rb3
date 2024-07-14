/* https://github.com/SwareJonge/mkdd/blob/main/libs/PowerPC_EABI_Support/src/Runtime/ptmf.c */

#include "ptmf.h"

const __ptmf __ptmf_null = { 0, 0, 0 };

/* clang-format off *//* asm funcs */

asm long __ptmf_test(register __ptmf* ptmf) {
    nofralloc

    // Load PTMF data
    lwz       r5, __ptmf.this_offset(ptmf)
    lwz       r6, __ptmf.virtual_offset(ptmf)
    lwz       r7, __ptmf.address(ptmf)

    // Return 1 if any are not 0
    li        r3, 0x1
    cmpwi     r5, 0
    cmpwi     cr6, r6, 0
    cmpwi     cr7, r7, 0
    bnelr-
    bnelr-    cr6
    bnelr-    cr7

    // Return 0 otherwise
    li        r3, 0
    blr
}

asm long __ptmf_cmpr(register __ptmf *left, register __ptmf *right) {
    nofralloc

    // Load PTMF data
    lwz r5, __ptmf.this_offset(left)
    lwz r6, __ptmf.this_offset(right)
    lwz r7, __ptmf.virtual_offset(left)
    lwz r8, __ptmf.virtual_offset(right)
    lwz r9, __ptmf.address(left)
    lwz r10, __ptmf.address(right)

    // Return 1 if any members are different
    li r3, 1
    cmpw r5, r6
    cmpw cr6, r7, r8
    cmpw cr7, r9, r10
    bnelr-
    bnelr- cr6
    bnelr- cr7

    // Return 0 if they are the same
    li r3, 0
    blr
}

asm void __ptmf_scall(register void* _this) {
    nofralloc

    // Load PTMF data
    lwz     r0, __ptmf.this_offset(r12)
    lwz     r11, __ptmf.virtual_offset(r12)
    lwz     r12, __ptmf.address(r12)

    // Apply this_offset
    add     _this, _this, r0

    // Do we need to load from the vtable?
    // (address unsigned less than 0x80000000/signed greater than 0)
    cmpwi   r11, 0
    blt-    cr0, @call
    // Yes, load vtable and index into it
    lwzx    r12, _this, r12
    lwzx    r12, r12, r11

@call: // Call function
    mtctr   r12
    bctr
}

asm void __ptmf_scall4(register void* _, register void* _this) {
    nofralloc

    lwz     r0, __ptmf.this_offset(r12)
    lwz     r11, __ptmf.virtual_offset(r12)
    lwz     r12, __ptmf.address(r12)

    // Apply this_offset
    add     _this, _this, r0

    // Do we need to load from the vtable?
    // (address unsigned less than 0x80000000/signed greater than 0)
    cmpwi   r11, 0
    blt-    cr0, @call
    // Yes, load vtable and index into it
    lwzx    r12, _this, r12
    lwzx    r12, r12, r11

@call: // Call function
    mtctr   r12
    bctr
}
