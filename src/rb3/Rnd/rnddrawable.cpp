#include "rnddrawable.hpp"
#include "rb3/data.hpp"

/*extern DataArray* SystemConfig(Symbol, Symbol, Symbol);
extern DataArray* gSystemConfig;
extern char* PathName(Hmx::Object const *);
extern DataArray* lbl_808F0548;

void RndDrawable::SetType(Symbol* sym) {
ghidra
Symbol SVar1;
  Symbol SVar2;
  int iVar3;
  RndDrawable *pRVar4;
  char *local_28;
  Symbol SStack_24;
  undefined4 local_20;
  Symbol aSStack_1c [4];

  if (lbl_808E3C80 == '\0') {
    local_20 = StaticClassName();
    SVar1.str = (char *)Symbol::Symbol(&SStack_24,lbl_808955B0);
    SVar2.str = (char *)Symbol::Symbol(aSStack_1c,lbl_808955B8);
    lbl_808F0548 = (DataArray *)SystemConfig(SVar2,(Symbol)&local_20,SVar1);
    lbl_808E3C80 = '\x01';
  }
  iVar3 = Symbol::IsNull(param_1);
  if (iVar3 == 0) {
    local_28 = param_1->str;
    iVar3 = DataArray::FindArray(lbl_808F0548,(Symbol)&local_28,false);
    if (iVar3 == 0) {
      pRVar4 = this;
      if (this != NULL) {
        pRVar4 = **(RndDrawable ***)this;
      }
      PathName((Object *)pRVar4);
      (**(code **)(*(int *)&this->field_0x4 + 8))(this);
      (**(code **)(***(int ***)this + 0x44))(**(int ***)this,0);
    }
    else {
      (**(code **)(***(int ***)this + 0x44))(**(int ***)this,iVar3);
    }
  }
  else {
    (**(code **)(***(int ***)this + 0x44))(**(int ***)this,0); // SetTypeDef
  }
  return;


	Symbol local_20 = StaticClassName();
	Symbol SVar1("types");
	Symbol SVar2("objects");
	lbl_808F0548 = SystemConfig(SVar2, local_20, SVar1);
	if (!sym->IsNull()) {
		DataArray* intermediate = lbl_808F0548->FindArray(*sym, false);
		if (intermediate) {
			PathName(this);
			ClassName();
			SetTypeDef(NULL);
		} else SetTypeDef(intermediate);
	} else SetTypeDef(NULL);
}*/
#pragma dont_inline on
Symbol RndDrawable::StaticClassName() {
	static Symbol lbl_808F054C("Draw");
	return lbl_808F054C;
}
Symbol RndDrawable::ClassName() const {
	return StaticClassName();
}
#pragma dont_inline reset
