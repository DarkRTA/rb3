#ifndef RUNTIME_PTMF_H
#define RUNTIME_PTMF_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __ptmf {
    long this_offset; // offset to acquire correct this* pointer
    long virtual_offset; // offset to acquire vtable
    long address; // function address if negative (0x80000000 or greater), vtable index if positive
} __ptmf;

long __ptmf_test(__ptmf *ptmf);
long __ptmf_cmpr(__ptmf *ptmf1, __ptmf *ptmf2);
void __ptmf_scall(register void* _this);
void __ptmf_scall4(register void* _dummy, register void* _this);

#ifdef __cplusplus
}
#endif

#endif
