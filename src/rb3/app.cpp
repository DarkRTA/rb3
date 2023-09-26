#include "app.hpp"

#include <revolution/OS.h>

#include "unknown.hpp"
#include "types.h"

void App::Run()
{
	App::RunWithoutDebugging();
}

// NONMATCHING: several incorrect types, may not be functionally identical
#pragma sdata 0
void App::RunWithoutDebugging()
{
	void *sp10;
	void *sp8;
	f32 temp_f31;
	s32 temp_r15;
	s32 var_r16;

	temp_r15 = fn_806F61D4();
	fn_8030F9EC(&sp10);
	fn_8030FC2C(&sp10);
	var_r16 = 0;
	while (true) {
		if (((s32)lbl_8097CD88 != 0)
			&& ((var_r16 % ((lbl_8097CD88 * 4) - 3)) == 0)) {
			OSReport("checking consistency %d...\n", lbl_8097CD88);
		}
		var_r16 += 1;
		fn_8000F868(&sp8, "ffRunWithoutDebugging");
		fn_8030EE90(0);
		fn_8000F368();
		fn_802995D0(lbl_808FFF3C);
		fn_805095A0(lbl_809876E0);
		fn_8018DA9C(lbl_808FB8A0);
		fn_8025E6BC();
		fn_8025E6C8();
		fn_80267AA4(lbl_808FF430);
		fn_80261068(&lbl_808FEC10);
		fn_8022D8BC(lbl_808FDA84);
		lbl_80990E38->virt88();
		fn_800AB640(&lbl_808F3EC8);
		fn_802C3F08(&lbl_80900870);
		lbl_80901348->virt78();
		lbl_808FC398->virt18();
		fn_8033B944(&lbl_8091B8D8);
		fn_8000F80C(&sp8, -1);
		fn_8000EFF0(temp_r15);
		temp_f31 = fn_8000ED64(&sp10);
		fn_8030FC2C(&sp10);
		fn_8000F804(&lbl_80992AE8);
		fn_8000EFF4(temp_f31);
	}
}
