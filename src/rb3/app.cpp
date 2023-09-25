#include "app.hpp"

#include <revolution/OS.h>

#include "unknown.hpp"
#include "types.h"

void App::Run()
{
	App::RunWithoutDebugging();
}

// NONMATCHING: this is literally copied and pasted ghidra output
/*
void App::RunWithoutDebugging()
{
	s32 uVar1;
	s32 iVar2;
	s32 iVar3;
	s8 uVar4;
	s8 uVar5;
	s8 auStack_88[8];
	s8 auStack_80[128];

	uVar1 = fn_806F61D4();
	fn_8030F9EC(auStack_80);
	fn_8030FC2C(auStack_80);
	iVar3 = 0;
	do {
		if ((lbl_8097CD88._0_4_ != 0)
			&& (iVar2 = lbl_8097CD88._0_4_ * 4 + -3,
				iVar3 == (iVar3 / iVar 2) * iVar2)) {
			OSReport(
				s_checking_consistency_ % d... _80805944,
				lbl_8097 CD88._0_4_);
		}
		iVar3 = iVar3 + 1;
		fn_8000F868(auStack_88, s_ffRunWithoutDebugging_808056 22 + 2);
		fn_8030EE90(0);
		fn_8000F368();
		fn_802995D0(lbl_808FFF3C);
		fn_805095A0(lbl_809876E0._0_4_);
		fn_8018DA9C(lbl_808FB8A0._0_4_);
		fn_8025E6BC();
		fn_8025E6C8();
		fn_80267AA4(lbl_808FF430);
		fn_80261068(lbl_808FEC10);
		fn_8022D8BC(lbl_808FDA84);
		(**(code **)(*lbl_80990E38._0_4_ + 0x88))();
		fn_800AB640(lbl_808F3EC8);
		fn_802C3F08(lbl_80900870);
		(**(code **)(*(int *)lbl_80901348._0_4_ + 0x78))();
		(**(code **)(*(int *)(lbl_808FC398 + 4) + 0x18))();
		fn_8033B944(lbl_8091B8D8);
		fn_8000F80C(auStack_88, 0xffffffff);
		fn_8000EFF0(uVar1);
		uVar4 = fn_8000ED64(auStack_80);
		fn_8030FC2C(auStack_80);
		uVar5 = fn_8000F804(lbl_80992AE8);
		fn_8000EFF4(uVar5, uVar4);
	} while (true);
}
*/
