#ifndef RUNTIME_RUNTIME_H
#define RUNTIME_RUNTIME_H

#ifdef __cplusplus
extern "C" {
#endif

/* macros for GPR/FPR resting and saving */
#define SAVE_FPR(reg) _savefpr_ ## reg
#define RESTORE_FPR(reg) _restfpr_ ## reg
#define SAVE_FPR2(reg) _savef ## reg
#define RESTORE_FPR2(reg) _restf ## reg
#define SAVE_GPR(reg) _savegpr_ ## reg
#define SAVE32_GPR(reg) _save32gpr_ ## reg
#define RESTORE_GPR(reg) _restgpr_ ## reg
#define RESTORE32_GPR(reg) _rest32gpr_ ## reg

asm void __div2u(void);
asm void __div2i(void);
asm void __mod2u(void);
asm void __mod2i(void);
asm void __shl2i(void);
asm void __shr2u(void);
asm void __shr2i(void);
asm void __cvt_sll_dbl(void);
asm void __cvt_ull_dbl(void);
asm void __cvt_sll_flt(void);
asm void __cvt_ull_flt(void);
asm void __cvt_dbl_usll(void);
asm void __cvt_dbl_ull(void);

void SAVE_FPR(14)(void);
void SAVE_FPR(15)(void);
void SAVE_FPR(16)(void);
void SAVE_FPR(17)(void);
void SAVE_FPR(18)(void);
void SAVE_FPR(19)(void);
void SAVE_FPR(20)(void);
void SAVE_FPR(21)(void);
void SAVE_FPR(22)(void);
void SAVE_FPR(23)(void);
void SAVE_FPR(24)(void);
void SAVE_FPR(25)(void);
void SAVE_FPR(26)(void);
void SAVE_FPR(27)(void);
void SAVE_FPR(28)(void);
void SAVE_FPR(29)(void);
void SAVE_FPR(30)(void);
void SAVE_FPR(31)(void);
void SAVE_FPR2(14)(void);
void SAVE_FPR2(15)(void);
void SAVE_FPR2(16)(void);
void SAVE_FPR2(17)(void);
void SAVE_FPR2(18)(void);
void SAVE_FPR2(19)(void);
void SAVE_FPR2(20)(void);
void SAVE_FPR2(21)(void);
void SAVE_FPR2(22)(void);
void SAVE_FPR2(23)(void);
void SAVE_FPR2(24)(void);
void SAVE_FPR2(25)(void);
void SAVE_FPR2(26)(void);
void SAVE_FPR2(27)(void);
void SAVE_FPR2(28)(void);
void SAVE_FPR2(29)(void);
void SAVE_FPR2(30)(void);
void SAVE_FPR2(31)(void);
void RESTORE_FPR(14)(void);
void RESTORE_FPR(15)(void);
void RESTORE_FPR(16)(void);
void RESTORE_FPR(17)(void);
void RESTORE_FPR(18)(void);
void RESTORE_FPR(19)(void);
void RESTORE_FPR(20)(void);
void RESTORE_FPR(21)(void);
void RESTORE_FPR(22)(void);
void RESTORE_FPR(23)(void);
void RESTORE_FPR(24)(void);
void RESTORE_FPR(25)(void);
void RESTORE_FPR(26)(void);
void RESTORE_FPR(27)(void);
void RESTORE_FPR(28)(void);
void RESTORE_FPR(29)(void);
void RESTORE_FPR(30)(void);
void RESTORE_FPR(31)(void);
void RESTORE_FPR2(14)(void);
void RESTORE_FPR2(15)(void);
void RESTORE_FPR2(16)(void);
void RESTORE_FPR2(17)(void);
void RESTORE_FPR2(18)(void);
void RESTORE_FPR2(19)(void);
void RESTORE_FPR2(20)(void);
void RESTORE_FPR2(21)(void);
void RESTORE_FPR2(22)(void);
void RESTORE_FPR2(23)(void);
void RESTORE_FPR2(24)(void);
void RESTORE_FPR2(25)(void);
void RESTORE_FPR2(26)(void);
void RESTORE_FPR2(27)(void);
void RESTORE_FPR2(28)(void);
void RESTORE_FPR2(29)(void);
void RESTORE_FPR2(30)(void);
void RESTORE_FPR2(31)(void);
void SAVE_GPR(14)(void);
void SAVE_GPR(15)(void);
void SAVE_GPR(16)(void);
void SAVE_GPR(17)(void);
void SAVE_GPR(18)(void);
void SAVE_GPR(19)(void);
void SAVE_GPR(20)(void);
void SAVE_GPR(21)(void);
void SAVE_GPR(22)(void);
void SAVE_GPR(23)(void);
void SAVE_GPR(24)(void);
void SAVE_GPR(25)(void);
void SAVE_GPR(26)(void);
void SAVE_GPR(27)(void);
void SAVE_GPR(28)(void);
void SAVE_GPR(29)(void);
void SAVE_GPR(30)(void);
void SAVE_GPR(31)(void);
void SAVE32_GPR(14)(void);
void SAVE32_GPR(15)(void);
void SAVE32_GPR(16)(void);
void SAVE32_GPR(17)(void);
void SAVE32_GPR(18)(void);
void SAVE32_GPR(19)(void);
void SAVE32_GPR(20)(void);
void SAVE32_GPR(21)(void);
void SAVE32_GPR(22)(void);
void SAVE32_GPR(23)(void);
void SAVE32_GPR(24)(void);
void SAVE32_GPR(25)(void);
void SAVE32_GPR(26)(void);
void SAVE32_GPR(27)(void);
void SAVE32_GPR(28)(void);
void SAVE32_GPR(29)(void);
void SAVE32_GPR(30)(void);
void SAVE32_GPR(31)(void);
void RESTORE_GPR(14)(void);
void RESTORE_GPR(15)(void);
void RESTORE_GPR(16)(void);
void RESTORE_GPR(17)(void);
void RESTORE_GPR(18)(void);
void RESTORE_GPR(19)(void);
void RESTORE_GPR(20)(void);
void RESTORE_GPR(21)(void);
void RESTORE_GPR(22)(void);
void RESTORE_GPR(23)(void);
void RESTORE_GPR(24)(void);
void RESTORE_GPR(25)(void);
void RESTORE_GPR(26)(void);
void RESTORE_GPR(27)(void);
void RESTORE_GPR(28)(void);
void RESTORE_GPR(29)(void);
void RESTORE_GPR(30)(void);
void RESTORE_GPR(31)(void);
void RESTORE32_GPR(14)(void);
void RESTORE32_GPR(15)(void);
void RESTORE32_GPR(16)(void);
void RESTORE32_GPR(17)(void);
void RESTORE32_GPR(18)(void);
void RESTORE32_GPR(19)(void);
void RESTORE32_GPR(20)(void);
void RESTORE32_GPR(21)(void);
void RESTORE32_GPR(22)(void);
void RESTORE32_GPR(23)(void);
void RESTORE32_GPR(24)(void);
void RESTORE32_GPR(25)(void);
void RESTORE32_GPR(26)(void);
void RESTORE32_GPR(27)(void);
void RESTORE32_GPR(28)(void);
void RESTORE32_GPR(29)(void);
void RESTORE32_GPR(30)(void);
void RESTORE32_GPR(31)(void);

#ifdef __cplusplus
}
#endif

#endif
